#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qmqtt_client.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QMQTT::Client *client, QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onConnected();
    void onConnacked(quint8 ack);
    
private:
    QMQTT::Client *_client;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
