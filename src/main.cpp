#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include "ui/StartView.hpp"
#include "ui/QtShopview.h"
#include "ui/BattleView.hpp"
#include "ui/PetEncyclopediaView.hpp"
#include "ui/RecordsView.hpp"
#include "model/Player.hpp"
#include "engine/BattleEngine.hpp"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QStackedWidget* _stackedWidget;
    StartView* _startView;
    QtShopview* _shopView;
    BattleView* _battleView;
    PetEncyclopediaView* _encyclopediaView;
    RecordsView* _recordsView;
    Player* _player;

public:
    MainWindow(QWidget* parent = nullptr)
        : QMainWindow(parent)
    {
        // 创建玩家
        _player = new Player(10, 5, 1, 0);

        // 创建堆叠窗口部件
        _stackedWidget = new QStackedWidget(this);
        setCentralWidget(_stackedWidget);

        // 创建开始界面
        _startView = new StartView(this);
        _stackedWidget->addWidget(_startView);

        // 创建商店视图
        _shopView = new QtShopview(_player, this);
        _stackedWidget->addWidget(_shopView);

        // 创建战斗视图
        _battleView = new BattleView(_player, this);
        _stackedWidget->addWidget(_battleView);

        // 创建宠物图鉴视图
        _encyclopediaView = new PetEncyclopediaView(this);
        _stackedWidget->addWidget(_encyclopediaView);

        // 创建战绩视图
        _recordsView = new RecordsView(this);
        _stackedWidget->addWidget(_recordsView);

        // 连接开始界面信号
        connect(_startView, &StartView::playClicked, this, &MainWindow::onPlayClicked);
        connect(_startView, &StartView::encyclopediaClicked, this, &MainWindow::onEncyclopediaClicked);
        connect(_startView, &StartView::recordsClicked, this, &MainWindow::onRecordsClicked);

        // 连接商店视图信号
        connect(_shopView, &QtShopview::endTurn, this, &MainWindow::onEndTurn);

        // 连接战斗视图信号
        connect(_battleView, &BattleView::battleFinished, this, &MainWindow::onBattleFinished);
        connect(_battleView, &BattleView::backToShop, this, &MainWindow::onBackToShop);

        // 连接图鉴视图信号
        connect(_encyclopediaView, &PetEncyclopediaView::backClicked, this, &MainWindow::onBackToStart);

        // 连接战绩视图信号
        connect(_recordsView, &RecordsView::backClicked, this, &MainWindow::onBackToStart);

        // 设置窗口属性
        setWindowTitle("Super Auto Pets");
        resize(900, 700);

        // 显示开始界面
        _stackedWidget->setCurrentWidget(_startView);
    }

    ~MainWindow()
    {
        delete _player;
    }

