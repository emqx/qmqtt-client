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
#include "pubform.h"
#include "ui_pubform.h"

PubForm::PubForm(QWidget *parent) :
    MqttForm(parent),
    ui(new Ui::PubForm)
{
    ui->setupUi(this);
    onPublishReady();

    ui->pubButton->setShortcut(QKeySequence(tr("Ctrl+P")));
}

PubForm::~PubForm()
{
    delete ui;
}

void PubForm::onPublishReady()
{
    ui->pubButton->setEnabled(!ui->topicLineEdit->text().isEmpty()
                              && !ui->payloadEdit->toPlainText().isEmpty());
}

void PubForm::onPublish()
{
    QMQTT::Message msg(0, ui->topicLineEdit->text(), ui->payloadEdit->toPlainText().toUtf8());
    _client->publish(msg);
}

void PubForm::lineEditSetFocus()
{
    ui->topicLineEdit->setFocus();
}
