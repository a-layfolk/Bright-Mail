#include "regist.h"
#include "ui_regist.h"
#include "Client/Client_Core.h"
#include <QMessageBox>
#include <QDebug>

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
    QString qsUsername = ui->lineEditUsername->text();
    QString qsPassword = ui->lineEditPassword->text();
    QString qsPhone = ui->lineEditPhone->text();

    string stdUsername = qsUsername.toStdString();
    string stdPassword = qsPassword.toStdString();
    string stdPhone = qsPassword.toStdString();

    const char* chUsername = stdUsername.c_str();
    const char* chPassword = stdPassword.c_str();
    const char* chPhone = stdPhone.c_str();

    CLIENT::Client_Core CC("123.57.176.139");

    qDebug() << chUsername;
    qDebug() << chPassword;
    qDebug() << chPhone;

    char* rt_val = CC.Sign_up(chUsername, chPassword, chPhone);
    if(rt_val != NULL)
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
