#include "writeemail.h"
#include "ui_writeemail.h"
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include "Client/Client_Core.h"
#include <QDebug>

WriteEmail::WriteEmail(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WriteEmail)
{
    ui->setupUi(this);
    /*--------禁用删除按钮--------*/
    ui->btnDelete->setDisabled(true);
    ui->textEditMain->setText(QString(
        "亲，写邮件界面禁用删除按钮，你可以使用清空按钮哦"));
    /*--------禁用删除按钮--------*/

    /*----------预备阶段----------*/

    QString user = ui->lineEditTargetName->text().trimmed();
    QString phone = ui->lineEditTargetPhone->text().trimmed();

    std::string stdUser =  user.toStdString();
    std::string stdPhone = phone.toStdString();

    chUser = stdUser.c_str();
    chPhone = stdPhone.c_str();


    /*
        //预留位置给对方的id
        //通过查询电话号码返回id
        全局变量名字为targetId
    */



}

WriteEmail::~WriteEmail()
{
    delete ui;
}

void WriteEmail::on_btnClear_clicked()
{

    //添加弹窗，提醒是否要清空
    int isOk = QMessageBox::question(this,
                    tr("确定清空"),
                    tr("你确定要清空所写的内容吗?"),
                    QMessageBox::Yes | QMessageBox::No);

    if (isOk == QMessageBox::Yes)
    {
        ui->textEditMain->clear();
    }
}

void WriteEmail::on_btnReturn_clicked()
{

}

void WriteEmail::on_btnLoad_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("打开邮件"), "",
        tr("邮件 (*.txt);;All Files (*)"));

    if (fileName.isEmpty())
    {
        return;
    }
    else
    {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::information(this, tr("无法打开文件"),
                file.errorString());
            return;
        }

       //读取文件
       QByteArray data=file.readAll();
       file.close();

       QString qsData = QString(data);
       ui->textEditMain->clear();
       ui->textEditMain->setText(qsData);
    }
}


void WriteEmail::on_btnSave_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                            tr("保存邮件"), "",
                            tr("邮件 (*.txt);;All Files (*)"));
    if (fileName.isEmpty())
    {
        return;
    }
    else
    {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly))
        {
            QMessageBox::information(this, tr("无法打开文件"),
            file.errorString());
            return;
        }

        QString content = ui->textEditMain->toPlainText();
        std::string stdContent = content.toStdString();
        const char* chContent = stdContent.c_str();

        file.write(chContent);
        file.close();
    }
}

void WriteEmail::on_btnSend_clicked()
{

    QString title = ui->lineEditEmailTitle->text().trimmed();
    std::string stdTitle = title.toStdString();
    chTitle = stdTitle.c_str();


    QString content = ui->textEditMain->toPlainText();
    std::string stdContent = content.toStdString();
    chContent = stdContent.c_str();

    qDebug() << chTitle;
    qDebug() << chContent;

    CLIENT::Client_Core CC("123.57.176.139");
    int i = CC.Send_Mail("17", "1581", "sended", chTitle, chContent);
    if(i == 0)
    {
       qDebug() << "success";
    }
    else
    {
       qDebug() << "failure";
    }
}

void WriteEmail::on_btnAnnex_clicked()
{

}

void WriteEmail::on_btnDraft_clicked()
{
//    email_type = "draft";

//    int ret_send = Send_Mail(ownerId, targetId, email_type, chTitle, chContent);
//    if(ret_send == 0)
//    {
//        QMessageBox::information(this, tr("草稿箱"),
//            tr("添加成功"));
//        return;
//    }
//    else
//    {
//        QMessageBox::information(this, tr("草稿箱"),
//            tr("添加失败"));
//        return;
//    }
}

void WriteEmail::on_btnDelete_clicked()
{

}

