#include "BattleEngine.hpp"
#include <QThread>

BattleEngine::BattleEngine()
    : _player1Team(nullptr)
    , _player2Team(nullptr)
    , _eventCallback(nullptr)
    , _inBattle(false)
    , _result(BattleResult::Draw)
    , _player1Turn(true)
{
}

void BattleEngine::initialize(std::vector<std::unique_ptr<Pet>>& p1, 
                               std::vector<std::unique_ptr<Pet>>& p2)
{
    _player1Team = &p1;
    _player2Team = &p2;
    _inBattle = false;
    _player1Turn = true;
}

void BattleEngine::setEventCallback(EventCallback callback)
{
    _eventCallback = callback;
}

void BattleEngine::_triggerEvent(const BattleEvent& event)
{
    if (_eventCallback)
    {
        _eventCallback(event);
    }
}

BattleResult BattleEngine::startBattle()
{
    _inBattle = true;
    
    // 战斗开始事件
    _triggerEvent({BattleEventType::BattleStart, "战斗开始！", -1, -1, 0, true});
    QThread::msleep(500);

    // 执行战斗前技能
    _executePreBattleSkills();

    // 主战斗循环
    while (!_isBattleOver())
    {
        _executeTurn();
        QThread::msleep(800);  // 每回合暂停，便于观看
    }

    _finishBattle();
    _inBattle = false;
    
    return _result;
}

void BattleEngine::startBattleManual()
{
    _inBattle = true;
    
    // 战斗开始事件
    _triggerEvent({BattleEventType::BattleStart, "战斗开始！", -1, -1, 0, true});
    
    // 执行战斗前技能
    _executePreBattleSkills();
}

bool BattleEngine::executeSingleStep()
{
    if (!_inBattle || _isBattleOver())
    {
        return false;
    }

    _executeTurn();
    
    if (_isBattleOver())
    {
        _finishBattle();
        _inBattle = false;
        return false;
    }
    
    return true;
}

void BattleEngine::_executePreBattleSkills()
{
    // 触发战斗前技能（如蜂蜜召唤蜜蜂）
    for (size_t i = 0; i < _player1Team->size(); ++i)
    {
        auto& pet = (*_player1Team)[i];
        if (pet)
        {
            pet->triggerPreBattleSkill();
            // 可以在这里添加具体的战斗前技能逻辑
        }
    }

    for (size_t i = 0; i < _player2Team->size(); ++i)
    {
        auto& pet = (*_player2Team)[i];
        if (pet)
        {
            pet->triggerPreBattleSkill();
        }
    }
}

void BattleEngine::_executeTurn()
{
    if (_isBattleOver())
        return;

    // 获取第一个存活的宠物
    int attackerIdx = _getFirstAlivePet(_player1Turn ? *_player1Team : *_player2Team);
    int defenderIdx = _getFirstAlivePet(_player1Turn ? *_player2Team : *_player1Team);

    if (attackerIdx == -1 || defenderIdx == -1)
        return;

    auto& attackerTeam = _player1Turn ? *_player1Team : *_player2Team;
    auto& defenderTeam = _player1Turn ? *_player2Team : *_player1Team;

    Pet* attacker = attackerTeam[attackerIdx].get();
    Pet* defender = defenderTeam[defenderIdx].get();

    // 回合开始事件
    _triggerEvent({
        BattleEventType::TurnStart,
        QString("%1 准备攻击 %2！")
            .arg(QString::fromStdString(attacker->getName()))
            .arg(QString::fromStdString(defender->getName())),
        attackerIdx, defenderIdx, 0, _player1Turn
    });

    // 应用伤害
    _applyDamage(attacker, attackerIdx, defender, defenderIdx, _player1Turn);

    // 清理死亡的宠物
    _cleanupDeadPets();

    // 切换回合
    _player1Turn = !_player1Turn;
}

int BattleEngine::_calculateDamage(Pet* attacker, Pet* defender)
{
    int baseDamage = attacker->getAttack();
    
    // 考虑西瓜护盾（50%减伤）
    if (defender->hasMelonShield())
    {
        baseDamage = baseDamage / 2;
    }
    
    // 考虑护甲（减少1点伤害）
    if (defender->hasArmor())
    {
        baseDamage = std::max(0, baseDamage - 1);
    }
    
    return baseDamage;
}

