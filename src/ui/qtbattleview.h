#ifndef QTBATTLEVIEW_H
#define QTBATTLEVIEW_H

#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGraphicsOpacityEffect>
#include <QTimer>
#include <vector>
#include <memory>
#include "../engine/BattleEngine.hpp"
#include "../model/Player.hpp"

namespace Ui
{
class QtBattleView;
}

class QtBattleView : public QWidget
{
    Q_OBJECT

public:
    ~QtBattleView();
    QtBattleView(Player* player, QWidget* parent = nullptr);

    // 开始新战斗
    void startNewBattle();

private slots:
    void on_start_button_clicked();
    void on_auto_play_button_clicked();
    void on_forward_button_clicked();
    void onAutoStep();
    void onBattleEvent(const BattleEvent& event);

private:
    Ui::QtBattleView* ui;
    BattleEngine _battleEngine;
    Player* _player;

    // AI对手的队伍
    std::vector<std::unique_ptr<Pet>> _aiTeam;

    // 宠物显示组件 - 存储指向UI中QLabel的指针
    QVector<QLabel*> _playerPetLabels;    // 玩家宠物显示标签
    QVector<QLabel*> _aiPetLabels;        // AI宠物显示标签
    QVector<QLabel*> _playerPetStatusLabels;    // 玩家宠物状态背景/图标标签
    QVector<QLabel*> _aiPetsStatusLabels;       // AI宠物状态背景/图标标签
    QVector<QLabel*> _playerAttackLabels;       // 玩家攻击力数值标签
    QVector<QLabel*> _playerHPLabels;           // 玩家生命值数值标签
    QVector<QLabel*> _aiAttackLabels;           // AI攻击力数值标签
    QVector<QLabel*> _aiHPLabels;               // AI生命值数值标签

    // 状态
    bool _battleStarted;
    bool _autoBattle;
    QTimer* _autoTimer;
    bool _pendingDisplayUpdate;

    void setupConnections();
    void updateBattleDisplay();
    void updatePetDisplay(int index, bool isPlayer, const Pet* pet);
    void highlightAttacker(int index, bool isPlayer);
    void highlightDefender(int index, bool isPlayer);
    void clearHighlights();
    void setupPetDisplays();             // 创建宠物显示区域
    void updatePetVisuals(int index, bool isPlayer, const Pet* pet); // 更新单个宠物显示
    void playAttackAnimation(int attackerIdx, bool isPlayerAttacker,
                             int defenderIdx, bool isPlayerDefender); // 攻击动画
    void playDamageEffect(int targetIdx, bool isPlayer, int damage); // 伤害效果
    void playDeathAnimation(int petIdx, bool isPlayer);              // 死亡动画

    QPixmap getPetPixmap(const Pet* pet);                            // 获取宠物图片

    // 生成AI对手
    void generateAITeam(int difficulty);

    //AI用来debug的
    QPixmap createColoredPixmap(const QString& petName);

signals:
    void battleFinished(BattleResult result);
    void backToShop();
};

#endif  // QTBATTLEVIEW_H
