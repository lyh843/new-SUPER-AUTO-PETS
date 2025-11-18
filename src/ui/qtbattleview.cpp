#include "qtbattleview.h"
#include "ui_qtbattleview.h"
#include "../model/Pet.hpp"
#include <QMessageBox>
#include <QScrollBar>
#include <QTextCursor>
#include <random>

//构造函数实现
QtBattleView::QtBattleView(Player* player, QWidget* parent) :
    QWidget(parent)
    , ui(new Ui::QtBattleView)
    , _player(player)
    , _battleStarted(false)
    , _autoBattle(false)
    , _pendingDisplayUpdate(false)
{
    ui->setupUi(this);

    _autoTimer = new QTimer(this);

    // 修复重复连接问题
    setupConnections();

    ui->start_font->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->auto_play_font->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->forward_font->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->start->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->auto_play->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->forward->setAttribute(Qt::WA_TransparentForMouseEvents);

    setupPetDisplays();
}

void QtBattleView::setupConnections()
{
    // 先断开所有可能的连接
    disconnect(ui->start_button, nullptr, this, nullptr);
    disconnect(ui->auto_play_button, nullptr, this, nullptr);
    disconnect(ui->forward_button, nullptr, this, nullptr);
    disconnect(_autoTimer, nullptr, this, nullptr);

    // 使用UniqueConnection确保只连接一次
    connect(_autoTimer, &QTimer::timeout, this, &QtBattleView::onAutoStep, Qt::UniqueConnection);
    connect(ui->start_button, &QPushButton::clicked, this, &QtBattleView::on_start_button_clicked, Qt::UniqueConnection);
    connect(ui->auto_play_button, &QPushButton::clicked, this, &QtBattleView::on_auto_play_button_clicked, Qt::UniqueConnection);
    connect(ui->forward_button, &QPushButton::clicked, this, &QtBattleView::on_forward_button_clicked, Qt::UniqueConnection);
}

//对战开始实现
void QtBattleView::startNewBattle()
{
    _battleStarted = false;
    _autoBattle = false;
    _pendingDisplayUpdate = false;
    _autoTimer->stop();

    // 生成AI对手
    generateAITeam(_player->getRound());

    // 延迟更新显示
    QTimer::singleShot(0, this, [this]() {
        updateBattleDisplay();
    });

    // 恢复自动播放图标和文字的原始状态
    ui->auto_play->setPixmap(QPixmap(":/else/photo/Refresh.png"));
    ui->auto_play_font->setText("<html><head/><body><p><span style=\" font-size:11pt; font-weight:700;\">自动播放</span></p></body></html>");

    // 移除透明度效果
    ui->start->setGraphicsEffect(nullptr);
    ui->forward->setGraphicsEffect(nullptr);

    // 恢复文字原始样式
    ui->start_font->setStyleSheet("color: white;");
    ui->forward_font->setStyleSheet("color: white;");

    ui->start_button->setEnabled(true);
    ui->auto_play_button->setEnabled(false);
    ui->forward_button->setEnabled(false);
}

//生成AI队伍实现
void QtBattleView::generateAITeam(int difficulty)
{
    _aiTeam.clear();

    std::random_device rd;
    std::mt19937 gen(rd());

    // 根据难度生成对手（2-5只宠物）
    int petCount = std::min(5, 2 + difficulty / 2);

    for (int i = 0; i < petCount; ++i)
    {
        // 随机选择宠物类型
        int petType = std::uniform_int_distribution<>(0, 7)(gen);

        std::unique_ptr<Pet> pet;
        switch (petType)
        {
        case 0: pet = std::make_unique<Cat>(4, 3, 1, 1); break;
        case 1: pet = std::make_unique<Ant>(2, 1, 1, 1); break;
        case 2: pet = std::make_unique<Fish>(3, 2, 1, 1); break;
        case 3: pet = std::make_unique<Cricket>(1, 2, 1, 1); break;
        case 4: pet = std::make_unique<Swan>(3, 1, 1, 2); break;
        case 5: pet = std::make_unique<Flamingo>(3, 2, 1, 2); break;
        case 6: pet = std::make_unique<Hedgehog>(3, 1, 1, 2); break;
        case 7: pet = std::make_unique<Peacock>(2, 5, 1, 3); break;
        }

                // 根据难度提升属性
        int levelBonus = difficulty / 3;
        for (int j = 0; j < levelBonus; ++j)
        {
            pet->gainExperience(2);
        }

        _aiTeam.push_back(std::move(pet));
    }

}

