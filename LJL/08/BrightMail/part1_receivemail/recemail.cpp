#include "recemail.h"
#include <QDebug>
#include <QModelIndex>

RecEmail::RecEmail(QWidget *parent)
    : QWidget(parent)
{


/*---------------------------------连接数据库，如果成功--------------------------------*/


//        int return_size_read;
//        int return_size_unread;
//        CLIENT::Client_Core CC("123.57.176.139");
//        CLIENT::EMAIL_INFO *newTableListRead = CC.Get_Mail_List("1","received_readed", &return_size_read);
//        CLIENT::EMAIL_INFO *newTableListUnRead = CC.Get_Mail_List("1", "received_unread", &return_size_unread);

//        /*---------------网格的基础内容创建---------------*/
//        emailWidget = new QTableWidget(this);
//        emailWidget->setSelectionBehavior(QAbstractItemView::SelectRows);       //设置每次选中一行
//        emailWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);        //设置不可编辑


//        /*------设置表格标题------*/

//        QStringList header_success;
//        header_success<<tr("邮件标题") << tr("发信人") << tr("发送时间") << tr("邮件编号");
//        emailWidget->setHorizontalHeaderLabels(header_success);
//        emailWidget->resize(1200, 800);
//        emailWidget->show();

//        /*------插入表格内容------*/
//        /*------表格为4列-----*/
//        emailWidget->setColumnCount(4);

//        /*------行数由连接数据库后赋值------*/
//        emailWidget->setRowCount(return_size_read);


//        /*---------------------for循环生成已读列表--------------------------*/
//        for(int i = 0; i < return_size_read; i++)
//        {
//            char *chEmailTitle = newTableListRead[i].emailTitle;
//            char *chTargetUsername = newTableListRead[i].targetUsername;
//            char *chEmailTime = newTableListRead[i].emailTime;
//            char *chEmailId = newTableListRead[i].emailId;

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

//            //把已读邮件的标题全部刷为绿色
//            item0->setForeground(QBrush(QColor(0, 255, 0)));

//            emailWidget->setItem(i, 0, item0);
//            emailWidget->setItem(i, 1, item1);
//            emailWidget->setItem(i, 2, item2);
//            emailWidget->setItem(i, 3, item3);
//        }
//        /*---------------------for循环生成已读列表--------------------------*/









//        /*---------------------for循环生成未读列表--------------------------*/
//        for(int i = 0; i < return_size_read; i++)
//        {
//            char *chEmailTitle = newTableListUnRead[i].emailTitle;
//            char *chTargetUsername = newTableListUnRead[i].targetUsername;
//            char *chEmailTime = newTableListUnRead[i].emailTime;
//            char *chEmailId = newTableListUnRead[i].emailId;

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

//            //把未读邮件的标题全部刷为红色
//            item0->setForeground(QBrush(QColor(255, 0, 0)));

//            emailWidget->setItem(i, 0, item0);
//            emailWidget->setItem(i, 1, item1);
//            emailWidget->setItem(i, 2, item2);
//            emailWidget->setItem(i, 3, item3);
//        }
        /*---------------------for循环生成未读列表--------------------------*/

/*---------------------------------连接数据库，如果成功--------------------------------*/










/*---------------------------------连接数据库，如果失败--------------------------------*/
    /*---------------网格的基础内容创建---------------*/
    emailWidget = new QTableWidget(this);
    emailWidget->setSelectionBehavior(QAbstractItemView::SelectRows);       //设置每次选中一行
    emailWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);        //设置不可编辑

                /*------设置表格标题------*/

    QStringList header_failure;
    header_failure<<tr("邮件标题") << tr("发信人") << tr("发送时间") << tr("邮件编号");
    emailWidget->setHorizontalHeaderLabels(header_failure);
    emailWidget->resize(1200, 800);
    emailWidget->show();

                /*------插入表格内容------*/
                /*------表格为4列-----*/
                /*------行数暂定为10列-----*/
    emailWidget->setColumnCount(4);
    int row_count = 10;
    emailWidget->setRowCount(row_count);

    for(int i = 0; i < 10; i++)
    {
        QTableWidgetItem *item0 = new QTableWidgetItem();
        QTableWidgetItem *item1 = new QTableWidgetItem();
        QTableWidgetItem *item2 = new QTableWidgetItem();
        QTableWidgetItem *item3 = new QTableWidgetItem();
        
        item0->setText("作业");
        item1->setText("张三");
        item2->setText("2020-9-15");
        item3->setText(QString("编号 %1").arg(i));
        if(i < 5)
        {
            item3->setForeground(QBrush(QColor(255, 0, 0)));
        }
        else
        {
            item3->setForeground(QBrush(QColor(0, 255, 0)));
        }


        emailWidget->setItem(i, 0, item0);
        emailWidget->setItem(i, 1, item1);
        emailWidget->setItem(i, 2, item2);
        emailWidget->setItem(i, 3, item3);
    }



    /*---------------网格的基础内容创建---------------*/

/*---------------------------------连接数据库，如果失败--------------------------------*/









    //双击定位到QTableWidget所在行号
    connect(emailWidget, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(tableDoubleClicked(QModelIndex)));




    /*----------------外界面的设置---------------*/
    this->resize(900, 600);
    setWindowTitle("收邮件");
    /*----------------外界面的设置---------------*/
}





void RecEmail::tableDoubleClicked(QModelIndex index)
{

    RecEmail newRecEmail;
    newRecEmail.show();
    /*-----------获取一行内容的方法----------*/

    //输出点击列的行号
    //qDebug() << index.row();

    //获取点击行的指定行的指定列内容
    //qDebug() << emailWidget->item(index.row(),1)->text();

    /*-----------获取一行内容的方法----------*/


    /*----------------跳转窗口---------------*/

    QString emailId = emailWidget->item(index.row(),3)->text();

    rec_details *new_rec_del = new rec_details;

    new_rec_del->sendData(emailId);

    new_rec_del->show();

//    this->hide();



     /*----------------跳转窗口---------------*/

}


/*---------------类的析构函数---------------*/
RecEmail::~RecEmail()
{

}
/*---------------类的析构函数---------------*/

