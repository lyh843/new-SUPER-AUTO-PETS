#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QDialog>
#include <QTimer>
#include "ui/StartView.hpp"
#include "ui/QtShopview.h"
#include "ui/qtbattleview.h"
#include "ui/PetEncyclopediaView.hpp"
#include "ui/RecordsView.hpp"
#include "model/Player.hpp"
#include "engine/BattleEngine.hpp"
#include "ui/resultturn.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QStackedWidget* _stackedWidget;
    StartView* _startView;
    QtShopview* _shopView;
    QtBattleView* _battleView;
    PetEncyclopediaView* _encyclopediaView;
    RecordsView* _recordsView;
    Player* _player;
    ResultTurn* _resultTurn;  // 添加为成员变量

public:
    MainWindow(QWidget* parent = nullptr)
        : QMainWindow(parent)
    {

        _resultTurn = nullptr;  // 初始化结算视图指针
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
        _battleView = new QtBattleView(_player, this);
        _stackedWidget->addWidget(_battleView);

        // 创建宠物图鉴视图
        _encyclopediaView = new PetEncyclopediaView(this);
        _stackedWidget->addWidget(_encyclopediaView);

        // 创建战绩视图
        _recordsView = new RecordsView(this);
        _stackedWidget->addWidget(_recordsView);

        // 连接开始界面信号 - 使用Qt::UniqueConnection确保信号只连接一次
        connect(_startView, &StartView::playClicked, this, &MainWindow::onPlayClicked, Qt::UniqueConnection);
        connect(_startView, &StartView::encyclopediaClicked, this, &MainWindow::onEncyclopediaClicked, Qt::UniqueConnection);
        connect(_startView, &StartView::recordsClicked, this, &MainWindow::onRecordsClicked, Qt::UniqueConnection);

        // 连接商店视图信号
        connect(_shopView, &QtShopview::endTurn, this, &MainWindow::onEndTurn);
        connect(_shopView, &QtShopview::encyclopediaClicked, this, &MainWindow::onEncyclopediaClicked);
        connect(_shopView, &QtShopview::settingsClicked, this, &MainWindow::onSettingsClicked);

        // 连接战斗视图信号
        connect(_battleView, &QtBattleView::battleFinished, this, &MainWindow::onBattleFinished, Qt::UniqueConnection);
        connect(_battleView, &QtBattleView::backToShop, this, &MainWindow::onBackToShop, Qt::UniqueConnection);

        // 连接图鉴视图信号
        connect(_encyclopediaView, &PetEncyclopediaView::backClicked, this, &MainWindow::onBackToStart, Qt::UniqueConnection);
        connect(_encyclopediaView, &PetEncyclopediaView::backToShopClicked, this, &MainWindow::onBackToShopFromEncyclopedia, Qt::UniqueConnection);

        // 连接战绩视图信号
        connect(_recordsView, &RecordsView::backClicked, this, &MainWindow::onBackToStart, Qt::UniqueConnection);

        // 设置窗口属性
        setWindowTitle("Super Auto Pets");
        resize(900, 700);

        // 显示开始界面
        _stackedWidget->setCurrentWidget(_startView);
    }

    ~MainWindow()
    {
        delete _player;
        delete _resultTurn;  // 删除结算视图
    }

