/**
 * Copyright (C) 2013-2017 Feng Lee <feng@emqtt.io>
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "qmqtt.h"
#include "connform.h"
#include "pubform.h"
#include "subform.h"
#include <QAction>
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
    void onMQTT_Connected();
    void onMQTT_Connacked(quint8 ack);
    void onMQTT_error(QMQTT::ClientError err);
    //slots changes
    //API:  void published(const QMQTT::Message& message);
    void onMQTT_Published(const QMQTT::Message &message);
    void onMQTT_Pubacked(quint8 type, quint16 msgid);
    void onMQTT_Received(const QMQTT::Message &message);
    void onMQTT_subscribed(const QString &topic);
    void onMQTT_subacked(quint16 msgid, quint8 qos);
    void onMQTT_unsubscribed(const QString &topic);
    void onMQTT_unsubacked(quint16 msgid);
    void onMQTT_Pong();
    void onMQTT_disconnected();

    void on_actionAbout_triggered();
    void on_actionQuit_triggered();

    void aboutApp();
    void publishTopic();
    void subscribeTopic();
    void connectServer();
    void quitApp();
    void clearMsg();

private:
    void clearChecked();
    void log(const QString & msg);
    QMQTT::Client *_client;
    Ui::MainWindow *ui;
    ConnForm * _connDialog;
    PubForm * _pubDialog;
    SubForm * _subDialog;

};

#endif // MAINWINDOW_H
