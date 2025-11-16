#include "StartView.hpp"
#include "ui_StartView.h"

StartView::StartView(QWidget* parent)
    : QWidget(parent)
    , _ui(new Ui::StartView)
{
    _ui->setupUi(this);

    // 让覆盖在按钮上的标签对鼠标事件透明，事件能穿透到下面的按钮
    // 这些标签在 UI 中位于按钮之上，会阻止按钮接收点击，故设置为透明
    _ui->playLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
    _ui->petsLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
    _ui->historyLabel->setAttribute(Qt::WA_TransparentForMouseEvents);

    // 连接信号槽，处理按钮点击
    connect(_ui->playButton, &QPushButton::clicked, this, &StartView::on_playButton_clicked);
    connect(_ui->encyclopediaButton, &QPushButton::clicked, this, &StartView::on_encyclopediaButton_clicked);
    connect(_ui->recordsButton, &QPushButton::clicked, this, &StartView::on_recordsButton_clicked);
}

StartView::~StartView()
{
    delete _ui;
}

void StartView::on_playButton_clicked()
{
    emit playClicked();
}

void StartView::on_encyclopediaButton_clicked()
{
    emit encyclopediaClicked();
}

void StartView::on_recordsButton_clicked()
{
    emit recordsClicked();
}



