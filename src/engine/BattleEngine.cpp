#include "BattleEngine.hpp"
#include <iostream>

void BattleEngine::initialize(std::vector<Pet>& p1, std::vector<Pet>& p2)
{
    _player1Team = &p1;
    _player2Team = &p2;
}

void BattleEngine::startBattle()
{
    _executePreBattleSkills(*_player1Team);
    _executePreBattleSkills(*_player2Team);

    while (!_isBattleOver())
    {
        _executeTurn(*_player1Team, *_player2Team);
        if (_isBattleOver())
            break;
        _executeTurn(*_player2Team, *_player1Team);
    }

    _finishBattle();
}

void BattleEngine::_executePreBattleSkills(std::vector<Pet>& team)
{
    for (auto& pet : team)
    {
        pet.triggerPreBattleSkill();
    }
}

void BattleEngine::_executeTurn(std::vector<Pet>& attacker, std::vector<Pet>& defender)
{
    if (attacker.empty() || defender.empty())
        return;

    attacker[0].attack(defender[0]);

    // 检查是否有动物死亡
    if (defender[0].isDead())
    {
        defender.erase(defender.begin());
    }
}

bool BattleEngine::_isBattleOver()
{
    return _player1Team->empty() || _player2Team->empty();
}

void BattleEngine::_finishBattle()
{
    if (_player1Team->empty() && _player2Team->empty())
        std::cout << "Draw!" << std::endl;
    else if (_player1Team->empty())
        std::cout << "Player 2 Wins!" << std::endl;
    else
        std::cout << "Player 1 Wins!" << std::endl;
}
