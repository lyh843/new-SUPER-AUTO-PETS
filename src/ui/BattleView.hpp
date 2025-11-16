#pragma once

#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QTimer>
#include <vector>
#include <memory>
#include "../engine/BattleEngine.hpp"
#include "../model/Player.hpp"

// 宠物战斗卡片显示
class BattlePetCard : public QWidget
{
    Q_OBJECT

private:
    QLabel* _nameLabel;
    QLabel* _statsLabel;
    QLabel* _statusLabel;
    int _index;

public:
    BattlePetCard(int index, QWidget* parent = nullptr);
    void updatePet(const Pet* pet);
    void clear();
    void setHighlight(bool highlight);
};

// 战斗视图主类
class BattleView : public QWidget
{
    Q_OBJECT

private:
    BattleEngine _battleEngine;
    Player* _player;
    
    // AI对手的队伍
    std::vector<std::unique_ptr<Pet>> _aiTeam;

    // UI 组件
    QLabel* _titleLabel;
    QTextEdit* _battleLog;
    
    // 玩家队伍显示
    QVector<BattlePetCard*> _playerPetCards;
    QLabel* _playerLabel;
    
    // AI队伍显示
    QVector<BattlePetCard*> _aiPetCards;
    QLabel* _aiLabel;
    
    // 按钮
    QPushButton* _startButton;
    QPushButton* _autoButton;
    QPushButton* _stepButton;
    QPushButton* _backButton;
    
    // 状态
    bool _battleStarted;
    bool _autoBattle;
    QTimer* _autoTimer;
    bool _pendingDisplayUpdate;

    void setupUI();
    void updateBattleDisplay();
    void appendLog(const QString& message);
    void highlightAttacker(int index, bool isPlayer);
    void highlightDefender(int index, bool isPlayer);
    void clearHighlights();
    
    // 生成AI对手
    void generateAITeam(int difficulty);

private slots:
    void onStartClicked();
    void onAutoClicked();
    void onStepClicked();
    void onBackClicked();
    void onAutoStep();
    void onBattleEvent(const BattleEvent& event);

signals:
    void battleFinished(BattleResult result);
    void backToShop();

public:
    BattleView(Player* player, QWidget* parent = nullptr);
    ~BattleView() = default;
    
    // 开始新战斗
    void startNewBattle();
};
