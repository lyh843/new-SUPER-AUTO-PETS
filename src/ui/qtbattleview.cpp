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

    // 设置透明度效果
    QGraphicsOpacityEffect *iconEffect_1 = new QGraphicsOpacityEffect(this);
    QGraphicsOpacityEffect *iconEffect_2 = new QGraphicsOpacityEffect(this);
    iconEffect_1->setOpacity(0.5);
    iconEffect_2->setOpacity(0.5);
    ui->auto_play->setGraphicsEffect(iconEffect_1);
    ui->forward->setGraphicsEffect(iconEffect_2);
    ui->auto_play_font->setStyleSheet("color: rgba(255, 255, 255, 0.5);");
    ui->forward_font->setStyleSheet("color: rgba(255, 255, 255, 0.5);");

    // 贴上玩家数据
    ui->heart_left_num->setText(QString::number(_player->getLives()));
    ui->heart_right_num->setText(QString::number(_player->getLives()));
    ui->hourglass_left_num->setText(QString::number(_player->getRound()));
    ui->hour_glass_right_num->setText(QString::number(_player->getRound()));
    ui->trophy_left_num->setText(QString::number(_player->getPrize()));
    ui->trophy_right_num->setText(QString::number(_player->getPrize()));

    // 恢复文字原始样式
    ui->start_font->setStyleSheet("color: white;");

    ui->start_button->setEnabled(true);
    ui->start_button->setCursor(Qt::PointingHandCursor);
    ui->auto_play_button->setEnabled(false);
    ui->auto_play_button->setCursor(Qt::ArrowCursor);
    ui->forward_button->setEnabled(false);
    ui->forward_button->setCursor(Qt::ArrowCursor);

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
        int petType = std::uniform_int_distribution<>(0, 12)(gen);

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
            case 8: pet = std::make_unique<Duck>(3, 2, 1, 1); break;
            case 9: pet = std::make_unique<Kangaroo>(3, 2, 1, 3); break;
            case 10: pet = std::make_unique<Dodo>(2, 4, 1, 3); break;
            case 11: pet = std::make_unique<Blowfish>(6, 3, 1, 4); break;
            case 12: pet = std::make_unique<Skunk>(5, 3, 1, 4); break;
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
    _playerPetStatusLabels.clear(); // 清空状态图标签
    _aiPetsStatusLabels.clear();    // 清空状态图标签
    _playerAttackLabels.clear();    // 新增: 清空容器
    _playerHPLabels.clear();        // 新增: 清空容器
    _aiAttackLabels.clear();        // 新增: 清空容器
    _aiHPLabels.clear();            // 新增: 清空容器

            // 使用UI中预留的宠物位置 (顺序为从右到左: 5, 4, 3, 2, 1)

    // 玩家宠物（从右到左）
    _playerPetLabels.append(ui->your_pet_5);
    _playerPetLabels.append(ui->your_pet_4);
    _playerPetLabels.append(ui->your_pet_3);
    _playerPetLabels.append(ui->your_pet_2);
    _playerPetLabels.append(ui->your_pet_1);

    // 玩家状态标签 (Status Image)
    _playerPetStatusLabels.append(ui->your_pet_5_status);
    _playerPetStatusLabels.append(ui->your_pet_4_status);
    _playerPetStatusLabels.append(ui->your_pet_3_status);
    _playerPetStatusLabels.append(ui->your_pet_2_status);
    _playerPetStatusLabels.append(ui->your_pet_1_status);

    // 玩家属性标签 (Attack)
    _playerAttackLabels.append(ui->your_Attack_5);
    _playerAttackLabels.append(ui->your_Attack_4);
    _playerAttackLabels.append(ui->your_Attack_3);
    _playerAttackLabels.append(ui->your_Attack_2);
    _playerAttackLabels.append(ui->your_Attack_1);

    // 玩家属性标签 (HP)
    _playerHPLabels.append(ui->your_HP_5);
    _playerHPLabels.append(ui->your_HP_4);
    _playerHPLabels.append(ui->your_HP_3);
    _playerHPLabels.append(ui->your_HP_2);
    _playerHPLabels.append(ui->your_HP_1);


    // AI 宠物（从左到右: 1, 2, 3, 4, 5)
    _aiPetLabels.append(ui->opponents_pet_1);
    _aiPetLabels.append(ui->opponents_pet_2);
    _aiPetLabels.append(ui->opponents_pet_3);
    _aiPetLabels.append(ui->opponents_pet_4);
    _aiPetLabels.append(ui->opponents_pet_5);

    // AI 状态标签 (Status Image)
    _aiPetsStatusLabels.append(ui->opponents_pet_1_status);
    _aiPetsStatusLabels.append(ui->opponents_pet_2_status);
    _aiPetsStatusLabels.append(ui->opponents_pet_3_status);
    _aiPetsStatusLabels.append(ui->opponents_pet_4_status);
    _aiPetsStatusLabels.append(ui->opponents_pet_5_status);

    // AI 属性标签 (Attack)
    _aiAttackLabels.append(ui->opponents_Attack_1);
    _aiAttackLabels.append(ui->opponents_Attack_2);
    _aiAttackLabels.append(ui->opponents_Attack_3);
    _aiAttackLabels.append(ui->opponents_Attack_4);
    _aiAttackLabels.append(ui->opponents_Attack_5);

    // AI 属性标签 (HP)
    _aiHPLabels.append(ui->opponents_HP_1);
    _aiHPLabels.append(ui->opponents_HP_2);
    _aiHPLabels.append(ui->opponents_HP_3);
    _aiHPLabels.append(ui->opponents_HP_4);
    _aiHPLabels.append(ui->opponents_HP_5);
}

