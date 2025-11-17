#pragma once

#include <vector>
#include <memory>
#include <functional>
#include <QString>
#include "../model/Pet.hpp"

// 战斗事件类型
enum class BattleEventType
{
    BattleStart,        // 战斗开始
    TurnStart,          // 回合开始
    Attack,             // 攻击事件
    TakeDamage,         // 受到伤害
    PetDeath,           // 宠物死亡
    SkillTrigger,       // 技能触发
    BattleEnd           // 战斗结束
};

// 战斗事件结构
struct BattleEvent
{
    BattleEventType type;
    QString message;
    int attackerIndex;  // 攻击者索引（-1表示无）
    int defenderIndex;  // 防御者索引（-1表示无）
    int damage;         // 伤害值
    bool isPlayer1;     // 是否是玩家1的事件
};

// 战斗结果
enum class BattleResult
{
    Player1Win,
    Player2Win,
    Draw
};

class BattleEngine
{
public:
    using EventCallback = std::function<void(const BattleEvent&)>;

    BattleEngine();
    ~BattleEngine() = default;

    // 初始化战场，传入两边玩家的动物队伍的unique_ptr
    void initialize(std::vector<std::unique_ptr<Pet>>& player1, 
                   std::vector<std::unique_ptr<Pet>>& player2);

    // 设置事件回调（用于战斗界面更新）
    void setEventCallback(EventCallback callback);

    // 开始一场战斗（自动完成）
    BattleResult startBattle();

    // 手动启动战斗（不自动执行，用于单步/自动模式）
    void startBattleManual();

    // 执行单步战斗（用于逐步演示）
    bool executeSingleStep();

    // 获取当前战斗状态
    bool isInBattle() const { return _inBattle; }
    BattleResult getResult() const { return _result; }

    // 获取队伍信息（用于界面显示）
    const std::vector<std::unique_ptr<Pet>>& getPlayer1Team() const { return _player1Team; }
    const std::vector<std::unique_ptr<Pet>>& getPlayer2Team() const { return _player2Team; }

private:
    std::vector<std::unique_ptr<Pet>> _player1Team;
    std::vector<std::unique_ptr<Pet>> _player2Team;
    EventCallback _eventCallback;
    bool _inBattle;
    BattleResult _result;
    bool _player1Turn;  // 是否是玩家1的回合

    // 触发事件
    void _triggerEvent(const BattleEvent& event);

    // 处理战斗前技能
    void _executePreBattleSkills();

    // 处理每个回合攻击
    void _executeTurn();

    // 计算实际伤害（考虑护甲、护盾等）
    int _calculateDamage(Pet* attacker, Pet* defender);

    // 应用伤害到目标
    void _applyDamage(Pet* attacker, int attackerIdx, Pet* defender, int defenderIdx, bool isPlayer1Attacking);

    // 处理宠物死亡
    void _handlePetDeath(int index, bool isPlayer1);

    // 清理死亡的宠物
    void _cleanupDeadPets();

    // 检查胜负
    bool _isBattleOver();

    // 战斗结束处理
    void _finishBattle();

    // 获取队伍中第一个存活的宠物索引
    int _getFirstAlivePet(const std::vector<std::unique_ptr<Pet>>& team) const;
};
