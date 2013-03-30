#ifndef MQTTFORM_H
#define MQTTFORM_H

#include <QWidget>
#include "qmqtt.h"

class MqttForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit MqttForm(QWidget *parent = 0) :
        QWidget(parent) {
    }

    ~MqttForm() {
    }
    void init(QMQTT::Client *client) {
        _client = client;
    }

protected:
    QMQTT::Client *_client;

};

#endif // MQTTFORM_H