void QtBattleView::setupPetDisplays()
{
    // 清空容器
    _playerPetLabels.clear();
    _aiPetLabels.clear();

    // 使用UI中预留的宠物位置
    _playerPetLabels.append(ui->your_pet_1);
    _playerPetLabels.append(ui->your_pet_2);
    _playerPetLabels.append(ui->your_pet_3);
    _playerPetLabels.append(ui->your_pet_4);
    _playerPetLabels.append(ui->your_pet_5);

    _aiPetLabels.append(ui->opponents_pet_1);
    _aiPetLabels.append(ui->opponents_pet_2);
    _aiPetLabels.append(ui->opponents_pet_3);
    _aiPetLabels.append(ui->opponents_pet_4);
    _aiPetLabels.append(ui->opponents_pet_5);
}

//更新单个宠物图片实现
void QtBattleView::updatePetDisplay(int index, bool isPlayer, const Pet* pet)
{
    if (!pet) return;

    QLabel* petLabel = isPlayer ? _playerPetLabels.value(index) : _aiPetLabels.value(index);
    if (!petLabel) return;

    petLabel->setPixmap(QPixmap(QString(":/Pet/photo/Pet/%1.png").arg(pet->getName())));

    petLabel->setScaledContents(true); // 关键：启用内容自适应

    // 2. 显示血量和攻击力（可以用tooltip或者额外label）
    QString tooltip = QString("%1\nHP: %2\nATK: %3")
                          .arg(QString::fromStdString(pet->getName()))
                          .arg(pet->getHP())
                          .arg(pet->getAttack());

    if (pet->hasArmor()) tooltip += "\n🛡️护甲";
    if (pet->hasMelonShield()) tooltip += "\n🍉西瓜护盾";
    if (pet->canRevive()) tooltip += "\n🍄复活";

    petLabel->setToolTip(tooltip);
}

//更新战斗场景实现
void QtBattleView::updateBattleDisplay()
{
    if (!_player) return;

            // 更新玩家宠物显示
    for (int i = 0; i < _playerPetLabels.size(); ++i) {
        if (i < _player->getPetCount()) {
            Pet* pet = _player->getPetAt(i);
            updatePetDisplay(i, true, pet);  // true表示是玩家宠物
        }
    }

            // 更新AI宠物显示
    for (int i = 0; i < _aiPetLabels.size(); ++i) {
        if (i < static_cast<int>(_aiTeam.size()) && _aiTeam[i]) {
            updatePetDisplay(i, false, _aiTeam[i].get());  // false表示是AI宠物
        }
    }
    setUpdatesEnabled(true);
    update();  // 只更新一次
}

//高亮三步走
void QtBattleView::highlightAttacker(int index, bool isPlayer)
{
    clearHighlights();

    auto& labels = isPlayer ? _playerPetLabels : _aiPetLabels;
    //待实现
    //if (index >= 0 && index < labels.size()) {
    //    labels[index]->setStyleSheet("border: 4px solid gold;");
    //}
}

void QtBattleView::highlightDefender(int index, bool isPlayer)
{
    auto& labels = isPlayer ? _playerPetLabels : _aiPetLabels;
    //待实现
    // if (index >= 0 && index < labels.size()) {
    //     labels[index]->setStyleSheet("border: 4px solid orange;");
    // }
}

void QtBattleView::clearHighlights()
{
   //待实现
   // 恢复默认样式
   // for (auto* label : _playerPetLabels) {
   //     label->setStyleSheet("border: 2px solid green;");
   // }
   // for (auto* label : _aiPetLabels) {
   //     label->setStyleSheet("border: 2px solid red;");
   // }
}

QtBattleView::~QtBattleView()
{
    delete ui;
}

//按开始按钮
void QtBattleView::on_start_button_clicked()
{
    _battleStarted = true;

    // 创建玩家宠物的副本用于战斗
    std::vector<std::unique_ptr<Pet>> playerPetsCopy;
    for (int i = 0; i < _player->getPetCount(); ++i) {
        Pet* originalPet = _player->getPetAt(i);
        if (originalPet) {
            // 创建宠物副本（需要Pet类有拷贝构造函数）
            auto petCopy = std::make_unique<Pet>(*originalPet);
            playerPetsCopy.push_back(std::move(petCopy));
        }
    }

    // 创建AI宠物的副本用于战斗
    std::vector<std::unique_ptr<Pet>> aiPetsCopy;
    for (size_t i = 0; i < _aiTeam.size(); ++i) {
        if (_aiTeam[i]) {
            qDebug() << "复制AI宠物" << i << ":" << _aiTeam[i]->getName().c_str();

            // 使用拷贝构造函数创建副本
            auto petCopy = std::make_unique<Pet>(*_aiTeam[i]);
            aiPetsCopy.push_back(std::move(petCopy));
        }
    }

    qDebug() << "玩家宠物复制完成，数量:" << playerPetsCopy.size();
    qDebug() << "AI宠物复制完成，数量:" << aiPetsCopy.size();

    // 初始化战斗引擎
    _battleEngine.initialize(playerPetsCopy, aiPetsCopy);

    // 设置事件回调
    _battleEngine.setEventCallback([this](const BattleEvent& event) {
        onBattleEvent(event);
    });

    // 触发战斗开始事件
    _battleEngine.startBattleManual();

    ui->start_button->setEnabled(false);
    QGraphicsOpacityEffect *iconEffect = new QGraphicsOpacityEffect(this);
    iconEffect->setOpacity(0.5); // 50% 透明度
    ui->start->setGraphicsEffect(iconEffect);
    ui->start_font->setStyleSheet("color: rgba(255, 255, 255, 0.5);");

    ui->auto_play_button->setEnabled(true);
    ui->forward_button->setEnabled(true);
}

