#include "details_deleted.h"
#include "ui_details_deleted.h"
#include <QMessageBox>
#include <QDebug>

details_deleted::details_deleted(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::details_deleted)
{
    ui->setupUi(this);
}

details_deleted::~details_deleted()
{
    delete ui;
}

void details_deleted::on_btnRecover_clicked()
{

}

void details_deleted::on_btnDeleteForever_clicked()
{
    int isOk = QMessageBox::question(this,
                        tr("确定删除"),
                        tr("你确定要永久删除 \"%1\"吗?").arg(ui->lineEditEmailTitle->text()),
                        QMessageBox::Yes | QMessageBox::No);

    if (isOk == QMessageBox::Yes)
    {
             /*
                删除语句
             */
        QMessageBox::information(this, tr("删除成功"),
        tr("\"%1\"已经被永久删除").arg(ui->lineEditEmailTitle->text()));
        ui->lineEditEmailTitle->clear();
        ui->textEditContent->clear();
        ui->lineEditPhone->clear();
        ui->lineEditUser->clear();
    }
}

void details_deleted::on_btnReturn_clicked()
{

}

void details_deleted::sendData(QString data)
{
    qDebug() << data;
    qDebug() << "lshajsghdjkag";
}

