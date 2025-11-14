#ifndef QTSHOPVIEW_H
#define QTSHOPVIEW_H

#include <QWidget>

namespace Ui
{
class QtShopview;
}

class QtShopview : public QWidget
{
    Q_OBJECT

public:
    explicit QtShopview(QWidget* parent = nullptr);
    ~QtShopview();

private:
    Ui::QtShopview* ui;
};

#endif  // QTSHOPVIEW_H
