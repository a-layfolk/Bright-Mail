#ifndef REC_DETAILS_H
#define REC_DETAILS_H

#include <QWidget>

namespace Ui {
class rec_details;
}

class rec_details : public QWidget
{
    Q_OBJECT

public:
    explicit rec_details(QWidget *parent = 0);
    ~rec_details();

public:
    void sendData(QString data);

private slots:
    void on_delButton_clicked();

    void on_btnReturn_clicked();

private:
    Ui::rec_details *ui;

};

#endif // REC_DETAILS_H
