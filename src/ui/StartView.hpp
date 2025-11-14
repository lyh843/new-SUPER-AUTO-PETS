#pragma once

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QPixmap>
#include <QResizeEvent>

namespace Ui {
class StartView;
}

class StartView : public QWidget
{
    Q_OBJECT

private:
    Ui::StartView* _ui;
    QLabel* _bgLabel{nullptr};
    QPixmap _bgPixmap;

public:
    explicit StartView(QWidget* parent = nullptr);
    ~StartView();

protected:
    void resizeEvent(QResizeEvent* event) override;
    void paintEvent(QPaintEvent* event) override;

signals:
    void playClicked();           // 开始游戏
    void encyclopediaClicked();   // 打开宠物图鉴
    void recordsClicked();        // 查看战绩
};

