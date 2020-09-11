#include "transemail.h"
#include "ui_transemail.h"

TransEmail::TransEmail(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TransEmail)
{
    ui->setupUi(this);
}

TransEmail::~TransEmail()
{
    delete ui;
}

void TransEmail::on_buttonReturn_clicked()
{
    //子窗口关闭时，传递信号
    emit ExitWin();

    //传递信号之后，子窗口关闭
    this->close();
}
