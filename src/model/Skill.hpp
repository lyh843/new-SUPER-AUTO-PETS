#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Pet.hpp"
#include "../engine/BattleEngine.hpp"
#include <random>
#include <algorithm>
#include <Qstring>

class Pet;
class BattleEngine;

// 技能基类：覆盖你需要的所有事件点
class Skill {
public:
    virtual ~Skill() = default;

    // 战斗开始前（BattleEngine::_executePreBattleSkills）
    virtual void onPreBattle(Pet* self, BattleEngine* engine) {}

    // 攻击前触发
    virtual void onAttack(Pet* self, Pet* target, BattleEngine* engine) {}

    // 受伤触发
    virtual void onHurt(Pet* self, Pet* attacker, int damage, BattleEngine* engine) {}

    // 攻击造成伤害触发
    virtual void onDealDamage(Pet* self, Pet* target, int damage, BattleEngine* engine) {}

    // 死亡触发
    virtual void onFaint(Pet* self, BattleEngine* engine, bool isPlayer1, int index) {}

    // 队友死亡触发
    virtual void onFriendFaint(Pet* self, Pet* faintedFriend, BattleEngine* engine, bool isPlayer1, int indexOfFainted) {}

    // 出售触发（非战斗）——蟋蟀等商店/出售触发技能
    virtual void onSell(Pet* self, std::vector<std::unique_ptr<Pet>>& ownerTeam) {}

    // 战斗开始触发
    virtual void onStart(Pet* ownerPet) {
        // 默认啥也不做，具体技能子类会 override
    }
};

static int randIndex(int n) {
    if (n <= 0) return -1;
    return std::rand() % n;
}

class SkillAnt : public Skill {
public:
    void onFaint(Pet* self, BattleEngine* engine, bool isPlayer1, int index) override;
};

class SkillFish : public Skill {
public:
    void onPreBattle(Pet* self, BattleEngine* engine) override;
};

class SkillCricket : public Skill {
public:
    void onSell(Pet* self, std::vector<std::unique_ptr<Pet>>& ownerTeam) override;
};

class SkillHedgehog : public Skill {
public:
    void onHurt(Pet* self, Pet* attacker, int damage, BattleEngine* engine) override;
};

class SkillPeacock : public Skill {
public:
    void onHurt(Pet* self, Pet* attacker, int damage, BattleEngine* engine) override;
};

class SkillCamel : public Skill {
public:
    void onHurt(Pet* self, Pet* attacker, int damage, BattleEngine* engine) override;
};

class SkillDodo : public Skill {
public:
    void onPreBattle(Pet* self, BattleEngine* engine) override;
};

class SkillBlowfish : public Skill {
public:
    void onHurt(Pet* self, Pet* attacker, int damage, BattleEngine* engine) override;
};

class SkillSkunk : public Skill {
public:
    void onPreBattle(Pet* self, BattleEngine* engine) override;
};

class SkillFlamingo : public Skill {
public:
    void onFaint(Pet* self, BattleEngine* engine, bool isPlayer1, int index) override;
    void onDealDamage(Pet* self, Pet* target, int damage, BattleEngine* engine) override;
};

class SkillKangaroo : public Skill {
public:
    void onPreBattle(Pet* self, BattleEngine* engine) override;
};

/* ---------------- Swan ----------------
   回合开始时获得 1 金币（这是一个回合外事件，示例未实现）
*/
class SkillSwan : public Skill {
public:
    //需要在 Player 回合开始时调用
};

class SkillDuck : public Skill {
public:
    void onPreBattle(Pet* self, BattleEngine* engine) override {
        // Duck 无战斗技能（出售时给商店宠物+1HP 归商店逻辑）
    }
};