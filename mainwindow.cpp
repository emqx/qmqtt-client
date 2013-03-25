#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QMQTT::Client *client, QWidget *parent) :
    QMainWindow(parent),
    _client(client),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(_client, SIGNAL(connected()), this, SLOT(onConnected()));
}

void MainWindow::onConnected()
{
    _client->subscribe("a/b/c", 0);
    qDebug("MainWindow connected...");
}

void MainWindow::onConnacked(quint8 ack)
{
    qDebug("MainWindow onConnacked:%d", ack);
}

MainWindow::~MainWindow()
{
    delete ui;
}
