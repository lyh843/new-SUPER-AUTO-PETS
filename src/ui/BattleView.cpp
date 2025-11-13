#include "BattleView.hpp"
#include "../model/Pet.hpp"
#include <QMessageBox>
#include <QScrollBar>
#include <random>

// ============= BattlePetCard 实现 =============

BattlePetCard::BattlePetCard(int index, QWidget* parent)
    : QWidget(parent)
    , _index(index)
{
    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(5, 5, 5, 5);
    layout->setSpacing(3);

    _nameLabel = new QLabel("空", this);
    _nameLabel->setAlignment(Qt::AlignCenter);
    _nameLabel->setStyleSheet("font-size: 14px; font-weight: bold;");

    _statsLabel = new QLabel("", this);
    _statsLabel->setAlignment(Qt::AlignCenter);
    _statsLabel->setStyleSheet("font-size: 12px;");

    _statusLabel = new QLabel("", this);
    _statusLabel->setAlignment(Qt::AlignCenter);
    _statusLabel->setStyleSheet("font-size: 10px; color: #888;");

    layout->addWidget(_nameLabel);
    layout->addWidget(_statsLabel);
    layout->addWidget(_statusLabel);

    setStyleSheet(
        "QWidget {"
        "    background-color: white; "
        "    border: 2px solid #ddd; "
        "    border-radius: 5px;"
        "}"
    );
    
    setFixedSize(120, 90);
}

void BattlePetCard::updatePet(const Pet* pet)
{
    if (!pet)
    {
        clear();
        return;
    }

    _nameLabel->setText(QString::fromStdString(pet->getName()));
    _statsLabel->setText(QString("⚔️%1 ❤️%2").arg(pet->getAttack()).arg(pet->getHP()));
    
    // 显示特殊状态
    QStringList status;
    if (pet->hasArmor()) status << "🛡️护甲";
    if (pet->hasMelonShield()) status << "🍉护盾";
    if (pet->canRevive()) status << "🍄复活";
    
    _statusLabel->setText(status.join(" "));
}

void BattlePetCard::clear()
{
    _nameLabel->setText("空");
    _statsLabel->setText("");
    _statusLabel->setText("");
}

void BattlePetCard::setHighlight(bool highlight)
{
    if (highlight)
    {
        setStyleSheet(
            "QWidget {"
            "    background-color: #fff3cd; "
            "    border: 3px solid #ffc107; "
            "    border-radius: 5px;"
            "}"
        );
    }
    else
    {
        setStyleSheet(
            "QWidget {"
            "    background-color: white; "
            "    border: 2px solid #ddd; "
            "    border-radius: 5px;"
            "}"
        );
    }
}

// ============= BattleView 实现 =============

BattleView::BattleView(Player* player, QWidget* parent)
    : QWidget(parent)
    , _player(player)
    , _battleStarted(false)
    , _autoBattle(false)
{
    _autoTimer = new QTimer(this);
    connect(_autoTimer, &QTimer::timeout, this, &BattleView::onAutoStep);
    
    setupUI();
}

