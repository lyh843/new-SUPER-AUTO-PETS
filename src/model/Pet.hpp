#pragma once

#include <memory>
#include <string>
#include <string_view>
#include <vector>
#include "Food.hpp"
#include "Skill.hpp"
#include "Player.hpp"

class BattleEngine;
class Skill;

class Pet
{
protected:
    std::string _name;
    std::string _chineseName;
    std::string _introSkills;
    int _hp;
    int _damage;
    int _ownerPlayer;
    int _level;
    int _exp;
    int _tier;
    int _cost = 3;
    std::shared_ptr<Skill> _skill;

    // 基础属性（用于计算升级后的值）

    int _baseHP;
    int _baseAttack;

    // Food Perk相关
    FoodPerkType _foodPerk;  // 当前拥有的食物加成类型
    bool _hasArmor;          // 是否有护甲（降低伤害）
    bool _canRevive;         // 是否有复活效果
    bool _hasMelonShield;    // 是否有西瓜护盾（50%减伤）

public:
    Pet(std::string name, std::string chineseName, std::string introSkills, int hp, int attack, int ownerPlayer, int tier = 1)
        : _name(name)
        , _chineseName(chineseName)
        ,_introSkills(introSkills)
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
        , _hasMelonShield(false)
        , _skill(nullptr) {};
    Pet(const Pet& other);               //拷贝构造函数
    virtual ~Pet() = default;
    std::string getName() const { return _name; };
    std::string getChineseName() const { return _chineseName;};

    std::string getIntroSkills() const {return _introSkills;};
    int getHP() const { return _hp; };
    void setHP(int hp) { _hp = hp; };
    void addHP(int x) { _hp += x; };
    int getAttack() const { return _damage; };
    void setAttack(int attack) { _damage = attack; };
    int getCost() const { return _cost; };
    bool isDead() const { return _hp <= 0; };
    void attack(Pet& other) { other.receiveDamage(_damage); };
    virtual bool receiveDamage(int damage)
    {
        _hp -= damage;
        return isDead();
    };

    // 新增的属性和方法
    int getLevel() const { return _level; };
    int getExp() const { return _exp; };
    int getTier() const { return _tier; };

    virtual void levelUp(int hp, int atk);

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

    virtual void triggerPreBattleSkill(BattleEngine* engine);
    virtual void triggerOnAttack(Pet* target, BattleEngine* engine);
    virtual void triggerOnHurt(Pet* attacker, int damage, BattleEngine* engine);
    virtual void triggerOnDealDamage(Pet* target, int damage, BattleEngine* engine);
    virtual void triggerOnFaint(BattleEngine* engine, bool isPlayer1, int index);
    virtual void triggerOnFriendFaint(Pet* faintedFriend, BattleEngine* engine, bool isPlayer1, int indexOfFainted);
    virtual void triggerOnSell(std::vector<std::unique_ptr<Pet>>& ownerTeam);

    void setSkill(std::unique_ptr<Skill> s) { _skill = std::move(s); }
    Skill* getSkill() const { return _skill.get(); }
    void onStartBattle(BattleEngine* engine);

    virtual void triggerPreBattleSkill() {}; // 兼容旧调用（如果无 engine）
    virtual void triggerPostBattleSkill() {}; // 兼容占位

    // 简单工具：给宠物加攻击（便于技能使用）
    void addAttack(int v) { _damage += v; }
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

// 蟋蟀 - Tier 1：出售以后对任意的两个队友+1攻击力
class Cricket : public Pet
{
public:
    Cricket(int hp = 1, int attack = 2, int ownerPlayer = 0, int tier = 1);
    Cricket(const Cricket& other);                          // 新增拷贝构造函数
    ~Cricket() = default;
};

// 鸭 - Tier 1：出售给商店宠物+1生命值
class Duck : public Pet
{
public:
    Duck(int hp = 3, int attack = 2, int ownerPlayer = 0, int tier = 1);
    Duck(const Duck& other);                                // 新增拷贝构造函数
    ~Duck() = default;
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

// 袋鼠 - Tier 2：前方的友方+1攻击/+1生命
class Kangaroo : public Pet
{
public:
    Kangaroo(int hp = 3, int attack = 2, int ownerPlayer = 0, int tier = 2);
    Kangaroo(const Kangaroo& other);                        // 新增拷贝构造函数
    ~Kangaroo() = default;
};

// 孔雀 - Tier 3：受到攻击+1攻击力
class Peacock : public Pet
{
public:
    Peacock(int hp = 2, int attack = 5, int ownerPlayer = 0, int tier = 3);
    Peacock(const Peacock& other);                          // 新增拷贝构造函数
    ~Peacock() = default;
};

// 骆驼 - Tier 3：受到攻击给后面最近的朋友+2攻击/+2生命
class Camel : public Pet
{
public:
    Camel(int hp = 4, int attack = 2, int ownerPlayer = 0, int tier = 3);
    Camel(const Camel& other);                              // 新增拷贝构造函数
    ~Camel() = default;
    bool receiveDamage(int damage)override
    {
        _hp -= damage * 0.5;

        return isDead();
    };
};

// 渡渡鸟 - Tier 3：战斗开始前给予前方最近队友50%攻击力
class Dodo : public Pet
{
public:
    Dodo(int hp = 2, int attack = 4, int ownerPlayer = 0, int tier = 3);
    Dodo(const Dodo& other);                                // 新增拷贝构造函数
    ~Dodo() = default;
};

// 河豚 - Tier 4：受到伤害对一个随机敌人造成3伤害
class Blowfish : public Pet
{
public:
    Blowfish(int hp = 6, int attack = 3, int ownerPlayer = 0, int tier = 4);
    Blowfish(const Blowfish& other);                        // 新增拷贝构造函数
    ~Blowfish() = default;
};

// 臭鼬 - Tier 4：战斗开始前将最高血量的敌人减少1/3血量
class Skunk : public Pet
{
public:
    Skunk(int hp = 5, int attack = 3, int ownerPlayer = 0, int tier = 4);
    Skunk(const Skunk& other);                              // 新增拷贝构造函数
    ~Skunk() = default;
};

class IronCow : public Pet
{
public:
    IronCow(int hp = 0, int attack = 0, int ownerPlayer = 0, int tier = 1000);
    IronCow(const IronCow& other);                              // 新增拷贝构造函数
    ~IronCow() = default;
};

class Cultivated : public Pet
{
public:
    Cultivated(int hp = 1, int attack = 20, int ownerPlayer = 0, int tier = 999);
    Cultivated(const Cultivated& other);                              // 新增拷贝构造函数
    ~Cultivated() = default;
};
