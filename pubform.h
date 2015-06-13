#ifndef PUBFORM_H
#define PUBFORM_H

#include <QWidget>
#include "mqttform.h"

namespace Ui {
class PubForm;
}

class PubForm : public MqttForm
{
    Q_OBJECT
    
public:
    explicit PubForm(QWidget *parent = 0);
    ~PubForm();
    void lineEditSetFocus();

public slots:
    void onPublishReady();
    void onPublish();

private:
    Ui::PubForm *ui;
};

#endif // PUBFORM_H
