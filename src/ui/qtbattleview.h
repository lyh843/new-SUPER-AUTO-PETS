#ifndef QTBATTLEVIEW_H
#define QTBATTLEVIEW_H

#include <QWidget>

namespace Ui
{
class QtBattleView;
}

class QtBattleView : public QWidget
{
    Q_OBJECT

public:
    explicit QtBattleView(QWidget* parent = nullptr);
    ~QtBattleView();

private:
    Ui::QtBattleView* ui;
};

#endif  // QTBATTLEVIEW_H
