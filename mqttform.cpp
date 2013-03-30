#include "mqttform.h"
#include "ui_mqttform.h"

MqttForm::MqttForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MqttForm)
{
    ui->setupUi(this);
}

MqttForm::~MqttForm()
{
    delete ui;
}
