#include "resultturn.h"
#include "ui_resultturn.h"
#include <QPixmap>
#include "BattleView.hpp"
#include <QResizeEvent>  // 添加这个头文件

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
    
    // 设置窗口固定大小
    setFixedSize(1400, 800);
    
    // 设置背景标签的位置和大小（覆盖整个窗口）
    ui->label_background->setGeometry(0, 0, 1400, 800);
    ui->label_background->setScaledContents(true);  // 图片缩放以适应标签大小
    
    // 设置6个结果图标的位置和大小（左下方横向排列）
    int iconWidth = 60;   // 图标宽度
    int iconHeight = 60;  // 图标高度
    int startX = 50;      // 起始X坐标
    int startY = 700;     // 起始Y坐标（靠近底部）
    int spacing = 20;     // 图标间距
    
    // 设置每个图标的位置和大小
    ui->label_resultIcon_0->setGeometry(startX, startY, iconWidth, iconHeight);
    ui->label_resultIcon_1->setGeometry(startX + (iconWidth + spacing), startY, iconWidth, iconHeight);
    ui->label_resultIcon_2->setGeometry(startX + 2*(iconWidth + spacing), startY, iconWidth, iconHeight);
    ui->label_resultIcon_3->setGeometry(startX + 3*(iconWidth + spacing), startY, iconWidth, iconHeight);
    ui->label_resultIcon_4->setGeometry(startX + 4*(iconWidth + spacing), startY, iconWidth, iconHeight);
    
    // 设置图标缩放以适应标签大小
    ui->label_resultIcon_0->setScaledContents(true);
    ui->label_resultIcon_1->setScaledContents(true);
    ui->label_resultIcon_2->setScaledContents(true);
    ui->label_resultIcon_3->setScaledContents(true);
    ui->label_resultIcon_4->setScaledContents(true);
}

void ResultTurn::loadingPicture(BattleResult result, Player* _player)
{
    QPixmap bkgnd_victory(":/else/photo/Victory.png");
    QPixmap bkgnd_defeat(":/else/photo/Defeat.png");
    QPixmap bkgnd_draw(":/else/photo/Draw.png");
    QPixmap heart_icon(":/else/photo/Heart.png");
    QPixmap heartbroken_icon(":/else/photo/HeartBroke.png");

    int playerLives = _player->getLives();

    // 缩放背景图片以适应标签大小
    bkgnd_victory = bkgnd_victory.scaled(ui->label_background->size(), Qt::KeepAspectRatioByExpanding);
    bkgnd_defeat = bkgnd_defeat.scaled(ui->label_background->size(), Qt::KeepAspectRatioByExpanding);
    bkgnd_draw = bkgnd_draw.scaled(ui->label_background->size(), Qt::KeepAspectRatioByExpanding);
    
    // 缩放心形图标
    heart_icon = heart_icon.scaled(ui->label_resultIcon_0->size(), Qt::KeepAspectRatio);
    heartbroken_icon = heartbroken_icon.scaled(ui->label_resultIcon_0->size(), Qt::KeepAspectRatio);

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

}

ResultTurn::~ResultTurn()
{
    delete ui;
}
