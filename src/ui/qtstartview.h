#ifndef QTSTARTVIEW_H
#define QTSTARTVIEW_H

#include <QWidget>

namespace Ui
{
class qtStartView;
}

class qtStartView : public QWidget
{
    Q_OBJECT

public:
    explicit qtStartView(QWidget* parent = nullptr);
    ~qtStartView();

private:
    Ui::qtStartView* ui;
};

#endif  // QTSTARTVIEW_H
