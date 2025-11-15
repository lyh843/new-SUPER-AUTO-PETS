#include "qtshopview.h"
#include "ui_qtshopview.h"

QtShopview::QtShopview(QWidget* parent) : QWidget(parent), ui(new Ui::QtShopview)
{
    ui->setupUi(this);
}

QtShopview::~QtShopview()
{
    delete ui;
}
