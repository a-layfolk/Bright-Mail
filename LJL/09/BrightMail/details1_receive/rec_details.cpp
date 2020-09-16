#include "rec_details.h"
#include "ui_rec_details.h"
#include <QMessageBox>
#include <QDebug>

rec_details::rec_details(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::rec_details)
{
    ui->setupUi(this);

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
}
