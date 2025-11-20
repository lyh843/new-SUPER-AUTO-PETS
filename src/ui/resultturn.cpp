#include "resultturn.h"
#include "ui_resultturn.h"
#include <QPixmap>
#include "BattleView.hpp"

#include "ui/StartView.hpp"
#include "ui/QtShopview.h"
#include "ui/qtbattleview.h"
#include "ui/PetEncyclopediaView.hpp"
#include "ui/RecordsView.hpp"
#include "model/Player.hpp"
#include "engine/BattleEngine.hpp"

ResultTurn::ResultTurn(QWidget* parent) : QWidget(parent), ui(new Ui::ResultTurn)
{
    ui->setupUi(this);
    // QPixmap bkgnd_victory(":/else/photo/Victory.png");
    // QPixmap bkgnd_defeat(":/else/photo/Defeat.png");
    // QPixmap bkgnd_draw(":/else/photo/Draw.png");
    // QPixmap heart_icon(":/else/photo/Heart.png");
    // QPixmap heartbroken_icon(":/else/photo/HeartBroke.png");
    // bkgnd_victory = bkgnd_victory.scaled(this->size(), Qt::IgnoreAspectRatio);
    // bkgnd_defeat = bkgnd_defeat.scaled(this->size(), Qt::IgnoreAspectRatio);
}

void ResultTurn::loadingPicture(BattleResult result, Player* _player)
{
    QPixmap bkgnd_victory(":/else/photo/Victory.png");
    QPixmap bkgnd_defeat(":/else/photo/Defeat.png");
    QPixmap bkgnd_draw(":/else/photo/Draw.png");
    QPixmap heart_icon(":/else/photo/Heart.png");
    QPixmap heartbroken_icon(":/else/photo/HeartBroke.png");

    int playerLives = _player->getLives();

    if (result == BattleResult::Player1Win)
    {
        ui->label_background->setPixmap(bkgnd_victory);
    }
    else if (result == BattleResult::Player2Win)
    {
        ui->label_background->setPixmap(bkgnd_defeat);
    }
    else // Draw
    {
        ui->label_background->setPixmap(bkgnd_draw);
    }

    
    // 根据玩家生命值显示相应数量的图标
    if (playerLives >= 1) {
        ui->label_resultIcon_0->setPixmap(heart_icon);
    } else {
        ui->label_resultIcon_0->setPixmap(heartbroken_icon);
    }
    if (playerLives >= 2) {
        ui->label_resultIcon_1->setPixmap(heart_icon);
    } else {
        ui->label_resultIcon_1->setPixmap(heartbroken_icon);
    }
    if (playerLives >= 3) {
        ui->label_resultIcon_2->setPixmap(heart_icon);
    } else {
        ui->label_resultIcon_2->setPixmap(heartbroken_icon);
    }
    if (playerLives >= 4) {
        ui->label_resultIcon_3->setPixmap(heart_icon);
    } else {
        ui->label_resultIcon_3->setPixmap(heartbroken_icon);
    }
    if (playerLives >= 5) {
        ui->label_resultIcon_4->setPixmap(heart_icon);
    } else {
        ui->label_resultIcon_4->setPixmap(heartbroken_icon);
    }
    if (playerLives >= 6) {
        ui->label_resultIcon_5->setPixmap(heart_icon);
    } else {
        ui->label_resultIcon_5->setPixmap(heartbroken_icon);
    }
        

}

ResultTurn::~ResultTurn()
{
    delete ui;
}
