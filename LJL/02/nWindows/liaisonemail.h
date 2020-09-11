#ifndef LIAISONEMAIL_H
#define LIAISONEMAIL_H

#include <QDialog>
#include <QLabel>

namespace Ui {
class LiaisonEmail;
}

class LiaisonEmail : public QDialog
{
    Q_OBJECT

public:
    explicit LiaisonEmail(QWidget *parent = 0);
    ~LiaisonEmail();

signals:
    //子窗口新建一个信号槽传递关闭事件
    void ExitWin();

private slots:
    void on_buttonReturn_clicked();

private:
    Ui::LiaisonEmail *ui;

};

#endif // LIAISONEMAIL_H