//按自动播放按钮
void QtBattleView::on_auto_play_button_clicked()
{
    if (_autoBattle)
    {
        // 停止自动战斗
        _autoBattle = false;
        _autoTimer->stop();
        qDebug() << "停止自动播放";

        // 改变自动播放图标及文本
        ui->auto_play->setPixmap(QPixmap(":/else/photo/Refresh.png"));
        ui->auto_play_font->setText("<html><head/><body><p><span style=\" font-size:11pt; font-weight:700;\">自动播放</span></p></body></html>");
        // 恢复按钮透明度
        ui->forward->setGraphicsEffect(nullptr);
        ui->forward_font->setStyleSheet("color: white;");
        ui->forward_button->setEnabled(true);
    }
    else
    {
        // 开始自动战斗
        _autoBattle = true;

        // 设置按钮半透明效果
        QGraphicsOpacityEffect *iconEffect_2 = new QGraphicsOpacityEffect(this);
        iconEffect_2->setOpacity(0.5);
        ui->forward->setGraphicsEffect(iconEffect_2);
        ui->forward_font->setStyleSheet("color: rgba(255, 255, 255, 0.5);");
        ui->forward_button->setEnabled(false);

        // 自动播放图标与文字改变
        ui->auto_play->setPixmap(QPixmap(":/else/photo/Pause.png"));
        ui->auto_play_font->setText("<html><head/><body><p><span style=\" font-size:11pt; font-weight:700;\">暂停</span></p></body></html>");

        _autoTimer->start(1500);  // 每1.5秒执行一步
        // 立即执行第一步
        qDebug() << "立即执行第一步";
        onAutoStep();
    }
}

//按单步执行按钮
void QtBattleView::on_forward_button_clicked()
{
    // 直接执行战斗步骤
    bool hasMore = _battleEngine.executeSingleStep();

    if (!hasMore)
    {
        // 战斗结束
        BattleResult result = _battleEngine.getResult();
        emit battleFinished(result);

        ui->auto_play_button->setEnabled(false);
        ui->forward_button->setEnabled(false);
    }

    // 延迟更新显示，避免阻塞
    QTimer::singleShot(10, this, [this]() {
        updateBattleDisplay();
    });
}

//实现自动执行
void QtBattleView::onAutoStep()
{
    on_forward_button_clicked();

    if (!_battleEngine.isInBattle())
    {
        _autoTimer->stop();
        _autoBattle = false;
    }
}

//实现对战
void QtBattleView::onBattleEvent(const BattleEvent& event)
{
    // 直接处理事件，但标记需要更新显示
    switch (event.type)
    {
    case BattleEventType::BattleStart:
        break;

    case BattleEventType::TurnStart:
        highlightAttacker(event.attackerIndex, event.isPlayer1);
        highlightDefender(event.defenderIndex, !event.isPlayer1);
        _pendingDisplayUpdate = true;
        break;

    case BattleEventType::Attack:
        break;

    case BattleEventType::TakeDamage:
        _pendingDisplayUpdate = true;
        break;

    case BattleEventType::PetDeath:
        _pendingDisplayUpdate = true;
        break;

    case BattleEventType::SkillTrigger:
        _pendingDisplayUpdate = true;
        break;

    case BattleEventType::BattleEnd:
        clearHighlights();
        _pendingDisplayUpdate = true;
        break;
    }

    // 延迟更新显示，避免频繁重绘导致卡顿
    if (_pendingDisplayUpdate)
    {
        _pendingDisplayUpdate = false;
        QTimer::singleShot(10, this, [this]() {
            updateBattleDisplay();
        });
    }
}
