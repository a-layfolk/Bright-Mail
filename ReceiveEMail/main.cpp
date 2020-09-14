#include "recemail.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RecEmail w;
    w.show();

    return a.exec();
}
