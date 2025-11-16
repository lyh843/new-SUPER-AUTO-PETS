#include "qtbattleview.h"
#include "ui_qtbattleview.h"

QtBattleView::QtBattleView(QWidget* parent) : QWidget(parent), ui(new Ui::QtBattleView)
{
    ui->setupUi(this);
}

QtBattleView::~QtBattleView()
{
    delete ui;
}

void QtBattleView::on_start_button_clicked()
{

}


void QtBattleView::on_auto_play_button_clicked()
{

}


void QtBattleView::on_forward_button_clicked()
{

}

