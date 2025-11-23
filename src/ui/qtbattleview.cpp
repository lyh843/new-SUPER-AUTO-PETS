#include "qtbattleview.h"
#include "ui_qtbattleview.h"
#include "../model/Pet.hpp"
#include <QMessageBox>
#include <QScrollBar>
#include <QTextCursor>
#include <random>
#include <QPropertyAnimation>   // 动画属性
#include <QSequentialAnimationGroup> // 动画序列
#include <QParallelAnimationGroup> // 实现同时动画
#include <QPoint>               // 坐标点
#include <QEasingCurve>         // 缓动曲线，让动画更自然
#include <QCoreApplication>

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
    _pendingBattleEnd = false;
    _activeAnimationCount = 0;
    _autoTimer->stop();

    // 生成AI对手
    generateAITeam(_player->getRound());

    updateBattleDisplay();

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

// 建立展示宠物的容器
void QtBattleView::setupPetDisplays()
{
    // 清空容器
    _playerPetLabels.clear();
    _aiPetLabels.clear();
    _playerPetStatusLabels.clear(); // 清空状态图标签
    _aiPetsStatusLabels.clear();    // 清空状态图标签
    _playerAttackLabels.clear();    // 清空容器
    _playerHPLabels.clear();        // 清空容器
    _aiAttackLabels.clear();        // 清空容器
    _aiHPLabels.clear();            // 清空容器

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
        petLabel->hide();    // 宠物死亡或位置为空时，隐藏所有相关标签
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

void QtBattleView::playAttackAnimation(int attackerIdx, bool isPlayerAttacker,
                                       int defenderIdx, bool isPlayerDefender)
{
    // [修复: 统一标签获取逻辑]
    // 统一将第一个索引视为 P1 宠物的索引，第二个索引视为 P2 宠物的索引
    // 这与 BattleEngine 中固定的索引发送方式 (P1, P2, true) 保持一致。

    QLabel* playerPetLabel = nullptr;
    QLabel* aiPetLabel = nullptr;

    int p1PetIdx = attackerIdx;
    int p2PetIdx = defenderIdx;

    // 1. 获取 P1 (左侧) 宠物标签
    if (p1PetIdx >= 0 && p1PetIdx < _playerPetLabels.size()) {
        playerPetLabel = _playerPetLabels[p1PetIdx];
    }

    // 2. 获取 P2 (右侧/AI) 宠物标签
    if (p2PetIdx >= 0 && p2PetIdx < _aiPetLabels.size()) {
        aiPetLabel = _aiPetLabels[p2PetIdx];
    }

    // 检查标签有效性 (其余代码保持不变)
    if (!playerPetLabel || !aiPetLabel || playerPetLabel->isHidden() || aiPetLabel->isHidden()) {
        qDebug() << "Attack animation skipped: Pet labels not found or hidden.";
        return;
    }

    // 使用 geometry() 获取位置和大小，更可靠
    QRect p1Rect = playerPetLabel->geometry();
    QRect p2Rect = aiPetLabel->geometry();

    QPoint p1StartPos = p1Rect.topLeft();
    QPoint p2StartPos = p2Rect.topLeft();

    qDebug() << "P1 Start Pos:" << p1StartPos << "P2 Start Pos:" << p2StartPos;

    // 计算对撞点：两只宠物的中心点
    QPoint p1Center = p1Rect.center();
    QPoint p2Center = p2Rect.center();

    QPoint collisionPoint;
    collisionPoint.setX((p1Center.x() + p2Center.x()) / 2);
    collisionPoint.setY((p1Center.y() + p2Center.y()) / 2);

    // 调整对撞点，让宠物不完全重叠
    QPoint p1AttackPos = p1StartPos + (collisionPoint - p1Center) * 0.8;
    QPoint p2AttackPos = p2StartPos + (collisionPoint - p2Center) * 0.8;

    qDebug() << "P1 Attack Pos:" << p1AttackPos << "P2 Attack Pos:" << p2AttackPos;

    const int ANIMATION_DURATION = 300; // 稍微延长动画时间

    // 为 P1 (左侧) 宠物创建动画组 (冲刺 -> 返回)
    QSequentialAnimationGroup* p1Sequence = new QSequentialAnimationGroup(this);

    // P1 冲刺
    QPropertyAnimation* p1Move = new QPropertyAnimation(playerPetLabel, "pos", this);
    p1Move->setDuration(ANIMATION_DURATION);
    p1Move->setStartValue(p1StartPos);
    p1Move->setEndValue(p1AttackPos);
    p1Move->setEasingCurve(QEasingCurve::OutQuad);
    p1Sequence->addAnimation(p1Move);

    // P1 返回
    QPropertyAnimation* p1Return = new QPropertyAnimation(playerPetLabel, "pos", this);
    p1Return->setDuration(ANIMATION_DURATION);
    p1Return->setStartValue(p1AttackPos);
    p1Return->setEndValue(p1StartPos);
    p1Return->setEasingCurve(QEasingCurve::InQuad);
    p1Sequence->addAnimation(p1Return);


    // 为 P2 (右侧) 宠物创建动画组 (冲刺 -> 返回)
    QSequentialAnimationGroup* p2Sequence = new QSequentialAnimationGroup(this);

    // P2 冲刺
    QPropertyAnimation* p2Move = new QPropertyAnimation(aiPetLabel, "pos", this);
    p2Move->setDuration(ANIMATION_DURATION);
    p2Move->setStartValue(p2StartPos);
    p2Move->setEndValue(p2AttackPos);
    p2Move->setEasingCurve(QEasingCurve::OutQuad);
    p2Sequence->addAnimation(p2Move);

    // P2 返回
    QPropertyAnimation* p2Return = new QPropertyAnimation(aiPetLabel, "pos", this);
    p2Return->setDuration(ANIMATION_DURATION);
    p2Return->setStartValue(p2AttackPos);
    p2Return->setEndValue(p2StartPos);
    p2Return->setEasingCurve(QEasingCurve::InQuad);
    p2Sequence->addAnimation(p2Return);


    // 并行播放 P1 和 P2 的动画序列
    QParallelAnimationGroup* parallelGroup = new QParallelAnimationGroup(this);
    parallelGroup->addAnimation(p1Sequence);
    parallelGroup->addAnimation(p2Sequence);
    qDebug()<<"播放动画！"<<_activeAnimationCount;

    // 启动时增加计数
    _activeAnimationCount++;

    // 播放动画并在完成后自动清理和更新显示
    connect(parallelGroup, &QParallelAnimationGroup::finished, this, [this, parallelGroup]() {
        // [关键代码] 完成时减少计数并检查是否需要更新显示
        _activeAnimationCount--;
        if (_activeAnimationCount == 0) {
            if (_pendingDisplayUpdate) {
                // 清除标记，执行显示更新（死亡宠物消失，新宠物顶上）
                _pendingDisplayUpdate = false;
                updateBattleDisplay();
            }

            // 【关键修改】在动画结束并显示更新后，检查并处理战斗结束逻辑
            handleBattleEndActions();
        }
        parallelGroup->deleteLater();
    });

    parallelGroup->start();
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
            // 使用拷贝构造函数创建副本
            auto petCopy = std::make_unique<Pet>(*_aiTeam[i]);
            aiPetsCopy.push_back(std::move(petCopy));
        }
    }

    // 初始化战斗引擎
    _battleEngine.initialize(playerPetsCopy, aiPetsCopy, _player);

    // 设置事件回调
    _battleEngine.setEventCallback([this](const BattleEvent& event) {
        onBattleEvent(event);
    });



    // 触发战斗开始事件
    _battleEngine.startBattleManual();
    updateBattleDisplay();

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
        onAutoStep();
    }
}

