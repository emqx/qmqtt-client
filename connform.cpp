#include "connform.h"
#include "ui_connform.h"

ConnForm::ConnForm(QWidget *parent) :
    MqttForm(parent),
    ui(new Ui::ConnForm)
{
    ui->setupUi(this);
    ui->disconnButton->setEnabled(false);
}

ConnForm::~ConnForm()
{
    delete ui;
}

void ConnForm::onConnect()
{
    QString clientId = ui->leClientId->text();
    QString username = ui->leUser->text();
    QString passwd = ui->lePasswd->text();
    QString willtopic = ui->leWillTopic->text();
    QString willmsg = ui->teWillMsg->toPlainText();
    // New API do not use.
    //QMQTT::Will *will;
    if(!_client->isConnectedToHost()) {
        //changes
        //API:  void setHost(const QHostAddress& host);
        QHostAddress hostAdd(ui->leHost->text());
        _client->setHost(hostAdd);
        _client->setPort(ui->sbPort->value());
        _client->setKeepAlive(ui->sbKeepalive->value());
        //changes
        //API:  void setCleanSession(const bool cleansess);;
        _client->setCleanSession(ui->cbCleanSess->isChecked());
        if(!clientId.isEmpty())  _client->setClientId(clientId);
        if(!username.isEmpty()) _client->setUsername(username);
        if(!passwd.isEmpty()) _client->setPassword(passwd);
        //Use directly setWillTopic and setWillMessage.
        if(!willtopic.isEmpty() && !willmsg.isEmpty()) {
            //New
            //API: void setWillTopic(const QString& willTopic);
            //API: void setWillQos(const quint8 willQos);
            //API: void setWillRetain(const bool willRetain);
            //API: void setWillMessage(const QString& willMessage);
            _client->setWillTopic(willtopic);
            _client->setWillMessage(willmsg);
        }
        //changes
        //API:  void connectToHost();
        _client->connectToHost();
    }
}

void ConnForm::onDisconnect()
{
    //changes
    //API:  bool isConnectedToHost() const;
    if(_client->isConnectedToHost()) {
        //change disconnected() to disconnectFromHost()
        _client->disconnectFromHost();
    }
}

void ConnForm::updateUiStatus()
{
    //changes
    //API:  bool isConnectedToHost() const;
    ui->connButton->setEnabled(!_client->isConnectedToHost());
    ui->disconnButton->setEnabled(_client->isConnectedToHost());
}