void BattleView::setupUI()
{
    auto* mainLayout = new QVBoxLayout(this);

    // 标题
    _titleLabel = new QLabel("⚔️ 战斗场景", this);
    _titleLabel->setAlignment(Qt::AlignCenter);
    _titleLabel->setStyleSheet(
        "font-size: 32px; "
        "font-weight: bold; "
        "color: #dc3545; "
        "padding: 15px;"
    );
    mainLayout->addWidget(_titleLabel);

    // 战场布局
    auto* battleLayout = new QVBoxLayout();

    // AI队伍区域
    _aiLabel = new QLabel("🤖 对手队伍", this);
    _aiLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #666;");
    _aiLabel->setAlignment(Qt::AlignCenter);
    battleLayout->addWidget(_aiLabel);

    auto* aiTeamLayout = new QHBoxLayout();
    aiTeamLayout->setSpacing(10);
    for (int i = 0; i < 5; ++i)
    {
        auto* card = new BattlePetCard(i, this);
        _aiPetCards.append(card);
        aiTeamLayout->addWidget(card);
    }
    battleLayout->addLayout(aiTeamLayout);

    battleLayout->addSpacing(20);

    // 玩家队伍区域
    _playerLabel = new QLabel("👤 我方队伍", this);
    _playerLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #4CAF50;");
    _playerLabel->setAlignment(Qt::AlignCenter);
    battleLayout->addWidget(_playerLabel);

    auto* playerTeamLayout = new QHBoxLayout();
    playerTeamLayout->setSpacing(10);
    for (int i = 0; i < 5; ++i)
    {
        auto* card = new BattlePetCard(i, this);
        _playerPetCards.append(card);
        playerTeamLayout->addWidget(card);
    }
    battleLayout->addLayout(playerTeamLayout);

    mainLayout->addLayout(battleLayout);

    // 战斗日志
    auto* logLabel = new QLabel("📜 战斗日志", this);
    logLabel->setStyleSheet("font-size: 16px; font-weight: bold; padding-top: 10px;");
    mainLayout->addWidget(logLabel);

    _battleLog = new QTextEdit(this);
    _battleLog->setReadOnly(true);
    _battleLog->setMaximumHeight(150);
    _battleLog->setStyleSheet(
        "QTextEdit {"
        "    background-color: #f8f9fa; "
        "    border: 2px solid #ddd; "
        "    border-radius: 5px; "
        "    padding: 5px; "
        "    font-size: 13px;"
        "}"
    );
    mainLayout->addWidget(_battleLog);

    // 操作按钮
    auto* buttonLayout = new QHBoxLayout();

    _startButton = new QPushButton("▶️ 开始战斗", this);
    _startButton->setStyleSheet(
        "QPushButton {"
        "    font-size: 16px; "
        "    font-weight: bold; "
        "    background-color: #28a745; "
        "    color: white; "
        "    border: none; "
        "    border-radius: 5px; "
        "    padding: 10px 20px;"
        "}"
        "QPushButton:hover { background-color: #218838; }"
        "QPushButton:disabled { background-color: #6c757d; }"
    );
    connect(_startButton, &QPushButton::clicked, this, &BattleView::onStartClicked);
    buttonLayout->addWidget(_startButton);

    _autoButton = new QPushButton("⏩ 自动战斗", this);
    _autoButton->setEnabled(false);
    _autoButton->setStyleSheet(
        "QPushButton {"
        "    font-size: 16px; "
        "    font-weight: bold; "
        "    background-color: #ffc107; "
        "    color: white; "
        "    border: none; "
        "    border-radius: 5px; "
        "    padding: 10px 20px;"
        "}"
        "QPushButton:hover { background-color: #e0a800; }"
        "QPushButton:disabled { background-color: #6c757d; }"
    );
    connect(_autoButton, &QPushButton::clicked, this, &BattleView::onAutoClicked);
    buttonLayout->addWidget(_autoButton);

    _stepButton = new QPushButton("⏯️ 单步执行", this);
    _stepButton->setEnabled(false);
    _stepButton->setStyleSheet(
        "QPushButton {"
        "    font-size: 16px; "
        "    font-weight: bold; "
        "    background-color: #17a2b8; "
        "    color: white; "
        "    border: none; "
        "    border-radius: 5px; "
        "    padding: 10px 20px;"
        "}"
        "QPushButton:hover { background-color: #138496; }"
        "QPushButton:disabled { background-color: #6c757d; }"
    );
    connect(_stepButton, &QPushButton::clicked, this, &BattleView::onStepClicked);
    buttonLayout->addWidget(_stepButton);

    _backButton = new QPushButton("⬅️ 返回商店", this);
    _backButton->setStyleSheet(
        "QPushButton {"
        "    font-size: 16px; "
        "    font-weight: bold; "
        "    background-color: #6c757d; "
        "    color: white; "
        "    border: none; "
        "    border-radius: 5px; "
        "    padding: 10px 20px;"
        "}"
        "QPushButton:hover { background-color: #5a6268; }"
    );
    connect(_backButton, &QPushButton::clicked, this, &BattleView::onBackClicked);
    buttonLayout->addWidget(_backButton);

    mainLayout->addLayout(buttonLayout);

    setStyleSheet("background-color: #f0f0f0;");
}

void BattleView::startNewBattle()
{
    _battleStarted = false;
    _autoBattle = false;
    _autoTimer->stop();
    
    _battleLog->clear();
    appendLog("准备开始新的战斗...");
    
    // 生成AI对手
    generateAITeam(_player->getRound());
    
    updateBattleDisplay();
    
    _startButton->setEnabled(true);
    _autoButton->setEnabled(false);
    _stepButton->setEnabled(false);
}

void BattleView::generateAITeam(int difficulty)
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
    
    appendLog(QString("AI对手生成完毕！共有 %1 只宠物").arg(_aiTeam.size()));
}

