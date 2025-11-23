#include "RecordsView.hpp"
#include <QHeaderView>
#include <QMessageBox>
#include <QPainter>
#include <QDir>
#include <QCoreApplication>
#include <QBrush>
#include <vector>

// 静态成员变量定义
std::vector<RecordsView::RecordData> RecordsView::_allRecords;

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
        "color: #000000; "  /* 黑色文字 */
        "background: transparent; "
        "padding: 20px;"
    );
    titleLabel->raise();
    mainLayout->addWidget(titleLabel);

    // 统计信息
    _statsLabel = new QLabel(this);
    _statsLabel->setAlignment(Qt::AlignCenter);
    _statsLabel->setStyleSheet(
        "font-size: 18px; "
        "color: #666; "
        "padding: 10px; "
        "background-color: rgba(255,255,255,220); " /* 半透明白 */
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
        "    background-color: rgba(255,255,255,200); " /* 半透明白 */
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
        "    background-color: rgba(244,67,54,220); " /* 半透明红 */
        "    color: white; "
        "    border: none; "
        "    border-radius: 5px; "
        "    padding: 10px;"
        "}"
        "QPushButton:hover {"
        "    background-color: rgba(218,25,11,220); "
        "}"
    );
    buttonLayout->addWidget(_clearButton);

    buttonLayout->addStretch();

    _backButton = new QPushButton("⬅️ 返回主菜单", this);
    _backButton->setStyleSheet(
        "QPushButton {"
        "    font-size: 16px; "
        "    font-weight: bold; "
        "    background-color: rgba(33,150,243,220); " /* 半透明蓝 */
        "    color: white; "
        "    border: none; "
        "    border-radius: 5px; "
        "    padding: 10px;"
        "}"
        "QPushButton:hover {"
        "    background-color: rgba(11,125,218,220); "
        "}"
    );
    buttonLayout->addWidget(_backButton);

    mainLayout->addLayout(buttonLayout);

    connect(_backButton, &QPushButton::clicked, this, &RecordsView::backClicked);
    connect(_clearButton, &QPushButton::clicked, this, &RecordsView::onClearClicked);
}

void RecordsView::loadRecords()
{
    // 清空表格
    _recordsTable->setRowCount(0);
    
    // 从静态存储中加载所有战绩
    for (const auto& record : _allRecords) {
        int row = _recordsTable->rowCount();
        _recordsTable->insertRow(row);

        auto* item0 = new QTableWidgetItem(QString::number(row + 1));
        auto* item1 = new QTableWidgetItem(QString::number(record.round));
        auto* item2 = new QTableWidgetItem(QString::number(record.wins));
        auto* item3 = new QTableWidgetItem(QString::number(record.trophies));

        // 确保表格内数字为黑色
        item0->setForeground(QBrush(Qt::black));
        item1->setForeground(QBrush(Qt::black));
        item2->setForeground(QBrush(Qt::black));
        item3->setForeground(QBrush(Qt::black));

        _recordsTable->setItem(row, 0, item0);
        _recordsTable->setItem(row, 1, item1);
        _recordsTable->setItem(row, 2, item2);
        _recordsTable->setItem(row, 3, item3);

        // 设置居中对齐
        for (int col = 0; col < 4; ++col) {
            if (auto* item = _recordsTable->item(row, col)) {
                item->setTextAlignment(Qt::AlignCenter);
            }
        }
    }
    
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
    // 保存到静态存储
    _allRecords.push_back({round, wins, trophies});
    
    // 如果当前视图正在显示，则更新表格
    if (_recordsTable) {
        int row = _recordsTable->rowCount();
        _recordsTable->insertRow(row);

        auto* item0 = new QTableWidgetItem(QString::number(row + 1));
        auto* item1 = new QTableWidgetItem(QString::number(round));
        auto* item2 = new QTableWidgetItem(QString::number(wins));
        auto* item3 = new QTableWidgetItem(QString::number(trophies));

        // 确保表格内数字为黑色，便于在浅色半透明背景上阅读
        item0->setForeground(QBrush(Qt::black));
        item1->setForeground(QBrush(Qt::black));
        item2->setForeground(QBrush(Qt::black));
        item3->setForeground(QBrush(Qt::black));

        _recordsTable->setItem(row, 0, item0);
        _recordsTable->setItem(row, 1, item1);
        _recordsTable->setItem(row, 2, item2);
        _recordsTable->setItem(row, 3, item3);

        // 设置居中对齐
        for (int col = 0; col < 4; ++col) {
            if (auto* item = _recordsTable->item(row, col)) {
                item->setTextAlignment(Qt::AlignCenter);
            }
        }
        
        updateStats();
    }
}

void RecordsView::refreshRecords()
{
    loadRecords();
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
        // 清空静态存储
        _allRecords.clear();
        // 清空表格
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

