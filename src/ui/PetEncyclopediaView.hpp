#pragma once

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QPixmap>

class PetEncyclopediaView : public QWidget
{
    Q_OBJECT

private:
    QScrollArea* _scrollArea;
    QWidget* _contentWidget;
    QVBoxLayout* _mainLayout;
    QPushButton* _backToStartButton;
    QPushButton* _backToShopButton;
    QPixmap _bgPixmap;

    void setupUI();
    QWidget* createPetCard(const QString& name, const QString& tier, int attack, int health, const QString& ability);
    QWidget* createFoodCard(const QString& name, const QString& tier, int cost, const QString& effect);

public:
    explicit PetEncyclopediaView(QWidget* parent = nullptr);
    ~PetEncyclopediaView() = default;

protected:
    void paintEvent(QPaintEvent* event) override;

signals:
    void backClicked();      // 返回主菜单
    void backToShopClicked(); // 返回商店
};

