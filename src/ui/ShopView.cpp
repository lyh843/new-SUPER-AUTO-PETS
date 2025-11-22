// #include "ShopView.hpp"
// #include <QMessageBox>
// #include <QString>

// // ==================== PetCard 实现 ====================

// PetCard::PetCard(int index, bool isPlayerPet, QWidget* parent)
//     : QWidget(parent)
//     , _index(index)
//     , _isPlayerPet(isPlayerPet)
// {
//     auto* layout = new QVBoxLayout(this);
//     layout->setSpacing(5);
//     layout->setContentsMargins(5, 5, 5, 5);

//     _nameLabel = new QLabel("空", this);
//     _nameLabel->setAlignment(Qt::AlignCenter);
//     _nameLabel->setStyleSheet("font-weight: bold; font-size: 14px;");

//     _statsLabel = new QLabel("", this);
//     _statsLabel->setAlignment(Qt::AlignCenter);

//     _levelLabel = new QLabel("", this);
//     _levelLabel->setAlignment(Qt::AlignCenter);

//     _actionButton = new QPushButton(isPlayerPet ? "出售" : "购买", this);
//     _actionButton->setEnabled(false);

//     layout->addWidget(_nameLabel);
//     layout->addWidget(_statsLabel);
//     layout->addWidget(_levelLabel);
//     layout->addWidget(_actionButton);

//     // 设置样式
//     setStyleSheet("QWidget { border: 2px solid #ccc; border-radius: 5px; background-color: #f9f9f9; }");
//     setFixedSize(120, 150);

//     connect(_actionButton, &QPushButton::clicked, [this]() {
//         emit clicked(_index, _isPlayerPet);
//     });
// }

// void PetCard::updatePet(Pet* pet)
// {
//     if (pet)
//     {
//         _nameLabel->setText(QString::fromStdString(pet->getName()));
//         _statsLabel->setText(QString("❤️%1 ⚔️%2").arg(pet->getHP()).arg(pet->getAttack()));
//         _levelLabel->setText(QString("等级 %1 (经验 %2)").arg(pet->getLevel()).arg(pet->getExp()));
//         _actionButton->setEnabled(true);
//         setStyleSheet("QWidget { border: 2px solid #4CAF50; border-radius: 5px; background-color: #e8f5e9; }");
//     }
//     else
//     {
//         clear();
//     }
// }

// void PetCard::clear()
// {
//     _nameLabel->setText("空");
//     _statsLabel->setText("");
//     _levelLabel->setText("");
//     _actionButton->setEnabled(false);
//     setStyleSheet("QWidget { border: 2px solid #ccc; border-radius: 5px; background-color: #f9f9f9; }");
// }

// // ==================== FoodCard 实现 ====================

// FoodCard::FoodCard(int index, QWidget* parent)
//     : QWidget(parent)
//     , _index(index)
// {
//     auto* layout = new QVBoxLayout(this);
//     layout->setSpacing(5);
//     layout->setContentsMargins(5, 5, 5, 5);

//     _nameLabel = new QLabel("空", this);
//     _nameLabel->setAlignment(Qt::AlignCenter);
//     _nameLabel->setStyleSheet("font-weight: bold; font-size: 14px;");

//     _costLabel = new QLabel("", this);
//     _costLabel->setAlignment(Qt::AlignCenter);

//     _actionButton = new QPushButton("购买", this);
//     _actionButton->setEnabled(false);

//     layout->addWidget(_nameLabel);
//     layout->addWidget(_costLabel);
//     layout->addWidget(_actionButton);

//     setStyleSheet("QWidget { border: 2px solid #ccc; border-radius: 5px; background-color: #f9f9f9; }");
//     setFixedSize(120, 120);

//     connect(_actionButton, &QPushButton::clicked, [this]() {
//         emit clicked(_index);
//     });
// }

