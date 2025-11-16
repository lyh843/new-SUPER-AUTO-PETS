#include "qtbattleview.h"
#include "ui_qtbattleview.h"
#include "../model/Pet.hpp"
#include <QMessageBox>
#include <QScrollBar>
#include <QTextCursor>
#include <random>
#include <QPainter>        // 添加这行
#include <QDebug>          // 添加这行用于调试输出
#include <QFont>           // 添加这行

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
    connect(ui->start_button, &QPushButton::clicked, this, &QtBattleView::on_start_button_clicked);
    connect(ui->auto_play_button, &QPushButton::clicked, this, &QtBattleView::on_auto_play_button_clicked);
    connect(ui->forward_button, &QPushButton::clicked, this, &QtBattleView::on_forward_button_clicked);
    connect(_autoTimer, &QTimer::timeout, this, &QtBattleView::onAutoStep);

    setupPetDisplays();
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

    // 初始化战斗引擎
    _battleEngine.initialize(_player->getPets(), _aiTeam);

    // 设置事件回调
    _battleEngine.setEventCallback([this](const BattleEvent& event) {
        onBattleEvent(event);
    });

    // 触发战斗开始事件
    _battleEngine.startBattleManual();

    ui->start_button->setEnabled(false);
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
        // 按键改变透明度待实现
        // _autoButton->setText("⏩ 自动战斗");
        ui->forward_button->setEnabled(true);
    }
    else
    {
        // 开始自动战斗
        _autoBattle = true;
        // 按键改变透明度待实现
        // _autoButton->setText("⏸️ 暂停");
        ui->forward_button->setEnabled(false);
        _autoTimer->start(1500);  // 每1.5秒执行一步
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

