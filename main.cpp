#include <QApplication>

#include "qmqtt.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w(new QMQTT::Client());
    w.show();
    return a.exec();
}
