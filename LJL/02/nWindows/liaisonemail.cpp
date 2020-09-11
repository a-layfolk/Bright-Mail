#include "liaisonemail.h"
#include "ui_liaisonemail.h"
#include <QTableWidget>     //表格给的头文件

LiaisonEmail::LiaisonEmail(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LiaisonEmail)
{
    ui->setupUi(this);
}

LiaisonEmail::~LiaisonEmail()
{
    delete ui;
}

void LiaisonEmail::on_buttonReturn_clicked()
{
    //子窗口关闭时，传递信号
    emit ExitWin();

    //传递信号之后，子窗口关闭
    this->close();
}
