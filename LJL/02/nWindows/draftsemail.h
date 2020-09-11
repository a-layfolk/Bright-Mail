#ifndef DRAFTSEMAIL_H
#define DRAFTSEMAIL_H

#include <QDialog>

namespace Ui {
class DraftsEmail;
}

class DraftsEmail : public QDialog
{
    Q_OBJECT

public:
    explicit DraftsEmail(QWidget *parent = 0);
    ~DraftsEmail();

signals:
    //子窗口新建一个信号槽传递关闭事件
    void ExitWin();

private slots:
    void on_buttonReturn_clicked();

private:
    Ui::DraftsEmail *ui;
};

#endif // DRAFTSEMAIL_H
