#ifndef WRITEEMAIL_H
#define WRITEEMAIL_H

#include <QWidget>
#include <Client/Client_Core.h>

namespace Ui {
class WriteEmail;
}

class WriteEmail : public QWidget
{
    Q_OBJECT

public:
    explicit WriteEmail(QWidget *parent = 0);
    ~WriteEmail();

private slots:
    void on_btnClear_clicked();

    void on_btnReturn_clicked();

    void on_btnLoad_clicked();

    void on_btnSave_clicked();

    void on_btnSend_clicked();

    void on_btnAnnex_clicked();

    void on_btnDraft_clicked();

    void on_btnDelete_clicked();



private:
    Ui::WriteEmail *ui;


    /*----------定义连接数据库需要的变量----------*/
    const char* chUser;
    const char* chPhone;
    const char* chTitle;
    const char* chContent;
    //预留位置给全局变量收件人id
    const char* targrtId;

    //预留位置给邮件类型
    const char* email_type;
    /*----------定义连接数据库需要的变量----------*/


    /*
        //预留位置给超级全局变量
        //用户id
    */






};

#endif // WRITEEMAIL_H
