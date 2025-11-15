#include "qtshopview.h"
#include <qcontainerfwd.h>
#include <qdebug.h>
#include <qfont.h>
#include <qicon.h>
#include <qmessagebox.h>
#include <qnamespace.h>
#include <qobject.h>
#include <qpushbutton.h>
#include <qsize.h>
#include <memory>
#include "model/Pet.hpp"
#include "model/Player.hpp"
#include "ui_qtshopview.h"

QtPet::QtPet(QPushButton* petPushButton, int index, bool isPlayerPet)
    :_petPushButton(petPushButton), 
    _index(index), 
    _isPlayerPet(isPlayerPet){
    }

void QtPet::updatePet(Pet* pet){
    if(pet){
        _petPushButton->setIcon(QIcon(QString(":/Pet/photo/Pet/%1.png").arg(pet->getName())));
        _petPushButton->setIconSize(QSize(100, 100));
    }
    else{
        clear();
    }
}

void QtPet::clear(){
    _petPushButton->setIcon(QIcon());
}

QPushButton* QtPet::getPushButton(){
    return _petPushButton;
}

QtFood::QtFood(QPushButton* foodPushButton, int index)
    :_foodPushButton(foodPushButton), _index(index){

    }

void QtFood::updateFood(Food* food){
    if(food){
        _foodPushButton->setIcon(QIcon(QString(":/Food/photo/Food/%1.png").arg(food->getName())));
        _foodPushButton->setIconSize(QSize(100, 100));
    }
    else{
        clear();
    }
}

void QtFood::clear(){
    _foodPushButton->setIcon(QIcon());
}

QPushButton* QtFood::getPushButton(){
    return _foodPushButton;
}


QtShopview::QtShopview(Player* player, QWidget* parent) 
    :_player(player)
    , QWidget(parent)
    , ui(new Ui::QtShopview)
{
    _shop = std::make_unique<Shop>(_player);
    ui->setupUi(this);
    setupUI();
    updateUI();
}

void QtShopview::setupUI(){
    ui->coinIndex->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    ui->heartIndex->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    ui->roundIndex->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    ui->prizeIndex->setAlignment(Qt::AlignRight | Qt::AlignVCenter);


    QtPet* playerPet1 = new QtPet(ui->playAnimals1, 1, true);
    QtPet* playerPet2 = new QtPet(ui->playAnimals2, 2, true);
    QtPet* playerPet3 = new QtPet(ui->playAnimals3, 2, true);
    QtPet* playerPet4 = new QtPet(ui->playAnimals4, 2, true);
    QtPet* playerPet5 = new QtPet(ui->playAnimals5, 2, true);
    _playerPets.push_back(playerPet1);
    _playerPets.push_back(playerPet2);
    _playerPets.push_back(playerPet3);
    _playerPets.push_back(playerPet4);
    _playerPets.push_back(playerPet5);

    QtPet* shopPet1 = new QtPet(ui->shopAnimals1, 1, false); 
    QtPet* shopPet2 = new QtPet(ui->shopAnimals2, 2, false); 
    QtPet* shopPet3 = new QtPet(ui->shopAnimals3, 3, false); 
    QtPet* shopPet4 = new QtPet(ui->shopAnimals4, 4, false); 
    QtPet* shopPet5 = new QtPet(ui->shopAnimals5, 5, false); 
    QtPet* shopPet6 = new QtPet(ui->shopAnimals6, 6, false); 
    _shopPets.push_back(shopPet1);
    _shopPets.push_back(shopPet2);
    _shopPets.push_back(shopPet3);
    _shopPets.push_back(shopPet4);  
    _shopPets.push_back(shopPet5);
    _shopPets.push_back(shopPet6);

    QtFood* shopFood1 = new QtFood(ui->shopFood1, 1);
    QtFood* shopFood2 = new QtFood(ui->shopFood2, 2);
    _shopFoods.push_back(shopFood1);
    _shopFoods.push_back(shopFood2);

    connect(ui->refreshButton, &QPushButton::clicked, this, &QtShopview::onRefreshClicked);
    connect(ui->frightButton, &QPushButton::clicked, this, &QtShopview::onEndTurnClicked);
    connect(ui->petBookButton, &QPushButton::clicked, this, &QtShopview::onPetBookClicked);
    connect(ui->settingsButton, &QPushButton::clicked, this, &QtShopview::onSettingsClicked);

    for(int i = 0; i < 5; i++){
        QPushButton* btn = _playerPets[i]->getPushButton();
        connect(btn, &QPushButton::clicked, this, [this, i](){
            onPlayerPetClicked(i, true);
        });
    }
    for(int i = 0; i < 6; i++){
        QPushButton* btn = _shopPets[i]->getPushButton();
        connect(btn, &QPushButton::clicked, [this, i](){
            onShopPetClicked(i, false);
        });
    }
    for(int i = 0; i < 2; i++){
        QPushButton* btn = _shopFoods[i]->getPushButton();
        connect(btn, &QPushButton::clicked, [this, i](){
            onFoodClicked(i);
        });
    }
    
}


