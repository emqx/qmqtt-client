#include "mainwindow.h"
#include <QApplication>

#include "qmqtt.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMQTT::Client *client = new QMQTT::Client("localhost", 1883);
    client->setClientId("DemoClient");
    MainWindow w(client);
    w.show();
    client->connect();
    return a.exec();
}
