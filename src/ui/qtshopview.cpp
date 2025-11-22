#include "qtshopview.h"
#include <qcontainerfwd.h>
#include <qcoreevent.h>
#include <qdebug.h>
#include <qevent.h>
#include <qfont.h>
#include <qgraphicseffect.h>
#include <qicon.h>
#include <qimage.h>
#include <qlabel.h>
#include <qmessagebox.h>
#include <qnamespace.h>
#include <qobject.h>
#include <qpixmap.h>
#include <qpushbutton.h>
#include <qsize.h>
#include <memory>
#include "model/Pet.hpp"
#include "model/Player.hpp"
#include "ui/BattleView.hpp"
#include "ui_qtshopview.h"

QtPet::QtPet(QPushButton* petPushButton,
             QLabel* petInfo,
             QLabel* petInfoAttack,
             QLabel* petInfoHeart,
             QLabel* petInfoCoin,
             QLabel* petInfoCoinIndex,
             QLabel* petInfoLevel,
             QLabel* petFreeze,
             int index,
             bool isPlayerPet)
    : _petPushButton(petPushButton)
    , _petInfo(petInfo)
    , _petInfoAttack(petInfoAttack)
    , _petInfoHeart(petInfoHeart)
    , _petInfoCoin(petInfoCoin)
    , _petInfoCoinIndex(petInfoCoinIndex)
    , _petInfoLevel(petInfoLevel)
    , _petFreeze(petFreeze)
    , _index(index)
    , _isPlayerPet(isPlayerPet)
{
    _petPushButton->installEventFilter(this);
    _isFreeze = false;
}

bool QtPet::eventFilter(QObject* obj, QEvent *event){
    if (obj == _petPushButton){
        if(event->type() == QEvent::MouseButtonPress){
            QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
            if(mouseEvent->button() == Qt::RightButton){
                emit freezeClicked(_index);
                return true;
            }
        }
    }
    return QObject::eventFilter(obj, event);
}


void QtPet::updatePet(Pet* pet)
{
    _pet = pet;
    if (pet)
    {
        QString path = QString(":/Pet/photo/Pet/%1.png").arg(pet->getName());
        QPixmap pix(path);
        QImage img = pix.toImage().flipped(Qt::Horizontal);
        _petPushButton->setIcon(QIcon(QPixmap::fromImage(img)));
        _petPushButton->setIconSize(QSize(100, 100));
        _petInfo->show();
        _petInfoAttack->show();
        _petInfoAttack->setText(QString::number(pet->getAttack()));
        _petInfoHeart->show();
        _petInfoHeart->setText(QString::number(pet->getHP()));
        QString tip = QString("<b>%1</b><br>%2").arg(QString::fromStdString(pet->getChineseName()))
        .arg(QString::fromStdString(pet->getIntroSkills()));
        _petPushButton->setToolTip(tip);
        if (_petInfoCoin != nullptr)
        {
            _petInfoCoin->show();
            _petInfoCoinIndex->show();
            _petInfoCoinIndex->setText(QString::number(pet->getCost()));
        }
        if(_petInfoLevel != nullptr){
            _petInfoLevel->show();
            if(pet->getLevel() == 1){
                _petInfoLevel->setPixmap(QPixmap(QString(":/else/photo/petLevel1.png")));
            }
            else if(pet->getLevel() == 2){
                _petInfoLevel->setPixmap(QPixmap(QString(":/else/photo/petLevel2.png")));
            }
            else {
                _petInfoLevel->setPixmap(QPixmap(QString(":/else/photo/petLevel3.png")));
            }
        }
        if(_petFreeze != nullptr){
            _petFreeze->setAttribute(Qt::WA_TransparentForMouseEvents);
            if(_isFreeze){
                QGraphicsOpacityEffect* effect = new QGraphicsOpacityEffect(_petFreeze);
                effect->setOpacity(0.75);
                _petFreeze->setGraphicsEffect(effect);
                _petFreeze->show();
            }
            else{
                _petFreeze->hide();
            }
        }
    }
    else
    {
        clear();
    }
}

void QtPet::clear()
{
    _petPushButton->setIcon(QIcon());
    _petPushButton->setToolTip("");
    _petInfo->hide();
    _petInfoAttack->hide();
    _petInfoHeart->hide();
    if (_petInfoCoin != nullptr)
    {
        _petInfoCoin->hide();
        _petInfoCoinIndex->hide();
    }
    if(_petInfoLevel != nullptr){
        _petInfoLevel->hide();
    }
    if(_petFreeze != nullptr){
        _isFreeze = false;
        _petFreeze->hide();
    }
}

