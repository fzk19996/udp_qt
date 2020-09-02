/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGroupBox *groupBox;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_recieved;
    QLabel *label_duration;
    QLabel *label_speed;
    QPushButton *bt_detect_net;
    QTextEdit *target_ip_edit;
    QGroupBox *groupBox_2;
    QGroupBox *groupBox_3;
    QLabel *label_5;
    QComboBox *comboBox_2;
    QLabel *label_6;
    QTextEdit *cache_size_edit;
    QGroupBox *groupBox_4;
    QLabel *label_7;
    QComboBox *comboBox_3;
    QLabel *label_8;
    QComboBox *comboBox_4;
    QGroupBox *groupBox_5;
    QLabel *label_10;
    QComboBox *comboBox_6;
    QGroupBox *groupBox_6;
    QLabel *label_16;
    QLabel *label_17;
    QLabel *label_sended_3;
    QLabel *label_speed_3;
    QPushButton *bt_task_begin;
    QPushButton *bt_stop_task;
    QLabel *label_18;
    QTextEdit *data_edit;
    QTextEdit *text_console;
    QLabel *label_15;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QToolBar *toolBar;
    QToolBar *toolBar_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(563, 583);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(20, 20, 231, 171));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 30, 59, 16));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 60, 51, 16));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 90, 51, 16));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 120, 51, 16));
        label_recieved = new QLabel(groupBox);
        label_recieved->setObjectName(QStringLiteral("label_recieved"));
        label_recieved->setGeometry(QRect(80, 80, 121, 16));
        label_duration = new QLabel(groupBox);
        label_duration->setObjectName(QStringLiteral("label_duration"));
        label_duration->setGeometry(QRect(90, 90, 121, 16));
        label_speed = new QLabel(groupBox);
        label_speed->setObjectName(QStringLiteral("label_speed"));
        label_speed->setGeometry(QRect(90, 120, 121, 16));
        bt_detect_net = new QPushButton(groupBox);
        bt_detect_net->setObjectName(QStringLiteral("bt_detect_net"));
        bt_detect_net->setGeometry(QRect(70, 140, 80, 22));
        target_ip_edit = new QTextEdit(groupBox);
        target_ip_edit->setObjectName(QStringLiteral("target_ip_edit"));
        target_ip_edit->setGeometry(QRect(80, 30, 191, 21));
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(20, 210, 231, 321));
        groupBox_3 = new QGroupBox(groupBox_2);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 30, 211, 80));
        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 20, 59, 14));
        comboBox_2 = new QComboBox(groupBox_3);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));
        comboBox_2->setGeometry(QRect(70, 20, 131, 22));
        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 60, 59, 14));
        cache_size_edit = new QTextEdit(groupBox_3);
        cache_size_edit->setObjectName(QStringLiteral("cache_size_edit"));
        cache_size_edit->setGeometry(QRect(70, 50, 131, 21));
        cache_size_edit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        groupBox_4 = new QGroupBox(groupBox_2);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(10, 130, 211, 80));
        label_7 = new QLabel(groupBox_4);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(10, 20, 59, 14));
        comboBox_3 = new QComboBox(groupBox_4);
        comboBox_3->setObjectName(QStringLiteral("comboBox_3"));
        comboBox_3->setGeometry(QRect(70, 20, 131, 22));
        label_8 = new QLabel(groupBox_4);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(0, 60, 71, 16));
        comboBox_4 = new QComboBox(groupBox_4);
        comboBox_4->setObjectName(QStringLiteral("comboBox_4"));
        comboBox_4->setGeometry(QRect(70, 50, 131, 22));
        groupBox_5 = new QGroupBox(groupBox_2);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setGeometry(QRect(10, 220, 211, 80));
        label_10 = new QLabel(groupBox_5);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(10, 50, 71, 16));
        comboBox_6 = new QComboBox(groupBox_5);
        comboBox_6->setObjectName(QStringLiteral("comboBox_6"));
        comboBox_6->setGeometry(QRect(70, 50, 131, 22));
        groupBox_6 = new QGroupBox(centralWidget);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        groupBox_6->setGeometry(QRect(300, 20, 231, 171));
        label_16 = new QLabel(groupBox_6);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(10, 56, 61, 20));
        label_17 = new QLabel(groupBox_6);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(10, 90, 61, 16));
        label_sended_3 = new QLabel(groupBox_6);
        label_sended_3->setObjectName(QStringLiteral("label_sended_3"));
        label_sended_3->setGeometry(QRect(90, 90, 51, 16));
        label_speed_3 = new QLabel(groupBox_6);
        label_speed_3->setObjectName(QStringLiteral("label_speed_3"));
        label_speed_3->setGeometry(QRect(90, 120, 51, 16));
        bt_task_begin = new QPushButton(groupBox_6);
        bt_task_begin->setObjectName(QStringLiteral("bt_task_begin"));
        bt_task_begin->setGeometry(QRect(30, 110, 80, 22));
        bt_stop_task = new QPushButton(groupBox_6);
        bt_stop_task->setObjectName(QStringLiteral("bt_stop_task"));
        bt_stop_task->setGeometry(QRect(130, 110, 80, 22));
        label_18 = new QLabel(groupBox_6);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(10, 30, 61, 16));
        data_edit = new QTextEdit(groupBox_6);
        data_edit->setObjectName(QStringLiteral("data_edit"));
        data_edit->setGeometry(QRect(30, 50, 211, 41));
        text_console = new QTextEdit(centralWidget);
        text_console->setObjectName(QStringLiteral("text_console"));
        text_console->setGeometry(QRect(310, 240, 221, 281));
        label_15 = new QLabel(centralWidget);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(300, 210, 59, 14));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 563, 25));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);
        toolBar_2 = new QToolBar(MainWindow);
        toolBar_2->setObjectName(QStringLiteral("toolBar_2"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar_2);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("MainWindow", "\347\275\221\347\273\234\346\243\200\346\265\213", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "\347\233\256\346\240\207\347\275\221\345\235\200", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "\346\216\245\346\224\266", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "\345\273\266\346\227\266", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "\351\200\237\345\272\246", Q_NULLPTR));
        label_recieved->setText(QString());
        label_duration->setText(QString());
        label_speed->setText(QString());
        bt_detect_net->setText(QApplication::translate("MainWindow", "\346\243\200\346\265\213", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "\346\225\260\346\215\256\344\274\240\350\276\223\351\205\215\347\275\256", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "\347\274\223\345\255\230\351\205\215\347\275\256", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "\347\255\226\347\225\245", Q_NULLPTR));
        comboBox_2->clear();
        comboBox_2->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "\345\210\206\347\211\207", Q_NULLPTR)
        );
        label_6->setText(QApplication::translate("MainWindow", "\345\244\247\345\260\217", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "\345\216\213\347\274\251\347\255\226\347\225\245", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindow", "\347\255\226\347\225\245", Q_NULLPTR));
        comboBox_3->clear();
        comboBox_3->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "\345\216\213\347\274\251", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\344\270\215\350\277\233\350\241\214\346\223\215\344\275\234", Q_NULLPTR)
        );
        label_8->setText(QApplication::translate("MainWindow", "\347\256\227\346\263\225", Q_NULLPTR));
        comboBox_4->clear();
        comboBox_4->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Snappy", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Gzip", Q_NULLPTR)
        );
        groupBox_5->setTitle(QApplication::translate("MainWindow", "\344\274\240\350\276\223\351\205\215\347\275\256", Q_NULLPTR));
        label_10->setText(QApplication::translate("MainWindow", "\345\267\256\351\224\231\346\243\200\346\265\213", Q_NULLPTR));
        comboBox_6->clear();
        comboBox_6->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "\345\245\207\345\201\266\346\240\241\351\252\214", Q_NULLPTR)
         << QApplication::translate("MainWindow", "CRC\346\240\241\351\252\214", Q_NULLPTR)
        );
        groupBox_6->setTitle(QApplication::translate("MainWindow", "\346\225\260\346\215\256\344\274\240\350\276\223", Q_NULLPTR));
        label_16->setText(QString());
        label_17->setText(QApplication::translate("MainWindow", "\346\223\215\344\275\234", Q_NULLPTR));
        label_sended_3->setText(QString());
        label_speed_3->setText(QString());
        bt_task_begin->setText(QApplication::translate("MainWindow", "begin", Q_NULLPTR));
        bt_stop_task->setText(QApplication::translate("MainWindow", "stop", Q_NULLPTR));
        label_18->setText(QApplication::translate("MainWindow", "\350\276\223\345\205\245\346\225\260\346\215\256", Q_NULLPTR));
        label_15->setText(QApplication::translate("MainWindow", "\346\230\276\347\244\272\347\252\227\345\217\243", Q_NULLPTR));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", Q_NULLPTR));
        toolBar_2->setWindowTitle(QApplication::translate("MainWindow", "toolBar_2", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
