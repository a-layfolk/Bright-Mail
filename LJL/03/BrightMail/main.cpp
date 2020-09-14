#include "dialog.h"
#include <QApplication>
#include "part6_friends/friends.h"
#include "extra1_tcp/clientwidget.h"
#include "extra1_tcp/serverwidget.h"

#include <QApplication>

#include "dialog.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog dialog;
    dialog.resize(600, 800);
    dialog.show();


//    Friends w;
//    w.resize(600, 800);
//    w.show();

//    ServerWidget w;
//    w.show();

//    ClientWidget w2;
//    w2.show();


    return a.exec();
}