void BattleEngine::_applyDamage(Pet* attacker, int attackerIdx, Pet* defender, 
                                 int defenderIdx, bool isPlayer1Attacking)
{
    int damage = _calculateDamage(attacker, defender);
    
    // 攻击事件
    _triggerEvent({
        BattleEventType::Attack,
        QString("%1 攻击了 %2，造成 %3 点伤害！")
            .arg(QString::fromStdString(attacker->getName()))
            .arg(QString::fromStdString(defender->getName()))
            .arg(damage),
        attackerIdx, defenderIdx, damage, isPlayer1Attacking
    });

    // 应用伤害
    defender->receiveDamage(damage);

    // 受伤事件
    _triggerEvent({
        BattleEventType::TakeDamage,
        QString("%1 剩余生命：%2")
            .arg(QString::fromStdString(defender->getName()))
            .arg(defender->getHP()),
        attackerIdx, defenderIdx, damage, isPlayer1Attacking
    });

    // 检查是否死亡
    if (defender->isDead())
    {
        _handlePetDeath(defenderIdx, !isPlayer1Attacking);
    }
}

void BattleEngine::_handlePetDeath(int index, bool isPlayer1)
{
    auto& team = isPlayer1 ? *_player1Team : *_player2Team;
    
    if (index >= 0 && index < static_cast<int>(team.size()))
    {
        Pet* deadPet = team[index].get();
        
        _triggerEvent({
            BattleEventType::PetDeath,
            QString("%1 被击败了！")
                .arg(QString::fromStdString(deadPet->getName())),
            -1, index, 0, isPlayer1
        });

        // 触发死亡技能
        deadPet->triggerPostBattleSkill();
        
        // 处理复活效果
        if (deadPet->canRevive())
        {
            deadPet->setHP(1);  // 复活后1点生命
            deadPet->setCanRevive(false);  // 只能复活一次
            
            _triggerEvent({
                BattleEventType::SkillTrigger,
                QString("%1 复活了！（蘑菇效果）")
                    .arg(QString::fromStdString(deadPet->getName())),
                -1, index, 0, isPlayer1
            });
        }
    }
}

void BattleEngine::_cleanupDeadPets()
{
    // 移除死亡的宠物（从后往前遍历，避免索引问题）
    for (int i = _player1Team->size() - 1; i >= 0; --i)
    {
        if ((*_player1Team)[i]->isDead())
        {
            _player1Team->erase(_player1Team->begin() + i);
        }
    }

    for (int i = _player2Team->size() - 1; i >= 0; --i)
    {
        if ((*_player2Team)[i]->isDead())
        {
            _player2Team->erase(_player2Team->begin() + i);
        }
    }
}

bool BattleEngine::_isBattleOver()
{
    int player1Alive = 0;
    int player2Alive = 0;

    for (const auto& pet : *_player1Team)
    {
        if (pet && !pet->isDead())
            player1Alive++;
    }

    for (const auto& pet : *_player2Team)
    {
        if (pet && !pet->isDead())
            player2Alive++;
    }

    return player1Alive == 0 || player2Alive == 0;
}

void BattleEngine::_finishBattle()
{
    int player1Alive = 0;
    int player2Alive = 0;

    for (const auto& pet : *_player1Team)
    {
        if (pet && !pet->isDead())
            player1Alive++;
    }

    for (const auto& pet : *_player2Team)
    {
        if (pet && !pet->isDead())
            player2Alive++;
    }

    QString resultMessage;
    
    if (player1Alive == 0 && player2Alive == 0)
    {
        _result = BattleResult::Draw;
        resultMessage = "平局！双方全军覆没！";
    }
    else if (player1Alive == 0)
    {
        _result = BattleResult::Player2Win;
        resultMessage = "失败！对手获胜！";
    }
    else
    {
        _result = BattleResult::Player1Win;
        resultMessage = "胜利！你赢得了这场战斗！";
    }

    _triggerEvent({
        BattleEventType::BattleEnd,
        resultMessage,
        -1, -1, 0, true
    });
}

int BattleEngine::_getFirstAlivePet(const std::vector<std::unique_ptr<Pet>>& team) const
{
    for (size_t i = 0; i < team.size(); ++i)
    {
        if (team[i] && !team[i]->isDead())
        {
            return static_cast<int>(i);
        }
    }
    return -1;
}
