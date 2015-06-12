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