void QtShopview::updatePlayerInfo(){
    ui->coinIndex->setText(QString::number(_player->getCoin()));
    ui->heartIndex->setText(QString::number(_player->getLives()));
    ui->roundIndex->setText(QString::number(_player->getRound()));
    ui->prizeIndex->setText(QString::number(_player->getPrize()));
    ui->coinIndex->setStyleSheet("color: black;");
    ui->heartIndex->setStyleSheet("color: black;");
    ui->roundIndex->setStyleSheet("color: black;");
    ui->prizeIndex->setStyleSheet("color: black;");
    QFont font = ui->coinIndex->font();
    font.setBold(true);
    font.setPointSize(14);
    font = ui->heartIndex->font();
    font.setBold(true);
    font.setPointSize(14);
    font = ui->roundIndex->font();
    font.setBold(true);
    font.setPointSize(14);
    font = ui->prizeIndex->font();
    font.setBold(true);
    font.setPointSize(14);
    ui->coinIndex->show();
    ui->coinIndex->raise();
    ui->heartIndex->show();
    ui->roundIndex->show();
    ui->prizeIndex->show();
}

void QtShopview::updatePlayerPets(){
    for(int i = 0; i < 5; i++){
        Pet* pet = _player->getPetAt(i);
        _playerPets[i]->updatePet(pet);
        _playerPets[i]->getPushButton()->setEnabled(pet != nullptr);
    }
}

void QtShopview::updateShopPets(){ 
    for(int i = 0; i < 6; i++){
        Pet* pet = _shop->getPet(i);
        _shopPets[i]->updatePet(pet);
        _shopPets[i]->getPushButton()->setEnabled(pet != nullptr);
    }
}

void QtShopview::updateShopFoods(){
    for(int i = 0; i < 2; i++){
        Food* food = _shop->getFood(i);
        _shopFoods[i]->updateFood(food);
    }
}

void QtShopview::updateUI(){
    updatePlayerInfo();
    updatePlayerPets();
    updateShopPets();
    updateShopFoods();
}

void QtShopview::onRefreshClicked(){
    if(_shop->refresh()){
        updateUI();
        QMessageBox::information(this, "刷新成功", "商店已刷新！");
    }
    else{
        QMessageBox::information(this, "刷新失败", "刷新商店需要 1 金币！");
    }
}

void QtShopview::onEndTurnClicked(){ 
    emit endTurn();
}

void QtShopview::onShopPetClicked(int index, bool isPlayerPet){ 
    if(_player->getPetCount() >= 5){
        QMessageBox::warning(this, "阵容已满", "你的宠物阵容已满！请先出售一只宠物。");
        return;
    }
    int emptySlot = -1;
    for(int i = 0; i < 5; i++){
        if(_player->getPetAt(i) == nullptr){
            emptySlot = i;
            break;
        }
    }
    if(emptySlot == -1){
        QMessageBox::warning(this, "阵容已满", "你的宠物阵容已满！");
        return;
    }
    if(_shop->buyPet(index, emptySlot)){
        updateUI();
        QMessageBox::information(this, "购买成功", "宠物已加入你的阵容！");
    }
    else{
        QMessageBox::information(this, "购买失败", "你没有足够的金币！");
    }
}

