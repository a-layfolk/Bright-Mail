#include "deliver_details.h"
#include "ui_deliver_details.h"
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QDebug>

deliver_details::deliver_details(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::deliver_details)
{
    ui->setupUi(this);
}

deliver_details::~deliver_details()
{
    delete ui;
}

void deliver_details::on_btnReturn_clicked()
{
    /*---------------------返回已发送的列表-----------=----*/




    /*---------------------返回已发送的列表-----------=----*/

}

void deliver_details::on_btnTrans_clicked()
{
    const char *chUser = ui->lineEditUser->text().toStdString().c_str();
    const char *chPhone = ui->lineEditPhone->text().toStdString().c_str();

    //转发的操作数据库语句
    /*----------------------预留位置----------------------*/





    /*----------------------预留位置----------------------*/

}

void deliver_details::on_btnDelete_clicked()
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

void deliver_details::on_btnSave_clicked()
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

        QString content = ui->textEditContent->toPlainText();
        std::string stdContent = content.toStdString();
        const char* chContent = stdContent.c_str();

        file.write(chContent);
        file.close();
    }
}


void deliver_details::sendData(QString data)
{
    qDebug() << data;
    qDebug() << "lshajsghdjkag";
}
