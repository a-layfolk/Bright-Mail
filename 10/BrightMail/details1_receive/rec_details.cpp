#include "rec_details.h"
#include "ui_rec_details.h"
#include <QMessageBox>
#include <QDebug>
#include "Client/Client_Core.h"

rec_details::rec_details(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::rec_details)
{
    ui->setupUi(this);
    ui->lineEditUser->setText("张三");
    ui->lineEditPhone->setText("13888888888");

    CLIENT::Client_Core CC("123.57.176.139");
    CLIENT::EMAIL_CONTENT *tmp = CC.Get_Mail_Detail("1", "1");

    ui->lineEditEmailTitle->setText(QString("nihaoa"));
    ui->textEditContent->setText(QString("xxxxxxxxxx"));





}

rec_details::~rec_details()
{
    delete ui;
}

void rec_details::on_delButton_clicked()
{
    int isOk = QMessageBox::question(this,
                tr("确定删除"),
                tr("你确定要删除 \"%1\"吗?").arg(ui->lineEditEmailTitle->text()),
                QMessageBox::Yes | QMessageBox::No);

     if (isOk == QMessageBox::Yes)
     {
         /*
            删除语句
         */
        QMessageBox::information(this, tr("删除成功"),
        tr("\"%1\"已经被移除").arg(ui->lineEditEmailTitle->text()));
        ui->lineEditEmailTitle->clear();
        ui->textEditContent->clear();
        ui->lineEditPhone->clear();
        ui->lineEditUser->clear();
     }
}

void rec_details::on_btnReturn_clicked()
{

}


void rec_details::sendData(QString data)
{
    qDebug() << data;
    qDebug() << "lshajsghdjkag";

//    tmpData = data;
//    qDebug() << tmpData;

//    struct EMAIL_CONTENT
//    {
//        char *emailTitle;
//        char *emailContent;
//        char *emailType;
//        char *targetUsername;
//        char *emailTime;
//        char *fileName;
//    };
}
