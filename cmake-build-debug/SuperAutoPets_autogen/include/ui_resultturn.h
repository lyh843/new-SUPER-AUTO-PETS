/********************************************************************************
** Form generated from reading UI file 'resultturn.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESULTTURN_H
#define UI_RESULTTURN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ResultTurn
{
public:
    QLabel *label_background;
    QLabel *label_resultIcon_0;
    QLabel *label_resultIcon_1;
    QLabel *label_resultIcon_2;
    QLabel *label_resultIcon_3;
    QLabel *label_resultIcon_4;

    void setupUi(QWidget *ResultTurn)
    {
        if (ResultTurn->objectName().isEmpty())
            ResultTurn->setObjectName("ResultTurn");
        ResultTurn->resize(1400, 800);
        label_background = new QLabel(ResultTurn);
        label_background->setObjectName("label_background");
        label_background->setGeometry(QRect(290, 130, 49, 14));
        label_resultIcon_0 = new QLabel(ResultTurn);
        label_resultIcon_0->setObjectName("label_resultIcon_0");
        label_resultIcon_0->setGeometry(QRect(30, 730, 49, 14));
        label_resultIcon_1 = new QLabel(ResultTurn);
        label_resultIcon_1->setObjectName("label_resultIcon_1");
        label_resultIcon_1->setGeometry(QRect(100, 730, 49, 14));
        label_resultIcon_2 = new QLabel(ResultTurn);
        label_resultIcon_2->setObjectName("label_resultIcon_2");
        label_resultIcon_2->setGeometry(QRect(170, 730, 49, 14));
        label_resultIcon_3 = new QLabel(ResultTurn);
        label_resultIcon_3->setObjectName("label_resultIcon_3");
        label_resultIcon_3->setGeometry(QRect(250, 730, 49, 14));
        label_resultIcon_4 = new QLabel(ResultTurn);
        label_resultIcon_4->setObjectName("label_resultIcon_4");
        label_resultIcon_4->setGeometry(QRect(330, 730, 49, 14));

        retranslateUi(ResultTurn);

        QMetaObject::connectSlotsByName(ResultTurn);
    } // setupUi

    void retranslateUi(QWidget *ResultTurn)
    {
        ResultTurn->setWindowTitle(QCoreApplication::translate("ResultTurn", "Form", nullptr));
        label_background->setText(QString());
        label_resultIcon_0->setText(QString());
        label_resultIcon_1->setText(QString());
        label_resultIcon_2->setText(QString());
        label_resultIcon_3->setText(QString());
        label_resultIcon_4->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ResultTurn: public Ui_ResultTurn {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESULTTURN_H
