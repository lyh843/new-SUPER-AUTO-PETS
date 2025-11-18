#ifndef QTSHOPVIEW_H
#define QTSHOPVIEW_H

#include "../model/Player.hpp"
#include "../model/Shop.hpp"
#include "model/Pet.hpp"

#include <QPushButton>
#include <QWidget>
#include <QLabel>


namespace Ui
{
class QtShopview;
}

class QtPet
{
private:
    Pet* _pet;
    QPushButton* _petPushButton;
    QLabel* _petInfo;
    QLabel* _petInfoAttack;
    QLabel* _petInfoHeart;
    QLabel* _petInfoCoin;
    QLabel* _petInfoCoinIndex; 
    // std::pair<int, int> _loc;
    int _index;
    bool _isPlayerPet;
    bool _isFreeze;

public:
    QtPet(QPushButton* petPushButton, QLabel* petInfo, QLabel* petInfoAttack, QLabel* petInfoHeart, QLabel* petInfoCoin,
        QLabel* petInfoCoinIndex, int index, bool isPlayerPet);
    void updatePet(Pet* pet);
    void clear();
    void freeze();
    void clicked();
    QPushButton* getPushButton();
    Pet* getPet(){ return _pet; };
    Pet* setPet(Pet* pet){
        _pet = pet;
    }
};

class QtFood
{
private:
    Food* _food;
    QPushButton* _foodPushButton;
    QLabel* _foodInfoCoin;
    QLabel* _foodInfoCoinIndex; 
    // std::pair<int, int> _loc;
    int _index;
public:
    QtFood(QPushButton* foodPushButton,  QLabel* foodInfoCoin, QLabel* foodInfoCoinIndex, int index);
    void updateFood(Food* food);
    void clear();
    void freeze();
    void clicked();
    QPushButton* getPushButton();
};

class QtShopview : public QWidget
{
    Q_OBJECT
private:
    Ui::QtShopview* ui;
    std::unique_ptr<Shop> _shop;
    Player* _player;

    QVector<QtPet*> _playerPets;
    QVector<QtFood*> _shopFoods;
    QVector<QtPet*> _shopPets;

    // 选择状态
    int _selectedShopPetIndex;
    int _selectedFoodIndex;
    int _targetPetIndex;

    void setupUI();
    void updateUI();
    void updatePlayerInfo();
    void updatePlayerPets();
    void updateShopPets();
    void updateShopFoods();

private slots:
    void onRefreshClicked();
    void onEndTurnClicked();
    void onShopPetClicked(int index, bool isPlayerPet);
    void onPlayerPetClicked(int index, bool isPlayerPet);
    void onFoodClicked(int index);
    void onPetFreezeClicked(int index);
    void onFoodFreezeClicked(int index);
    void onPetBookClicked();
    void onSettingsClicked();

signals:
    void endTurn();
    void encyclopediaClicked();
    void settingsClicked();


public:
    QtShopview(Player* player, QWidget* parent = nullptr);
    ~QtShopview();
    void resetShop();
};

#endif  // QTSHOPVIEW_H
