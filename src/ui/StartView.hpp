#pragma once

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

namespace Ui {
class StartView;
}

class StartView : public QWidget
{
    Q_OBJECT

private:
    Ui::StartView* _ui;

public:
    explicit StartView(QWidget* parent = nullptr);
    ~StartView();

signals:
    void playClicked();           // 开始游戏
    void encyclopediaClicked();   // 打开宠物图鉴
    void recordsClicked();        // 查看战绩
};

