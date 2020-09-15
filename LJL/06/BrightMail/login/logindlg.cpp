#include "login/logindlg.h"
#include "ui_logindlg.h"
#include <QMessageBox>
#include <Client/Client_Core.h>

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
    QByteArray baTmp2 = username.toLatin1();

    char *chUsername = baTmp1.data();
    char *chPassword = baTmp2.data();
    /*---------- 将QString转换为char* ----------*/


    /*----------connect----------*/

    CLIENT::Client_Core CC("123.57.176.139");
    // 如果错误则弹出警告对话框
    // trimmed()是去除字符串前后空白字符的函数

    int rt_val = CC.Sign_in(chUsername, chPassword);

    if(rt_val == 0)
    {
        accept();
    }
    else
    {
        QMessageBox::warning(this, tr("Waring"),
                            tr("user name or password error!"),
                            QMessageBox::Yes);

        //清空内容
        ui->usrLineEdit->clear();
        ui->pwdLineEdit->clear();
        //定位光标
        ui->usrLineEdit->setFocus();
    }

    /*----------connect----------*/
}
