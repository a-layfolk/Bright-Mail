#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_buttonWrite_clicked();

    void on_buttonTrans_clicked();

    void on_buttonReceive_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
