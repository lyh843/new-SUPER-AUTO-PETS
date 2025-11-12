#pragma once

#include <vector>

#include "Pet.hpp"

constexpr int Max_round = 10;
constexpr int Max_prize = 5;

class Player
{
private:
    int _coin;
    int _lives;
    int _round;
    int _prize;
    std::vector<std::unique_ptr<Pet>> _pets;  // 宠物阵容（最多5只）

public:
    // 默认构造函数
    Player(int coin = 10, int lives = 5, int round = 1, int prize = 0)
        : _coin(coin), _lives(lives), _round(round), _prize(prize) {};
    // 获取当前金币数
    int getCoin() { return _coin; };
    // 获取当前生命
    int getLives() { return _lives; };
    // 获取当前回合
    int getRound() { return _round; };
    // 获取当前奖杯
    int getPrize() { return _prize; };

    // 扣除金币（默认扣1）。传入：扣除的数量；返回：成功返回true,失败返回false
    bool decreaseCoin(int num = 1)
    {
        if (_coin < num)
            return false;
        _coin -= num;
        return true;
    };

    // 增加金币（默认加1），无返回值
    void addCoin(int num = 1)
    {
        _coin += num;
        return;
    };

    // 扣除生命（默认扣1）成功返回true,失败返回false
    bool decreaseLives(int num = 1)
    {
        if (_lives < num)
            return false;
        _lives -= num;
        return true;
    };

    // 增加生命（默认加1)最大值不超过5
    bool addLives(int num = 1)
    {
        if (_lives + num > 5)
        {
            _lives = 5;
        }
        else
        {
            _lives += num;
        }
        return true;
    };

    // 回合数加1，如果回合数（加完后）没超过max_round时返回true，否则false
    bool addRound(int num = 1)
    {
        _round += 1;
        if (_round <= Max_round)
            return true;
        else
            return false;
    };

    // 奖杯数加1，如果奖杯数（加完后）没超过max_prize时返回true，否则false
    bool addPrize(int num = 1)
    {
        _prize += 1;
        if (_prize <= Max_prize)
            return true;
        else
            return false;
    };

    // 宠物管理
    const std::vector<std::unique_ptr<Pet>>& getPets() const { return _pets; }
    std::vector<std::unique_ptr<Pet>>& getPets() { return _pets; }
    
    // 添加宠物到指定位置（index: 0-4）
    bool addPet(std::unique_ptr<Pet> pet, int index);
    
    // 移除指定位置的宠物
    std::unique_ptr<Pet> removePet(int index);
    
    // 获取指定位置的宠物
    Pet* getPetAt(int index) const;
    
    // 获取宠物数量
    int getPetCount() const;
};
