/********************************************************************************
** Form generated from reading UI file 'StartView.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTVIEW_H
#define UI_STARTVIEW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StartView
{
public:
    QLabel *background_label;
    QLabel *brandLabel;
    QPushButton *playButton;
    QPushButton *encyclopediaButton;
    QPushButton *recordsButton;
    QLabel *playLabel;
    QLabel *petsLabel;
    QLabel *historyLabel;

    void setupUi(QWidget *StartView)
    {
        if (StartView->objectName().isEmpty())
            StartView->setObjectName("StartView");
        StartView->resize(1400, 800);
        background_label = new QLabel(StartView);
        background_label->setObjectName("background_label");
        background_label->setGeometry(QRect(0, 0, 1400, 800));
        background_label->setPixmap(QPixmap(QString::fromUtf8(":/else/photo/backgroundStartview.png")));
        background_label->setScaledContents(true);
        brandLabel = new QLabel(StartView);
        brandLabel->setObjectName("brandLabel");
        brandLabel->setGeometry(QRect(10, 10, 290, 135));
        brandLabel->setPixmap(QPixmap(QString::fromUtf8(":/else/photo/Brand.png")));
        brandLabel->setScaledContents(true);
        playButton = new QPushButton(StartView);
        playButton->setObjectName("playButton");
        playButton->setGeometry(QRect(430, 90, 570, 210));
        playButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        playButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: transparent;\n"
"    border: none;\n"
"}\n"
""));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/else/photo/Buttonstartview.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        playButton->setIcon(icon);
        playButton->setIconSize(QSize(570, 210));
        encyclopediaButton = new QPushButton(StartView);
        encyclopediaButton->setObjectName("encyclopediaButton");
        encyclopediaButton->setGeometry(QRect(430, 330, 570, 100));
        encyclopediaButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        encyclopediaButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: transparent;\n"
"    border: none;\n"
"}\n"
""));
        encyclopediaButton->setIcon(icon);
        encyclopediaButton->setIconSize(QSize(570, 210));
        recordsButton = new QPushButton(StartView);
        recordsButton->setObjectName("recordsButton");
        recordsButton->setGeometry(QRect(430, 470, 570, 100));
        recordsButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        recordsButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: transparent;\n"
"    border: none;\n"
"}\n"
""));
        recordsButton->setIcon(icon);
        recordsButton->setIconSize(QSize(570, 210));
        playLabel = new QLabel(StartView);
        playLabel->setObjectName("playLabel");
        playLabel->setGeometry(QRect(660, 130, 151, 121));
        QFont font;
        font.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221")});
        font.setPointSize(48);
        font.setBold(true);
        playLabel->setFont(font);
        playLabel->setStyleSheet(QString::fromUtf8("color:black;"));
        petsLabel = new QLabel(StartView);
        petsLabel->setObjectName("petsLabel");
        petsLabel->setGeometry(QRect(660, 330, 141, 100));
        petsLabel->setFont(font);
        petsLabel->setStyleSheet(QString::fromUtf8("color:black;"));
        historyLabel = new QLabel(StartView);
        historyLabel->setObjectName("historyLabel");
        historyLabel->setGeometry(QRect(660, 470, 171, 100));
        historyLabel->setFont(font);
        historyLabel->setStyleSheet(QString::fromUtf8("color:black;"));

        retranslateUi(StartView);

        QMetaObject::connectSlotsByName(StartView);
    } // setupUi

    void retranslateUi(QWidget *StartView)
    {
        StartView->setWindowTitle(QCoreApplication::translate("StartView", "Super Auto Pets - \344\270\273\350\217\234\345\215\225", nullptr));
        background_label->setText(QString());
        brandLabel->setText(QString());
        playButton->setText(QString());
        encyclopediaButton->setText(QString());
        recordsButton->setText(QString());
        playLabel->setText(QCoreApplication::translate("StartView", "\346\270\270\347\216\251", nullptr));
        petsLabel->setText(QCoreApplication::translate("StartView", "\345\256\240\347\211\251", nullptr));
        historyLabel->setText(QCoreApplication::translate("StartView", "\346\210\230\347\273\251", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StartView: public Ui_StartView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTVIEW_H
