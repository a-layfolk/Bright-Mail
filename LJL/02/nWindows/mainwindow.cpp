#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "writeemail.h"
#include "transemail.h"
#include "receiveemail.h"
#include "deleteemail.h"
#include "draftsemail.h"
#include "liaisonemail.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::on_buttonWrite_clicked()
{
    WriteEmail *writeLog = new WriteEmail(this);

    writeLog->show();   //打开writeLog窗口

    this->hide();   //之后主窗口隐藏

    //功能实现：当子窗口触发了关闭事件后，主窗口获取的子窗口关闭信号并还原主窗口
    connect(writeLog,SIGNAL(ExitWin()),this,SLOT(show()));
}



void MainWindow::on_buttonTrans_clicked()
{
    TransEmail *transLog = new TransEmail(this);

    transLog->show();   //打开writeLog窗口

    this->hide();   //之后主窗口隐藏

    //功能实现：当子窗口触发了关闭事件后，主窗口获取的子窗口关闭信号并还原主窗口
    connect(transLog,SIGNAL(ExitWin()),this,SLOT(show()));
}

void MainWindow::on_buttonReceive_clicked()
{
    ReceiveEMail *receiveLog = new ReceiveEMail(this);

    receiveLog->show();   //打开writeLog窗口

    this->hide();   //之后主窗口隐藏

    //功能实现：当子窗口触发了关闭事件后，主窗口获取的子窗口关闭信号并还原主窗口
    connect(receiveLog,SIGNAL(ExitWin()),this,SLOT(show()));
}

void MainWindow::on_buttonDelete_clicked()
{
    DeleteEmail *deletelog = new DeleteEmail(this);

    deletelog->show();

    this->hide();

    connect(deletelog, SIGNAL(ExitWin()), this, SLOT(show()));
}

void MainWindow::on_buttonDrafts_clicked()
{
    DraftsEmail *draftslog = new DraftsEmail(this);

   draftslog->show();

    this->hide();

    connect(draftslog, SIGNAL(ExitWin()), this, SLOT(show()));
}

void MainWindow::on_buttonLiaison_clicked()
{
    LiaisonEmail *liaisonlog = new LiaisonEmail(this);

   liaisonlog->show();

    this->hide();

    connect(liaisonlog, SIGNAL(ExitWin()), this, SLOT(show()));
}