private slots:
    void onPlayClicked()
    {
        // 删除旧的玩家对象
        delete _player;
        
        // 删除旧的结果视图
        if (_resultTurn)
        {
            _stackedWidget->removeWidget(_resultTurn);
            delete _resultTurn;
            _resultTurn = nullptr;
        }

        // 开始新游戏
        _player = new Player(10, 5, 1, 0);
        
        // 重新创建商店视图
        if (_shopView)
        {
            // 断开所有信号连接，避免旧信号触发
            disconnect(_shopView, nullptr, this, nullptr);
            _stackedWidget->removeWidget(_shopView);
            delete _shopView;
            _shopView = nullptr;
        }
        _shopView = new QtShopview(_player, this);
        _stackedWidget->insertWidget(1, _shopView);
        connect(_shopView, &QtShopview::endTurn, this, &MainWindow::onEndTurn, Qt::UniqueConnection);
        connect(_shopView, &QtShopview::encyclopediaClicked, this, &MainWindow::onEncyclopediaClicked, Qt::UniqueConnection);
        connect(_shopView, &QtShopview::settingsClicked, this, &MainWindow::onSettingsClicked, Qt::UniqueConnection);

        // 重新创建战斗视图（因为它持有player指针）
        if (_battleView)
        {
            // 断开所有信号连接，避免旧信号触发
            disconnect(_battleView, nullptr, this, nullptr);
            _stackedWidget->removeWidget(_battleView);
            delete _battleView;
            _battleView = nullptr;
        }
        _battleView = new QtBattleView(_player, this);
        _stackedWidget->insertWidget(2, _battleView);
        connect(_battleView, &QtBattleView::battleFinished, this, &MainWindow::onBattleFinished, Qt::UniqueConnection);
        connect(_battleView, &QtBattleView::backToShop, this, &MainWindow::onBackToShop, Qt::UniqueConnection);

        // 确保widget已正确添加到stackedWidget
        if (_stackedWidget->indexOf(_shopView) == -1)
        {
            _stackedWidget->addWidget(_shopView);
        }
        if (_stackedWidget->indexOf(_battleView) == -1)
        {
            _stackedWidget->addWidget(_battleView);
        }
        
        // 先切换到商店界面，避免在显示对话框时触发其他信号
        int shopIndex = _stackedWidget->indexOf(_shopView);
        if (shopIndex >= 0)
        {
            _stackedWidget->setCurrentIndex(shopIndex);
        }
        else
        {
            _stackedWidget->setCurrentWidget(_shopView);
        }
        setWindowTitle("Super Auto Pets - 商店");
        
        // 显示欢迎消息（在切换视图后显示，避免触发异常信号）
        QMessageBox::information(this, "欢迎", 
            "欢迎来到 Super Auto Pets！\n\n"
            "游戏规则：\n"
            "1. 使用金币购买宠物和食物\n"
            "2. 合理搭配宠物阵容\n"
            "3. 相同宠物能够合并升级\n"
            "4. 刷新商店需要 1 金币\n"
            "5. 出售宠物获得 1 金币\n\n"
            "祝你游戏愉快！");

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

    void onBackToShopFromEncyclopedia()
    {
        // 从宠物图鉴返回商店
        if (_shopView && _stackedWidget->indexOf(_shopView) >= 0)
        {
            int shopIndex = _stackedWidget->indexOf(_shopView);
            _stackedWidget->setCurrentIndex(shopIndex);
            setWindowTitle("Super Auto Pets - 商店");
        }
        else
        {
            // 如果商店视图不存在，返回主菜单
            onBackToStart();
        }
    }

    void onSettingsClicked()
    {
        // 显示设置对话框，提供返回主菜单和退出游戏选项
        QMessageBox msgBox(this);
        msgBox.setWindowTitle("⚙️ 设置");
        msgBox.setText("请选择操作：");
        msgBox.setIcon(QMessageBox::Question);

        QPushButton* backToStartBtn = msgBox.addButton("🏠 返回主菜单", QMessageBox::ActionRole);
        QPushButton* exitGameBtn = msgBox.addButton("🚪 退出游戏", QMessageBox::DestructiveRole);
        QPushButton* cancelBtn = msgBox.addButton("取消", QMessageBox::RejectRole);

        msgBox.exec();

        if (msgBox.clickedButton() == backToStartBtn)
        {
            // 返回主菜单
            onBackToStart();
        }
        else if (msgBox.clickedButton() == exitGameBtn)
        {
            // 退出游戏
            auto reply = QMessageBox::question(this, "确认退出", 
                                              "确定要退出游戏吗？\n当前的游戏进度将不会保存。",
                                              QMessageBox::Yes | QMessageBox::No,
                                              QMessageBox::No);
            if (reply == QMessageBox::Yes)
            {
                QApplication::quit();
            }
        }
        // 如果点击取消，什么都不做
    }

    void onEndTurn()
    {
        // 检查战斗视图是否有效
        if (!_battleView)
        {
            QMessageBox::warning(this, "错误", "战斗视图未初始化！");
            return;
        }

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
            
            // 确保战斗视图在stackedWidget中
            int battleIndex = _stackedWidget->indexOf(_battleView);
            if (battleIndex >= 0)
            {
                _stackedWidget->setCurrentIndex(battleIndex);
            }
            else
            {
                // 如果不在，先添加到stackedWidget再切换
                _stackedWidget->addWidget(_battleView);
                _stackedWidget->setCurrentWidget(_battleView);
            }
            
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

    // 创建或重置结算视图
    if (!_resultTurn)
    {
        _resultTurn = new ResultTurn(this);
        _stackedWidget->addWidget(_resultTurn);
    }

    // 加载结果图片
    _resultTurn->loadingPicture(result, _player);

    // 显示结果界面
    _stackedWidget->setCurrentWidget(_resultTurn);
    setWindowTitle("Super Auto Pets - 战斗结果");

    // 使用单次定时器，2秒后自动返回商店
    QTimer::singleShot(2000, this, [this]() {
        onBackToShop();
    });
}


    void onBackToShop()
    {
        // 新回合开始
        _player->addRound();
        _player->setCoin(10);  // 新回合开始，获得 10 金币

        // 重置商店
        _shopView->resetShop();


        // 重置结果视图（如果存在）
        if (_resultTurn && _stackedWidget->indexOf(_resultTurn) >= 0)
        {
            _stackedWidget->removeWidget(_resultTurn);
            delete _resultTurn;
            _resultTurn = nullptr;
        }

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
