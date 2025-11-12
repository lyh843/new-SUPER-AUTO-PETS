#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include "ui/ShopView.hpp"
#include "model/Player.hpp"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Player* _player;
    ShopView* _shopView;

public:
    MainWindow(QWidget* parent = nullptr)
        : QMainWindow(parent)
    {
        // 创建玩家
        _player = new Player(10, 5, 1, 0);

        // 创建主窗口部件
        auto* centralWidget = new QWidget(this);
        setCentralWidget(centralWidget);

        auto* mainLayout = new QVBoxLayout(centralWidget);

        // 添加标题
        auto* titleLabel = new QLabel("🎮 Super Auto Pets", this);
        titleLabel->setAlignment(Qt::AlignCenter);
        titleLabel->setStyleSheet("font-size: 32px; font-weight: bold; color: #4CAF50; padding: 20px;");
        mainLayout->addWidget(titleLabel);

        // 创建商店视图
        _shopView = new ShopView(_player, this);
        mainLayout->addWidget(_shopView);

        // 连接信号
        connect(_shopView, &ShopView::endTurn, this, &MainWindow::onEndTurn);

        // 设置窗口属性
        setWindowTitle("Super Auto Pets - 商店");
        resize(900, 700);

        // 显示欢迎消息
        QMessageBox::information(this, "欢迎", 
            "欢迎来到 Super Auto Pets！\n\n"
            "游戏规则：\n"
            "1. 使用金币购买宠物和食物\n"
            "2. 合理搭配宠物阵容\n"
            "3. 相同宠物会合并升级\n"
            "4. 刷新商店需要 1 金币\n"
            "5. 出售宠物获得 1 金币\n\n"
            "祝你游戏愉快！");
    }

    ~MainWindow()
    {
        delete _player;
    }

private slots:
    void onEndTurn()
    {
        // 回合结束处理
        auto reply = QMessageBox::question(this, "结束回合",
                                           "确定要结束本回合并开始战斗吗？",
                                           QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes)
        {
            // 这里应该进入战斗界面，目前只是简单处理
            _player->addRound();
            _player->addCoin(10);  // 新回合开始，获得 10 金币

            QMessageBox::information(this, "回合结束",
                                     QString("回合 %1 战斗结束！\n\n"
                                             "战斗结果：胜利！\n"
                                             "新回合开始，获得 10 金币。")
                                         .arg(_player->getRound() - 1));

            // 重置商店
            _shopView->resetShop();
        }
    }
};

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    // 设置应用程序样式
    app.setStyle("Fusion");

    MainWindow window;
    window.show();

    return app.exec();
}

#include "main.moc"
