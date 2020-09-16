#include "regist.h"
#include "ui_regist.h"
#include "Client/Client_Core.h"
#include <QMessageBox>

Regist::Regist(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Regist)
{
    ui->setupUi(this);
}

Regist::~Regist()
{
    delete ui;
}

void Regist::on_btnRegister_clicked()
{
    const char* chUsername = ui->lineEditUsername->text().toStdString().c_str();
    const char* chPassword = ui->lineEditPassword->text().toStdString().c_str();
    const char* chPhone = ui->lineEditPhone->text().toStdString().c_str();

    CLIENT::Client_Core CC("123.57.176.139");

    int rt_val = CC.Sign_up(chUsername, chPassword, chPhone);
    if(rt_val == 0)
    {
        QMessageBox::information(this, tr("注册成功"),
                            tr("请返回登录界面登录"),
                            QMessageBox::Yes);
        accept();
    }
    else
    {
        QMessageBox::information(this, tr("注册失败"),
                            tr("请重新注册"),
                            QMessageBox::Yes);
    }
}
