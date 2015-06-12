#include <QListWidgetItem>

#include "subform.h"
#include "ui_subform.h"

SubForm::SubForm(QWidget *parent) :
    MqttForm(parent),
    ui(new Ui::SubForm)
{
    ui->setupUi(this);
    topics = new QMap<QString, QListWidgetItem *>();
}

SubForm::~SubForm()
{
    delete ui;
    delete topics;
}

void SubForm::init(QMQTT::Client *client)
{
    MqttForm::init(client);
    connect(_client, SIGNAL(subscribed(const QString &)), this, SLOT(onSubscribed(const QString &)));
    connect(_client, SIGNAL(unsubscribed(const QString &)), this, SLOT(onUnsubscribed(const QString &)));
}

void SubForm::onSubscribed(const QString &topic)
{
    if(!topics->contains(topic)) {
        QListWidgetItem *item = new QListWidgetItem(topic);
        topics->insert(topic, item);
        ui->listWidget->addItem(item);
    }
}

void SubForm::onUnsubscribed(const QString &topic)
{
    if(topics->contains(topic)) {
        QListWidgetItem *item = topics->take(topic);
        ui->listWidget->removeItemWidget(item);
        delete item;
    }
}

void SubForm::onTopicInput(QString topic) {
    ui->subButton->setEnabled(!topic.isEmpty());
    ui->unsubButton->setEnabled(!topic.isEmpty());
}

void SubForm::onSubscribe()
{
    QString topic = ui->topicLineEdit->text();
    quint8 qos = ui->qosComboBox->currentIndex();
    qDebug("Qos: %d", qos);
    _client->subscribe(topic, qos);
}

void SubForm::onUnsubscribe()
{
    QString topic = ui->topicLineEdit->text();
    _client->unsubscribe(topic);
}
