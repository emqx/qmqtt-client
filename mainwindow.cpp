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

    //add pushBtuoon slots
    connect(ui->pushButtonConnect,SIGNAL(clicked(bool)),this,SLOT(connectServer()));
    connect(ui->pushButtonPusblish,SIGNAL(clicked(bool)),this,SLOT(publishTopic()));
    connect(ui->pushButtonSubscribe,SIGNAL(clicked(bool)),this,SLOT(subscribeTopic()));
    connect(ui->pushButtonQuit,SIGNAL(clicked(bool)),this,SLOT(quitApp()));
    connect(ui->pushButtonClear,SIGNAL(clicked(bool)),this,SLOT(clearMsg()));
    connect(ui->pushButtonAbout,SIGNAL(clicked(bool)),this,SLOT(aboutApp()));

    //connform slots
    connect(_client, SIGNAL(disconnected()), ui->conForm, SLOT(updateUiStatus()));
    connect(_client, SIGNAL(connected()), ui->conForm, SLOT(updateUiStatus()));
    //mainwindow slots
    connect(_client, SIGNAL(connected()), this, SLOT(onMQTT_Connected()));

    //todo: should emit on server suback
    //connect(_client, SIGNAL(connacked(quint8)), this, SLOT(onMQTT_Connacked(quint8)));
    connect(_client, SIGNAL(error(QMQTT::ClientError)), this, SLOT(onMQTT_error(QMQTT::ClientError)));

    //slots changes
    //API:  void published(const QMQTT::Message& message);
    connect(_client,SIGNAL(published(const QMQTT::Message &)),this,SLOT(onMQTT_Published(const QMQTT::Message &)));

    //todo: should emit on server suback
    //connect(_client, SIGNAL(pubacked(quint8, quint16)), this, SLOT(onMQTT_Pubacked(quint8, quint16)));
    connect(_client, SIGNAL(received(const QMQTT::Message &)), this, SLOT(onMQTT_Received(const QMQTT::Message &)));
    connect(_client, SIGNAL(subscribed(const QString &)), this, SLOT(onMQTT_subscribed(const QString &)));

    //todo: should emit on server suback
    //connect(_client, SIGNAL(subacked(quint16, quint8)), this, SLOT(onMQTT_subacked(quint16, quint8)));
    connect(_client, SIGNAL(unsubscribed(const QString &)), this, SLOT(onMQTT_unsubscribed(const QString &)));
    //todo: should emit on server suback
    //connect(_client, SIGNAL(unsubacked(quint16)), this, SLOT(onMQTT_unsubacked(quint16)));
    //connect(_client, SIGNAL(pong()), this, SLOT(onMQTT_Pong()));
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
    log(tr("connected to %1:%2").arg(_client->host().toString()).arg(_client->port()));
    //todo: should emit on server suback
    ui->pushButtonPusblish->setEnabled(true);
    ui->pushButtonSubscribe->setEnabled(true);
}



void MainWindow::onMQTT_Connacked(quint8 ack)
{
    //todo: should emit on server suback
    /*
    QString ackStatus;
    switch(ack) {
    case QMQTT::CONNACK_ACCEPT:
        ui->pushButtonPusblish->setEnabled(true);
        ui->pushButtonSubscribe->setEnabled(true);
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
    log(tr("connacked: %1, %2").arg(ack).arg(ackStatus));
    */
}


void MainWindow::onMQTT_error(QMQTT::ClientError err)
{
    //todo: should emit on server suback
    /*
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
    */
}

void MainWindow::onMQTT_Published(const QMQTT::Message &message)
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
    log("pong received.");
}

void MainWindow::onMQTT_disconnected()
{
    ui->pushButtonPusblish->setEnabled(false);
    ui->pushButtonSubscribe->setEnabled(false);
    log("disconnected");
}

/* -----------------------------------------------------------
 UI Action Slots
 -----------------------------------------------------------*/


void MainWindow::log(const QString & msg)
{
    ui->logConsole->append(msg);
}



void MainWindow::quitApp()
{
    qApp->quit();
}

void MainWindow::connectServer()
{
     ui->stackedWidget->setCurrentWidget(ui->conForm);
}



void MainWindow::aboutApp()
{
    QMessageBox::information(NULL, tr("About QMQTT"),
             tr("Version: 0.1.1\n\n"
                 "MQTT Client written with Qt\n\n"
                 "Site: https://www.github.com/emqtt/qmqtt-client\n"));
}

void MainWindow::clearMsg()
{
    ui->logConsole->clear();
}

void MainWindow::subscribeTopic()
{
    ui->stackedWidget->setCurrentWidget(ui->subForm);
    ui->subForm->clearLineEdit(); // also sets focus to lineEdit
}

void MainWindow::publishTopic()
{
    ui->stackedWidget->setCurrentWidget(ui->pubForm);
    ui->pubForm->lineEditSetFocus();
}

void MainWindow::on_actionAbout_triggered()
{
    aboutApp();
}

void MainWindow::on_actionQuit_triggered()
{
    quitApp();
}
