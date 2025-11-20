#ifndef RESULTTURN_H
#define RESULTTURN_H

#include <QWidget>

namespace Ui
{
class resultTurn;
}

class resultTurn : public QWidget
{
    Q_OBJECT

public:
    explicit resultTurn(QWidget* parent = nullptr);
    ~resultTurn();

private:
    Ui::resultTurn* ui;
};

#endif  // RESULTTURN_H
