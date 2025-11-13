#pragma once

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>

class RecordsView : public QWidget
{
    Q_OBJECT

private:
    QTableWidget* _recordsTable;
    QPushButton* _backButton;
    QPushButton* _clearButton;
    QLabel* _statsLabel;

    void setupUI();
    void loadRecords();
    void updateStats();

public:
    explicit RecordsView(QWidget* parent = nullptr);
    ~RecordsView() = default;

    void addRecord(int round, int wins, int trophies);

signals:
    void backClicked();  // 返回主菜单

private slots:
    void onClearClicked();
};

