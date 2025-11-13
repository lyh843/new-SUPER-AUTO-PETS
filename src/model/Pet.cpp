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

// 派生类构造函数实现

Cat::Cat(int hp, int attack, int ownerPlayer, int tier)
    : Pet("猫", hp, attack, ownerPlayer, tier) {}

Ant::Ant(int hp, int attack, int ownerPlayer, int tier)
    : Pet("蚂蚁", hp, attack, ownerPlayer, tier) {}

Fish::Fish(int hp, int attack, int ownerPlayer, int tier)
    : Pet("鱼", hp, attack, ownerPlayer, tier) {}

Cricket::Cricket(int hp, int attack, int ownerPlayer, int tier)
    : Pet("蟋蟀", hp, attack, ownerPlayer, tier) {}

Swan::Swan(int hp, int attack, int ownerPlayer, int tier)
    : Pet("天鹅", hp, attack, ownerPlayer, tier) {}

Flamingo::Flamingo(int hp, int attack, int ownerPlayer, int tier)
    : Pet("火烈鸟", hp, attack, ownerPlayer, tier) {}

Hedgehog::Hedgehog(int hp, int attack, int ownerPlayer, int tier)
    : Pet("刺猬", hp, attack, ownerPlayer, tier) {}

Peacock::Peacock(int hp, int attack, int ownerPlayer, int tier)
    : Pet("孔雀", hp, attack, ownerPlayer, tier) {}

// 所有 Pet 派生类全部在这里手动注册一次
static Registrar<Cat> catRegistrar;
static Registrar<Ant> antRegistrar;
static Registrar<Fish> fishRegistrar;
static Registrar<Cricket> cricketRegistrar;
static Registrar<Swan> swanRegistrar;
static Registrar<Flamingo> flamingoRegistrar;
static Registrar<Hedgehog> hedgehogRegistrar;
static Registrar<Peacock> peacockRegistrar;