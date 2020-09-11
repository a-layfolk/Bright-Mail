#ifndef DELETEEMAIL_H
#define DELETEEMAIL_H

#include <QDialog>

namespace Ui {
class DeleteEmail;
}

class DeleteEmail : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteEmail(QWidget *parent = 0);
    ~DeleteEmail();

signals:
    //子窗口新建一个信号槽传递关闭事件
    void ExitWin();

private slots:
    void on_buttonReturn_clicked();

private:
    Ui::DeleteEmail *ui;
};

#endif // DELETEEMAIL_H