//按单步执行按钮
void QtBattleView::on_forward_button_clicked()
{
    if (!_battleEngine.isInBattle())
        return;

    clearHighlights();

    // 执行单步战斗，这会触发事件链，包括 BattleEnd
    _battleEngine.executeSingleStep();
    
    // 如果战斗已经结束且没有动画在播放，立即处理结束逻辑
    if (!_battleEngine.isInBattle() && _activeAnimationCount == 0)
    {
        handleBattleEndActions();
    }
}

void QtBattleView::handleBattleEndActions()
{
    // 如果没有结束事件在等待，或者动画还在播放，则不执行
    if (!_pendingBattleEnd || _activeAnimationCount > 0) return;

    // 清除标记，表示战斗结束逻辑已开始执行
    _pendingBattleEnd = false;

    // 检查战斗是否真的结束了
    if (!_battleEngine.isInBattle())
    {
        // 战斗结束，获取结果并发出信号
        BattleResult result = _battleEngine.getResult();
        emit battleFinished(result);

        // 禁用所有战斗控制按钮
        ui->auto_play_button->setEnabled(false);
        ui->auto_play_button->setCursor(Qt::ArrowCursor);
        ui->forward_button->setEnabled(false);
        ui->forward_button->setCursor(Qt::ArrowCursor);
        
        // 停止自动战斗
        if (_autoBattle) {
            _autoTimer->stop();
            _autoBattle = false;
        }
    }
}

