#include "mainwindow.h"
#include <QApplication>
#include "logindlg.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    LoginDlg logindlg;                        // 建立自己新建的类的对象dlg

    if(logindlg.exec() == QDialog::Accepted) // 利用Accepted返回值判断按钮是否被按下
    {
        w.show();                      // 如果被按下，显示主窗口
        return a.exec();               // 程序一直执行，直到主窗口关闭
    }
    else return 0;
}