// void FoodCard::updateFood(Food* food)
// {
//     if (food)
//     {
//         _nameLabel->setText(QString::fromStdString(food->getName()));
//         _costLabel->setText(QString("💰 %1 金币").arg(food->getCost()));
//         _actionButton->setEnabled(true);
//         setStyleSheet("QWidget { border: 2px solid #FF9800; border-radius: 5px; background-color: #fff3e0; }");
//     }
//     else
//     {
//         clear();
//     }
// }

// void FoodCard::clear()
// {
//     _nameLabel->setText("空");
//     _costLabel->setText("");
//     _actionButton->setEnabled(false);
//     setStyleSheet("QWidget { border: 2px solid #ccc; border-radius: 5px; background-color: #f9f9f9; }");
// }

// // ==================== ShopView 实现 ====================

// ShopView::ShopView(Player* player, QWidget* parent)
//     : QWidget(parent)
//     , _player(player)
//     , _selectedShopPetIndex(-1)
//     , _selectedFoodIndex(-1)
//     , _targetPetIndex(-1)
// {
//     _shop = std::make_unique<Shop>(_player);
//     setupUI();
//     updateUI();
// }

// void ShopView::setupUI()
// {
//     auto* mainLayout = new QVBoxLayout(this);
//     mainLayout->setSpacing(15);
//     mainLayout->setContentsMargins(20, 20, 20, 20);

//     // ===== 玩家信息栏 =====
//     auto* infoLayout = new QHBoxLayout();
//     _coinLabel = new QLabel("💰 金币: 10", this);
//     _livesLabel = new QLabel("❤️ 生命: 5", this);
//     _roundLabel = new QLabel("🔄 回合: 1", this);
//     _prizeLabel = new QLabel("🏆 奖杯: 0", this);

//     _coinLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #FFD700;");
//     _livesLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #FF0000;");
//     _roundLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #2196F3;");
//     _prizeLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #FFA500;");

//     infoLayout->addWidget(_coinLabel);
//     infoLayout->addWidget(_livesLabel);
//     infoLayout->addWidget(_roundLabel);
//     infoLayout->addWidget(_prizeLabel);
//     infoLayout->addStretch();

//     mainLayout->addLayout(infoLayout);

//     // ===== 玩家宠物区域 =====
//     auto* playerLabel = new QLabel("我的宠物阵容", this);
//     playerLabel->setStyleSheet("font-size: 18px; font-weight: bold;");
//     mainLayout->addWidget(playerLabel);

//     auto* playerPetLayout = new QHBoxLayout();
//     for (int i = 0; i < 5; ++i)
//     {
//         auto* card = new PetCard(i, true, this);
//         _playerPetCards.append(card);
//         playerPetLayout->addWidget(card);
//         connect(card, &PetCard::clicked, this, &ShopView::onPlayerPetClicked);
//     }
//     playerPetLayout->addStretch();
//     mainLayout->addLayout(playerPetLayout);

//     // ===== 商店宠物区域 =====
//     auto* shopPetLabel = new QLabel("商店 - 宠物", this);
//     shopPetLabel->setStyleSheet("font-size: 18px; font-weight: bold;");
//     mainLayout->addWidget(shopPetLabel);

//     auto* shopPetLayout = new QHBoxLayout();
//     for (int i = 0; i < PET_SHOP_SIZE; ++i)
//     {
//         auto* card = new PetCard(i, false, this);
//         _shopPetCards.append(card);
//         shopPetLayout->addWidget(card);
//         connect(card, &PetCard::clicked, this, &ShopView::onShopPetClicked);
//     }
//     shopPetLayout->addStretch();
//     mainLayout->addLayout(shopPetLayout);

//     // ===== 商店食物区域 =====
//     auto* shopFoodLabel = new QLabel("商店 - 食物", this);
//     shopFoodLabel->setStyleSheet("font-size: 18px; font-weight: bold;");
//     mainLayout->addWidget(shopFoodLabel);