void BattleView::updateBattleDisplay()
{
    // 更新玩家队伍显示
    for (int i = 0; i < 5; ++i)
    {
        if (i < _player->getPetCount())
        {
            _playerPetCards[i]->updatePet(_player->getPetAt(i));
        }
        else
        {
            _playerPetCards[i]->clear();
        }
    }

    // 更新AI队伍显示
    for (int i = 0; i < 5; ++i)
    {
        if (i < static_cast<int>(_aiTeam.size()))
        {
            _aiPetCards[i]->updatePet(_aiTeam[i].get());
        }
        else
        {
            _aiPetCards[i]->clear();
        }
    }
}

void BattleView::appendLog(const QString& message)
{
    _battleLog->append(message);
    // 自动滚动到底部
    _battleLog->verticalScrollBar()->setValue(_battleLog->verticalScrollBar()->maximum());
}

void BattleView::clearHighlights()
{
    for (auto* card : _playerPetCards)
    {
        card->setHighlight(false);
    }
    for (auto* card : _aiPetCards)
    {
        card->setHighlight(false);
    }
}

void BattleView::highlightAttacker(int index, bool isPlayer)
{
    clearHighlights();
    auto& cards = isPlayer ? _playerPetCards : _aiPetCards;
    if (index >= 0 && index < cards.size())
    {
        cards[index]->setHighlight(true);
    }
}

void BattleView::highlightDefender(int index, bool isPlayer)
{
    auto& cards = isPlayer ? _playerPetCards : _aiPetCards;
    if (index >= 0 && index < cards.size())
    {
        cards[index]->setHighlight(true);
    }
}

void BattleView::onStartClicked()
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
    
    appendLog("战斗已准备就绪！点击'单步执行'或'自动战斗'开始战斗。");
    
    _startButton->setEnabled(false);
    _autoButton->setEnabled(true);
    _stepButton->setEnabled(true);
}

void BattleView::onAutoClicked()
{
    if (_autoBattle)
    {
        // 停止自动战斗
        _autoBattle = false;
        _autoTimer->stop();
        _autoButton->setText("⏩ 自动战斗");
        _stepButton->setEnabled(true);
    }
    else
    {
        // 开始自动战斗
        _autoBattle = true;
        _autoButton->setText("⏸️ 暂停");
        _stepButton->setEnabled(false);
        _autoTimer->start(1500);  // 每1.5秒执行一步
    }
}

void BattleView::onStepClicked()
{
    bool hasMore = _battleEngine.executeSingleStep();
    
    if (!hasMore)
    {
        // 战斗结束
        BattleResult result = _battleEngine.getResult();
        emit battleFinished(result);
        
        _autoButton->setEnabled(false);
        _stepButton->setEnabled(false);
    }
    
    updateBattleDisplay();
}

void BattleView::onAutoStep()
{
    onStepClicked();
    
    if (!_battleEngine.isInBattle())
    {
        _autoTimer->stop();
        _autoBattle = false;
        _autoButton->setText("⏩ 自动战斗");
    }
}

void BattleView::onBackClicked()
{
    if (_battleStarted && _battleEngine.isInBattle())
    {
        auto reply = QMessageBox::question(
            this,
            "确认退出",
            "战斗还在进行中，确定要返回商店吗？",
            QMessageBox::Yes | QMessageBox::No
        );
        
        if (reply == QMessageBox::No)
        {
            return;
        }
    }
    
    emit backToShop();
}

void BattleView::onBattleEvent(const BattleEvent& event)
{
    switch (event.type)
    {
    case BattleEventType::BattleStart:
        appendLog("=== " + event.message + " ===");
        break;
        
    case BattleEventType::TurnStart:
        appendLog(event.message);
        highlightAttacker(event.attackerIndex, event.isPlayer1);
        highlightDefender(event.defenderIndex, !event.isPlayer1);
        break;
        
    case BattleEventType::Attack:
        appendLog("  ➤ " + event.message);
        break;
        
    case BattleEventType::TakeDamage:
        appendLog("    " + event.message);
        updateBattleDisplay();
        break;
        
    case BattleEventType::PetDeath:
        appendLog("  💀 " + event.message);
        break;
        
    case BattleEventType::SkillTrigger:
        appendLog("  ✨ " + event.message);
        break;
        
    case BattleEventType::BattleEnd:
        appendLog("=== " + event.message + " ===");
        clearHighlights();
        break;
    }
    
    updateBattleDisplay();
}
