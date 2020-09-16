#include "login/logindlg.h"
#include "ui_logindlg.h"
#include <QMessageBox>
#include <Client/Client_Core.h>
#include "regist/regist.h"

LoginDlg::LoginDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDlg)
{
    ui->setupUi(this);
}

LoginDlg::~LoginDlg()
{
    delete ui;
}

void LoginDlg::on_loginBtn_clicked()
{
    // 判断用户名和密码是否正确，


    /*---------- 将QString转换为char* ----------*/
    QString username = ui->usrLineEdit->text().trimmed();
    QString password = ui->pwdLineEdit->text().trimmed();

    QByteArray baTmp1 = username.toLatin1();
    QByteArray baTmp2 = password.toLatin1();

    char *chUsername = baTmp1.data();
    char *chPassword = baTmp2.data();
    /*---------- 将QString转换为char* ----------*/




    /*----------connect----------*/
    CLIENT::Client_Core CC("123.57.176.139");

    char* rt_val = CC.Sign_in(chUsername, chPassword);

    if(rt_val != NULL)
    {
        accept();   //关闭窗体，并设置返回值为Accepted
    }
    else
    {
        QMessageBox::warning(this, tr("登录失败"),
                            tr("未注册，请先注册"),
                            QMessageBox::Yes);

        //清空内容
        ui->usrLineEdit->clear();
        ui->pwdLineEdit->clear();
        //定位光标
        ui->usrLineEdit->setFocus();
    }

    /*----------connect----------*/
}


void LoginDlg::on_registBtn_clicked()
{
    Regist newRegist;

    if(newRegist.exec() == QDialog::Accepted)
    {
        LoginDlg newLoginDlg;
        newLoginDlg.exec();
    }
}
