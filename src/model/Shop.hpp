#pragma once

#include "Food.hpp"
#include "Pet.hpp"
#include "Player.hpp"

#include <memory>
#include <vector>
#include <random>

constexpr int PET_SHOP_SIZE = 3;   // 商店宠物格子数
constexpr int FOOD_SHOP_SIZE = 2;  // 商店食物格子数
constexpr int REFRESH_COST = 1;    // 刷新商店的费用
constexpr int PET_COST = 3;        // 购买宠物的费用
constexpr int SELL_REWARD = 1;     // 出售宠物的奖励

class Shop
{
private:
    std::vector<std::unique_ptr<Pet>> _petShopList;   // 商店中的宠物
    std::vector<std::unique_ptr<Food>> _foodShopList; // 商店中的食物
    Player* _player;                                  // 玩家引用
    std::vector<bool> _petFrozen;                     // 宠物是否被冻结
    std::vector<bool> _foodFrozen;                    // 食物是否被冻结
    std::mt19937 _rng;                                // 随机数生成器

    // 生成随机宠物
    std::unique_ptr<Pet> generateRandomPet();
    
    // 生成随机食物
    std::unique_ptr<Food> generateRandomFood();

public:
    // 构造函数：传入玩家引用
    Shop(Player* player);

    // 刷新商店（扣除1金币）
    bool refresh();

    // 购买食物：foodIndex是食物在商店中的位置，targetPetIndex是目标宠物在玩家阵容中的位置
    bool buyFood(int foodIndex, int targetPetIndex);

    // 购买宠物：petIndex是宠物在商店中的位置，targetPetIndex是放置位置
    bool buyPet(int petIndex, int targetPetIndex);

    // 出售宠物：targetPetIndex是要卖的宠物在玩家阵容中的位置
    bool sell(int targetPetIndex);

    // 冻结/解冻宠物
    void togglePetFreeze(int index);
    
    // 冻结/解冻食物
    void toggleFoodFreeze(int index);

    // 获取商店宠物
    Pet* getPet(int index) const;

    // 获取商店食物
    Food* getFood(int index) const;

    // 获取玩家
    Player* getPlayer() const { return _player; }
    
    // 检查宠物是否被冻结
    bool isPetFrozen(int index) const;
    
    // 检查食物是否被冻结
    bool isFoodFrozen(int index) const;

    void swapPets(int index, int targetIndex);

    ~Shop() = default;
};
