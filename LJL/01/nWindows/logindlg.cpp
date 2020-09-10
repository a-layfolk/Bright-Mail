#include "logindlg.h"
#include "ui_logindlg.h"
#include <QMessageBox>

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
    // 如果错误则弹出警告对话框
    // trimmed()是去除字符串前后空白字符的函数
    if(ui->usrLineEdit->text().trimmed() == tr("layfolk") &&
           ui->pwdLineEdit->text().trimmed() == tr("123456"))
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
}
