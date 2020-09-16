#ifndef DETAILS_DRAFT_H
#define DETAILS_DRAFT_H

#include <QWidget>

namespace Ui {
class details_draft;
}

class details_draft : public QWidget
{
    Q_OBJECT

public:
    explicit details_draft(QWidget *parent = 0);
    ~details_draft();

public:
    void sendData(QString data);

private slots:
    void on_btnClear_clicked();

    void on_btnReturn_clicked();

    void on_btnLoad_clicked();

    void on_btnSave_clicked();

    void on_btnSend_clicked();

    void on_btnDelete_clicked();

    void on_btnAnnex_clicked();

    void on_btnDraft_clicked();

private:
    Ui::details_draft *ui;
};

#endif // DETAILS_DRAFT_H
