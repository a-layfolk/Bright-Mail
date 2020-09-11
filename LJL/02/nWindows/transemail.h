#ifndef TRANSEMAIL_H
#define TRANSEMAIL_H

#include <QDialog>

namespace Ui {
class TransEmail;
}

class TransEmail : public QDialog
{
    Q_OBJECT

public:
    explicit TransEmail(QWidget *parent = 0);
    ~TransEmail();

signals:
    //子窗口新建一个信号槽传递关闭事件
    void ExitWin();

private slots:
    void on_buttonReturn_clicked();

private:
    Ui::TransEmail *ui;
};

#endif // TRANSEMAIL_H
