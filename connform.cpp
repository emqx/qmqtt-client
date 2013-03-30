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
    QMQTT::Will *will;
    if(!_client->isConnected()) {
        _client->setHost(ui->leHost->text());
        _client->setPort(ui->sbPort->value());
        _client->setKeepAlive(ui->sbKeepalive->value());
        _client->setCleansess(ui->cbCleanSess->isChecked());
        if(!clientId.isEmpty())  _client->setClientId(clientId);
        if(!username.isEmpty()) _client->setUsername(username);
        if(!passwd.isEmpty()) _client->setPassword(passwd);
        //FIXME: this api is not good
        if(!willtopic.isEmpty() && !willmsg.isEmpty()) {
            will = new QMQTT::Will(willtopic, willmsg);
            _client->setWill(will);
        }
        _client->connect();
    }
}

void ConnForm::onDisconnect()
{
    if(_client->isConnected()) {
        //TODO: FIX LATER
        _client->disconnect();
    }
}

void ConnForm::updateUiStatus()
{
    ui->connButton->setEnabled(!_client->isConnected());
    ui->disconnButton->setEnabled(_client->isConnected());
}

