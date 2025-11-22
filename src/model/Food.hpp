#pragma once

#include <memory>
#include <string>

// 前向声明，避免循环依赖
class Pet;

// Food Perk 枚举 - 表示食物可以提供的各种效果类型
enum class FoodPerkType
{
    None,        // 无效果
    Apple,       // 苹果：+1攻击 +1生命
    Honey,       // 蜂蜜：战斗开始召唤蜜蜂
    MeatBone,    // 骨头：+3攻击
    Garlic,      // 大蒜：+2生命，+1护甲（减少伤害）
    Salad,       // 色拉：+1攻击 +2生命
    CannedFood,  // 罐头：+2攻击 +2生命
    Pizza,       //  pizza：+2攻击 +2生命（作用于2个宠物）
    Melon,       // 西瓜：战斗开始获得50%伤害减少（仅一次）
    Mushroom,    // 蘑菇：死亡时复活一次
    Steak,       // 牛排：+20攻击（临时，仅本回合）
    Coconut,     // 椰子：+3生命（护甲）
    Pear         // 梨子：+2攻击 +1生命
};

class Food
{
private:
    std::string _name;
    std::string _chineseName;
    std::string _introSkills;
    int _tier;               // 食物等级，影响购买成本和出现阶段
    int _cost;               // 购买成本
    FoodPerkType _perkType;  // 食物提供的加成类型

    // 数值加成（某些食物直接改变数值）
    int _hpBonus;
    int _attackBonus;

public:
    // 构造函数
    Food(const std::string& name, std::string chineseName, std::string introSkills, int tier, int cost, FoodPerkType perkType, int hpBonus = 0, int attackBonus = 0);

    ~Food() = default;

    // Getter方法
    std::string getName() const { return _name; }

    std::string getChineseName() const { return _chineseName;};

    std::string getIntroSkills() const {return _introSkills;};
    int getTier() const { return _tier; }
    int getCost() const { return _cost; }
    FoodPerkType getPerkType() const { return _perkType; }
    int getHPBonus() const { return _hpBonus; }
    int getAttackBonus() const { return _attackBonus; }

    // 应用食物效果到宠物
    // 返回是否成功应用（某些食物可能有应用条件限制）
    bool applyToPet(Pet* pet);

    // 创建特定类型食物的工厂方法
    static std::unique_ptr<Food> createApple();
    static std::unique_ptr<Food> createHoney();
    static std::unique_ptr<Food> createMeatBone();
    static std::unique_ptr<Food> createGarlic();
    static std::unique_ptr<Food> createSalad();
    static std::unique_ptr<Food> createCannedFood();
    static std::unique_ptr<Food> createMelon();
    static std::unique_ptr<Food> createMushroom();
    static std::unique_ptr<Food> createPear();
};