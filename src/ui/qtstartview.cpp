#include "qtstartview.h"
#include "ui_qtstartview.h"

qtStartView::qtStartView(QWidget* parent) : QWidget(parent), ui(new Ui::qtStartView)
{
    ui->setupUi(this);
}

qtStartView::~qtStartView()
{
    delete ui;
}
