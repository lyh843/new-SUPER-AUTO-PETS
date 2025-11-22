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
    QLabel *setting;
    QLabel *hourglass_left_num;
    QLabel *heart_left_num;
    QLabel *trophy_left_num;
    QLabel *hour_glass_right_num;
    QLabel *heart_right_num;
    QLabel *trophy_right_num;
    QLabel *your_pet_1_status;
    QLabel *your_pet_3_status;
    QLabel *your_pet_4_status;
    QLabel *your_pet_5_status;
    QLabel *opponents_pet_1_status;
    QLabel *opponents_pet_2_status;
    QLabel *opponents_pet_3_status;
    QLabel *opponents_pet_4_status;
    QLabel *opponents_pet_5_status;
    QLabel *your_pet_2_status;
    QLabel *your_Attack_1;
    QLabel *your_HP_1;
    QLabel *your_HP_2;
    QLabel *your_HP_3;
    QLabel *your_HP_4;
    QLabel *your_HP_5;
    QLabel *your_Attack_2;
    QLabel *your_Attack_3;
    QLabel *your_Attack_4;
    QLabel *your_Attack_5;
    QLabel *opponents_Attack_1;
    QLabel *opponents_Attack_2;
    QLabel *opponents_Attack_3;
    QLabel *opponents_Attack_4;
    QLabel *opponents_Attack_5;
    QLabel *opponents_HP_1;
    QLabel *opponents_HP_2;
    QLabel *opponents_HP_3;
    QLabel *opponents_HP_4;
    QLabel *opponents_HP_5;

    void setupUi(QWidget *QtBattleView)
    {
        if (QtBattleView->objectName().isEmpty())
            QtBattleView->setObjectName("QtBattleView");
        QtBattleView->resize(1400, 800);
        start_button = new QPushButton(QtBattleView);
        start_button->setObjectName("start_button");
        start_button->setGeometry(QRect(530, 10, 85, 100));
        start_button->setCursor(QCursor(Qt::CursorShape::ArrowCursor));
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
        start_font->setCursor(QCursor(Qt::CursorShape::ArrowCursor));
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
        background->setEnabled(true);
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
        setting = new QLabel(QtBattleView);
        setting->setObjectName("setting");
        setting->setGeometry(QRect(1325, 15, 60, 60));
        setting->setPixmap(QPixmap(QString::fromUtf8(":/else/photo/ButtonFlatOrange.png")));
        setting->setScaledContents(true);
        hourglass_left_num = new QLabel(QtBattleView);
        hourglass_left_num->setObjectName("hourglass_left_num");
        hourglass_left_num->setGeometry(QRect(17, 733, 51, 51));
        hourglass_left_num->setStyleSheet(QString::fromUtf8("/* \346\233\264\345\256\214\346\225\264\347\232\204\346\240\267\345\274\217 */\n"
"color: white;\n"
"font-weight: bold;\n"
"font-size: 18px;\n"
"font-family: \"Microsoft YaHei\";\n"
"background-color: transparent;\n"
""));
        hourglass_left_num->setScaledContents(false);
        hourglass_left_num->setAlignment(Qt::AlignmentFlag::AlignCenter);
        heart_left_num = new QLabel(QtBattleView);
        heart_left_num->setObjectName("heart_left_num");
        heart_left_num->setGeometry(QRect(107, 733, 51, 51));
        heart_left_num->setStyleSheet(QString::fromUtf8("/* \346\233\264\345\256\214\346\225\264\347\232\204\346\240\267\345\274\217 */\n"
"color: white;\n"
"font-weight: bold;\n"
"font-size: 18px;\n"
"font-family: \"Microsoft YaHei\";\n"
"background-color: transparent;"));
        heart_left_num->setScaledContents(false);
        heart_left_num->setAlignment(Qt::AlignmentFlag::AlignCenter);
        trophy_left_num = new QLabel(QtBattleView);
        trophy_left_num->setObjectName("trophy_left_num");
        trophy_left_num->setGeometry(QRect(61, 733, 51, 51));
        trophy_left_num->setStyleSheet(QString::fromUtf8("/* \346\233\264\345\256\214\346\225\264\347\232\204\346\240\267\345\274\217 */\n"
"color: white;\n"
"font-weight: bold;\n"
"font-size: 18px;\n"
"font-family: \"Microsoft YaHei\";\n"
"background-color: transparent;"));
        trophy_left_num->setScaledContents(false);
        trophy_left_num->setAlignment(Qt::AlignmentFlag::AlignCenter);
        hour_glass_right_num = new QLabel(QtBattleView);
        hour_glass_right_num->setObjectName("hour_glass_right_num");
        hour_glass_right_num->setGeometry(QRect(1237, 733, 51, 51));
        hour_glass_right_num->setStyleSheet(QString::fromUtf8("/* \346\233\264\345\256\214\346\225\264\347\232\204\346\240\267\345\274\217 */\n"
"color: white;\n"
"font-weight: bold;\n"
"font-size: 18px;\n"
"font-family: \"Microsoft YaHei\";\n"
"background-color: transparent;"));
        hour_glass_right_num->setScaledContents(false);
        hour_glass_right_num->setAlignment(Qt::AlignmentFlag::AlignCenter);
        heart_right_num = new QLabel(QtBattleView);
        heart_right_num->setObjectName("heart_right_num");
        heart_right_num->setGeometry(QRect(1327, 733, 51, 51));
        heart_right_num->setStyleSheet(QString::fromUtf8("/* \346\233\264\345\256\214\346\225\264\347\232\204\346\240\267\345\274\217 */\n"
"color: white;\n"
"font-weight: bold;\n"
"font-size: 18px;\n"
"font-family: \"Microsoft YaHei\";\n"
"background-color: transparent;"));
        heart_right_num->setScaledContents(false);
        heart_right_num->setAlignment(Qt::AlignmentFlag::AlignCenter);
        trophy_right_num = new QLabel(QtBattleView);
        trophy_right_num->setObjectName("trophy_right_num");
        trophy_right_num->setGeometry(QRect(1281, 733, 51, 51));
        trophy_right_num->setStyleSheet(QString::fromUtf8("/* \346\233\264\345\256\214\346\225\264\347\232\204\346\240\267\345\274\217 */\n"
"color: white;\n"
"font-weight: bold;\n"
"font-size: 18px;\n"
"font-family: \"Microsoft YaHei\";\n"
"background-color: transparent;"));
        trophy_right_num->setScaledContents(false);
        trophy_right_num->setAlignment(Qt::AlignmentFlag::AlignCenter);
        your_pet_1_status = new QLabel(QtBattleView);
        your_pet_1_status->setObjectName("your_pet_1_status");
        your_pet_1_status->setGeometry(QRect(15, 570, 130, 60));
        your_pet_1_status->setPixmap(QPixmap(QString::fromUtf8(":/else/photo/Stats.png")));
        your_pet_1_status->setScaledContents(true);
        your_pet_3_status = new QLabel(QtBattleView);
        your_pet_3_status->setObjectName("your_pet_3_status");
        your_pet_3_status->setGeometry(QRect(279, 570, 130, 60));
        your_pet_3_status->setPixmap(QPixmap(QString::fromUtf8(":/else/photo/Stats.png")));
        your_pet_3_status->setScaledContents(true);
        your_pet_4_status = new QLabel(QtBattleView);
        your_pet_4_status->setObjectName("your_pet_4_status");
        your_pet_4_status->setGeometry(QRect(411, 570, 130, 60));
        your_pet_4_status->setPixmap(QPixmap(QString::fromUtf8(":/else/photo/Stats.png")));
        your_pet_4_status->setScaledContents(true);
        your_pet_5_status = new QLabel(QtBattleView);
        your_pet_5_status->setObjectName("your_pet_5_status");
        your_pet_5_status->setGeometry(QRect(543, 570, 130, 60));
        your_pet_5_status->setPixmap(QPixmap(QString::fromUtf8(":/else/photo/Stats.png")));
        your_pet_5_status->setScaledContents(true);
        opponents_pet_1_status = new QLabel(QtBattleView);
        opponents_pet_1_status->setObjectName("opponents_pet_1_status");
        opponents_pet_1_status->setGeometry(QRect(727, 570, 130, 60));
        opponents_pet_1_status->setPixmap(QPixmap(QString::fromUtf8(":/else/photo/Stats.png")));
        opponents_pet_1_status->setScaledContents(true);
        opponents_pet_2_status = new QLabel(QtBattleView);
        opponents_pet_2_status->setObjectName("opponents_pet_2_status");
        opponents_pet_2_status->setGeometry(QRect(859, 570, 130, 60));
        opponents_pet_2_status->setPixmap(QPixmap(QString::fromUtf8(":/else/photo/Stats.png")));
        opponents_pet_2_status->setScaledContents(true);
        opponents_pet_3_status = new QLabel(QtBattleView);
        opponents_pet_3_status->setObjectName("opponents_pet_3_status");
        opponents_pet_3_status->setGeometry(QRect(991, 570, 130, 60));
        opponents_pet_3_status->setPixmap(QPixmap(QString::fromUtf8(":/else/photo/Stats.png")));
        opponents_pet_3_status->setScaledContents(true);
        opponents_pet_4_status = new QLabel(QtBattleView);
        opponents_pet_4_status->setObjectName("opponents_pet_4_status");
        opponents_pet_4_status->setGeometry(QRect(1123, 570, 130, 60));
        opponents_pet_4_status->setPixmap(QPixmap(QString::fromUtf8(":/else/photo/Stats.png")));
        opponents_pet_4_status->setScaledContents(true);
        opponents_pet_5_status = new QLabel(QtBattleView);
        opponents_pet_5_status->setObjectName("opponents_pet_5_status");
        opponents_pet_5_status->setGeometry(QRect(1255, 570, 130, 60));
        opponents_pet_5_status->setPixmap(QPixmap(QString::fromUtf8(":/else/photo/Stats.png")));
        opponents_pet_5_status->setScaledContents(true);
        your_pet_2_status = new QLabel(QtBattleView);
        your_pet_2_status->setObjectName("your_pet_2_status");
        your_pet_2_status->setGeometry(QRect(147, 570, 130, 60));
        your_pet_2_status->setPixmap(QPixmap(QString::fromUtf8(":/else/photo/Stats.png")));
        your_pet_2_status->setScaledContents(true);
        your_Attack_1 = new QLabel(QtBattleView);
        your_Attack_1->setObjectName("your_Attack_1");
        your_Attack_1->setEnabled(true);
        your_Attack_1->setGeometry(QRect(25, 575, 51, 51));
        your_Attack_1->setStyleSheet(QString::fromUtf8("/* \346\233\264\345\256\214\346\225\264\347\232\204\346\240\267\345\274\217 */\n"
"color: white;\n"
"font-weight: bold;\n"
"font-size: 24px;\n"
"font-family: \"Microsoft YaHei\";\n"
"background-color: transparent;"));
        your_Attack_1->setScaledContents(false);
        your_Attack_1->setAlignment(Qt::AlignmentFlag::AlignCenter);
        your_HP_1 = new QLabel(QtBattleView);
        your_HP_1->setObjectName("your_HP_1");
        your_HP_1->setEnabled(true);
        your_HP_1->setGeometry(QRect(88, 575, 51, 51));
        your_HP_1->setStyleSheet(QString::fromUtf8("/* \346\233\264\345\256\214\346\225\264\347\232\204\346\240\267\345\274\217 */\n"
"color: white;\n"
"font-weight: bold;\n"
"font-size: 24px;\n"
"font-family: \"Microsoft YaHei\";\n"
"background-color: transparent;"));
        your_HP_1->setScaledContents(false);
        your_HP_1->setAlignment(Qt::AlignmentFlag::AlignCenter);
        your_HP_2 = new QLabel(QtBattleView);
        your_HP_2->setObjectName("your_HP_2");
        your_HP_2->setEnabled(true);
        your_HP_2->setGeometry(QRect(220, 575, 51, 51));
        your_HP_2->setStyleSheet(QString::fromUtf8("/* \346\233\264\345\256\214\346\225\264\347\232\204\346\240\267\345\274\217 */\n"
"color: white;\n"
"font-weight: bold;\n"
"font-size: 24px;\n"
"font-family: \"Microsoft YaHei\";\n"
"background-color: transparent;"));
        your_HP_2->setScaledContents(false);
        your_HP_2->setAlignment(Qt::AlignmentFlag::AlignCenter);
        your_HP_3 = new QLabel(QtBattleView);
        your_HP_3->setObjectName("your_HP_3");
        your_HP_3->setEnabled(true);
        your_HP_3->setGeometry(QRect(352, 575, 51, 51));
        your_HP_3->setStyleSheet(QString::fromUtf8("/* \346\233\264\345\256\214\346\225\264\347\232\204\346\240\267\345\274\217 */\n"
"color: white;\n"
"font-weight: bold;\n"
"font-size: 24px;\n"
"font-family: \"Microsoft YaHei\";\n"
"background-color: transparent;"));
        your_HP_3->setScaledContents(false);
        your_HP_3->setAlignment(Qt::AlignmentFlag::AlignCenter);
        your_HP_4 = new QLabel(QtBattleView);
        your_HP_4->setObjectName("your_HP_4");
        your_HP_4->setEnabled(true);
        your_HP_4->setGeometry(QRect(484, 575, 51, 51));
        your_HP_4->setStyleSheet(QString::fromUtf8("/* \346\233\264\345\256\214\346\225\264\347\232\204\346\240\267\345\274\217 */\n"
"color: white;\n"
"font-weight: bold;\n"
"font-size: 24px;\n"
"font-family: \"Microsoft YaHei\";\n"
"background-color: transparent;"));
        your_HP_4->setScaledContents(false);
        your_HP_4->setAlignment(Qt::AlignmentFlag::AlignCenter);
        your_HP_5 = new QLabel(QtBattleView);
        your_HP_5->setObjectName("your_HP_5");
        your_HP_5->setEnabled(true);
        your_HP_5->setGeometry(QRect(616, 575, 51, 51));
        your_HP_5->setStyleSheet(QString::fromUtf8("/* \346\233\264\345\256\214\346\225\264\347\232\204\346\240\267\345\274\217 */\n"
"color: white;\n"
"font-weight: bold;\n"
"font-size: 24px;\n"
"font-family: \"Microsoft YaHei\";\n"
"background-color: transparent;"));
        your_HP_5->setScaledContents(false);
        your_HP_5->setAlignment(Qt::AlignmentFlag::AlignCenter);
        your_Attack_2 = new QLabel(QtBattleView);
        your_Attack_2->setObjectName("your_Attack_2");
        your_Attack_2->setEnabled(true);
        your_Attack_2->setGeometry(QRect(157, 575, 51, 51));
        your_Attack_2->setStyleSheet(QString::fromUtf8("/* \346\233\264\345\256\214\346\225\264\347\232\204\346\240\267\345\274\217 */\n"
"color: white;\n"
"font-weight: bold;\n"
"font-size: 24px;\n"
"font-family: \"Microsoft YaHei\";\n"
"background-color: transparent;"));
        your_Attack_2->setScaledContents(false);
        your_Attack_2->setAlignment(Qt::AlignmentFlag::AlignCenter);
        your_Attack_3 = new QLabel(QtBattleView);
        your_Attack_3->setObjectName("your_Attack_3");
        your_Attack_3->setEnabled(true);
        your_Attack_3->setGeometry(QRect(289, 575, 51, 51));
        your_Attack_3->setStyleSheet(QString::fromUtf8("/* \346\233\264\345\256\214\346\225\264\347\232\204\346\240\267\345\274\217 */\n"
"color: white;\n"
"font-weight: bold;\n"
"font-size: 24px;\n"
"font-family: \"Microsoft YaHei\";\n"
"background-color: transparent;"));
        your_Attack_3->setScaledContents(false);
        your_Attack_3->setAlignment(Qt::AlignmentFlag::AlignCenter);
        your_Attack_4 = new QLabel(QtBattleView);
        your_Attack_4->setObjectName("your_Attack_4");
        your_Attack_4->setEnabled(true);
        your_Attack_4->setGeometry(QRect(421, 575, 51, 51));
        your_Attack_4->setStyleSheet(QString::fromUtf8("/* \346\233\264\345\256\214\346\225\264\347\232\204\346\240\267\345\274\217 */\n"
"color: white;\n"
"font-weight: bold;\n"
"font-size: 24px;\n"
"font-family: \"Microsoft YaHei\";\n"
"background-color: transparent;"));
        your_Attack_4->setScaledContents(false);
        your_Attack_4->setAlignment(Qt::AlignmentFlag::AlignCenter);
        your_Attack_5 = new QLabel(QtBattleView);
        your_Attack_5->setObjectName("your_Attack_5");
        your_Attack_5->setEnabled(true);
        your_Attack_5->setGeometry(QRect(553, 575, 51, 51));
        your_Attack_5->setStyleSheet(QString::fromUtf8("/* \346\233\264\345\256\214\346\225\264\347\232\204\346\240\267\345\274\217 */\n"
"color: white;\n"
"font-weight: bold;\n"
"font-size: 24px;\n"
"font-family: \"Microsoft YaHei\";\n"
"background-color: transparent;"));
        your_Attack_5->setScaledContents(false);
        your_Attack_5->setAlignment(Qt::AlignmentFlag::AlignCenter);
        opponents_Attack_1 = new QLabel(QtBattleView);
        opponents_Attack_1->setObjectName("opponents_Attack_1");
        opponents_Attack_1->setEnabled(true);
        opponents_Attack_1->setGeometry(QRect(736, 575, 51, 51));
        opponents_Attack_1->setStyleSheet(QString::fromUtf8("/* \346\233\264\345\256\214\346\225\264\347\232\204\346\240\267\345\274\217 */\n"
"color: white;\n"
"font-weight: bold;\n"
"font-size: 24px;\n"
"font-family: \"Microsoft YaHei\";\n"
"background-color: transparent;"));
        opponents_Attack_1->setScaledContents(false);
        opponents_Attack_1->setAlignment(Qt::AlignmentFlag::AlignCenter);
        opponents_Attack_2 = new QLabel(QtBattleView);
        opponents_Attack_2->setObjectName("opponents_Attack_2");
        opponents_Attack_2->setEnabled(true);
        opponents_Attack_2->setGeometry(QRect(868, 575, 51, 51));
        opponents_Attack_2->setStyleSheet(QString::fromUtf8("/* \346\233\264\345\256\214\346\225\264\347\232\204\346\240\267\345\274\217 */\n"
"color: white;\n"
"font-weight: bold;\n"
"font-size: 24px;\n"
"font-family: \"Microsoft YaHei\";\n"
"background-color: transparent;"));
        opponents_Attack_2->setScaledContents(false);
        opponents_Attack_2->setAlignment(Qt::AlignmentFlag::AlignCenter);
        opponents_Attack_3 = new QLabel(QtBattleView);
        opponents_Attack_3->setObjectName("opponents_Attack_3");
        opponents_Attack_3->setEnabled(true);
        opponents_Attack_3->setGeometry(QRect(1000, 575, 51, 51));
        opponents_Attack_3->setStyleSheet(QString::fromUtf8("/* \346\233\264\345\256\214\346\225\264\347\232\204\346\240\267\345\274\217 */\n"
"color: white;\n"
"font-weight: bold;\n"
"font-size: 24px;\n"
"font-family: \"Microsoft YaHei\";\n"
"background-color: transparent;"));
        opponents_Attack_3->setScaledContents(false);
        opponents_Attack_3->setAlignment(Qt::AlignmentFlag::AlignCenter);
        opponents_Attack_4 = new QLabel(QtBattleView);
        opponents_Attack_4->setObjectName("opponents_Attack_4");
        opponents_Attack_4->setEnabled(true);
        opponents_Attack_4->setGeometry(QRect(1132, 575, 51, 51));
        opponents_Attack_4->setStyleSheet(QString::fromUtf8("/* \346\233\264\345\256\214\346\225\264\347\232\204\346\240\267\345\274\217 */\n"
"color: white;\n"
"font-weight: bold;\n"
"font-size: 24px;\n"
"font-family: \"Microsoft YaHei\";\n"
"background-color: transparent;"));
        opponents_Attack_4->setScaledContents(false);
        opponents_Attack_4->setAlignment(Qt::AlignmentFlag::AlignCenter);
        opponents_Attack_5 = new QLabel(QtBattleView);
        opponents_Attack_5->setObjectName("opponents_Attack_5");
        opponents_Attack_5->setEnabled(true);
        opponents_Attack_5->setGeometry(QRect(1264, 575, 51, 51));
        opponents_Attack_5->setStyleSheet(QString::fromUtf8("/* \346\233\264\345\256\214\346\225\264\347\232\204\346\240\267\345\274\217 */\n"
"color: white;\n"
"font-weight: bold;\n"
"font-size: 24px;\n"
"font-family: \"Microsoft YaHei\";\n"
"background-color: transparent;"));
        opponents_Attack_5->setScaledContents(false);
        opponents_Attack_5->setAlignment(Qt::AlignmentFlag::AlignCenter);
        opponents_HP_1 = new QLabel(QtBattleView);
        opponents_HP_1->setObjectName("opponents_HP_1");
        opponents_HP_1->setEnabled(true);
        opponents_HP_1->setGeometry(QRect(800, 575, 51, 51));
        opponents_HP_1->setStyleSheet(QString::fromUtf8("/* \346\233\264\345\256\214\346\225\264\347\232\204\346\240\267\345\274\217 */\n"
"color: white;\n"
"font-weight: bold;\n"
"font-size: 24px;\n"
"font-family: \"Microsoft YaHei\";\n"
"background-color: transparent;"));
        opponents_HP_1->setScaledContents(false);
        opponents_HP_1->setAlignment(Qt::AlignmentFlag::AlignCenter);
        opponents_HP_2 = new QLabel(QtBattleView);
        opponents_HP_2->setObjectName("opponents_HP_2");
        opponents_HP_2->setEnabled(true);
        opponents_HP_2->setGeometry(QRect(932, 575, 51, 51));
        opponents_HP_2->setStyleSheet(QString::fromUtf8("/* \346\233\264\345\256\214\346\225\264\347\232\204\346\240\267\345\274\217 */\n"
"color: white;\n"
"font-weight: bold;\n"
"font-size: 24px;\n"
"font-family: \"Microsoft YaHei\";\n"
"background-color: transparent;"));
        opponents_HP_2->setScaledContents(false);
        opponents_HP_2->setAlignment(Qt::AlignmentFlag::AlignCenter);
        opponents_HP_3 = new QLabel(QtBattleView);
        opponents_HP_3->setObjectName("opponents_HP_3");
        opponents_HP_3->setEnabled(true);
        opponents_HP_3->setGeometry(QRect(1064, 575, 51, 51));
        opponents_HP_3->setStyleSheet(QString::fromUtf8("/* \346\233\264\345\256\214\346\225\264\347\232\204\346\240\267\345\274\217 */\n"
"color: white;\n"
"font-weight: bold;\n"
"font-size: 24px;\n"
"font-family: \"Microsoft YaHei\";\n"
"background-color: transparent;"));
        opponents_HP_3->setScaledContents(false);
        opponents_HP_3->setAlignment(Qt::AlignmentFlag::AlignCenter);
        opponents_HP_4 = new QLabel(QtBattleView);
        opponents_HP_4->setObjectName("opponents_HP_4");
        opponents_HP_4->setEnabled(true);
        opponents_HP_4->setGeometry(QRect(1196, 575, 51, 51));
        opponents_HP_4->setStyleSheet(QString::fromUtf8("/* \346\233\264\345\256\214\346\225\264\347\232\204\346\240\267\345\274\217 */\n"
"color: white;\n"
"font-weight: bold;\n"
"font-size: 24px;\n"
"font-family: \"Microsoft YaHei\";\n"
"background-color: transparent;"));
        opponents_HP_4->setScaledContents(false);
        opponents_HP_4->setAlignment(Qt::AlignmentFlag::AlignCenter);
        opponents_HP_5 = new QLabel(QtBattleView);
        opponents_HP_5->setObjectName("opponents_HP_5");
        opponents_HP_5->setEnabled(true);
        opponents_HP_5->setGeometry(QRect(1328, 575, 51, 51));
        opponents_HP_5->setStyleSheet(QString::fromUtf8("/* \346\233\264\345\256\214\346\225\264\347\232\204\346\240\267\345\274\217 */\n"
"color: white;\n"
"font-weight: bold;\n"
"font-size: 24px;\n"
"font-family: \"Microsoft YaHei\";\n"
"background-color: transparent;"));
        opponents_HP_5->setScaledContents(false);
        opponents_HP_5->setAlignment(Qt::AlignmentFlag::AlignCenter);
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
        setting->raise();
        settingsButton->raise();
        forward_button->raise();
        forward_font->raise();
        forward->raise();
        start_button->raise();
        start->raise();
        start_font->raise();
        hourglass_left_num->raise();
        heart_left_num->raise();
        trophy_left_num->raise();
        hour_glass_right_num->raise();
        heart_right_num->raise();
        trophy_right_num->raise();
        your_pet_1_status->raise();
        your_pet_3_status->raise();
        your_pet_4_status->raise();
        your_pet_5_status->raise();
        opponents_pet_1_status->raise();
        opponents_pet_2_status->raise();
        opponents_pet_3_status->raise();
        opponents_pet_4_status->raise();
        opponents_pet_5_status->raise();
        your_pet_2_status->raise();
        your_Attack_1->raise();
        your_HP_1->raise();
        your_HP_2->raise();
        your_HP_3->raise();
        your_HP_4->raise();
        your_HP_5->raise();
        your_Attack_2->raise();
        your_Attack_3->raise();
        your_Attack_4->raise();
        your_Attack_5->raise();
        opponents_Attack_1->raise();
        opponents_Attack_2->raise();
        opponents_Attack_3->raise();
        opponents_Attack_4->raise();
        opponents_Attack_5->raise();
        opponents_HP_1->raise();
        opponents_HP_2->raise();
        opponents_HP_3->raise();
        opponents_HP_4->raise();
        opponents_HP_5->raise();

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
        setting->setText(QString());
        hourglass_left_num->setText(QCoreApplication::translate("QtBattleView", "1", nullptr));
        heart_left_num->setText(QCoreApplication::translate("QtBattleView", "1", nullptr));
        trophy_left_num->setText(QCoreApplication::translate("QtBattleView", "1", nullptr));
        hour_glass_right_num->setText(QCoreApplication::translate("QtBattleView", "1", nullptr));
        heart_right_num->setText(QCoreApplication::translate("QtBattleView", "1", nullptr));
        trophy_right_num->setText(QCoreApplication::translate("QtBattleView", "1", nullptr));
        your_pet_1_status->setText(QString());
        your_pet_3_status->setText(QString());
        your_pet_4_status->setText(QString());
        your_pet_5_status->setText(QString());
        opponents_pet_1_status->setText(QString());
        opponents_pet_2_status->setText(QString());
        opponents_pet_3_status->setText(QString());
        opponents_pet_4_status->setText(QString());
        opponents_pet_5_status->setText(QString());
        your_pet_2_status->setText(QString());
        your_Attack_1->setText(QCoreApplication::translate("QtBattleView", "1", nullptr));
        your_HP_1->setText(QCoreApplication::translate("QtBattleView", "1", nullptr));
        your_HP_2->setText(QCoreApplication::translate("QtBattleView", "1", nullptr));
        your_HP_3->setText(QCoreApplication::translate("QtBattleView", "1", nullptr));
        your_HP_4->setText(QCoreApplication::translate("QtBattleView", "1", nullptr));
        your_HP_5->setText(QCoreApplication::translate("QtBattleView", "1", nullptr));
        your_Attack_2->setText(QCoreApplication::translate("QtBattleView", "1", nullptr));
        your_Attack_3->setText(QCoreApplication::translate("QtBattleView", "1", nullptr));
        your_Attack_4->setText(QCoreApplication::translate("QtBattleView", "1", nullptr));
        your_Attack_5->setText(QCoreApplication::translate("QtBattleView", "1", nullptr));
        opponents_Attack_1->setText(QCoreApplication::translate("QtBattleView", "1", nullptr));
        opponents_Attack_2->setText(QCoreApplication::translate("QtBattleView", "1", nullptr));
        opponents_Attack_3->setText(QCoreApplication::translate("QtBattleView", "1", nullptr));
        opponents_Attack_4->setText(QCoreApplication::translate("QtBattleView", "1", nullptr));
        opponents_Attack_5->setText(QCoreApplication::translate("QtBattleView", "1", nullptr));
        opponents_HP_1->setText(QCoreApplication::translate("QtBattleView", "1", nullptr));
        opponents_HP_2->setText(QCoreApplication::translate("QtBattleView", "1", nullptr));
        opponents_HP_3->setText(QCoreApplication::translate("QtBattleView", "1", nullptr));
        opponents_HP_4->setText(QCoreApplication::translate("QtBattleView", "1", nullptr));
        opponents_HP_5->setText(QCoreApplication::translate("QtBattleView", "1", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtBattleView: public Ui_QtBattleView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTBATTLEVIEW_H
