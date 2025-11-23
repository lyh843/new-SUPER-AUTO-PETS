#include "BattleEngine.hpp"
#include <QThread>
#include "model/Player.hpp"
#include <qdebug.h>

BattleEngine::BattleEngine()
    : _player1Team()
    , _player2Team()
    , _eventCallback(nullptr)
    , _inBattle(false)
    , _result(BattleResult::Draw)
    , _player1Turn(true)
{
}

void BattleEngine::initialize(std::vector<std::unique_ptr<Pet>>& p1,
                               std::vector<std::unique_ptr<Pet>>& p2, Player* player)
{
    _player1Team.clear();
    _player2Team.clear();

    _player1Team = std::move(p1);
    _player2Team = std::move(p2);

    _player = player;

    _inBattle = false;
    _player1Turn = true;

    qDebug() << "战斗初始化：玩家宠物" << _player1Team.size()
             << " AI宠物" << _player2Team.size();
}

void BattleEngine::setEventCallback(EventCallback callback)
{
    _eventCallback = callback;
}

void BattleEngine::_triggerEvent(const BattleEvent& event)
{
    if (_eventCallback)
        _eventCallback(event);
}

BattleResult BattleEngine::startBattle()
{
    _inBattle = true;

    _triggerEvent({BattleEventType::BattleStart, "战斗开始！", -1, -1, 0, true});

    QThread::msleep(500);

    _executePreBattleSkills();

    while (!_isBattleOver())
    {
        _executeTurn();
        QThread::msleep(800);
    }

    _finishBattle();
    _inBattle = false;

    return _result;
}

void BattleEngine::startBattleManual()
{
    _executePreBattleSkills();

    _inBattle = true;

    _triggerEvent({BattleEventType::BattleStart, "战斗开始！", -1, -1, 0, true});
}

bool BattleEngine::executeSingleStep()
{
    if (!_inBattle || _isBattleOver())
        return false;

    _executeTurn();

    if (_isBattleOver())
    {
        _finishBattle();
        _inBattle = false;
        return false;
    }

    return true;
}

/* ======================== 战斗前技能 ======================== */

void BattleEngine::_executePreBattleSkills()
{
    //优先检查实现Swan的技能
    for (auto &pet : _player1Team)
    {
        if (dynamic_cast<Swan*>(pet.get()))
        {
            _player->addCoin();
        }
    }

    //Kangaroo技能实现
    for (auto &pet : _player1Team)
        if (pet)
            pet->onStartBattle(this);

    for (auto &pet : _player2Team)
        if (pet)
            pet->onStartBattle(this);


}

/* ======================== 主回合流程 ======================== */

void BattleEngine::_executeTurn()
{
    if (_isBattleOver()) {return;}

    int attacker_1_Idx = _getFirstAlivePet( _player1Team);
    int attacker_2_Idx = _getFirstAlivePet(_player2Team);

    if (attacker_1_Idx == -1 || attacker_2_Idx == -1)
        return;

    auto &attacker_1_Team = _player1Team;
    auto &attacker_2_Team = _player2Team;

    Pet* attacker_1 = attacker_1_Team[attacker_1_Idx].get();
    Pet* attacker_2 = attacker_2_Team[attacker_2_Idx].get();

    _triggerEvent({
        BattleEventType::TurnStart,
        QString("%1 准备攻击 %2！")
            .arg(QString::fromStdString(attacker_1->getName()))
            .arg(QString::fromStdString(attacker_2->getName())),
        attacker_1_Idx, attacker_2_Idx, 0, _player1Turn
    });

    /* ===== 攻击前技能 ===== */
    attacker_1->triggerOnAttack(attacker_2, this);

    _triggerEvent({
        BattleEventType::Attack,
        QString("%1 与 %2 发起对撞！")
            .arg(QString::fromStdString(attacker_1->getName()))
            .arg(QString::fromStdString(attacker_2->getName())),
        attacker_1_Idx,           // 攻击方（当前回合）的队伍索引
        attacker_2_Idx,           // 防御方（当前回合）的队伍索引
        0,                     // 伤害值设为 0，因为 TakeDamage 报告伤害
        true          // 攻击方是否为 Player1
    });

    _applyDamage(attacker_1, attacker_1_Idx, attacker_2, attacker_2_Idx);

    _cleanupDeadPets();

    _player1Turn = !_player1Turn;
}

