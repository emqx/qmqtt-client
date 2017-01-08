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

