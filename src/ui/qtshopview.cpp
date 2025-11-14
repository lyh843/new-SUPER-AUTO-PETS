#include "qtshopview.h"
#include "ui_qtshopview.h"

QtShopview::QtShopview(QWidget* parent) : QWidget(parent), ui(new Ui::QtShopview)
{
    ui->setupUi(this);
    ui->playAnimalsSpace1->move(230, 310);
    ui->playAnimals2Space2->move(330, 310);
}

QtShopview::~QtShopview()
{
    delete ui;
}
