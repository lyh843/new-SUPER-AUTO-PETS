#ifndef RESULTTURN_H
#define RESULTTURN_H

#include <QWidget>
#include "BattleView.hpp"

#include "ui/StartView.hpp"
#include "ui/QtShopview.h"
#include "ui/qtbattleview.h"
#include "ui/PetEncyclopediaView.hpp"
#include "ui/RecordsView.hpp"
#include "model/Player.hpp"
#include "engine/BattleEngine.hpp"


namespace Ui
{
class ResultTurn;
}

class ResultTurn : public QWidget
{
    Q_OBJECT

public:
    explicit ResultTurn(QWidget* parent = nullptr);
    void loadingPicture(BattleResult result, Player* _player);
    ~ResultTurn();

private:
    Ui::ResultTurn* ui;
};

#endif  // RESULTTURN_H
