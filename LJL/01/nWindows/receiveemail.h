#ifndef RECEIVEEMAIL_H
#define RECEIVEEMAIL_H

#include <QDialog>

namespace Ui {
class ReceiveEMail;
}

class ReceiveEMail : public QDialog
{
    Q_OBJECT

public:
    explicit ReceiveEMail(QWidget *parent = 0);
    ~ReceiveEMail();

signals:
    //子窗口新建一个信号槽传递关闭事件
    void ExitWin();

private slots:
    void on_buttonReturn_clicked();

private:
    Ui::ReceiveEMail *ui;
};

#endif // RECEIVEEMAIL_H
