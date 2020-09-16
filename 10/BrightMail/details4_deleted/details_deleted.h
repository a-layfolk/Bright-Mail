#ifndef DETAILS_DELETED_H
#define DETAILS_DELETED_H

#include <QWidget>

namespace Ui {
class details_deleted;
}

class details_deleted : public QWidget
{
    Q_OBJECT

public:
    explicit details_deleted(QWidget *parent = 0);
    ~details_deleted();

public:
    void sendData(QString data);

private slots:
    void on_btnRecover_clicked();

    void on_btnDeleteForever_clicked();

    void on_btnReturn_clicked();

private:
    Ui::details_deleted *ui;
};

#endif // DETAILS_DELETED_H
