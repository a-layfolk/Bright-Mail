#include "widget.h"
#include "ui_widget.h"
#include<QPushButton>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
//    QPushButton b;
    b.setParent(this);
    b.setText("关闭窗口");

    //connect(信号发出者，处理的信号，信号接受者，执行的槽函数)
    connect(&b,&QPushButton::pressed,this,&Widget::close);
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}
