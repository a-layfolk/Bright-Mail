#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QPushButton>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    QPushButton b;//按钮直接显示在界面上需要在.h里而不是.cpp里写
};

#endif // WIDGET_H
