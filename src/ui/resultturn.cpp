#include "resultturn.h"
#include "ui_resultturn.h"

resultTurn::resultTurn(QWidget* parent) : QWidget(parent), ui(new Ui::resultTurn)
{
    ui->setupUi(this);
}

resultTurn::~resultTurn()
{
    delete ui;
}