QPushButton* QtPet::getPushButton()
{
    return _petPushButton;
}

QtFood::QtFood(QPushButton* foodPushButton, QLabel* foodInfoCoin, QLabel* foodInfoCoinIndex, QLabel* foodFreeze, int index)
    : _foodPushButton(foodPushButton), _index(index), _foodInfoCoin(foodInfoCoin), _foodFreeze(foodFreeze) ,_foodInfoCoinIndex(foodInfoCoinIndex)
{
    _isFreeze = false;
    _foodPushButton->installEventFilter(this);
}

void QtFood::updateFood(Food* food)
{
    _food = food;
    if (food)
    {
        _foodPushButton->setIcon(QIcon(QString(":/Food/photo/Food/%1.png").arg(food->getName())));
        _foodPushButton->setIconSize(QSize(100, 100));
        _foodInfoCoin->show();
        _foodInfoCoinIndex->show();
        _foodInfoCoinIndex->setText(QString::number(food->getCost()));
        QString tip = QString("<b>%1</b><br>%2").arg(QString::fromStdString(food->getChineseName()))
        .arg(QString::fromStdString(food->getIntroSkills()));
        _foodPushButton->setToolTip(tip);
        if(_isFreeze){
            QGraphicsOpacityEffect* effect = new QGraphicsOpacityEffect(_foodFreeze);
            effect->setOpacity(0.75);
            _foodFreeze->setGraphicsEffect(effect);
            _foodFreeze->setAttribute(Qt::WA_TransparentForMouseEvents);
            _foodFreeze->show();
        }
        else{
            _foodFreeze->hide();
        }
    }
    else
    {
        clear();
    }
}

bool QtFood::eventFilter(QObject *obj, QEvent *event){
    if (obj == _foodPushButton && event->type() == QEvent::MouseButtonPress) {
        QMouseEvent* mouse = static_cast<QMouseEvent*>(event);
        if (mouse->button() == Qt::RightButton) {
            emit freezeClicked(_index);
            return true;
        }
    }
    return QObject::eventFilter(obj, event);
}

void QtShopview::onFoodFreezeClicked(int index)
{
    _shop->toggleFoodFreeze(index);
    updateUI();
}


void QtFood::clear()
{
    _foodPushButton->setIcon(QIcon());
    _foodInfoCoin->hide();
    _foodInfoCoinIndex->hide();
    _foodPushButton->setToolTip("");
}

QPushButton* QtFood::getPushButton()
{
    return _foodPushButton;
}

QtShopview::QtShopview(Player* player, QWidget* parent) : _player(player), QWidget(parent), ui(new Ui::QtShopview)
{
    _shop = std::make_unique<Shop>(_player);
    ui->setupUi(this);
    setupUI();
    updateUI();
}