//     auto* shopFoodLayout = new QHBoxLayout();
//     for (int i = 0; i < FOOD_SHOP_SIZE; ++i)
//     {
//         auto* card = new FoodCard(i, this);
//         _shopFoodCards.append(card);
//         shopFoodLayout->addWidget(card);
//         connect(card, &FoodCard::clicked, this, &ShopView::onFoodClicked);
//     }
//     shopFoodLayout->addStretch();
//     mainLayout->addLayout(shopFoodLayout);

//     // ===== 操作按钮区域 =====
//     auto* buttonLayout = new QHBoxLayout();
    
//     _refreshButton = new QPushButton("🔄 刷新商店 (1💰)", this);
//     _refreshButton->setStyleSheet("QPushButton { background-color: #2196F3; color: white; font-size: 16px; padding: 10px; border-radius: 5px; }"
//                                    "QPushButton:hover { background-color: #1976D2; }");
//     connect(_refreshButton, &QPushButton::clicked, this, &ShopView::onRefreshClicked);

//     _endTurnButton = new QPushButton("✅ 结束回合 - 开始战斗", this);
//     _endTurnButton->setStyleSheet("QPushButton { background-color: #4CAF50; color: white; font-size: 16px; padding: 10px; border-radius: 5px; }"
//                                    "QPushButton:hover { background-color: #388E3C; }");
//     connect(_endTurnButton, &QPushButton::clicked, this, &ShopView::onEndTurnClicked);

//     buttonLayout->addWidget(_refreshButton);
//     buttonLayout->addWidget(_endTurnButton);
//     buttonLayout->addStretch();

//     mainLayout->addLayout(buttonLayout);
//     mainLayout->addStretch();

//     // 设置窗口样式
//     setStyleSheet("QWidget { background-color: #FFF8DC; }");
// }

// void ShopView::updateUI()
// {
//     updatePlayerInfo();
//     updatePlayerPets();
//     updateShopPets();
//     updateShopFoods();
// }

// void ShopView::updatePlayerInfo()
// {
//     _coinLabel->setText(QString("💰 金币: %1").arg(_player->getCoin()));
//     _livesLabel->setText(QString("❤️ 生命: %1").arg(_player->getLives()));
//     _roundLabel->setText(QString("🔄 回合: %1").arg(_player->getRound()));
//     _prizeLabel->setText(QString("🏆 奖杯: %1").arg(_player->getPrize()));
// }

// void ShopView::updatePlayerPets()
// {
//     for (int i = 0; i < 5; ++i)
//     {
//         Pet* pet = _player->getPetAt(i);
//         _playerPetCards[i]->updatePet(pet);
//     }
// }

// void ShopView::updateShopPets()
// {
//     for (int i = 0; i < PET_SHOP_SIZE; ++i)
//     {
//         Pet* pet = _shop->getPet(i);
//         _shopPetCards[i]->updatePet(pet);
//     }
// }

// void ShopView::updateShopFoods()
// {
//     for (int i = 0; i < FOOD_SHOP_SIZE; ++i)
//     {
//         Food* food = _shop->getFood(i);
//         _shopFoodCards[i]->updateFood(food);
//     }
// }

// void ShopView::onRefreshClicked()
// {
//     if (_shop->refresh())
//     {
//         updateUI();
//         QMessageBox::information(this, "刷新成功", "商店已刷新！");
//     }
//     else
//     {
//         QMessageBox::warning(this, "金币不足", "刷新商店需要 1 金币！");
//     }
// }

// void ShopView::onEndTurnClicked()
// {
//     emit endTurn();
// }

// void ShopView::onShopPetClicked(int index, bool isPlayerPet)
// {
//     // 购买宠物：需要选择放置位置
//     if (_player->getPetCount() >= 5)
//     {
//         QMessageBox::warning(this, "阵容已满", "你的宠物阵容已满！请先出售一只宠物。");
//         return;
//     }

