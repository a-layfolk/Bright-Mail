#include "deleteemail.h"
#include "ui_deleteemail.h"

DeleteEmail::DeleteEmail(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteEmail)
{
    ui->setupUi(this);
}

DeleteEmail::~DeleteEmail()
{
    delete ui;
}

void DeleteEmail::on_buttonReturn_clicked()
{
    //子窗口关闭时，传递信号
    emit ExitWin();

    //传递信号之后，子窗口关闭
    this->close();
}