void QtShopview::setupUI()
{
    ui->coinIndex->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    ui->heartIndex->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    ui->roundIndex->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    ui->prizeIndex->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    QtPet* playerPet1 = new QtPet(ui->playAnimals1, ui->playPetInfo1, ui->playPetInfo1_attack, ui->playPetInfo1_heart,
                                  nullptr, nullptr, ui->playPetLevel1, nullptr, 0, true);
    QtPet* playerPet2 = new QtPet(ui->playAnimals2, ui->playPetInfo2, ui->playPetInfo2_attack, ui->playPetInfo2_heart,
                                  nullptr, nullptr, ui->playPetLevel2, nullptr, 1, true);
    QtPet* playerPet3 = new QtPet(ui->playAnimals3, ui->playPetInfo3, ui->playPetInfo3_attack, ui->playPetInfo3_heart,
                                  nullptr, nullptr, ui->playPetLevel3, nullptr, 2, true);
    QtPet* playerPet4 = new QtPet(ui->playAnimals4, ui->playPetInfo4, ui->playPetInfo4_attack, ui->playPetInfo4_heart,
                                  nullptr, nullptr, ui->playPetLevel4, nullptr, 3, true);
    QtPet* playerPet5 = new QtPet(ui->playAnimals5, ui->playPetInfo5, ui->playPetInfo5_attack, ui->playPetInfo5_heart,
                                  nullptr, nullptr, ui->playPetLevel5, nullptr, 4, true);
    _playerPets.push_back(playerPet5);
    _playerPets.push_back(playerPet4);
    _playerPets.push_back(playerPet3);
    _playerPets.push_back(playerPet2);
    _playerPets.push_back(playerPet1);

    QtPet* shopPet1 = new QtPet(ui->shopAnimals1, ui->shopPetInfo1, ui->shopPetInfo1_attack, ui->shopPetInfo1_heart,
                                ui->shopPetCoin1, ui->shopPetCoin1_index, nullptr, ui->shopPetFreeze1, 0, false);
    QtPet* shopPet2 = new QtPet(ui->shopAnimals2, ui->shopPetInfo2, ui->shopPetInfo2_attack, ui->shopPetInfo2_heart,
                                ui->shopPetCoin2, ui->shopPetCoin2_index, nullptr, ui->shopPetFreeze2, 1, false);
    QtPet* shopPet3 = new QtPet(ui->shopAnimals3, ui->shopPetInfo3, ui->shopPetInfo3_attack, ui->shopPetInfo3_heart,
                                ui->shopPetCoin3, ui->shopPetCoin3_index, nullptr, ui->shopPetFreeze3, 2, false);
    QtPet* shopPet4 = new QtPet(ui->shopAnimals4, ui->shopPetInfo4, ui->shopPetInfo4_attack, ui->shopPetInfo4_heart,
                                ui->shopPetCoin4, ui->shopPetCoin4_index, nullptr, ui->shopPetFreeze4, 3, false);
    QtPet* shopPet5 = new QtPet(ui->shopAnimals5, ui->shopPetInfo5, ui->shopPetInfo5_attack, ui->shopPetInfo5_heart,
                                ui->shopPetCoin5, ui->shopPetCoin5_index, nullptr, ui->shopPetFreeze5, 4, false);
    QtPet* shopPet6 = new QtPet(ui->shopAnimals6, ui->shopPetInfo6, ui->shopPetInfo6_attack, ui->shopPetInfo6_heart,
                                ui->shopPetCoin6, ui->shopPetCoin6_index, nullptr, ui->shopPetFreeze6, 5, false);
    _shopPets.push_back(shopPet1);
    _shopPets.push_back(shopPet2);
    _shopPets.push_back(shopPet3);
    _shopPets.push_back(shopPet4);
    _shopPets.push_back(shopPet5);
    _shopPets.push_back(shopPet6);
    for(auto i : _shopPets){
        connect(i, &QtPet::freezeClicked, this, &QtShopview::onPetFreezeClicked);
    }

    QtFood* shopFood1 = new QtFood(ui->shopFood1, ui->shopFoodCoin1, ui->shopFoodCoin1_index, ui->shopFoodFreeze1, 0);
    QtFood* shopFood2 = new QtFood(ui->shopFood2, ui->shopFoodCoin2, ui->shopFoodCoin2_index, ui->shopFoodFreeze2, 1);
    _shopFoods.push_back(shopFood1);
    _shopFoods.push_back(shopFood2);
    for(auto i : _shopFoods){
        connect(i, &QtFood::freezeClicked, this, &QtShopview::onFoodFreezeClicked);
    }

    connect(ui->refreshButton, &QPushButton::clicked, this, &QtShopview::onRefreshClicked);
    connect(ui->frightButton, &QPushButton::clicked, this, &QtShopview::onEndTurnClicked);
    connect(ui->petBookButton, &QPushButton::clicked, this, &QtShopview::onPetBookClicked);
    connect(ui->settingsButton, &QPushButton::clicked, this, &QtShopview::onSettingsClicked);

    for (int i = 0; i < 5; i++)
    {
        QPushButton* btn = _playerPets[i]->getPushButton();
        connect(btn, &QPushButton::clicked, this, [this, i]() { onPlayerPetClicked(i, true); });
    }
    // 只连接前3个商店宠物槽位（商店只有3个槽位）
    for (int i = 0; i < 6; i++)
    {
        QPushButton* btn = _shopPets[i]->getPushButton();
        connect(btn, &QPushButton::clicked, [this, i]() { onShopPetClicked(i, false); });
    }
    for (int i = 0; i < 2; i++)
    {
        QPushButton* btn = _shopFoods[i]->getPushButton();
        connect(btn, &QPushButton::clicked, [this, i]() { onFoodClicked(i); });
    }
}

