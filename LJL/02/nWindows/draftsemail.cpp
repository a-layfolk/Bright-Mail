#include "draftsemail.h"
#include "ui_draftsemail.h"

DraftsEmail::DraftsEmail(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DraftsEmail)
{
    ui->setupUi(this);
}

DraftsEmail::~DraftsEmail()
{
    delete ui;
}

void DraftsEmail::on_buttonReturn_clicked()
{
    //子窗口关闭时，传递信号
    emit ExitWin();

    //传递信号之后，子窗口关闭
    this->close();
}
