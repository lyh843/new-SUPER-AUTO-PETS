#include "Player.hpp"

// 添加宠物到指定位置
bool Player::addPet(std::unique_ptr<Pet> pet, int index)
{
    if (!pet || index < 0 || index >= 5)
        return false;

    // 如果该位置已有宠物
    if (index < _pets.size() && _pets[index])
    {
        // 如果是相同类型的宠物，则合并（增加经验）
        if (_pets[index]->getName() == pet->getName())
        {
            _pets[index]->gainExperience(1);
            return true;
        }
        return false;  // 位置已被占用
    }

    // 扩展 vector 以容纳新宠物
    if (index >= _pets.size())
    {
        _pets.resize(index + 1);
    }

    _pets[index] = std::move(pet);
    return true;
}

// 移除指定位置的宠物
std::unique_ptr<Pet> Player::removePet(int index)
{
    if (index < 0 || index >= _pets.size() || !_pets[index])
        return nullptr;

    auto pet = std::move(_pets[index]);
    return pet;
}

// 获取指定位置的宠物
Pet* Player::getPetAt(int index) const
{
    if (index < 0 || index >= _pets.size())
        return nullptr;
    return _pets[index].get();
}

// 获取宠物数量
int Player::getPetCount() const
{
    int count = 0;
    for (const auto& pet : _pets)
    {
        if (pet->getName() != "")
            count++;
    }
    return count;
}