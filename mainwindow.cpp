#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QMQTT::Client *client, QWidget *parent) :
    QMainWindow(parent),
    _client(client),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->conForm->init(client);
    ui->pubForm->init(client);
    ui->subForm->init(client);
    ui->action_Subscribe->setEnabled(false);
    ui->action_Publish->setEnabled(false);
    ui->action_Connect->setChecked(true);

    //connform slots
    connect(_client, SIGNAL(disconnected()), ui->conForm, SLOT(updateUiStatus()));
    connect(_client, SIGNAL(connected()), ui->conForm, SLOT(updateUiStatus()));

    //mainwindow slots
    connect(_client, SIGNAL(connected()), this, SLOT(onMQTT_Connected()));
    connect(_client, SIGNAL(connacked(quint8)), this, SLOT(onMQTT_Connacked(quint8)));
    connect(_client, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onMQTT_error(QAbstractSocket::SocketError)));
    connect(_client, SIGNAL(published(QMQTT::Message &)), this, SLOT(onMQTT_Published(QMQTT::Message &)));
    connect(_client, SIGNAL(pubacked(quint8, quint16)), this, SLOT(onMQTT_Pubacked(quint8, quint16)));
    connect(_client, SIGNAL(received(const QMQTT::Message &)), this, SLOT(onMQTT_Received(const QMQTT::Message &)));
    connect(_client, SIGNAL(subscribed(const QString &)), this, SLOT(onMQTT_subscribed(const QString &)));
    connect(_client, SIGNAL(subacked(quint16, quint8)), this, SLOT(onMQTT_subacked(quint16, quint8)));
    connect(_client, SIGNAL(unsubscribed(const QString &)), this, SLOT(onMQTT_unsubscribed(const QString &)));
    connect(_client, SIGNAL(unsubacked(quint16)), this, SLOT(onMQTT_unsubacked(quint16)));
    connect(_client, SIGNAL(pong()), this, SLOT(onMQTT_Pong()));
    connect(_client, SIGNAL(disconnected()), this, SLOT(onMQTT_disconnected()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

/* -----------------------------------------------------------
 MQTT Client Slots
 -----------------------------------------------------------*/
void MainWindow::onMQTT_Connected()
{
    ui->action_Publish->setEnabled(true);
    ui->action_Subscribe->setEnabled(true);
    log(tr("connected to %1:%2").arg(_client->host()).arg(_client->port()));
}

void MainWindow::onMQTT_Connacked(quint8 ack)
{
    QString ackStatus;
    switch(ack) {
    case QMQTT::CONNACK_ACCEPT:
        ackStatus = "Connection Accepted";
        break;
    case QMQTT::CONNACK_PROTO_VER:
        ackStatus = "Connection Refused: unacceptable protocol version";
        break;
    case QMQTT::CONNACK_INVALID_ID:
        ackStatus = "Connection Refused: identifier rejected";
        break;
    case QMQTT::CONNACK_SERVER:
        ackStatus = "Connection Refused: server unavailable";
        break;
    case QMQTT::CONNACK_CREDENTIALS:
        ackStatus = "Connection Refused: bad user name or password";
        break;
    case QMQTT::CONNACK_AUTH:
        ackStatus = "Connection Refused: not authorized";
        break;
    }
    log(tr("connacked: %1, <b>%2</b>").arg(ack).arg(ackStatus));
}
void MainWindow::onMQTT_error(QAbstractSocket::SocketError err)
{
    QString errInfo;
    switch(err) {
    // 0	The connection was refused by the peer (or timed out).
    case QAbstractSocket::ConnectionRefusedError:
        errInfo = tr("Connection Refused");
    //	 1	The remote host closed the connection. Note that the client socket (i.e., this socket) will be closed after the remote close notification has been sent.
    case QAbstractSocket::RemoteHostClosedError:
        errInfo = tr("Remote Host Closed");
    //	2	The host address was not found.
    case QAbstractSocket::HostNotFoundError:
        errInfo = tr("Host Not Found Error");
    // 	3	The socket operation failed because the application lacked the required privileges.
    case QAbstractSocket::SocketAccessError:
        errInfo = tr("Socket Access Error");
    // 	4	The local system ran out of resources (e.g., too many sockets).
    case QAbstractSocket::SocketResourceError:
        errInfo = tr("Socket Resource Error");
    // 	5	The socket operation timed out.
    case QAbstractSocket::SocketTimeoutError:
        errInfo = tr("Socket Timeout Error");
    default:
        errInfo = tr("Socket Error");
    }
    log(errInfo);
}

void MainWindow::onMQTT_Published(QMQTT::Message &message)
{
    log(tr("message published to %1").arg(message.topic()));
    log(message.payload());
}

void MainWindow::onMQTT_Pubacked(quint8 type, quint16 msgid)
{
    log(tr("pubacked: type=%1, msgid=%2").arg(type, msgid));
}

void MainWindow::onMQTT_Received(const QMQTT::Message &message)
{
    log(tr("message recevied from %1: qos=%2").arg(message.topic()).arg(message.qos()));
    log(message.payload());
}

void MainWindow::onMQTT_subscribed(const QString &topic)
{
    log(tr("subscribed %1").arg(topic));
}

void MainWindow::onMQTT_subacked(quint16 msgid, quint8 qos)
{
    log(tr("subacked: msgid=%1, qos=%2").arg(msgid).arg(qos));
}

void MainWindow::onMQTT_unsubscribed(const QString &topic)
{
    log(tr("unsubscribed %1").arg(topic));
}

void MainWindow::onMQTT_unsubacked(quint16 msgid)
{
    log(tr("unsubacked: msgid=%1").arg(msgid));
}

void MainWindow::onMQTT_Pong()
{
    log("pong");
}

void MainWindow::onMQTT_disconnected()
{
    ui->action_Publish->setEnabled(false);
    ui->action_Subscribe->setEnabled(false);
    log("disconnected");
}

/* -----------------------------------------------------------
 UI Action Slots
 -----------------------------------------------------------*/
void MainWindow::on_action_Connect_triggered()
{
    clearChecked();
    ui->action_Connect->setChecked(true);
    ui->stackedWidget->setCurrentWidget(ui->conForm);
}

void MainWindow::on_action_Subscribe_triggered()
{
    clearChecked();
    ui->action_Subscribe->setChecked(true);
    ui->stackedWidget->setCurrentWidget(ui->subForm);
}

void MainWindow::on_action_Publish_triggered()
{
    clearChecked();
    ui->action_Publish->setChecked(true);
    ui->stackedWidget->setCurrentWidget(ui->pubForm);
}

void MainWindow::on_action_About_triggered()
{
    QMessageBox::information(NULL, tr("About QMQTT"),
             tr("Version: 0.1.0\n\n"
                 "MQTT Client written with Qt\n\n"
                 "Site: https://www.github.com/emqtt/qmqtt-client\n"));
}

//Private Methods
void MainWindow::clearChecked()
{
    ui->action_Connect->setChecked(false);
    ui->action_Publish->setChecked(false);
    ui->action_Subscribe->setChecked(false);
}

void MainWindow::log(const QString & msg)
{
    ui->logConsole->append(msg);
}


