#ifndef WRITEEMAIL_H
#define WRITEEMAIL_H

#include <QDialog>

namespace Ui {
class WriteEmail;
}

class WriteEmail : public QDialog
{
    Q_OBJECT

public:
    explicit WriteEmail(QWidget *parent = 0);
    ~WriteEmail();

signals:
    //子窗口新建一个信号槽传递关闭事件
    void ExitWin();

private slots:
    void on_buttonReturn_clicked();

    void on_buttonSend_clicked();

private:
    Ui::WriteEmail *ui;


};

#endif // WRITEEMAIL_H
