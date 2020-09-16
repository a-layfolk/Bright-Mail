#include "deleted.h"
#include <QDebug>
#include <QModelIndex>


Deleted::Deleted(QWidget *parent)
    : QWidget(parent)
{



    /*---------------------------------连接数据库，如果成功--------------------------------*/


//        int return_size;
//        CLIENT::Client_Core CC("123.57.176.139");
//        CLIENT::EMAIL_INFO *newTableList = CC.Get_Mail_List("1","deleted", &return_size);

//        /*---------------网格的基础内容创建---------------*/
//        emailWidget = new QTableWidget(this);
//        emailWidget->setSelectionBehavior(QAbstractItemView::SelectRows);       //设置每次选中一行
//        emailWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);        //设置不可编辑


//        /*------设置表格标题------*/

//        QStringList header_success;
//        header_success<<tr("邮件标题") << tr("收件人") << tr("发送时间") << tr("邮件编号");
//        emailWidget->setHorizontalHeaderLabels(header_success);
//        emailWidget->resize(1200, 800);
//        emailWidget->show();

//        /*------插入表格内容------*/
//        /*------表格为4列-----*/
//        emailWidget->setColumnCount(4);

//        /*------行数由连接数据库后赋值------*/
//        emailWidget->setRowCount(return_size);

//        for(int i = 0; i < return_size; i++)
//        {
//            char *chEmailTitle = newTableList[i].emailTitle;
//            char *chTargetUsername = newTableList[i].targetUsername;
//            char *chEmailTime = newTableList[i].emailTime;
//            char *chEmailId = newTableList[i].emailId;

//            QString qsEmailTitle = QString(chEmailTitle);
//            QString qsTargetUsername = QString(chTargetUsername);
//            QString qsEmailTime = QString(chEmailTime);
//            QString qsEmailId = QString(chEmailId);



//            /*--------返回的字符很可能是中文，需要转换一下-----*/
//            //这里先预留一个位置看看输出的是不是乱码
//            qDebug() << qsEmailTitle;
//            qDebug() << qsTargetUsername;
//            qDebug() << qsEmailTime;
//            qDebug() << qsEmailId;
//            /*--------返回的字符很可能是中文，需要转换一下-----*/


//            QTableWidgetItem *item0 = new QTableWidgetItem();
//            QTableWidgetItem *item1 = new QTableWidgetItem();
//            QTableWidgetItem *item2 = new QTableWidgetItem();
//            QTableWidgetItem *item3 = new QTableWidgetItem();


//            item0->setText(qsEmailTitle);
//            item1->setText(qsTargetUsername);
//            item2->setText(qsEmailTime);
//            item3->setText(qsEmailId);



//            emailWidget->setItem(i, 0, item0);
//            emailWidget->setItem(i, 1, item1);
//            emailWidget->setItem(i, 2, item2);
//            emailWidget->setItem(i, 3, item3);
//        }

    /*---------------------------------连接数据库，如果成功--------------------------------*/











    /*---------------网格的基础内容创建---------------*/
    emailWidget = new QTableWidget(this);
    emailWidget->setSelectionBehavior(QAbstractItemView::SelectRows);       //设置每次选中一行
    emailWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);        //设置不可编辑



                /*------设置表格标题------*/

    QStringList header_failure;
    header_failure<<("邮件标题") << tr("收件人") << tr("发送时间") << tr("邮件编号");
    emailWidget->setHorizontalHeaderLabels(header_failure);
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
        item2->setText("2020-9-15");
        item3->setText(QString("编号 %1").arg(i));


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


