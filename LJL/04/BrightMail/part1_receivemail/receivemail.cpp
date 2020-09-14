#include "receivemail.h"
#include "ui_receivemail.h"

ReceiveMail::ReceiveMail(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReceiveMail)
{
    ui->setupUi(this);
}

ReceiveMail::~ReceiveMail()
{
    delete ui;
}