void QtShopview::updatePlayerInfo()
{
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


void QtShopview::updatePlayerPets()
{
    for (int i = 0; i < 5; i++)
    {
        Pet* pet = _player->getPetAt(i);
        _playerPets[i]->updatePet(pet);
        _playerPets[i]->getPushButton()->setEnabled(pet != nullptr);
    }
}

void QtShopview::updateShopPets()
{
    // 商店只有3个宠物槽位（PET_SHOP_SIZE = 3）
    for (int i = 0; i < _shop->getPetShopSize(); i++)
    {
        Pet* pet = _shop->getPet(i);
        bool frozen = _shop->isPetFrozen(i);
        _shopPets[i]->setFreeze(frozen);
        _shopPets[i]->updatePet(pet);
        _shopPets[i]->getPushButton()->setEnabled(pet != nullptr);
    }
    // 隐藏多余的宠物槽位
    for (int i = _shop->getPetShopSize(); i < static_cast<int>(_shopPets.size()); i++)
    {
        _shopPets[i]->clear();
    }
}

void QtShopview::updateShopFoods()
{
    for (int i = 0; i < 2; i++)
    {
        Food* food = _shop->getFood(i);
        bool frozen = _shop->isFoodFrozen(i);
        _shopFoods[i]->setFreeze(frozen);
        _shopFoods[i]->updateFood(food);
    }
}

void QtShopview::updateUI()
{
    updatePlayerInfo();
    _player->compactPets();
    updatePlayerPets();
    updateShopPets();
    updateShopFoods();
}

void QtShopview::onRefreshClicked()
{
    if (_shop->refresh())
    {
        updateUI();
        QMessageBox::information(this, "刷新成功", "商店已刷新！");
    }
    else
    {
        QMessageBox::information(this, "刷新失败", "刷新商店需要 1 金币！");
    }
}

void QtShopview::onEndTurnClicked()
{
    emit endTurn();
}

void QtShopview::onShopPetClicked(int index, bool isPlayerPet)
{
    // 检查索引有效性（商店只有3个宠物槽位）
    if (index < 0 || index >= _shop->getPetShopSize())
    {
        return;
    }

    if (_player->getPetCount() >= 5)
    {
        QMessageBox::warning(this, "阵容已满", "你的宠物阵容已满！请先出售一只宠物。");
        return;
    }

    // 寻找空位 - 修复空指针访问问题
    int emptySlot = -1;
    for (int i = 0; i < 5; i++)
    {
        if (_player->getPetAt(i) == nullptr)
        {
            emptySlot = i;
            break;
        }
    }
    if (emptySlot == -1)
    {
        QMessageBox::warning(this, "阵容已满", "你的宠物阵容已满！");
        return;
    }

    if (_shop->buyPet(index, emptySlot))
    {
        updateUI();
        QMessageBox::information(this, "购买成功", "宠物已加入你的阵容！");
    }
    else
    {
        QMessageBox::information(this, "购买失败", "你没有足够的金币！");
    }
}

void QtShopview::onPlayerPetClicked(int index, bool isPlayerPet)
{
    // 检查索引有效性
    if (index < 0 || index >= 5)
    {
        return;
    }

    Pet* pet = _player->getPetAt(index);
    if (!pet)
    {
        return;
    }

    QMessageBox msgBox(this);
    msgBox.setWindowTitle("");
    msgBox.setText("需要进行换位还是出售？");

    QPushButton* moveBtn   = msgBox.addButton("换位", QMessageBox::AcceptRole);
    QPushButton* sellBtn   = msgBox.addButton("出售", QMessageBox::DestructiveRole);
    QPushButton* levelUpBtn = msgBox.addButton("升级", QMessageBox::ActionRole);
    QPushButton* cancelBtn = msgBox.addButton("取消", QMessageBox::RejectRole);

    msgBox.exec();

    if (msgBox.clickedButton() == moveBtn)
    {
        QMessageBox posBox(this);
        posBox.setWindowTitle("选择宠物");
        posBox.setText("请选择要与之交换的宠物：");
        struct ButtonItem
        {
            QPushButton* btn;
            int index;
        };
        QVector<ButtonItem> items;
        for (int i = 4; i >= 0; i--)
        {
            if (i == index)
                continue;
            Pet* p = _player->getPetAt(i);
            if (p)
            {
                QString name = QString::fromStdString(p->getChineseName());
                auto* btn    = posBox.addButton(name, QMessageBox::ActionRole);
                items.append({btn, i});
            }
        }
        if (items.isEmpty())
        {
            QMessageBox::information(this, "提示", "没有可交换的宠物。");
            return;
        }
        posBox.exec();
        int targetIndex = -1;
        for (const auto& item : items)
        {
            if (posBox.clickedButton() == item.btn)
            {
                targetIndex = item.index;
                break;
            }
        }
        if (targetIndex == -1)
            return;
        _player->swapPets(index, targetIndex);
        updateUI();
    }
    else if (msgBox.clickedButton() == sellBtn)
    {
        if (_shop->sell(index))
        {
            updateUI();
            QMessageBox::information(this, "出售成功", "宠物已出售，获得 1 金币！");
        }
    }
    else if(msgBox.clickedButton() == levelUpBtn){
        if(pet->getLevel() >= 3){
            QMessageBox::information(this, "提示", "宠物已到最高等级");
            return;
        }
        int samePetIndex = -1;
        Pet *selectedPet = nullptr;
        for(int i = 0; i < _player->getPetCount(); i++){
            if(i == index) continue;
            selectedPet = _player->getPetAt(i);
            if(selectedPet && selectedPet->getName() == pet->getName()){
                samePetIndex = i;
                break;
            }
        }

        if(samePetIndex != -1 && selectedPet->getLevel() < 3){
            if(selectedPet->getLevel() + pet->getLevel() >= 3){
                pet->levelUp();
                if(pet->getLevel() != 3){
                    pet->levelUp();
                }
                _player->removePet(samePetIndex);
                fishskill(_player,pet);
                updateUI();
                QMessageBox::information(this, "升级成功", "宠物已升级！");
            }
            else if(selectedPet->getLevel() + pet->getLevel() < 3){
                pet->levelUp();
                _player->removePet(samePetIndex);
                fishskill(_player,pet);
                updateUI();
                QMessageBox::information(this, "升级成功", "宠物已升级！");
            }
        }
        else{
            QMessageBox::warning(this, "升级失败", "没有找到同名且非最高等级宠物！");
        }
    }
    else
    {
        return;
    }
}

void QtShopview::onFoodClicked(int index)
{
    // 检查索引有效性
    if (index < 0 || index >= 2)
    {
        return;
    }

    // 购买食物：需要选择目标宠物
    if (_player->getPetCount() == 0)
    {
        QMessageBox::warning(this, "没有宠物", "你需要先购买宠物才能使用食物！");
        return;
    }

    // 让用户选择目标宠物
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("选择目标宠物");
    msgBox.setText("请选择要喂食的宠物：");

    QVector<QPushButton*> petButtons;
    for (int i = 4; i >= 0; i--)
    {
        Pet* pet = _player->getPetAt(i);
        if (pet)
        {
            auto* btn = msgBox.addButton(QString::fromStdString(pet->getChineseName()), QMessageBox::ActionRole);
            petButtons.append(btn);
        }
    }

    if (petButtons.isEmpty())
    {
        QMessageBox::warning(this, "没有宠物", "你需要先购买宠物才能使用食物！");
        return;
    }

    auto* cancelBtn = msgBox.addButton("取消", QMessageBox::RejectRole);
    msgBox.exec();

    auto* clickedBtn = msgBox.clickedButton();
    if (!clickedBtn || clickedBtn == cancelBtn)
        return;

    // 找到选择的宠物索引
    int targetPetIndex = -1;
    int buttonIndex    = 0;
    for (int i = 0; i < 5; ++i)
    {
        Pet* pet = _player->getPetAt(i);
        if (pet)
        {
            if (buttonIndex < petButtons.size() && clickedBtn == petButtons[buttonIndex])
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
void QtShopview::onPetFreezeClicked(int index)
{
    _shop->togglePetFreeze(index);
    updateUI();
}

void QtShopview::resetShop()
{
    // _shop = std::make_unique<Shop>(_player);
    _shop->refresh();
    _player->addCoin();
    updateUI();
}

void QtShopview::onPetBookClicked()
{
    emit encyclopediaClicked();
}

void QtShopview::onSettingsClicked()
{
    emit settingsClicked();
}

QtShopview::~QtShopview()
{
    delete ui;
}

void QtShopview::fishskill(Player* player,Pet* pet)
{
    //Fish技能实现
    if (dynamic_cast<Fish*>(pet))
    {
        auto& team = player->getPets();
        std::vector<int> candidates;
        for (size_t i = 0; i < team.size(); ++i)
            if (team[i].get() != pet && team[i].get())
                candidates.push_back(i);
        if (candidates.empty()) return;
        std::shuffle(candidates.begin(), candidates.end(), std::mt19937{std::random_device{}()});
        int cnt = std::min<int>(2, (int)candidates.size());
        for (int i = 0; i < cnt; ++i) {
            team[candidates[i]].get()->setHP(team[candidates[i]].get()->getHP() + 1);
            team[candidates[i]].get()->addAttack(1);
        }
    }
}
