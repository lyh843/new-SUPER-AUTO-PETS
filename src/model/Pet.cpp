#include "Pet.hpp"
#include <algorithm>
#include "Food.hpp"

// 实现升级逻辑
void Pet::levelUp()
{
    if (_level >= 3)
        return;  // 已达最高等级

    _level++;

    // 升级时提升属性：每级增长50%的基础属性
    int hpBonus     = _baseHP / 2;
    int attackBonus = _baseAttack / 2;

    _hp += hpBonus;
    _damage += attackBonus;
}

// 实现获得经验的逻辑
void Pet::gainExperience(int amount)
{
    _exp += amount;

    // 每2点经验升一级，最高3级
    // exp 0-1: level 1
    // exp 2-3: level 2
    // exp 4+:  level 3
    int targetLevel = std::min(3, 1 + _exp / 2);

    // 如果目标等级大于当前等级，则升级
    while (_level < targetLevel)
    {
        levelUp();
    }
}

// 实现应用食物的方法
bool Pet::applyFood(std::unique_ptr<Food>& food)
{
    if (!food)
        return false;

    // 应用食物效果（新的食物会覆盖旧的Food Perk）
    bool applied = food->applyToPet(this);

    if (applied)
    {
        // 更新Food Perk类型
        _foodPerk = food->getPerkType();

        // 根据食物类型设置特殊标记
        switch (food->getPerkType())
        {
        case FoodPerkType::Garlic:
            _hasArmor = true;
            break;
        case FoodPerkType::Mushroom:
            _canRevive = true;
            break;
        case FoodPerkType::Melon:
            _hasMelonShield = true;
            break;
        default:
            break;
        }
    }

    return applied;
}

template <class Derived>
struct Registrar
{
    Registrar()
    {
        static_assert(std::is_base_of<Pet, Derived>::value, "Derived must inherit from Pet");
        Creator creator = []() -> std::unique_ptr<Pet> { return std::make_unique<Derived>(); };
        getAllPets().push_back(creator);
    };
};

// 以下写派生类

// 猫 - Tier 1：基础宠物
class Cat : public Pet
{
private:
    static Registrar<Cat> _registrar;

public:
    Cat(int hp = 4, int attack = 3, int ownerPlayer = 0, int tier = 1) 
        : Pet("猫", hp, attack, ownerPlayer, tier) {};
    ~Cat() = default;
    void triggerPreBattleSkill() override {};
    void triggerPostBattleSkill() override {};
};

// 蚂蚁 - Tier 1：死亡时给随机友方宠物+2/+1
class Ant : public Pet
{
private:
    static Registrar<Ant> _registrar;

public:
    Ant(int hp = 2, int attack = 1, int ownerPlayer = 0, int tier = 1)
        : Pet("蚂蚁", hp, attack, ownerPlayer, tier) {};
    ~Ant() = default;
    void triggerPreBattleSkill() override {};
    void triggerPostBattleSkill() override {};
};

// 鱼 - Tier 1：升级时给随机两个友方宠物+1/+1
class Fish : public Pet
{
private:
    static Registrar<Fish> _registrar;

public:
    Fish(int hp = 3, int attack = 2, int ownerPlayer = 0, int tier = 1)
        : Pet("鱼", hp, attack, ownerPlayer, tier) {};
    ~Fish() = default;
    void triggerPreBattleSkill() override {};
    void triggerPostBattleSkill() override {};
};

// 蟋蟀 - Tier 1：死亡时召唤一只蜜蜂
class Cricket : public Pet
{
private:
    static Registrar<Cricket> _registrar;

public:
    Cricket(int hp = 1, int attack = 2, int ownerPlayer = 0, int tier = 1)
        : Pet("蟋蟀", hp, attack, ownerPlayer, tier) {};
    ~Cricket() = default;
    void triggerPreBattleSkill() override {};
    void triggerPostBattleSkill() override {};
};

// 天鹅 - Tier 2：回合开始时获得1金币
class Swan : public Pet
{
private:
    static Registrar<Swan> _registrar;

public:
    Swan(int hp = 3, int attack = 1, int ownerPlayer = 0, int tier = 2)
        : Pet("天鹅", hp, attack, ownerPlayer, tier) {};
    ~Swan() = default;
    void triggerPreBattleSkill() override {};
    void triggerPostBattleSkill() override {};
};

// 火烈鸟 - Tier 2：战斗结束时如果存活获得+2攻击
class Flamingo : public Pet
{
private:
    static Registrar<Flamingo> _registrar;

public:
    Flamingo(int hp = 3, int attack = 2, int ownerPlayer = 0, int tier = 2)
        : Pet("火烈鸟", hp, attack, ownerPlayer, tier) {};
    ~Flamingo() = default;
    void triggerPreBattleSkill() override {};
    void triggerPostBattleSkill() override {};
};

// 刺猬 - Tier 2：受到伤害时对敌人造成等量伤害
class Hedgehog : public Pet
{
private:
    static Registrar<Hedgehog> _registrar;

public:
    Hedgehog(int hp = 3, int attack = 1, int ownerPlayer = 0, int tier = 2)
        : Pet("刺猬", hp, attack, ownerPlayer, tier) {};
    ~Hedgehog() = default;
    void triggerPreBattleSkill() override {};
    void triggerPostBattleSkill() override {};
};

// 孔雀 - Tier 3：受到攻击前获得50%伤害减免
class Peacock : public Pet
{
private:
    static Registrar<Peacock> _registrar;

public:
    Peacock(int hp = 2, int attack = 5, int ownerPlayer = 0, int tier = 3)
        : Pet("孔雀", hp, attack, ownerPlayer, tier) {};
    ~Peacock() = default;
    void triggerPreBattleSkill() override {};
    void triggerPostBattleSkill() override {};
};

// 所有 Pet 派生类全部在这里手动注册一次
Registrar<Cat> Cat::_registrar;
Registrar<Ant> Ant::_registrar;
Registrar<Fish> Fish::_registrar;
Registrar<Cricket> Cricket::_registrar;
Registrar<Swan> Swan::_registrar;
Registrar<Flamingo> Flamingo::_registrar;
Registrar<Hedgehog> Hedgehog::_registrar;
Registrar<Peacock> Peacock::_registrar;