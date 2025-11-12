#include "Food.hpp"
#include <memory>
#include "Pet.hpp"


Food::Food(const std::string& name, int tier, int cost, FoodPerkType perkType, int hpBonus, int attackBonus)
    : _name(name), _tier(tier), _cost(cost), _perkType(perkType), _hpBonus(hpBonus), _attackBonus(attackBonus)
{}

bool Food::applyToPet(Pet* pet)
{
    if (!pet)
        return false;

    // 根据食物类型应用不同的效果
    switch (_perkType)
    {
    case FoodPerkType::Apple:
        // 苹果：直接增加属性
        pet->setHP(pet->getHP() + 1);
        pet->setAttack(pet->getAttack() + 1);
        break;

    case FoodPerkType::MeatBone:
        // 骨头：+3攻击
        pet->setAttack(pet->getAttack() + 3);
        break;

    case FoodPerkType::Garlic:
        // 大蒜：+2生命，添加护甲效果（这里先简单增加生命，后续可以扩展护甲机制）
        pet->setHP(pet->getHP() + 2);
        // TODO: 添加护甲标记
        break;

    case FoodPerkType::Salad:
        // 色拉：+1攻击 +2生命
        pet->setHP(pet->getHP() + 2);
        pet->setAttack(pet->getAttack() + 1);
        break;

    case FoodPerkType::CannedFood:
        // 罐头：+2攻击 +2生命
        pet->setHP(pet->getHP() + 2);
        pet->setAttack(pet->getAttack() + 2);
        break;

    case FoodPerkType::Melon:
        // 西瓜：战斗开始时获得50%伤害减免（这里先标记，后续在战斗系统中实现）
        // TODO: 添加伤害减免标记
        break;

    case FoodPerkType::Mushroom:
        // 蘑菇：死亡时复活一次（这里先标记，后续在战斗系统中实现）
        // TODO: 添加复活标记
        break;

    case FoodPerkType::Steak:
        // 牛排：临时+20攻击（仅本回合）
        pet->setAttack(pet->getAttack() + 20);
        // TODO: 标记为临时属性，回合结束需要恢复
        break;

    case FoodPerkType::Coconut:
        // 椰子：+3生命
        pet->setHP(pet->getHP() + 3);
        break;

    case FoodPerkType::Pear:
        // 梨子：+2攻击 +1生命
        pet->setHP(pet->getHP() + 1);
        pet->setAttack(pet->getAttack() + 2);
        break;

    case FoodPerkType::Honey:
        // 蜂蜜：战斗开始召唤蜜蜂（在战斗系统实现）
        // TODO: 在战斗系统实现召唤效果
        break;

    default:
        return false;
    }

    return true;
}

// 工厂方法：创建各种食物
std::unique_ptr<Food> Food::createApple()
{
    return std::make_unique<Food>("Apple", 1, 3, FoodPerkType::Apple, 1, 1);
}

std::unique_ptr<Food> Food::createHoney()
{
    return std::make_unique<Food>("Honey", 1, 3, FoodPerkType::Honey);
}

std::unique_ptr<Food> Food::createMeatBone()
{
    return std::make_unique<Food>("Meat Bone", 1, 3, FoodPerkType::MeatBone, 0, 3);
}

std::unique_ptr<Food> Food::createGarlic()
{
    return std::make_unique<Food>("Garlic", 2, 6, FoodPerkType::Garlic, 2, 0);
}

std::unique_ptr<Food> Food::createSalad()
{
    return std::make_unique<Food>("Salad", 2, 6, FoodPerkType::Salad, 2, 1);
}

std::unique_ptr<Food> Food::createCannedFood()
{
    return std::make_unique<Food>("罐头", 2, 6, FoodPerkType::CannedFood, 2, 2);
}

std::unique_ptr<Food> Food::createMelon()
{
    return std::make_unique<Food>("西瓜", 3, 9, FoodPerkType::Melon);
}

std::unique_ptr<Food> Food::createMushroom()
{
    return std::make_unique<Food>("蘑菇", 3, 9, FoodPerkType::Mushroom);
}

std::unique_ptr<Food> Food::createPear()
{
    return std::make_unique<Food>("梨子", 1, 3, FoodPerkType::Pear, 1, 2);
}