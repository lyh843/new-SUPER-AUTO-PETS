#pragma once

#include <vector>
#include "../model/Pet.hpp"

class BattleEngine
{
public:
    // 初始化战场，两边玩家的动物队伍
    void initialize(std::vector<Pet>& player1, std::vector<Pet>& player2);

    // 开始一场战斗
    void startBattle();

private:
    std::vector<Pet>* _player1Team;
    std::vector<Pet>* _player2Team;

    // 处理战斗前技能
    void _executePreBattleSkills(std::vector<Pet>& team);

    // 处理每个回合攻击
    void _executeTurn(std::vector<Pet>& attacker, std::vector<Pet>& defender);

    // 检查胜负
    bool _isBattleOver();

    // 战斗结束处理
    void _finishBattle();
};