//     // 寻找空位
//     int emptySlot = -1;
//     for (int i = 0; i < 5; ++i)
//     {
//         if (_player->getPetAt(i) == nullptr)
//         {
//             emptySlot = i;
//             break;
//         }
//     }

//     if (emptySlot == -1)
//     {
//         QMessageBox::warning(this, "阵容已满", "你的宠物阵容已满！");
//         return;
//     }

//     if (_shop->buyPet(index, emptySlot))
//     {
//         updateUI();
//         QMessageBox::information(this, "购买成功", "宠物已加入你的阵容！");
//     }
//     else
//     {
//         QMessageBox::warning(this, "购买失败", "金币不足或无法购买该宠物！");
//     }
// }

// void ShopView::onPlayerPetClicked(int index, bool isPlayerPet)
// {
//     // 出售宠物
//     Pet* pet = _player->getPetAt(index);
//     if (!pet)
//     {
//         QMessageBox::warning(this, "无法出售", "该位置没有宠物！");
//         return;
//     }

//     auto reply = QMessageBox::question(this, "确认出售",
//                                        QString("确定要出售 %1 吗？\n你将获得 1 金币。")
//                                            .arg(QString::fromStdString(pet->getName())),
//                                        QMessageBox::Yes | QMessageBox::No);

//     if (reply == QMessageBox::Yes)
//     {
//         if (_shop->sell(index))
//         {
//             updateUI();
//             QMessageBox::information(this, "出售成功", "已出售宠物，获得 1 金币！");
//         }
//     }
// }

// void ShopView::onFoodClicked(int index)
// {
//     // 购买食物：需要选择目标宠物
//     if (_player->getPetCount() == 0)
//     {
//         QMessageBox::warning(this, "没有宠物", "你需要先购买宠物才能使用食物！");
//         return;
//     }

//     // 让用户选择目标宠物
//     QMessageBox msgBox;
//     msgBox.setWindowTitle("选择目标宠物");
//     msgBox.setText("请选择要喂食的宠物：");

//     QVector<QPushButton*> petButtons;
//     for (int i = 0; i < 5; ++i)
//     {
//         Pet* pet = _player->getPetAt(i);
//         if (pet)
//         {
//             auto* btn = msgBox.addButton(QString::fromStdString(pet->getName()), QMessageBox::ActionRole);
//             petButtons.append(btn);
//         }
//     }

//     auto* cancelBtn = msgBox.addButton("取消", QMessageBox::RejectRole);
//     msgBox.exec();

//     auto* clickedBtn = msgBox.clickedButton();
//     if (clickedBtn == cancelBtn)
//         return;

//     // 找到选择的宠物索引
//     int targetPetIndex = -1;
//     int buttonIndex = 0;
//     for (int i = 0; i < 5; ++i)
//     {
//         Pet* pet = _player->getPetAt(i);
//         if (pet)
//         {
//             if (clickedBtn == petButtons[buttonIndex])
//             {
//                 targetPetIndex = i;
//                 break;
//             }
//             buttonIndex++;
//         }
//     }

//     if (targetPetIndex >= 0)
//     {
//         if (_shop->buyFood(index, targetPetIndex))
//         {
//             updateUI();
//             QMessageBox::information(this, "购买成功", "食物效果已应用到宠物！");
//         }
//         else
//         {
//             QMessageBox::warning(this, "购买失败", "金币不足或无法使用该食物！");
//         }
//     }
// }

// void ShopView::onPetFreezeClicked(int index)
// {
//     _shop->togglePetFreeze(index);
//     updateUI();
// }

// void ShopView::onFoodFreezeClicked(int index)
// {
//     _shop->toggleFoodFreeze(index);
//     updateUI();
// }

// void ShopView::resetShop()
// {
//     _shop = std::make_unique<Shop>(_player);
//     updateUI();
// }

