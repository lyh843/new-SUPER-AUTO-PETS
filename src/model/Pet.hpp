#pragma once

#include <memory>
#include <string>
#include <string_view>
#include <vector>
#include "Food.hpp"
#include "Skill.hpp"

class Pet
{
private:
    std::string _name;
    int _hp;
    int _damage;
    int _ownerPlayer;
    int _level;
    int _exp;
    int _tier;

    // 基础属性（用于计算升级后的值）
    int _baseHP;
    int _baseAttack;

    // Food Perk相关
    FoodPerkType _foodPerk;  // 当前拥有的食物加成类型
    bool _hasArmor;          // 是否有护甲（降低伤害）
    bool _canRevive;         // 是否有复活效果
    bool _hasMelonShield;    // 是否有西瓜护盾（50%减伤）

    void levelUp();

public:
    Pet(std::string name, int hp, int attack, int ownerPlayer, int tier = 1)
        : _name(name)
        , _hp(hp)
        , _damage(attack)
        , _ownerPlayer(ownerPlayer)
        , _level(1)
        , _exp(0)
        , _tier(tier)
        , _baseHP(hp)
        , _baseAttack(attack)
        , _foodPerk(FoodPerkType::None)
        , _hasArmor(false)
        , _canRevive(false)
        , _hasMelonShield(false) {};
    ~Pet() = default;
    std::string getName() { return _name; };
    int getHP() { return _hp; };
    void setHP(int hp) { _hp = hp; };
    int getAttack() { return _damage; };
    void setAttack(int attack) { _damage = attack; };
    bool isDead() { return _hp <= 0; };
    void attack(Pet& other) { other.receiveDamage(_damage); };
    bool receiveDamage(int damage)
    {
        _hp -= damage;
        return isDead();
    };

    // 新增的属性和方法
    int getLevel() const { return _level; };
    int getExp() const { return _exp; };
    int getTier() const { return _tier; };

    // 获得经验并自动升级
    void gainExperience(int amount);

    // Food Perk相关方法
    FoodPerkType getFoodPerk() const { return _foodPerk; }
    void setFoodPerk(FoodPerkType perk) { _foodPerk = perk; }
    bool hasArmor() const { return _hasArmor; }
    void setHasArmor(bool has) { _hasArmor = has; }
    bool canRevive() const { return _canRevive; }
    void setCanRevive(bool can) { _canRevive = can; }
    bool hasMelonShield() const { return _hasMelonShield; }
    void setHasMelonShield(bool has) { _hasMelonShield = has; }

    // 应用食物效果
    bool applyFood(std::unique_ptr<Food>& food);

    virtual void triggerPreBattleSkill() {};
    virtual void triggerPostBattleSkill() {};
};

using Creator = std::unique_ptr<Pet> (*)();

// 使用 getAllPets() 获得所有 Pet 派生类，即各种 Pets 。
// 注意：拿到返回值 vector 后不应该修改这个 vector ，但是可以任意使用 vector 的元素返回的 unique_ptr<Pet> 。
inline std::vector<Creator>& getAllPets()
{
    static std::vector<Creator> pets;
    return pets;
};
