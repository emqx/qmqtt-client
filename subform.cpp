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
#include <QListWidgetItem>

#include "subform.h"
#include "ui_subform.h"

SubForm::SubForm(QWidget *parent) :
    MqttForm(parent),
    ui(new Ui::SubForm)
{
    ui->setupUi(this);
    topics = new QMap<QString, QListWidgetItem *>();

    // clicking listWidget item, loads it into topicLineEdit (for "quick" unsubscribing)
    connect(ui->listWidget, &QListWidget::itemClicked, [&](QListWidgetItem * item) {ui->topicLineEdit->setText(item->text());});
    ui->listWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    // hitting Return in topicLineEdit, will subscribe or unsubscribe, if possible
    connect(ui->topicLineEdit, &QLineEdit::returnPressed,
            [&]()
            {if (ui->subButton->isEnabled())
                onSubscribe();
             else if (ui->unsubButton->isEnabled())
                onUnsubscribe();
            });

    ui->subButton->setShortcut(QKeySequence(tr("Ctrl+S")));
    ui->unsubButton->setShortcut(QKeySequence(tr("Ctrl+N")));
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
    clearLineEdit();
}

void SubForm::onUnsubscribed(const QString &topic)
{
    if(topics->contains(topic)) {
        QListWidgetItem *item = topics->take(topic);
        ui->listWidget->removeItemWidget(item);
        delete item;
    }
    clearLineEdit();
}

void SubForm::onTopicInput(QString topic) {
    const bool topicAlreadSub = topics->contains(topic);
    ui->subButton->setEnabled(!topic.isEmpty()   && !topicAlreadSub);
    ui->unsubButton->setEnabled(!topic.isEmpty() &&  topicAlreadSub);
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

void SubForm::clearLineEdit()
{
    ui->topicLineEdit->clear();
    ui->subButton->setEnabled(false);
    ui->unsubButton->setEnabled(false);
    ui->topicLineEdit->setFocus();
    ui->listWidget->clearSelection();
}