void QtShopview::onPlayerPetClicked(int index, bool isPlayerPet){ 
    Pet* pet = _player->getPetAt(index);
    if(!pet){
        return;
    }

    QMessageBox msgBox(this);
    msgBox.setWindowTitle("");
    msgBox.setText("需要进行换位还是出售？");

    QPushButton* moveBtn = msgBox.addButton("换位", QMessageBox::AcceptRole);
    QPushButton* sellBtn = msgBox.addButton("出售", QMessageBox::DestructiveRole);
    QPushButton* cancelBtn = msgBox.addButton("取消", QMessageBox::RejectRole);

    msgBox.exec();

    if (msgBox.clickedButton() == moveBtn) {
        QMessageBox posBox(this);
        posBox.setWindowTitle("选择宠物");
        posBox.setText("请选择要与之交换的宠物：");

        struct ButtonItem {
            QPushButton* btn;
            int index;
        };
        QVector<ButtonItem> items;
        for (int i = 0; i < 5; ++i)
        {
            if (i == index) continue;
            Pet* p = _player->getPetAt(i);
            if (p) {
                QString name = QString::fromStdString(p->getName());
                auto* btn = posBox.addButton(name, QMessageBox::ActionRole);

                items.append({btn, i});
            }
        }
        if (items.isEmpty()) {
            QMessageBox::information(this, "提示", "没有可交换的宠物。");
            return;
        }
        posBox.exec();
        int targetIndex = -1;
        for (const auto& item : items)
        {
            if (posBox.clickedButton() == item.btn) {
                targetIndex = item.index;
                break;
            }
        }
        if (targetIndex == -1)
            return;
        _player->swapPets(index, targetIndex);
        updateUI();
    }
    else if (msgBox.clickedButton() == sellBtn) {
        if (_shop->sell(index)) {
            updateUI();
            QMessageBox::information(this, "出售成功", "宠物已出售，获得 1 金币！");
        }
    }
    else {
        return;
    }
}

void QtShopview::onFoodClicked(int index){ 
    // 购买食物：需要选择目标宠物
    if (_player->getPetCount() == 0)
    {
        QMessageBox::warning(this, "没有宠物", "你需要先购买宠物才能使用食物！");
        return;
    }

    // 让用户选择目标宠物
    QMessageBox msgBox;
    msgBox.setWindowTitle("选择目标宠物");
    msgBox.setText("请选择要喂食的宠物：");

    QVector<QPushButton*> petButtons;
    for (int i = 0; i < 5; ++i)
    {
        Pet* pet = _player->getPetAt(i);
        if (pet)
        {
            auto* btn = msgBox.addButton(QString::fromStdString(pet->getName()), QMessageBox::ActionRole);
            petButtons.append(btn);
        }
    }

    auto* cancelBtn = msgBox.addButton("取消", QMessageBox::RejectRole);
    msgBox.exec();

    auto* clickedBtn = msgBox.clickedButton();
    if (clickedBtn == cancelBtn)
        return;

    // 找到选择的宠物索引
    int targetPetIndex = -1;
    int buttonIndex = 0;
    for (int i = 0; i < 5; ++i)
    {
        Pet* pet = _player->getPetAt(i);
        if (pet)
        {
            if (clickedBtn == petButtons[buttonIndex])
            {
                targetPetIndex = i;
                break;
            }
            buttonIndex++;
        }
    }

    if (targetPetIndex >= 0)
    {
        if (_shop->buyFood(index, targetPetIndex))
        {
            updateUI();
            QMessageBox::information(this, "购买成功", "食物效果已应用到宠物！");
        }
        else
        {
            QMessageBox::warning(this, "购买失败", "金币不足或无法使用该食物！");
        }
    }
}

void QtShopview::onPetFreezeClicked(int index){ 
    _shop->togglePetFreeze(index);
    updateUI();
}

void QtShopview::onFoodFreezeClicked(int index)
{
    _shop->toggleFoodFreeze(index);
    updateUI();
}

void QtShopview::resetShop()
{
    _shop = std::make_unique<Shop>(_player);
    updateUI();
}

void QtShopview::onPetBookClicked(){
    emit encyclopediaClicked();
}

void QtShopview::onSettingsClicked(){
    // TODO: Implement settings
}


QtShopview::~QtShopview()
{
    delete ui;
}
