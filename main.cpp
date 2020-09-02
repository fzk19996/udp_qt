#include "mainwindow.h"
#include <QApplication>
#include "net_speed.h"

int main(int argc, char *argv[])
{
    s_t_start();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
