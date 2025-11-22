// #pragma once

// #include <QWidget>
// #include <QPushButton>
// #include <QLabel>
// #include <QVBoxLayout>
// #include <QHBoxLayout>
// #include <QGridLayout>
// #include <memory>
// #include "../model/Shop.hpp"
// #include "../model/Player.hpp"

// // 宠物卡片类
// class PetCard : public QWidget
// {
//     Q_OBJECT

// private:
//     QLabel* _nameLabel;
//     QLabel* _statsLabel;
//     QLabel* _levelLabel;
//     QPushButton* _actionButton;
//     int _index;
//     bool _isPlayerPet;  // 是否是玩家的宠物

// public:
//     PetCard(int index, bool isPlayerPet, QWidget* parent = nullptr);
//     void updatePet(Pet* pet);
//     void clear();

// signals:
//     void clicked(int index, bool isPlayerPet);
//     void freezeClicked(int index);
// };

// // 食物卡片类
// class FoodCard : public QWidget
// {
//     Q_OBJECT

// private:
//     QLabel* _nameLabel;
//     QLabel* _costLabel;
//     QPushButton* _actionButton;
//     int _index;

// public:
//     FoodCard(int index, QWidget* parent = nullptr);
//     void updateFood(Food* food);
//     void clear();

// signals:
//     void clicked(int index);
//     void freezeClicked(int index);
// };

// // 商店视图主类
// class ShopView : public QWidget
// {
//     Q_OBJECT

// private:
//     std::unique_ptr<Shop> _shop;
//     Player* _player;

//     // UI 组件
//     QLabel* _coinLabel;
//     QLabel* _livesLabel;
//     QLabel* _roundLabel;
//     QLabel* _prizeLabel;

//     // 玩家宠物区域
//     QVector<PetCard*> _playerPetCards;

//     // 商店宠物区域
//     QVector<PetCard*> _shopPetCards;

//     // 商店食物区域
//     QVector<FoodCard*> _shopFoodCards;

//     // 按钮
//     QPushButton* _refreshButton;
//     QPushButton* _endTurnButton;

//     // 选择状态
//     int _selectedShopPetIndex;
//     int _selectedFoodIndex;
//     int _targetPetIndex;

//     void setupUI();
//     void updateUI();
//     void updatePlayerInfo();
//     void updatePlayerPets();
//     void updateShopPets();
//     void updateShopFoods();

// private slots:
//     void onRefreshClicked();
//     void onEndTurnClicked();
//     void onShopPetClicked(int index, bool isPlayerPet);
//     void onPlayerPetClicked(int index, bool isPlayerPet);
//     void onFoodClicked(int index);
//     void onPetFreezeClicked(int index);
//     void onFoodFreezeClicked(int index);

// signals:
//     void endTurn();  // 结束回合，进入战斗

// public:
//     ShopView(Player* player, QWidget* parent = nullptr);
//     ~ShopView() = default;

//     // 重置商店（新回合开始时调用）
//     void resetShop();
// };