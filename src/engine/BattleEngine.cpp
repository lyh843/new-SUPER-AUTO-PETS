#include "BattleEngine.hpp"
#include <QThread>
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
                               std::vector<std::unique_ptr<Pet>>& p2, std::unique_ptr<Player> player)
{
    _player1Team.clear();
    _player2Team.clear();

    _player1Team = std::move(p1);
    _player2Team = std::move(p2);
    _player = std::move(player);

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
    _inBattle = true;

    _triggerEvent({BattleEventType::BattleStart, "战斗开始！", -1, -1, 0, true});

    _executePreBattleSkills();
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

    for (auto &pet : _player1Team)
        if (pet)
            pet->onStartBattle();

    for (auto &pet : _player2Team)
        if (pet)
            pet->onStartBattle();
}

/* ======================== 主回合流程 ======================== */

void BattleEngine::_executeTurn()
{
    if (_isBattleOver())
        return;

    int attackerIdx = _getFirstAlivePet(_player1Turn ? _player1Team : _player2Team);
    int defenderIdx = _getFirstAlivePet(_player1Turn ? _player2Team : _player1Team);

    if (attackerIdx == -1 || defenderIdx == -1)
        return;

    auto &attackerTeam = _player1Turn ? _player1Team : _player2Team;
    auto &defenderTeam = _player1Turn ? _player2Team : _player1Team;

    Pet* attacker = attackerTeam[attackerIdx].get();
    Pet* defender = defenderTeam[defenderIdx].get();

    _triggerEvent({
        BattleEventType::TurnStart,
        QString("%1 准备攻击 %2！")
            .arg(QString::fromStdString(attacker->getName()))
            .arg(QString::fromStdString(defender->getName())),
        attackerIdx, defenderIdx, 0, _player1Turn
    });

    /* ===== 攻击前技能 ===== */
    attacker->triggerOnAttack(defender, this);

    _applyDamage(attacker, attackerIdx, defender, defenderIdx, _player1Turn);

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
    Pet* defender, int defenderIdx,
    bool isPlayer1Attacking
) {
    int damage = _calculateDamage(attacker, defender);

    _triggerEvent({
        BattleEventType::Attack,
        QString("%1 攻击了 %2，造成 %3 点伤害！")
            .arg(QString::fromStdString(attacker->getName()))
            .arg(QString::fromStdString(defender->getName()))
            .arg(damage),
        attackerIdx, defenderIdx, damage, isPlayer1Attacking
    });

    defender->receiveDamage(damage);

    /* ===== 受伤技能触发 ===== */
    defender->triggerOnHurt(attacker, damage, this);

    _triggerEvent({
        BattleEventType::TakeDamage,
        QString("%1 剩余生命：%2")
            .arg(QString::fromStdString(defender->getName()))
            .arg(defender->getHP()),
        attackerIdx, defenderIdx, damage, isPlayer1Attacking
    });

    /* ===== 攻击者造成伤害技能 ===== */
    attacker->triggerOnDealDamage(defender, damage, this);

    if (defender->isDead())
        _handlePetDeath(defenderIdx, !isPlayer1Attacking);
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