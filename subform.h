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

#ifndef SUBFORM_H
#define SUBFORM_H

#include <QWidget>
#include <QListWidgetItem>
#include "mqttform.h"

namespace Ui {
class SubForm;
}

class SubForm : public MqttForm
{
    Q_OBJECT
    
public:
    explicit SubForm(QWidget *parent = 0);
    ~SubForm();
    void init(QMQTT::Client *client);
    void clearLineEdit();

public slots:
    void onTopicInput(QString topic);
    void onSubscribe();
    void onUnsubscribe();

private slots:
    void onSubscribed(const QString &topic);
    void onUnsubscribed(const QString &topic);

private:
    Ui::SubForm *ui;
    QMap<QString, QListWidgetItem *> *topics;
};

#endif // SUBFORM_H
