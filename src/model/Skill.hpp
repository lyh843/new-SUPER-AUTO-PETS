#pragma once

#include <vector>
#include "Pet.hpp"
#include "Player.hpp"

class Skill
{
private:
    // 存储所有场上的 _pets ，容器的元素究竟应该是什么类型需要进一步考虑，暂定为此
    std::vector<std::weak_ptr<Pet>> _pets;
    virtual void _effect(Pet& pet)  = 0;  // 技能效果
    virtual bool _concept(Pet& pet) = 0;  // 用于筛选满足作用条件的 _pets

public:
    Skill()  = default;
    ~Skill() = default;
    void apply() {};
};