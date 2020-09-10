#include "receiveemail.h"
#include "ui_receiveemail.h"

ReceiveEMail::ReceiveEMail(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReceiveEMail)
{
    ui->setupUi(this);
}

ReceiveEMail::~ReceiveEMail()
{
    delete ui;
}

void ReceiveEMail::on_buttonReturn_clicked()
{
    //子窗口关闭时，传递信号
    emit ExitWin();

    //传递信号之后，子窗口关闭
    this->close();
}
