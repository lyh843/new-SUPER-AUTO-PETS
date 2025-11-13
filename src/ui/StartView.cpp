#include "StartView.hpp"
#include "ui_StartView.h"

StartView::StartView(QWidget* parent)
    : QWidget(parent)
    , _ui(new Ui::StartView)
{
    _ui->setupUi(this);

    // 设置标题样式
    _ui->titleLabel->setStyleSheet(
        "font-size: 48px; "
        "font-weight: bold; "
        "color: #4CAF50; "
        "padding: 20px;"
    );

    // 设置按钮样式
    QString buttonStyle = 
        "QPushButton {"
        "    font-size: 24px; "
        "    font-weight: bold; "
        "    background-color: #4CAF50; "
        "    color: white; "
        "    border: none; "
        "    border-radius: 10px; "
        "    padding: 15px; "
        "}"
        "QPushButton:hover {"
        "    background-color: #45a049; "
        "}"
        "QPushButton:pressed {"
        "    background-color: #3d8b40; "
        "}";

    _ui->playButton->setStyleSheet(buttonStyle);
    _ui->encyclopediaButton->setStyleSheet(buttonStyle);
    _ui->recordsButton->setStyleSheet(buttonStyle);

    // 设置背景颜色
    setStyleSheet("background-color: #f0f0f0;");

    // 连接信号
    connect(_ui->playButton, &QPushButton::clicked, this, &StartView::playClicked);
    connect(_ui->encyclopediaButton, &QPushButton::clicked, this, &StartView::encyclopediaClicked);
    connect(_ui->recordsButton, &QPushButton::clicked, this, &StartView::recordsClicked);

    // 设置布局居中对齐
    _ui->buttonsLayout->setAlignment(Qt::AlignHCenter);
}

StartView::~StartView()
{
    delete _ui;
}