/* ======================== 伤害计算 ======================== */

int BattleEngine::_calculateDamage(Pet* attacker, Pet* defender)
{
    int baseDamage = attacker->getAttack();

    if (defender->hasMelonShield())
        baseDamage /= 2;

    if (defender->hasArmor())
        baseDamage = std::max(0, baseDamage - 1);

    return baseDamage;
}

/* ======================== 伤害应用 ======================== */

void BattleEngine::_applyDamage(
    Pet* attacker, int attackerIdx,
    Pet* defender, int defenderIdx
) {
    int damage1 = _calculateDamage(attacker, defender);
    int damage2 = _calculateDamage(defender, attacker);

    // _triggerEvent({
    //     BattleEventType::Attack,
    //     QString("%1 攻击了 %2，造成 %3 点伤害！")
    //         .arg(QString::fromStdString(attacker->getName()))
    //         .arg(QString::fromStdString(defender->getName()))
    //         .arg(damage),
    //     attackerIdx, defenderIdx, damage, isPlayer1Attacking
    // });

    /* ===== 受伤技能触发 ===== */
    defender->triggerOnHurt(attacker, damage1, this);
    attacker->triggerOnHurt(defender, damage2, this);

    if (!defender->isDead()) defender->receiveDamage(damage1);
    if (!attacker->isDead()) attacker->receiveDamage(damage2);


    // _triggerEvent({
    //     BattleEventType::TakeDamage,
    //     QString("%1 剩余生命：%2")
    //         .arg(QString::fromStdString(defender->getName()))
    //         .arg(defender->getHP()),
    //     attackerIdx, defenderIdx, damage, isPlayer1Attacking
    // });

    // 触发 Defender 受伤事件
    _triggerEvent({
        BattleEventType::TakeDamage,
        QString("%1 受到 %2 点伤害，剩余生命：%3")
            .arg(QString::fromStdString(defender->getName()))
            .arg(damage1)
            .arg(defender->getHP()),
        attackerIdx, defenderIdx, damage1, !_player1Turn // _player1Turn 是 Attacker 的阵营，取反是 Defender 阵营
    });

    // 触发 Attacker 受伤事件 (自伤)
    _triggerEvent({
        BattleEventType::TakeDamage,
        QString("%1 受到 %2 点伤害，剩余生命：%3")
            .arg(QString::fromStdString(attacker->getName()))
            .arg(damage2)
            .arg(attacker->getHP()),
        defenderIdx, attackerIdx, damage2, _player1Turn // _player1Turn 是 Att击者阵营
    });

    /* ===== 攻击者造成伤害技能 ===== */
    if (!attacker->isDead()) attacker->triggerOnDealDamage(defender, damage1, this);
    if (!defender->isDead()) defender->triggerOnDealDamage(attacker, damage2, this);

    if (defender->isDead())
        _handlePetDeath(defenderIdx, false);
    if (attacker->isDead())
        _handlePetDeath(attackerIdx, true);
}

/* ======================== 死亡处理 ======================== */

