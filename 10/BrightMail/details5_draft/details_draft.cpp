#include "details_draft.h"
#include "ui_details_draft.h"
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QDebug>

details_draft::details_draft(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::details_draft)
{
    ui->setupUi(this);

    /*--------禁用附件按钮--------*/
    ui->btnAnnex->setDisabled(true);
    ui->textEditContent->setText(QString(
            "亲，草稿箱界面禁用添加附件按钮哦"));
    /*--------禁用附件按钮--------*/

}

details_draft::~details_draft()
{
    delete ui;
}

void details_draft::on_btnClear_clicked()
{
    //添加弹窗，提醒是否要清空
    int isOk = QMessageBox::question(this,
                        tr("确定清空"),
                        tr("你确定要清空所写的内容吗?"),
                        QMessageBox::Yes | QMessageBox::No);

    if (isOk == QMessageBox::Yes)
    {
        ui->textEditContent->clear();
    }
}

void details_draft::on_btnReturn_clicked()
{

}

void details_draft::on_btnLoad_clicked()
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
       ui->textEditContent->clear();
       ui->textEditContent->setText(qsData);
    }
}

void details_draft::on_btnSave_clicked()
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

void details_draft::on_btnSend_clicked()
{

}

void details_draft::on_btnDelete_clicked()
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

void details_draft::on_btnAnnex_clicked()
{
    //附件在草稿箱的时候被禁用
}

void details_draft::on_btnDraft_clicked()
{

}




void details_draft::sendData(QString data)
{
    qDebug() << data;
    qDebug() << "lshajsghdjkag";
}
