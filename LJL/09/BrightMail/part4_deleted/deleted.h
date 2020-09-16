#ifndef DELETED_H
#define DELETED_H

#include <QWidget>
#include <QTableWidget>
#include <Client/Client_Core.h>
#include "details4_deleted/details_deleted.h"

class Deleted : public QWidget
{
    Q_OBJECT

public:
    Deleted(QWidget *parent = 0);

    ~Deleted();

private slots:
    void tableDoubleClicked(QModelIndex);   //双击一行跳转的槽函数

public:
    QTableWidget *emailWidget;              //设置表格为全局变量，这样槽函数就可以访问它

};

#endif // DELETED_H
