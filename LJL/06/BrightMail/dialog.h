#ifndef DIALOG_H
#define DIALOG_H

/*---------------其他窗口的头文件---------------*/

#include "part1_receivemail/recemail.h"

#include "part3_deliver/deliver.h"
#include "part4_deleted/deleted.h"
#include "part5_draftBox/draftbox.h"
#include "part6_friends/friends.h"


#include "extra1_tcp/clientwidget.h"
#include "extra1_tcp/serverwidget.h"
#include "extra1_tcp/form.h"

/*---------------其他窗口的头文件---------------*/

#include <QDialog>

QT_BEGIN_NAMESPACE
class QAction;
class QDialogButtonBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QMenu;
class QMenuBar;
class QPushButton;
class QTextEdit;
QT_END_NAMESPACE

//! [0]
class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog();

public slots:
    /*----------点击跳转子窗口的槽函数----------*/
    void fir_buttons1_clicked();

    void fir_buttons2_clicked();

    void fir_buttons3_clicked();

    void fir_buttons4_clicked();

    void fir_buttons5_clicked();

    void fir_buttons6_clicked();
    /*----------点击跳转子窗口的槽函数----------*/





    /*-----------点击跳转到拓展功能的窗口----------*/

    void sec_buttons1_clicked();

    void sec_buttons2_clicked();

    void sec_buttons3_clicked();
    /*-----------点击跳转到拓展功能的窗口----------*/

private:
    void createMenu();
    void createHorizontalGroupBox();
    void createGridGroupBox();
    void createFormGroupBox();

    enum { NumGridRows = 3, NumButtons = 6 };

    QMenuBar *menuBar;
    QGroupBox *horizontalGroupBox;
    QGroupBox *gridGroupBox;
    QGroupBox *formGroupBox;
    QTextEdit *smallEditor;
    QTextEdit *bigEditor;
    QLabel *labels[NumGridRows];
    QLineEdit *lineEdits[NumGridRows];
    QPushButton *sec_buttons[NumGridRows];
    QPushButton *fir_buttons[NumButtons];
    QDialogButtonBox *buttonBox;

    QMenu *fileMenu;
    QAction *exitAction;




    /*----------为每一个窗口创建一个指针----------*/

    RecEmail *p_newRec;

    Deliver *p_newDeli;
    Deleted *p_newDeleted;
    DraftBox *p_newDraft;
    Friends *p_newFriend;


    ClientWidget *p_newClientWidget;
    ServerWidget *p_newServerWidget;
    /*----------为每一个窗口创建一个指针----------*/

};
//! [0]

#endif // DIALOG_H
