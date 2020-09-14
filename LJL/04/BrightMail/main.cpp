#include "dialog.h"
#include <QApplication>
#include "part6_friends/friends.h"
#include "extra1_tcp/clientwidget.h"
#include "extra1_tcp/serverwidget.h"
#include "login/logindlg.h"

#include <QApplication>
#include <QFile>
#include "dialog.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /*----------------qss文件的添加---------------*/


//    QString qss;
//    QFile qssFile(":/sources/beautify/qss/logindlg/logindlg.qss");
//    qssFile.open(QFile::ReadOnly);
//    if(qssFile.isOpen()){
//        qss=QLatin1String(qssFile.readAll());
//        a.setStyleSheet(qss);
//        qssFile.close();
//    }
//    else
//    {
//            qDebug()<<"open qss error";
//    }


//    Dialog dialog;
//    dialog.resize(600, 800);
//    dialog.show();


//    Friends w;
//    w.resize(600, 800);
//    w.show();

//    ServerWidget w;
//    w.show();

//    ClientWidget w2;
//    w2.show();



    /*---------------登录测试---------------*/


    Dialog newDialog;
    LoginDlg newLoginDlg;

    if (newLoginDlg.exec() == QDialog::Accepted)
    {
        newDialog.show();
        return a.exec();
    }
    else
    {
        return 0;
    }








    return a.exec();
}