//实现自动执行
void QtBattleView::onAutoStep()
{
    // 如果战斗已经结束，停止自动战斗
    if (!_battleEngine.isInBattle())
    {
        _autoTimer->stop();
        _autoBattle = false;
        // 如果战斗结束且没有动画在播放，处理结束逻辑
        if (_activeAnimationCount == 0)
        {
            handleBattleEndActions();
        }
        return;
    }

    on_forward_button_clicked();

    // 再次检查战斗是否结束（可能在执行单步后结束）
    if (!_battleEngine.isInBattle())
    {
        _autoTimer->stop();
        _autoBattle = false;
        // 如果战斗结束且没有动画在播放，处理结束逻辑
        if (_activeAnimationCount == 0)
        {
            handleBattleEndActions();
        }
    }
}

//实现对战
void QtBattleView::onBattleEvent(const BattleEvent& event)
{
    // 用于标记本次事件是否触发了需要更新显示的改动
    bool shouldMarkUpdate = false;

    switch (event.type)
    {
    case BattleEventType::BattleStart:
        break;

    case BattleEventType::TurnStart:
        highlightAttacker(event.attackerIndex, event.isPlayer1);
        highlightDefender(event.defenderIndex, !event.isPlayer1);
        break;

    case BattleEventType::Attack:
        // 1. 触发对撞动画
        playAttackAnimation(event.attackerIndex, event.isPlayer1,
                            event.defenderIndex, !event.isPlayer1);
        // 注意：这里不设置 shouldMarkUpdate。动画结束后，其回调会负责最终的更新。
        break;

    case BattleEventType::TakeDamage:
    case BattleEventType::PetDeath:
    case BattleEventType::SkillTrigger:
        // 2. 这些事件都会导致数据变化（血量/死亡/状态）
        shouldMarkUpdate = true;
        break;

    case BattleEventType::BattleEnd:
        clearHighlights();
        shouldMarkUpdate = true;
        _pendingBattleEnd = true; // 【关键修改】标记战斗结束等待处理
        break;
    }

    if (shouldMarkUpdate)
    {
        // 3. 标记需要更新（供动画结束回调使用）
        _pendingDisplayUpdate = true;

        // 4. 如果当前没有动画在播放，则立即更新显示。
        if (_activeAnimationCount == 0)
        {
            // 清除标记，并执行更新
            _pendingDisplayUpdate = false;
            updateBattleDisplay();
            // 【关键修改】在 UI 更新后，检查并处理战斗结束逻辑
            handleBattleEndActions();
        }
        // 否则，更新将被延迟，等待 playAttackAnimation 中的回调函数执行。
    }

}