private slots:
    void onPlayClicked()
    {
        // 删除旧的玩家对象
        delete _player;
        
        // 开始新游戏
        _player = new Player(10, 5, 1, 0);
        
        // 重新创建商店视图
        _stackedWidget->removeWidget(_shopView);
        delete _shopView;
        _shopView = new QtShopview(_player, this);
        _stackedWidget->insertWidget(1, _shopView);
        connect(_shopView, &QtShopview::endTurn, this, &MainWindow::onEndTurn);

        // 重新创建战斗视图（因为它持有player指针）
        _stackedWidget->removeWidget(_battleView);
        delete _battleView;
        _battleView = new BattleView(_player, this);
        _stackedWidget->insertWidget(2, _battleView);
        connect(_battleView, &BattleView::battleFinished, this, &MainWindow::onBattleFinished);
        connect(_battleView, &BattleView::backToShop, this, &MainWindow::onBackToShop);

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

        _stackedWidget->setCurrentWidget(_shopView);
        setWindowTitle("Super Auto Pets - 商店");
    }

    void onEncyclopediaClicked()
    {
        _stackedWidget->setCurrentWidget(_encyclopediaView);
        setWindowTitle("Super Auto Pets - 宠物图鉴");
    }

    void onRecordsClicked()
    {
        _stackedWidget->setCurrentWidget(_recordsView);
        setWindowTitle("Super Auto Pets - 战绩");
    }

    void onBackToStart()
    {
        _stackedWidget->setCurrentWidget(_startView);
        setWindowTitle("Super Auto Pets");
    }

    void onEndTurn()
    {
        // 检查玩家是否有宠物
        if (_player->getPetCount() == 0)
        {
            QMessageBox::warning(this, "无法战斗",
                               "你还没有购买任何宠物！\n请先购买宠物再开始战斗。");
            return;
        }

        // 回合结束处理
        auto reply = QMessageBox::question(this, "结束回合",
                                           "确定要结束本回合并开始战斗吗？",
                                           QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes)
        {
            // 进入战斗界面
            _battleView->startNewBattle();
            _stackedWidget->setCurrentWidget(_battleView);
            setWindowTitle("Super Auto Pets - 战斗");
        }
    }

    void onBattleFinished(BattleResult result)
    {
        QString resultMessage;
        int livesChange = 0;
        int prizeChange = 0;

        switch (result)
        {
        case BattleResult::Player1Win:
            resultMessage = "🎉 胜利！\n你赢得了这场战斗！";
            prizeChange = 1;
            break;
        case BattleResult::Player2Win:
            resultMessage = "😢 失败！\n你输掉了这场战斗！";
            livesChange = -1;
            break;
        case BattleResult::Draw:
            resultMessage = "🤝 平局！\n双方都没有获胜！";
            break;
        }

        // 更新玩家状态
        if (livesChange != 0)
        {
            _player->decreaseLives(-livesChange);
        }
        if (prizeChange != 0)
        {
            _player->addPrize(prizeChange);
        }

        // 显示战斗结果
        resultMessage += QString("\n\n当前状态：\n"
                                "❤️ 生命：%1\n"
                                "🏆 奖杯：%2\n"
                                "🔄 回合：%3")
                            .arg(_player->getLives())
                            .arg(_player->getPrize())
                            .arg(_player->getRound());

        QMessageBox::information(this, "战斗结果", resultMessage);

        // 检查游戏是否结束
        if (_player->getLives() <= 0)
        {
            QMessageBox::information(this, "游戏结束",
                                   QString("游戏结束！\n\n"
                                          "最终成绩：\n"
                                          "🏆 奖杯：%1\n"
                                          "🔄 回合：%2")
                                       .arg(_player->getPrize())
                                       .arg(_player->getRound()));
            
            // 返回主菜单
            _stackedWidget->setCurrentWidget(_startView);
            setWindowTitle("Super Auto Pets");
            return;
        }

        if (_player->getPrize() >= Max_prize)
        {
            QMessageBox::information(this, "游戏胜利！",
                                   QString("恭喜！你赢得了游戏！\n\n"
                                          "最终成绩：\n"
                                          "🏆 奖杯：%1\n"
                                          "🔄 回合：%2\n"
                                          "❤️ 生命：%3")
                                       .arg(_player->getPrize())
                                       .arg(_player->getRound())
                                       .arg(_player->getLives()));
            
            // 返回主菜单
            _stackedWidget->setCurrentWidget(_startView);
            setWindowTitle("Super Auto Pets");
            return;
        }

        // 继续下一回合
        onBackToShop();
    }

    void onBackToShop()
    {
        // 新回合开始
        _player->addRound();
        _player->addCoin(10);  // 新回合开始，获得 10 金币

        // 重置商店
        _shopView->resetShop();

        // 返回商店
        _stackedWidget->setCurrentWidget(_shopView);
        setWindowTitle("Super Auto Pets - 商店");

        QMessageBox::information(this, "新回合",
                               QString("回合 %1 开始！\n获得 10 金币。")
                                   .arg(_player->getRound()));
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
