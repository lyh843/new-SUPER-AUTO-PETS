#include "PetEncyclopediaView.hpp"
#include <QPainter>
#include <QDir>
#include <QCoreApplication>

PetEncyclopediaView::PetEncyclopediaView(QWidget* parent)
    : QWidget(parent)
{
    setupUI();

    // 加载背景图资源（优先使用 qrc）
    _bgPixmap = QPixmap(":/else/photo/backgroundStartview.png");
    if (_bgPixmap.isNull()) {
        QString fallback = QCoreApplication::applicationDirPath() + QDir::separator() + QLatin1String("..") + QDir::separator() + QLatin1String("src") + QDir::separator() + QLatin1String("ui") + QDir::separator() + QLatin1String("photo") + QDir::separator() + QLatin1String("backgroundStartview.png");
        _bgPixmap.load(fallback);
    }

    setAutoFillBackground(false);
}

void PetEncyclopediaView::setupUI()
{
    _mainLayout = new QVBoxLayout(this);

    // 标题栏
    auto* titleLabel = new QLabel("📚 宠物图鉴", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet(
        "font-size: 36px; "
        "font-weight: bold; "
        "color: #4CAF50; "
        "padding: 20px;"
    );
    _mainLayout->addWidget(titleLabel);

    // 滚动区域
    _scrollArea = new QScrollArea(this);
    _scrollArea->setWidgetResizable(true);
    _scrollArea->setStyleSheet("background-color: white; border: 2px solid #ddd; border-radius: 5px;");

    _contentWidget = new QWidget();
    auto* contentLayout = new QVBoxLayout(_contentWidget);
    contentLayout->setSpacing(15);

    // 宠物分组
    auto* petsGroup = new QGroupBox("🐾 宠物", _contentWidget);
    petsGroup->setStyleSheet(
        "QGroupBox {"
        "    font-size: 24px; "
        "    font-weight: bold; "
        "    color: #333; "
        "    border: 2px solid #4CAF50; "
        "    border-radius: 5px; "
        "    margin-top: 10px; "
        "    padding-top: 15px;"
        "}"
        "QGroupBox::title {"
        "    subcontrol-origin: margin; "
        "    left: 10px; "
        "    padding: 0 5px;"
        "}"
    );
    auto* petsLayout = new QVBoxLayout(petsGroup);

    // Tier 1 宠物
    petsLayout->addWidget(createPetCard("🐱 猫", "Tier 1", 3, 4, "基础宠物"));
    petsLayout->addWidget(createPetCard("🐜 蚂蚁", "Tier 1", 1, 2, "死亡时：给随机友方宠物 +2/+1"));
    petsLayout->addWidget(createPetCard("🐟 鱼", "Tier 1", 2, 3, "升级时：给随机两个友方宠物 +1/+1"));
    petsLayout->addWidget(createPetCard("🦗 蟋蟀", "Tier 1", 2, 1, "死亡时：召唤一只蜜蜂"));

    // Tier 2 宠物
    petsLayout->addWidget(createPetCard("🦢 天鹅", "Tier 2", 1, 3, "回合开始时：获得 1 金币"));
    petsLayout->addWidget(createPetCard("🦩 火烈鸟", "Tier 2", 2, 3, "战斗结束时：如果存活获得 +2 攻击"));
    petsLayout->addWidget(createPetCard("🦔 刺猬", "Tier 2", 1, 3, "受到伤害时：对敌人造成等量伤害"));

    // Tier 3 宠物
    petsLayout->addWidget(createPetCard("🦚 孔雀", "Tier 3", 5, 2, "受到攻击前：获得 50% 伤害减免"));

    contentLayout->addWidget(petsGroup);

    // 食物分组
    auto* foodsGroup = new QGroupBox("🍎 食物", _contentWidget);
    foodsGroup->setStyleSheet(
        "QGroupBox {"
        "    font-size: 24px; "
        "    font-weight: bold; "
        "    color: #333; "
        "    border: 2px solid #FF9800; "
        "    border-radius: 5px; "
        "    margin-top: 10px; "
        "    padding-top: 15px;"
        "}"
        "QGroupBox::title {"
        "    subcontrol-origin: margin; "
        "    left: 10px; "
        "    padding: 0 5px;"
        "}"
    );
    auto* foodsLayout = new QVBoxLayout(foodsGroup);

    // Tier 1 食物
    foodsLayout->addWidget(createFoodCard("🍎 苹果", "Tier 1", 3, "+1 攻击 +1 生命"));
    foodsLayout->addWidget(createFoodCard("🍯 蜂蜜", "Tier 1", 3, "战斗开始：召唤蜜蜂"));
    foodsLayout->addWidget(createFoodCard("🦴 骨头", "Tier 1", 3, "+3 攻击"));
    foodsLayout->addWidget(createFoodCard("🍐 梨子", "Tier 1", 3, "+2 攻击 +1 生命"));

    // Tier 2 食物
    foodsLayout->addWidget(createFoodCard("🧄 大蒜", "Tier 2", 6, "+2 生命 +1 护甲"));
    foodsLayout->addWidget(createFoodCard("🥗 色拉", "Tier 2", 6, "+1 攻击 +2 生命"));
    foodsLayout->addWidget(createFoodCard("🥫 罐头", "Tier 2", 6, "+2 攻击 +2 生命"));

    // Tier 3 食物
    foodsLayout->addWidget(createFoodCard("🍉 西瓜", "Tier 3", 9, "战斗开始：获得 50% 伤害减免"));
    foodsLayout->addWidget(createFoodCard("🍄 蘑菇", "Tier 3", 9, "死亡时：复活一次"));

    contentLayout->addWidget(foodsGroup);

    _contentWidget->setLayout(contentLayout);
    _scrollArea->setWidget(_contentWidget);
    _mainLayout->addWidget(_scrollArea);

    // 按钮布局
    auto* buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(10);
    
    // 返回商店按钮
    _backToShopButton = new QPushButton("⬅️ 返回商店", this);
    _backToShopButton->setStyleSheet(
        "QPushButton {"
        "    font-size: 18px; "
        "    font-weight: bold; "
        "    background-color: #4CAF50; "
        "    color: white; "
        "    border: none; "
        "    border-radius: 5px; "
        "    padding: 10px 20px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #45a049; "
        "}"
    );
    buttonLayout->addWidget(_backToShopButton);

    // 返回主菜单按钮
    _backToStartButton = new QPushButton("🏠 返回主菜单", this);
    _backToStartButton->setStyleSheet(
        "QPushButton {"
        "    font-size: 18px; "
        "    font-weight: bold; "
        "    background-color: #2196F3; "
        "    color: white; "
        "    border: none; "
        "    border-radius: 5px; "
        "    padding: 10px 20px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #0b7dda; "
        "}"
    );
    buttonLayout->addWidget(_backToStartButton);
    
    buttonLayout->addStretch();
    
    _mainLayout->addLayout(buttonLayout);

    connect(_backToShopButton, &QPushButton::clicked, this, &PetEncyclopediaView::backToShopClicked);
    connect(_backToStartButton, &QPushButton::clicked, this, &PetEncyclopediaView::backClicked);

    // 不使用全局样式背景，让 paintEvent 绘制背景图片
}

QWidget* PetEncyclopediaView::createPetCard(const QString& name, const QString& tier, 
                                             int attack, int health, const QString& ability)
{
    auto* petCard = new QWidget();
    petCard->setStyleSheet(
        "QWidget {"
        "    background-color: white; "
        "    border: 2px solid #ddd; "
        "    border-radius: 8px; "
        "    padding: 10px;"
        "}"
    );

    auto* layout = new QVBoxLayout(petCard);

    auto* nameLabel = new QLabel(QString("%1 (%2)").arg(name, tier), petCard);
    nameLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #333;");
    layout->addWidget(nameLabel);

    auto* statsLabel = new QLabel(QString("⚔️ %1  ❤️ %2").arg(attack).arg(health), petCard);
    statsLabel->setStyleSheet("font-size: 16px; color: #666;");
    layout->addWidget(statsLabel);

    auto* abilityLabel = new QLabel(QString("技能：%1").arg(ability), petCard);
    abilityLabel->setStyleSheet("font-size: 14px; color: #888;");
    abilityLabel->setWordWrap(true);
    layout->addWidget(abilityLabel);

    return petCard;
}

QWidget* PetEncyclopediaView::createFoodCard(const QString& name, const QString& tier, 
                                              int cost, const QString& effect)
{
    auto* foodCard = new QWidget();
    foodCard->setStyleSheet(
        "QWidget {"
        "    background-color: white; "
        "    border: 2px solid #ddd; "
        "    border-radius: 8px; "
        "    padding: 10px;"
        "}"
    );

    auto* layout = new QVBoxLayout(foodCard);

    auto* nameLabel = new QLabel(QString("%1 (%2)").arg(name, tier), foodCard);
    nameLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #333;");
    layout->addWidget(nameLabel);

    auto* costLabel = new QLabel(QString("💰 %1").arg(cost), foodCard);
    costLabel->setStyleSheet("font-size: 16px; color: #666;");
    layout->addWidget(costLabel);

    auto* effectLabel = new QLabel(QString("效果：%1").arg(effect), foodCard);
    effectLabel->setStyleSheet("font-size: 14px; color: #888;");
    effectLabel->setWordWrap(true);
    layout->addWidget(effectLabel);

    return foodCard;
}

void PetEncyclopediaView::paintEvent(QPaintEvent* event)
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

