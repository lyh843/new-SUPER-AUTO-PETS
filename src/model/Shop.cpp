#include "Shop.hpp"
#include <algorithm>
#include <chrono>
#include <functional>

Shop::Shop(Player* player)
    : _player(player)
    , _rng(std::chrono::steady_clock::now().time_since_epoch().count())
{
    _petShopList.resize(PET_SHOP_SIZE);
    _foodShopList.resize(FOOD_SHOP_SIZE);
    _petFrozen.resize(PET_SHOP_SIZE, false);
    _foodFrozen.resize(FOOD_SHOP_SIZE, false);

    // 初始化商店
    for (int i = 0; i < PET_SHOP_SIZE; ++i)
    {
        _petShopList[i] = generateRandomPet();
    }
    for (int i = 0; i < FOOD_SHOP_SIZE; ++i)
    {
        _foodShopList[i] = generateRandomFood();
    }
}

std::unique_ptr<Pet> Shop::generateRandomPet()
{
    // 获取所有可用的宠物类型
    auto& creators = getAllPets();
    if (creators.empty())
        return nullptr;

    // 随机选择一个
    std::uniform_int_distribution<size_t> dist(0, creators.size() - 1);
    return creators[dist(_rng)]();
}

std::unique_ptr<Food> Shop::generateRandomFood()
{
    // 创建食物类型列表
    std::vector<std::function<std::unique_ptr<Food>()>> foodCreators = {
        Food::createApple,
        Food::createHoney,
        Food::createMeatBone,
        Food::createGarlic,
        Food::createSalad,
        Food::createCannedFood,
        Food::createMelon,
        Food::createMushroom,
        Food::createPear
    };

    std::uniform_int_distribution<size_t> dist(0, foodCreators.size() - 1);
    return foodCreators[dist(_rng)]();
}

bool Shop::refresh()
{
    // 检查玩家是否有足够的金币
    if (!_player->decreaseCoin(REFRESH_COST))
        return false;

    // 刷新未冻结的宠物
    for (int i = 0; i < PET_SHOP_SIZE; ++i)
    {
        if (!_petFrozen[i])
        {
            _petShopList[i] = generateRandomPet();
        }
    }

    // 刷新未冻结的食物
    for (int i = 0; i < FOOD_SHOP_SIZE; ++i)
    {
        if (!_foodFrozen[i])
        {
            _foodShopList[i] = generateRandomFood();
        }
    }

    return true;
}

bool Shop::buyFood(int foodIndex, int targetPetIndex)
{
    // 验证索引
    if (foodIndex < 0 || foodIndex >= FOOD_SHOP_SIZE)
        return false;
    
    if (!_foodShopList[foodIndex])
        return false;

    // 检查玩家金币
    if (!_player->decreaseCoin(_foodShopList[foodIndex]->getCost()))
        return false;

    // 获取目标宠物
    Pet* targetPet = _player->getPetAt(targetPetIndex);
    if (!targetPet)
    {
        _player->addCoin(_foodShopList[foodIndex]->getCost());  // 退还金币
        return false;
    }

    // 应用食物效果
    if (!targetPet->applyFood(_foodShopList[foodIndex]))
    {
        _player->addCoin(_foodShopList[foodIndex]->getCost());  // 退还金币
        return false;
    }

    // 移除食物（已消耗）
    _foodShopList[foodIndex] = nullptr;
    _foodFrozen[foodIndex] = false;

    return true;
}

bool Shop::buyPet(int petIndex, int targetPetIndex)
{
    // 验证索引
    if (petIndex < 0 || petIndex >= PET_SHOP_SIZE)
        return false;
    
    if (!_petShopList[petIndex])
        return false;

    // 检查玩家金币
    if (!_player->decreaseCoin(PET_COST))
        return false;

    // 尝试添加宠物
    auto pet = std::move(_petShopList[petIndex]);
    if (!_player->addPet(std::move(pet), targetPetIndex))
    {
        _player->addCoin(PET_COST);  // 退还金币
        _petShopList[petIndex] = std::move(pet);  // 归还宠物
        return false;
    }

    // 清除该位置
    _petShopList[petIndex] = nullptr;
    _petFrozen[petIndex] = false;

    return true;
}

bool Shop::sell(int targetPetIndex)
{
    // 移除宠物
    auto pet = _player->removePet(targetPetIndex);
    if (!pet)
        return false;
    if (dynamic_cast<Duck*>(pet.get())) { //在Shop中实现Duck的技能
        for (int i = 0;i < _player->getPetCount(); i++)
        {
            _player->getPetAt(i)->addHP(1);
        }
    }
    if (dynamic_cast<Cricket*>(pet.get())) { //在Shop中调用Cricket技能
        pet.get()->triggerOnSell(_player->getPets());
    }
    // 给予玩家金币
    _player->addCoin(SELL_REWARD);

    return true;
}

void Shop::togglePetFreeze(int index)
{
    if (index >= 0 && index < PET_SHOP_SIZE)
    {
        _petFrozen[index] = !_petFrozen[index];
    }
}

void Shop::toggleFoodFreeze(int index)
{
    if (index >= 0 && index < FOOD_SHOP_SIZE)
    {
        _foodFrozen[index] = !_foodFrozen[index];
    }
}

Pet* Shop::getPet(int index) const
{
    if (index < 0 || index >= PET_SHOP_SIZE)
        return nullptr;
    return _petShopList[index].get();
}

Food* Shop::getFood(int index) const
{
    if (index < 0 || index >= FOOD_SHOP_SIZE)
        return nullptr;
    return _foodShopList[index].get();
}

bool Shop::isPetFrozen(int index) const
{
    if (index < 0 || index >= PET_SHOP_SIZE)
        return false;
    return _petFrozen[index];
}

bool Shop::isFoodFrozen(int index) const
{
    if (index < 0 || index >= FOOD_SHOP_SIZE)
        return false;
    return _foodFrozen[index];
}

void Shop::swapPets(int index, int targetIndex)
{ 
    std::swap(_petShopList[index], _petShopList[targetIndex]);
}