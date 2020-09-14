#ifndef RECEIVEMAIL_H
#define RECEIVEMAIL_H

#include <QWidget>

namespace Ui {
class ReceiveMail;
}

class ReceiveMail : public QWidget
{
    Q_OBJECT

public:
    explicit ReceiveMail(QWidget *parent = 0);
    ~ReceiveMail();

private:
    Ui::ReceiveMail *ui;
};

#endif // RECEIVEMAIL_H
