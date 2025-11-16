#ifndef QTBATTLEVIEW_H
#define QTBATTLEVIEW_H

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

namespace Ui
{
class QtBattleView;
}

class QtBattleView : public QWidget
{
    Q_OBJECT

public:
    explicit QtBattleView(QWidget* parent = nullptr);
    ~QtBattleView();
    QtBattleView(Player* player, QWidget* parent = nullptr);

    // 开始新战斗
    void startNewBattle();

private slots:
    void on_start_button_clicked();

    void on_auto_play_button_clicked();

    void on_forward_button_clicked();

private:
    Ui::QtBattleView* ui;
    BattleEngine _battleEngine;
    Player* _player;

    // AI对手的队伍
    std::vector<std::unique_ptr<Pet>> _aiTeam;

    // 状态
    bool _battleStarted;
    bool _autoBattle;
    QTimer* _autoTimer;
    bool _pendingDisplayUpdate;

    void updateBattleDisplay();
    void highlightAttacker(int index, bool isPlayer);
    void highlightDefender(int index, bool isPlayer);
    void clearHighlights();
    void setupPetDisplays();             // 创建宠物显示区域
    void updatePetVisuals(int index, bool isPlayer, const Pet* pet); // 更新单个宠物显示
    void playAttackAnimation(int attackerIdx, bool isPlayerAttacker,
                             int defenderIdx, bool isPlayerDefender); // 攻击动画
    void playDamageEffect(int targetIdx, bool isPlayer, int damage); // 伤害效果
    void playDeathAnimation(int petIdx, bool isPlayer);              // 死亡动画

    // 生成AI对手
    void generateAITeam(int difficulty);

};

#endif  // QTBATTLEVIEW_H
