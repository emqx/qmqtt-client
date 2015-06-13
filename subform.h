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
