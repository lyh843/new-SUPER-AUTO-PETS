#include "RecordsView.hpp"
#include <QHeaderView>
#include <QMessageBox>
#include <QPainter>
#include <QDir>
#include <QCoreApplication>

RecordsView::RecordsView(QWidget* parent)
    : QWidget(parent)
{
    setupUI();

    // 加载背景图资源到成员变量（使用 qrc 资源）
    _bgPixmap = QPixmap(":/else/photo/backgroundStartview.png");
    // 如果资源未打包到 qrc，也尝试从相对路径加载（可选）
    if (_bgPixmap.isNull()) {
        QString fallback = QCoreApplication::applicationDirPath() + QDir::separator() + QLatin1String("..") + QDir::separator() + QLatin1String("src") + QDir::separator() + QLatin1String("ui") + QDir::separator() + QLatin1String("photo") + QDir::separator() + QLatin1String("backgroundStartview.png");
        _bgPixmap.load(fallback);
    }

    // 让 paintEvent 负责绘制背景
    setAutoFillBackground(false);

    loadRecords();
}

void RecordsView::setupUI()
{
    auto* mainLayout = new QVBoxLayout(this);

    // 标题栏
    auto* titleLabel = new QLabel("📊 游戏战绩", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet(
        "font-size: 36px; "
        "font-weight: bold; "
        "color: #4CAF50; "
        "padding: 20px;"
    );
    mainLayout->addWidget(titleLabel);

    // 统计信息
    _statsLabel = new QLabel(this);
    _statsLabel->setAlignment(Qt::AlignCenter);
    _statsLabel->setStyleSheet(
        "font-size: 18px; "
        "color: #666; "
        "padding: 10px; "
        "background-color: white; "
        "border: 2px solid #ddd; "
        "border-radius: 5px;"
    );
    mainLayout->addWidget(_statsLabel);

    // 表格
    _recordsTable = new QTableWidget(this);
    _recordsTable->setColumnCount(4);
    _recordsTable->setHorizontalHeaderLabels({"序号", "回合数", "胜利次数", "奖杯数"});
    _recordsTable->horizontalHeader()->setStretchLastSection(true);
    _recordsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    _recordsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    _recordsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    _recordsTable->setStyleSheet(
        "QTableWidget {"
        "    background-color: white; "
        "    border: 2px solid #ddd; "
        "    border-radius: 5px; "
        "    font-size: 16px;"
        "}"
        "QHeaderView::section {"
        "    background-color: #4CAF50; "
        "    color: white; "
        "    padding: 8px; "
        "    font-weight: bold; "
        "    border: none;"
        "}"
    );
    mainLayout->addWidget(_recordsTable);

    // 按钮栏
    auto* buttonLayout = new QHBoxLayout();

    _clearButton = new QPushButton("🗑️ 清空记录", this);
    _clearButton->setStyleSheet(
        "QPushButton {"
        "    font-size: 16px; "
        "    font-weight: bold; "
        "    background-color: #f44336; "
        "    color: white; "
        "    border: none; "
        "    border-radius: 5px; "
        "    padding: 10px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #da190b; "
        "}"
    );
    buttonLayout->addWidget(_clearButton);

    buttonLayout->addStretch();

    _backButton = new QPushButton("⬅️ 返回主菜单", this);
    _backButton->setStyleSheet(
        "QPushButton {"
        "    font-size: 16px; "
        "    font-weight: bold; "
        "    background-color: #2196F3; "
        "    color: white; "
        "    border: none; "
        "    border-radius: 5px; "
        "    padding: 10px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #0b7dda; "
        "}"
    );
    buttonLayout->addWidget(_backButton);

    mainLayout->addLayout(buttonLayout);

    connect(_backButton, &QPushButton::clicked, this, &RecordsView::backClicked);
    connect(_clearButton, &QPushButton::clicked, this, &RecordsView::onClearClicked);
}

void RecordsView::loadRecords()
{
    // 目前使用示例数据，后续可以从文件或数据库加载
    _recordsTable->setRowCount(0);
    
    // 添加一些示例数据
    addRecord(5, 3, 150);
    addRecord(8, 6, 320);
    addRecord(3, 2, 100);
    
    updateStats();
}

void RecordsView::updateStats()
{
    int totalGames = _recordsTable->rowCount();
    int totalWins = 0;
    int totalTrophies = 0;
    int maxRound = 0;

    for (int i = 0; i < totalGames; ++i) {
        if (auto* winsItem = _recordsTable->item(i, 2)) {
            totalWins += winsItem->text().toInt();
        }
        if (auto* trophiesItem = _recordsTable->item(i, 3)) {
            totalTrophies += trophiesItem->text().toInt();
        }
        if (auto* roundItem = _recordsTable->item(i, 1)) {
            int round = roundItem->text().toInt();
            if (round > maxRound) {
                maxRound = round;
            }
        }
    }

    QString statsText = QString(
        "总游戏场次：%1  |  总胜利次数：%2  |  总奖杯数：%3  |  最高回合数：%4"
    ).arg(totalGames).arg(totalWins).arg(totalTrophies).arg(maxRound);

    _statsLabel->setText(statsText);
}

void RecordsView::addRecord(int round, int wins, int trophies)
{
    int row = _recordsTable->rowCount();
    _recordsTable->insertRow(row);

    _recordsTable->setItem(row, 0, new QTableWidgetItem(QString::number(row + 1)));
    _recordsTable->setItem(row, 1, new QTableWidgetItem(QString::number(round)));
    _recordsTable->setItem(row, 2, new QTableWidgetItem(QString::number(wins)));
    _recordsTable->setItem(row, 3, new QTableWidgetItem(QString::number(trophies)));

    // 设置居中对齐
    for (int col = 0; col < 4; ++col) {
        if (auto* item = _recordsTable->item(row, col)) {
            item->setTextAlignment(Qt::AlignCenter);
        }
    }
}

void RecordsView::onClearClicked()
{
    auto reply = QMessageBox::question(
        this,
        "确认清空",
        "确定要清空所有战绩记录吗？此操作不可撤销！",
        QMessageBox::Yes | QMessageBox::No
    );

    if (reply == QMessageBox::Yes) {
        _recordsTable->setRowCount(0);
        updateStats();
        QMessageBox::information(this, "提示", "战绩记录已清空！");
    }
}

void RecordsView::paintEvent(QPaintEvent* event)
{
    if (!_bgPixmap.isNull()) {
        QPainter p(this);
        QSize targetSize = size();
        QPixmap scaled = _bgPixmap.scaled(targetSize, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
        int x = (targetSize.width() - scaled.width()) / 2;
        int y = (targetSize.height() - scaled.height()) / 2;
        p.drawPixmap(x, y, scaled);
    }

    QWidget::paintEvent(event);
}

