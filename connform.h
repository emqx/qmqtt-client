#ifndef CONNFORM_H
#define CONNFORM_H

#include <QWidget>
#include "mqttform.h"

namespace Ui {
class ConnForm;
}

class ConnForm : public MqttForm
{
    Q_OBJECT
    
public:
    explicit ConnForm(QWidget *parent = 0);
    ~ConnForm();

public slots:
    void updateUiStatus();

private slots:
    void onConnect();
    void onDisconnect();

private:
    Ui::ConnForm *ui;
};

#endif // CONNFORM_H
