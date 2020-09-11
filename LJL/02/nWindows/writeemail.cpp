#include "writeemail.h"
#include "ui_writeemail.h"
#include "mainwindow.h"
#include <string>
#include <QDebug>
#include <iostream>
#include <QTextCodec>

WriteEmail::WriteEmail(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WriteEmail)
{
    ui->setupUi(this);
}

//析构函数
WriteEmail::~WriteEmail()
{
    delete ui;
}

void WriteEmail::on_buttonReturn_clicked()
{
    //子窗口关闭时，传递信号
    emit ExitWin();

    //传递信号之后，子窗口关闭
    this->close();
}


void WriteEmail::on_buttonSend_clicked()
{
    //点击发送按钮，在这里我先来尝试能不能获取文本
//    string str = ui->textEditConnent->toPlainText();
    std::string str = "喵喵喵";
    std::cout << str;

}