//更新单个宠物图片及属性实现
void QtBattleView::updatePetDisplay(int index, bool isPlayer, const Pet* pet)
{

    QLabel* petLabel = isPlayer ? _playerPetLabels.value(index) : _aiPetLabels.value(index);
    QLabel* statusLabel = isPlayer ? _playerPetStatusLabels.value(index) : _aiPetsStatusLabels.value(index);
    QLabel* attackLabel = isPlayer ? _playerAttackLabels.value(index) : _aiAttackLabels.value(index);
    QLabel* hpLabel = isPlayer ? _playerHPLabels.value(index) : _aiHPLabels.value(index);

    if (!petLabel || !statusLabel || !attackLabel || !hpLabel) return;

    if (!pet) {
        petLabel->hide();    // 宠物死亡或位置为空时，清除并隐藏所有相关标签
        statusLabel->hide(); // 隐藏 status 图片
        attackLabel->hide(); // 隐藏攻击力数值
        hpLabel->hide();     // 隐藏生命值数值
        return;
    }

    // 宠物存在时：
    petLabel->show();
    statusLabel->show(); // 显示 status 图片
    attackLabel->show(); // 显示攻击力数值
    hpLabel->show();     // 显示生命值数值

    // 更新宠物图片 (保持不变)
    QPixmap originalPixmap(QString(":/Pet/photo/Pet/%1.png").arg(pet->getName()));

    // 如果是AI的宠物，进行水平翻转
    if (isPlayer) {
        QTransform transform;
        transform.scale(-1, 1);  // 水平翻转
        originalPixmap = originalPixmap.transformed(transform);
    }

    petLabel->setPixmap(originalPixmap);
    petLabel->setScaledContents(true); // 启用内容自适应

    // 更新 Attack 和 HP 数值
    attackLabel->setText(QString::number(pet->getAttack()));
    hpLabel->setText(QString::number(pet->getHP()));
}

//更新战斗场景实现
//更新战斗场景实现
void QtBattleView::updateBattleDisplay()
{
    if (!_player) return;

    clearHighlights();

    // 确定队伍数据源
    const std::vector<std::unique_ptr<Pet>>* aiTeamPtr;
    int playerTeamSize;

    if (_battleStarted) {
        // ========== 状态 1: 战斗已开始 (使用 BattleEngine 实时数据) ==========
        aiTeamPtr = &_battleEngine.getPlayer2Team();
        const auto& playerTeam = _battleEngine.getPlayer1Team();
        playerTeamSize = playerTeam.size();

        // 1. 更新玩家宠物显示
        for (int i = 0; i < _playerPetLabels.size(); ++i) {
            if (i < static_cast<int>(playerTeamSize)) {
                const Pet* pet = playerTeam[i].get();
                updatePetDisplay(i, true, pet); // updatePetDisplay 现在处理所有显示逻辑
            }
            else {
                updatePetDisplay(i, true, nullptr); // 隐藏所有相关标签
            }
        }

    } else {
        // ========== 状态 2: 战斗尚未开始 (使用 Player 商店队伍和 _aiTeam 成员) ==========
        aiTeamPtr = &_aiTeam;
        playerTeamSize = _player->getPetCount();

        // 1. 更新玩家宠物显示 (使用 _player 对象的队伍)
        for (int i = 0; i < _playerPetLabels.size(); ++i) {
            if (i < playerTeamSize) {
                Pet* pet = _player->getPetAt(i);
                updatePetDisplay(i, true, pet); // updatePetDisplay 现在处理所有显示逻辑
            }
            else {
                updatePetDisplay(i, true, nullptr); // 隐藏所有相关标签
            }
        }
    }

    // 2. 更新 AI 宠物显示 (统一使用 aiTeamPtr)
    for (int i = 0; i < _aiPetLabels.size(); ++i) {
        if (i < static_cast<int>(aiTeamPtr->size())) {
            const Pet* pet = (*aiTeamPtr)[i].get();
            updatePetDisplay(i, false, pet); // updatePetDisplay 现在处理所有显示逻辑
        }
        else {
            updatePetDisplay(i, false, nullptr); // 隐藏所有相关标签
        }
    }

    setUpdatesEnabled(true);
    update();
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
    _battleEngine.initialize(playerPetsCopy, aiPetsCopy, _player);

    // 设置事件回调
    _battleEngine.setEventCallback([this](const BattleEvent& event) {
        onBattleEvent(event);
    });

    // 触发战斗开始事件
    _battleEngine.startBattleManual();

    ui->start_button->setEnabled(false);
    ui->start_button->setCursor(Qt::ArrowCursor);
    QGraphicsOpacityEffect *iconEffect = new QGraphicsOpacityEffect(this);
    iconEffect->setOpacity(0.5); // 50% 透明度
    ui->start->setGraphicsEffect(iconEffect);
    ui->start_font->setStyleSheet("color: rgba(255, 255, 255, 0.5);");

    ui->auto_play->setGraphicsEffect(nullptr);
    ui->forward->setGraphicsEffect(nullptr);
    ui->auto_play_font->setStyleSheet("color: white");
    ui->forward_font->setStyleSheet("color: white");
    ui->auto_play_button->setEnabled(true);
    ui->auto_play_button->setCursor(Qt::PointingHandCursor);
    ui->forward_button->setEnabled(true);
    ui->forward_button->setCursor(Qt::PointingHandCursor);
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
        ui->forward_button->setCursor(Qt::PointingHandCursor);
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
        ui->forward_button->setCursor(Qt::ArrowCursor);

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
        ui->auto_play_button->setCursor(Qt::ArrowCursor);
        ui->forward_button->setEnabled(false);
        ui->forward_button->setCursor(Qt::ArrowCursor);
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