void BattleEngine::_handlePetDeath(int index, bool isPlayer1)
{
    auto &team = isPlayer1 ? _player1Team : _player2Team;

    if (index < 0 || index >= (int)team.size())
        return;

    Pet* deadPet = team[index].get();

    _triggerEvent({
        BattleEventType::PetDeath,
        QString("%1 被击败了！").arg(QString::fromStdString(deadPet->getName())),
        -1, index, 0, isPlayer1
    });

    /* ===== 队友死亡触发技能 ===== */
    for (auto& pet : team)
        if (pet && !pet->isDead())
            pet->triggerOnFriendFaint(deadPet, this, isPlayer1, index);

    /* ===== 死亡技能（召唤、新单位） ===== */
    deadPet->triggerOnFaint(this, isPlayer1, index);

    /* ===== 复活效果 ===== */
    if (deadPet->canRevive())
    {
        deadPet->setHP(1);
        deadPet->setCanRevive(false);

        _triggerEvent({
            BattleEventType::SkillTrigger,
            QString("%1 复活了！（蘑菇效果）")
                .arg(QString::fromStdString(deadPet->getName())),
            -1, index, 0, isPlayer1
        });
    }
}

/* ======================== 移除死亡宠物 ======================== */

void BattleEngine::_cleanupDeadPets()
{
    for (int i = _player1Team.size() - 1; i >= 0; --i)
        if (_player1Team[i]->isDead())
            _player1Team.erase(_player1Team.begin() + i);

    for (int i = _player2Team.size() - 1; i >= 0; --i)
        if (_player2Team[i]->isDead())
            _player2Team.erase(_player2Team.begin() + i);
}

/* ======================== 判断战斗结束 ======================== */

bool BattleEngine::_isBattleOver()
{
    bool p1Alive = false, p2Alive = false;

    for (auto &pet : _player1Team)
        if (pet && !pet->isDead()) p1Alive = true;

    for (auto &pet : _player2Team)
        if (pet && !pet->isDead()) p2Alive = true;

    return !p1Alive || !p2Alive;
}

/* ======================== 战斗结束 ======================== */

void BattleEngine::_finishBattle()
{
    //优先检查实现Flamingo技能
    FlamingoSkill();

    int p1Alive = 0, p2Alive = 0;

    for (auto &pet : _player1Team)
        if (pet && !pet->isDead()) p1Alive++;

    for (auto &pet : _player2Team)
        if (pet && !pet->isDead()) p2Alive++;

    QString msg;

    if (p1Alive == 0 && p2Alive == 0)
    {
        _result = BattleResult::Draw;
        msg = "平局！双方全军覆没！";
    }
    else if (p1Alive == 0)
    {
        _result = BattleResult::Player2Win;
        msg = "失败！对手获胜！";
    }
    else
    {
        _result = BattleResult::Player1Win;
        msg = "胜利！你赢得了这场战斗！";
    }

    _triggerEvent({BattleEventType::BattleEnd, msg, -1, -1, 0, true});
}

/* ======================== 工具函数 ======================== */

int BattleEngine::_getFirstAlivePet(const std::vector<std::unique_ptr<Pet>>& team) const
{
    for (int i = 0; i < (int)team.size(); ++i)
        if (team[i] && !team[i]->isDead())
            return i;

    return -1;
}

/* ========== 群体伤害接口（供刺猬、鳄鱼等技能使用） ========== */

void BattleEngine::dealDamageToAll(int damage)
{
    auto apply = [&](auto& team){
        for (auto& pet : team)
            if (pet && !pet->isDead())
                pet->receiveDamage(damage);
    };

    apply(_player1Team);
    apply(_player2Team);

    _cleanupDeadPets();
}

void BattleEngine::emitEvent(const BattleEvent& event) {
    _triggerEvent(event);
}

void BattleEngine::FlamingoSkill()
{
    int count = 0;
    for (auto &pet : _player1Team)
    {
        if (pet.get()->getName() == "Flamingo" && !pet.get()->isDead())
        {
            count++;
        }
    }
    for (int i = _player->getPets().size() - 1; i >= 0 && count > 0; i--)
    {
        if (_player->getPets()[i].get()->getName() == "Flamingo")
        {
            _player->getPets()[i].get()->setAttack(_player->getPets()[i].get()->getAttack()+2);
            count--;
        }
    }
}
