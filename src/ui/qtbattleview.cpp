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
