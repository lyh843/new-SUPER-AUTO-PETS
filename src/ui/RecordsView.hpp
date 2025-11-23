#pragma once

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include <vector>

class RecordsView : public QWidget
{
    Q_OBJECT

private:
    QTableWidget* _recordsTable;
    QPushButton* _backButton;
    QPushButton* _clearButton;
    QLabel* _statsLabel;
    QPixmap _bgPixmap;

    // 静态存储战绩数据
    struct RecordData {
        int round;
        int wins;
        int trophies;
    };
    static std::vector<RecordData> _allRecords;

    void setupUI();
    void loadRecords();
    void updateStats();

public:
    explicit RecordsView(QWidget* parent = nullptr);
    ~RecordsView() = default;

    void addRecord(int round, int wins, int trophies);
    void refreshRecords();  // 刷新战绩显示

signals:
    void backClicked();  // 返回主菜单

private slots:
    void onClearClicked();
protected:
    void paintEvent(QPaintEvent* event) override;
};

