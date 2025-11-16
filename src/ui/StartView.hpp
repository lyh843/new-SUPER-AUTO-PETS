#pragma once

#include <QWidget>

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

private slots:
    void on_playButton_clicked();
    void on_encyclopediaButton_clicked();
    void on_recordsButton_clicked();
};

