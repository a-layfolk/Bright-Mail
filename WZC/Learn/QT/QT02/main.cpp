#include<QApplication>
#include<QWidget>//QT's widget basic object
#include<QPushButton>
int main(int argc, char *argv[])
{
    QApplication app(argc,argv);
    QWidget QW;
    QW.setWindowTitle("NO");
    QPushButton Button;
    Button.setText(":(");
    Button.setParent(&QW);
    QW.show();
    QPushButton Button2(&QW);
    Button2.move(100,100);
    Button2.setText("Mother");
    Button2.show();
    app.exec();
    return 0;
}
