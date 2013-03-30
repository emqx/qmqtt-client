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
    if(!_client->isConnected()) {
        //TODO: FIX LATER
        _client->setClientId("qmqttclient");
        _client->setKeepAlive(100000000);
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

