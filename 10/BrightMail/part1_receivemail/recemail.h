#ifndef RECEMAIL_H
#define RECEMAIL_H

#include <QWidget>
#include <QTableWidget>
#include "Client/Client_Core.h"
#include "details1_receive/rec_details.h"

class RecEmail : public QWidget
{
    Q_OBJECT

public:
    RecEmail(QWidget *parent = 0);
    ~RecEmail();



signals:

    /*--给主窗口传递一个子窗口关闭的信号--*/
    void ExitWin();
    /*--给主窗口传递一个子窗口关闭的信号--*/

    /*-----------跳转到详细界面的信号，有传参----------*/
    void self_signal(QString emailId);
    /*-----------跳转到详细界面的信号，有传参----------*/

private slots:
    void tableDoubleClicked(QModelIndex);   //双击一行跳转的槽函数


public:

    QTableWidget *emailWidget;              //设置表格为全局变量，这样槽函数就可以访问它
};



#endif // RECEMAIL_H
