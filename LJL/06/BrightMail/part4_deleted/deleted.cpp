#include "deleted.h"
#include <QDebug>
#include <QModelIndex>


Deleted::Deleted(QWidget *parent)
    : QWidget(parent)
{
    /*---------------网格的基础内容创建---------------*/
    emailWidget = new QTableWidget(this);
    emailWidget->setSelectionBehavior(QAbstractItemView::SelectRows);       //设置每次选中一行
    emailWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);        //设置不可编辑



                /*------设置表格标题------*/

    QStringList header;
    header<<tr("邮件标题") << tr("发信人") << tr("地址") << tr("状态");
    emailWidget->setHorizontalHeaderLabels(header);
    emailWidget->resize(1200, 800);
    emailWidget->show();

                /*------插入表格内容------*/
                /*------表格为4列-----*/
                /*------行数暂定为10列-----*/
    emailWidget->setColumnCount(4);
    int row_count = 10;
    emailWidget->setRowCount(row_count);

    for(int i = 0; i < row_count; i++)
    {
        QTableWidgetItem *item0 = new QTableWidgetItem();
        QTableWidgetItem *item1 = new QTableWidgetItem();
        QTableWidgetItem *item2 = new QTableWidgetItem();
        QTableWidgetItem *item3 = new QTableWidgetItem();

        item0->setText(QString("已删除 %1").arg(i));
        item1->setText("张三");
        item2->setText("111111");
        item3->setText("点击进入可选择永久删除");
        item3->setForeground(QBrush(QColor(255, 0, 0)));


        emailWidget->setItem(i, 0, item0);
        emailWidget->setItem(i, 1, item1);
        emailWidget->setItem(i, 2, item2);
        emailWidget->setItem(i, 3, item3);
    }
    /*---------------网格的基础内容创建---------------*/



    //双击定位到QTableWidget所在行号
    connect(emailWidget, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(tableDoubleClicked(QModelIndex)));




    /*----------------外界面的设置---------------*/
    this->resize(1200, 800);
    setWindowTitle("已删除");
    /*----------------外界面的设置---------------*/
}





void Deleted::tableDoubleClicked(QModelIndex index)
{

    /*-----------获取一行内容的方法----------*/

    //输出点击列的行号
    //qDebug() << index.row();

    //获取点击行的指定行的指定列内容
    //qDebug() << emailWidget->item(index.row(),1)->text();

    /*-----------获取一行内容的方法----------*/




    /*----------------点击将指定列的未删除变为已删除---------------*/

            /*----------将界面的未删除显示为已删除----------*/

    QTableWidgetItem *tmpitem = new QTableWidgetItem();
    tmpitem->setText("永久删除");
    tmpitem->setForeground(QBrush(QColor(0, 255, 0)));
    emailWidget->setItem(index.row(), 3, tmpitem);

            /*----------将界面的未删除显示为已删除----------*/


            /*----------改变数据库的内容----------*/




            /*----------改变数据库的内容----------*/


    /*----------------点击将指定列的未删除变为已删除---------------*/





    /*----------------跳转窗口---------------*/

        //    Read *r = new Read();
        //    r->show();
        //    this->hide();




     /*----------------跳转窗口---------------*/

}








/*---------------类的析构函数---------------*/
Deleted::~Deleted()
{

}
/*---------------类的析构函数---------------*/


