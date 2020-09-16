#ifndef DELIVER_DETAILS_H
#define DELIVER_DETAILS_H

#include <QWidget>

namespace Ui {
class deliver_details;
}

class deliver_details : public QWidget
{
    Q_OBJECT

public:
    explicit deliver_details(QWidget *parent = 0);
    ~deliver_details();

public:
    void sendData(QString data);

private slots:
    void on_btnReturn_clicked();

    void on_btnTrans_clicked();

    void on_btnDelete_clicked();

    void on_btnSave_clicked();

private:
    Ui::deliver_details *ui;
};

#endif // DELIVER_DETAILS_H
