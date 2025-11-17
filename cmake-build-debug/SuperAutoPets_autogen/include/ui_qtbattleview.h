/********************************************************************************
** Form generated from reading UI file 'qtbattleview.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTBATTLEVIEW_H
#define UI_QTBATTLEVIEW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtBattleView
{
public:
    QPushButton *start_button;
    QPushButton *auto_play_button;
    QPushButton *forward_button;
    QLabel *start;
    QLabel *auto_play;
    QLabel *forward;
    QLabel *start_font;
    QLabel *auto_play_font;
    QLabel *forward_font;
    QLabel *background;
    QLabel *hourglass_left;
    QLabel *heart_left;
    QLabel *trophy_left;
    QLabel *You;
    QLabel *hourglass_right;
    QLabel *trophy_right;
    QLabel *heart_right;
    QLabel *Opponent;
    QLabel *mask_right;
    QLabel *mask_left;
    QLabel *your_pet_1;
    QLabel *your_pet_2;
    QLabel *your_pet_3;
    QLabel *your_pet_4;
    QLabel *your_pet_5;
    QLabel *opponents_pet_1;
    QLabel *opponents_pet_2;
    QLabel *opponents_pet_3;
    QLabel *opponents_pet_4;
    QLabel *opponents_pet_5;
    QPushButton *settingsButton;
    QLabel *label;

    void setupUi(QWidget *QtBattleView)
    {
        if (QtBattleView->objectName().isEmpty())
            QtBattleView->setObjectName("QtBattleView");
        QtBattleView->resize(1400, 800);
        start_button = new QPushButton(QtBattleView);
        start_button->setObjectName("start_button");
        start_button->setGeometry(QRect(530, 10, 85, 100));
        start_button->setStyleSheet(QString::fromUtf8("background-color: rgba(0, 0, 0, 0.3);\n"
"border-radius: 10px;\n"
"border: 1px solid rgba(100, 100, 100, 0.5);"));
        auto_play_button = new QPushButton(QtBattleView);
        auto_play_button->setObjectName("auto_play_button");
        auto_play_button->setGeometry(QRect(658, 10, 85, 100));
        auto_play_button->setStyleSheet(QString::fromUtf8("background-color: rgba(0, 0, 0, 0.3);\n"
"border-radius: 10px;\n"
"border: 1px solid rgba(100, 100, 100, 0.5);"));
        forward_button = new QPushButton(QtBattleView);
        forward_button->setObjectName("forward_button");
        forward_button->setGeometry(QRect(786, 10, 85, 100));
        forward_button->setStyleSheet(QString::fromUtf8("background-color: rgba(0, 0, 0, 0.3);\n"
"border-radius: 10px;\n"
"border: 1px solid rgba(100, 100, 100, 0.5);"));
        start = new QLabel(QtBattleView);
        start->setObjectName("start");
        start->setGeometry(QRect(550, 47, 50, 50));
        start->setBaseSize(QSize(0, 0));
        start->setCursor(QCursor(Qt::CursorShape::ArrowCursor));
        start->setStyleSheet(QString::fromUtf8("background-image: url(D:\\SAP_projects_new\\new-SUPER-AUTO-PETS\\src\\photo);\n"
"background-repeat: no-repeat;\n"
"background-position: center;"));
        start->setTextFormat(Qt::TextFormat::AutoText);
        start->setPixmap(QPixmap(QString::fromUtf8(":/else/photo/Play.png")));
        start->setScaledContents(true);
        auto_play = new QLabel(QtBattleView);
        auto_play->setObjectName("auto_play");
        auto_play->setGeometry(QRect(678, 47, 50, 50));
        auto_play->setTextFormat(Qt::TextFormat::MarkdownText);
        auto_play->setPixmap(QPixmap(QString::fromUtf8(":/else/photo/Refresh.png")));
        auto_play->setScaledContents(true);
        forward = new QLabel(QtBattleView);
        forward->setObjectName("forward");
        forward->setGeometry(QRect(806, 47, 50, 50));
        forward->setBaseSize(QSize(0, 0));
        forward->setCursor(QCursor(Qt::CursorShape::ArrowCursor));
        forward->setStyleSheet(QString::fromUtf8("background-image: url(D:\\SAP_projects_new\\new-SUPER-AUTO-PETS\\src\\photo);\n"
"background-repeat: no-repeat;\n"
"background-position: center;"));
        forward->setTextFormat(Qt::TextFormat::AutoText);
        forward->setPixmap(QPixmap(QString::fromUtf8(":/else/photo/Skip.png")));
        forward->setScaledContents(true);
        start_font = new QLabel(QtBattleView);
        start_font->setObjectName("start_font");
        start_font->setGeometry(QRect(533, 15, 81, 31));
        start_font->setStyleSheet(QString::fromUtf8("color: white;"));
        start_font->setLineWidth(0);
        start_font->setTextFormat(Qt::TextFormat::MarkdownText);
        start_font->setScaledContents(true);
        start_font->setAlignment(Qt::AlignmentFlag::AlignCenter);
        start_font->setWordWrap(true);
        auto_play_font = new QLabel(QtBattleView);
        auto_play_font->setObjectName("auto_play_font");
        auto_play_font->setGeometry(QRect(661, 15, 81, 31));
        auto_play_font->setStyleSheet(QString::fromUtf8("color: white;"));
        auto_play_font->setLineWidth(0);
        auto_play_font->setTextFormat(Qt::TextFormat::MarkdownText);
        auto_play_font->setScaledContents(true);
        auto_play_font->setAlignment(Qt::AlignmentFlag::AlignCenter);
        auto_play_font->setWordWrap(true);
        forward_font = new QLabel(QtBattleView);
        forward_font->setObjectName("forward_font");
        forward_font->setGeometry(QRect(789, 15, 81, 31));
        forward_font->setStyleSheet(QString::fromUtf8("color: white;"));
        forward_font->setLineWidth(0);
        forward_font->setTextFormat(Qt::TextFormat::MarkdownText);
        forward_font->setScaledContents(true);
        forward_font->setAlignment(Qt::AlignmentFlag::AlignCenter);
        forward_font->setWordWrap(true);
        background = new QLabel(QtBattleView);
        background->setObjectName("background");
        background->setGeometry(QRect(0, 0, 1400, 800));
        background->setPixmap(QPixmap(QString::fromUtf8(":/else/photo/FieldBattleView.png")));
        background->setScaledContents(true);
        background->setAlignment(Qt::AlignmentFlag::AlignCenter);
        hourglass_left = new QLabel(QtBattleView);
        hourglass_left->setObjectName("hourglass_left");
        hourglass_left->setGeometry(QRect(20, 737, 45, 45));
        hourglass_left->setPixmap(QPixmap(QString::fromUtf8(":/else/photo/NewHourglass.png")));
        hourglass_left->setScaledContents(true);
        heart_left = new QLabel(QtBattleView);
        heart_left->setObjectName("heart_left");
        heart_left->setGeometry(QRect(110, 737, 45, 45));
        heart_left->setPixmap(QPixmap(QString::fromUtf8(":/else/photo/Heart.png")));
        heart_left->setScaledContents(true);
        trophy_left = new QLabel(QtBattleView);
        trophy_left->setObjectName("trophy_left");
        trophy_left->setGeometry(QRect(64, 737, 45, 45));
        trophy_left->setPixmap(QPixmap(QString::fromUtf8(":/else/photo/NewTrophy.png")));
        trophy_left->setScaledContents(true);
        You = new QLabel(QtBattleView);
        You->setObjectName("You");
        You->setGeometry(QRect(140, 730, 111, 61));
        You->setStyleSheet(QString::fromUtf8("color: white;\n"
"font-weight: 600;\n"
"font-size: 24px;"));
        You->setScaledContents(true);
        You->setAlignment(Qt::AlignmentFlag::AlignCenter);
        You->setWordWrap(true);
        hourglass_right = new QLabel(QtBattleView);
        hourglass_right->setObjectName("hourglass_right");
        hourglass_right->setGeometry(QRect(1240, 737, 45, 45));
        hourglass_right->setPixmap(QPixmap(QString::fromUtf8(":/else/photo/NewHourglass.png")));
        hourglass_right->setScaledContents(true);
        trophy_right = new QLabel(QtBattleView);
        trophy_right->setObjectName("trophy_right");
        trophy_right->setGeometry(QRect(1284, 737, 45, 45));
        trophy_right->setPixmap(QPixmap(QString::fromUtf8(":/else/photo/NewTrophy.png")));
        trophy_right->setScaledContents(true);
        heart_right = new QLabel(QtBattleView);
        heart_right->setObjectName("heart_right");
        heart_right->setGeometry(QRect(1330, 737, 45, 45));
        heart_right->setPixmap(QPixmap(QString::fromUtf8(":/else/photo/Heart.png")));
        heart_right->setScaledContents(true);
        Opponent = new QLabel(QtBattleView);
        Opponent->setObjectName("Opponent");
        Opponent->setGeometry(QRect(1090, 730, 151, 61));
        Opponent->setStyleSheet(QString::fromUtf8("color: white;\n"
"font-weight: 600;\n"
"font-size: 24px;"));
        Opponent->setScaledContents(true);
        Opponent->setAlignment(Qt::AlignmentFlag::AlignCenter);
        Opponent->setWordWrap(true);
        mask_right = new QLabel(QtBattleView);
        mask_right->setObjectName("mask_right");
        mask_right->setGeometry(QRect(1090, 732, 297, 56));
        mask_right->setStyleSheet(QString::fromUtf8("background-color: rgba(0, 0, 0, 0.3);\n"
"border-radius: 12px;\n"
"border: 1px solid rgba(100, 100, 100, 0.5);"));
        mask_left = new QLabel(QtBattleView);
        mask_left->setObjectName("mask_left");
        mask_left->setGeometry(QRect(14, 732, 221, 56));
        mask_left->setStyleSheet(QString::fromUtf8("background-color: rgba(0, 0, 0, 0.3);\n"
"border-radius: 12px;\n"
"border: 1px solid rgba(100, 100, 100, 0.5);"));
        your_pet_1 = new QLabel(QtBattleView);
        your_pet_1->setObjectName("your_pet_1");
        your_pet_1->setGeometry(QRect(15, 440, 130, 130));
        your_pet_1->setScaledContents(true);
        your_pet_2 = new QLabel(QtBattleView);
        your_pet_2->setObjectName("your_pet_2");
        your_pet_2->setGeometry(QRect(147, 440, 130, 130));
        your_pet_2->setScaledContents(true);
        your_pet_3 = new QLabel(QtBattleView);
        your_pet_3->setObjectName("your_pet_3");
        your_pet_3->setGeometry(QRect(279, 440, 130, 130));
        your_pet_3->setScaledContents(true);
        your_pet_4 = new QLabel(QtBattleView);
        your_pet_4->setObjectName("your_pet_4");
        your_pet_4->setGeometry(QRect(411, 440, 130, 130));
        your_pet_4->setScaledContents(true);
        your_pet_5 = new QLabel(QtBattleView);
        your_pet_5->setObjectName("your_pet_5");
        your_pet_5->setGeometry(QRect(543, 440, 130, 130));
        your_pet_5->setScaledContents(true);
        opponents_pet_1 = new QLabel(QtBattleView);
        opponents_pet_1->setObjectName("opponents_pet_1");
        opponents_pet_1->setGeometry(QRect(727, 440, 130, 130));
        opponents_pet_1->setScaledContents(true);
        opponents_pet_2 = new QLabel(QtBattleView);
        opponents_pet_2->setObjectName("opponents_pet_2");
        opponents_pet_2->setGeometry(QRect(859, 440, 130, 130));
        opponents_pet_2->setScaledContents(true);
        opponents_pet_3 = new QLabel(QtBattleView);
        opponents_pet_3->setObjectName("opponents_pet_3");
        opponents_pet_3->setGeometry(QRect(991, 440, 130, 130));
        opponents_pet_3->setScaledContents(true);
        opponents_pet_4 = new QLabel(QtBattleView);
        opponents_pet_4->setObjectName("opponents_pet_4");
        opponents_pet_4->setGeometry(QRect(1123, 440, 130, 130));
        opponents_pet_4->setScaledContents(true);
        opponents_pet_5 = new QLabel(QtBattleView);
        opponents_pet_5->setObjectName("opponents_pet_5");
        opponents_pet_5->setGeometry(QRect(1255, 440, 130, 130));
        opponents_pet_5->setScaledContents(true);
        settingsButton = new QPushButton(QtBattleView);
        settingsButton->setObjectName("settingsButton");
        settingsButton->setGeometry(QRect(1325, 15, 60, 60));
        settingsButton->setMouseTracking(false);
        settingsButton->setAcceptDrops(false);
        settingsButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-repeat: no-repeat;\n"
"    background-position: center;\n"
"    background-size: contain;\n"
"    background-color: transparent;\n"
"    border: none;\n"
"    border: none;\n"
"    min-width: 40px;\n"
"    min-height: 40px;\n"
"}"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/else/photo/Bars.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        settingsButton->setIcon(icon);
        settingsButton->setIconSize(QSize(40, 40));
        settingsButton->setCheckable(false);
        settingsButton->setAutoRepeat(false);
        settingsButton->setAutoExclusive(false);
        settingsButton->setAutoDefault(false);
        label = new QLabel(QtBattleView);
        label->setObjectName("label");
        label->setGeometry(QRect(1325, 15, 60, 60));
        label->setPixmap(QPixmap(QString::fromUtf8(":/else/photo/ButtonFlatOrange.png")));
        label->setScaledContents(true);
        background->raise();
        auto_play_button->raise();
        auto_play->raise();
        auto_play_font->raise();
        mask_right->raise();
        mask_left->raise();
        heart_left->raise();
        heart_right->raise();
        hourglass_left->raise();
        hourglass_right->raise();
        Opponent->raise();
        trophy_left->raise();
        trophy_right->raise();
        You->raise();
        your_pet_1->raise();
        your_pet_2->raise();
        your_pet_3->raise();
        your_pet_4->raise();
        your_pet_5->raise();
        opponents_pet_1->raise();
        opponents_pet_2->raise();
        opponents_pet_3->raise();
        opponents_pet_4->raise();
        opponents_pet_5->raise();
        label->raise();
        settingsButton->raise();
        forward_button->raise();
        forward_font->raise();
        forward->raise();
        start_button->raise();
        start->raise();
        start_font->raise();

        retranslateUi(QtBattleView);

        QMetaObject::connectSlotsByName(QtBattleView);
    } // setupUi

    void retranslateUi(QWidget *QtBattleView)
    {
        QtBattleView->setWindowTitle(QCoreApplication::translate("QtBattleView", "Form", nullptr));
        start_button->setText(QString());
        auto_play_button->setText(QString());
        forward_button->setText(QString());
        start->setText(QString());
        auto_play->setText(QString());
        forward->setText(QString());
        start_font->setText(QCoreApplication::translate("QtBattleView", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:700;\">\345\274\200\345\247\213\346\210\230\346\226\227</span></p></body></html>", nullptr));
        auto_play_font->setText(QCoreApplication::translate("QtBattleView", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:700;\">\350\207\252\345\212\250\346\222\255\346\224\276</span></p></body></html>", nullptr));
        forward_font->setText(QCoreApplication::translate("QtBattleView", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:700;\">\345\215\225\346\255\245\346\211\247\350\241\214</span></p></body></html>", nullptr));
        background->setText(QString());
        hourglass_left->setText(QString());
        heart_left->setText(QString());
        trophy_left->setText(QString());
        You->setText(QCoreApplication::translate("QtBattleView", "You", nullptr));
        hourglass_right->setText(QString());
        trophy_right->setText(QString());
        heart_right->setText(QString());
        Opponent->setText(QCoreApplication::translate("QtBattleView", "Opponent", nullptr));
        mask_right->setText(QString());
        mask_left->setText(QString());
        your_pet_1->setText(QString());
        your_pet_2->setText(QString());
        your_pet_3->setText(QString());
        your_pet_4->setText(QString());
        your_pet_5->setText(QString());
        opponents_pet_1->setText(QString());
        opponents_pet_2->setText(QString());
        opponents_pet_3->setText(QString());
        opponents_pet_4->setText(QString());
        opponents_pet_5->setText(QString());
        settingsButton->setText(QString());
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class QtBattleView: public Ui_QtBattleView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTBATTLEVIEW_H
