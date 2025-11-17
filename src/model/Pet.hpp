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
    Pet(const Pet& other);                                      // 拷贝构造函数
    ~Pet() = default;
    std::string getName() const { return _name; };
    int getHP() const { return _hp; };
    void setHP(int hp) { _hp = hp; };
    int getAttack() const { return _damage; };
    void setAttack(int attack) { _damage = attack; };
    bool isDead() const { return _hp <= 0; };
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

// 宠物派生类声明

// 猫 - Tier 1：基础宠物
class Cat : public Pet
{
public:
    Cat(int hp = 4, int attack = 3, int ownerPlayer = 0, int tier = 1);
    Cat(const Cat& other);                                  // 新增拷贝构造函数
    ~Cat() = default;
};

// 蚂蚁 - Tier 1：死亡时给随机友方宠物+2/+1
class Ant : public Pet
{
public:
    Ant(int hp = 2, int attack = 1, int ownerPlayer = 0, int tier = 1);
    Ant(const Ant& other);                                  // 新增拷贝构造函数
    ~Ant() = default;
};

// 鱼 - Tier 1：升级时给随机两个友方宠物+1/+1
class Fish : public Pet
{
public:
    Fish(int hp = 3, int attack = 2, int ownerPlayer = 0, int tier = 1);
    Fish(const Fish& other);                                // 新增拷贝构造函数
    ~Fish() = default;
};

// 蟋蟀 - Tier 1：死亡时召唤一只蜜蜂
class Cricket : public Pet
{
public:
    Cricket(int hp = 1, int attack = 2, int ownerPlayer = 0, int tier = 1);
    Cricket(const Cricket& other);                          // 新增拷贝构造函数
    ~Cricket() = default;
};

// 天鹅 - Tier 2：回合开始时获得1金币
class Swan : public Pet
{
public:
    Swan(int hp = 3, int attack = 1, int ownerPlayer = 0, int tier = 2);
    Swan(const Swan& other);                                // 新增拷贝构造函数
    ~Swan() = default;
};

// 火烈鸟 - Tier 2：战斗结束时如果存活获得+2攻击
class Flamingo : public Pet
{
public:
    Flamingo(int hp = 3, int attack = 2, int ownerPlayer = 0, int tier = 2);
    Flamingo(const Flamingo& other);                        // 新增拷贝构造函数
    ~Flamingo() = default;
};

// 刺猬 - Tier 2：受到伤害时对敌人造成等量伤害
class Hedgehog : public Pet
{
public:
    Hedgehog(int hp = 3, int attack = 1, int ownerPlayer = 0, int tier = 2);
    Hedgehog(const Hedgehog& other);                        // 新增拷贝构造函数
    ~Hedgehog() = default;
};

// 孔雀 - Tier 3：受到攻击前获得50%伤害减免
class Peacock : public Pet
{
public:
    Peacock(int hp = 2, int attack = 5, int ownerPlayer = 0, int tier = 3);
    Peacock(const Peacock& other);                          // 新增拷贝构造函数
    ~Peacock() = default;
};
