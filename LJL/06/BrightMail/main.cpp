/*---------------界面的头文件---------------*/
#include "dialog.h"

#include "extra1_tcp/clientwidget.h"
#include "extra1_tcp/serverwidget.h"
#include "login/logindlg.h"
#include "part1_receivemail/recemail.h"
#include "part3_deliver/deliver.h"
#include "part4_deleted/deleted.h"
#include "part5_draftBox/draftbox.h"
#include "part6_friends/friends.h"
/*---------------界面的头文件---------------*/


/*---------------通信的头文件--------------*/
#include "Client/Client_Core.h"
/*---------------通信的头文件--------------*/


#include <QApplication>
#include <QFile>


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


    /*----------------qss文件的添加---------------*/




    /*----------------主界面的测试---------------*/

    Dialog dialog;
    dialog.resize(600, 800);
    dialog.show();

    /*----------------主界面的测试---------------*/




    /*---------------联系人界面的测试---------------*/

//    Friends w;
//    w.resize(600, 800);
//    w.show();

     /*---------------联系人界面的测试---------------*/



    /*---------------TCP模块测试-------------*/

//    ServerWidget w;
//    w.show();

//    ClientWidget w2;
//    w2.show();

    /*---------------TCP模块测试-------------*/



    /*---------------登录测试---------------*/


//    Dialog newDialog;
//    LoginDlg newLoginDlg;

//    if (newLoginDlg.exec() == QDialog::Accepted)
//    {
//        newDialog.show();
//        return a.exec();
//    }
//    else
//    {
//        return 0;
//    }


     /*---------------登录测试---------------*/





    /*----------------登录模块连接数据库测试---------------*/














    /*----------------登录模块连接数据库测试---------------*/


//     CLIENT::Client_Core CC("123.57.176.139");
//    // CLIENT::Client_Core CC;
//    // CLIENT::Client_Core CC("0.0.0.0");
//    const char *request = argv[1];
//    if(argv[1]==NULL)
//    {
//        request="sign_in";
//    }
//    // char user_name[20];
//    // char password[20];
//    char telephone[20];
//    int rt_val = -1;

//    std::cout << "input username:" << std::endl;
//    const char* user_name="WZC";
//    std::cout << "input password:" << std::endl;
//    const char* password="WZCNB";
//    if (strcmp(request, "sign_in") == 0)
//    {
//        rt_val = CC.Sign_in((char*)user_name, (char*)password);
//    }
//    else if (strcmp(request, "sign_up") == 0)
//    {
//        std::cout << "input telephone:" << std::endl;
//        std::cin >> telephone;
//        rt_val = CC.Sign_up((char*)user_name, (char*)password, telephone);
//    }

//    if (rt_val < 0)
//    {
//        std::cout << "login fail" << std::endl;
//    }
//    else
//    {
//        std::cout << "login success" << std::endl;
//    }
//    CC.Send_Exit();



     /*----------------登录模块连接数据库测试---------------*/








    /*----------------收邮件界面的测试-------------*/

//    RecEmail *rec = new RecEmail;
//    rec->show();





    /*----------------收邮件界面的测试-------------*/








    /*----------------草稿箱的测试-------------*/


//        DraftBox dra;
//        dra.show();


     /*----------------草稿箱的测试-------------*/





    /*-----------------已发送的测试--------------*/

//    Deliver deli;
//    deli.show();



    /*-----------------已发送的测试--------------*/





    /*-----------------已删除界面的测试--------------*/


//    Deleted dl;
//    dl.show();



     /*-----------------已删除界面的测试--------------*/
    return a.exec();
}
