#ifndef QTSHOPVIEW_H
#define QTSHOPVIEW_H

#include "../model/Player.hpp"
#include "../model/Shop.hpp"
#include "model/Pet.hpp"

#include <QPushButton>
#include <QWidget>
#include <utility>


namespace Ui
{
class QtShopview;
}

class QtPet
{
private:
    Pet* _pet;
    QPushButton* _petPushButton;
    std::pair<int, int> _loc;
    int _index;
    bool _isPlayerPet;
    bool _isFreeze;

public:
    QtPet(QPushButton* petPushButton, int index, bool isPlayerPet);
    void updatePet(Pet* pet);
    void clear();
    void freeze();
    void clicked();
    QPushButton* getPushButton();
    Pet* getPet(){ return _pet; };
};

class QtFood
{
private:
    Food* _food;
    QPushButton* _foodPushButton;
    std::pair<int, int> _loc;
    int _index;
public:
    QtFood(QPushButton* foodPushButton, int index);
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


public:
    QtShopview(Player* player, QWidget* parent = nullptr);
    ~QtShopview();
    void resetShop();
};

#endif  // QTSHOPVIEW_H
