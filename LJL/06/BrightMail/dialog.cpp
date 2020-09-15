#include <QtWidgets>
#include "dialog.h"
#include <QDebug>

Dialog::Dialog()
{

    createMenu();
    createHorizontalGroupBox();
    createGridGroupBox();
    createFormGroupBox();


    //显示在最下面的文字编辑器
    bigEditor = new QTextEdit;
    //设置文字编辑器为只读
    bigEditor->setReadOnly(true);
    bigEditor->setPlainText(tr("欢迎来到Bright Mail邮件系统 \n"
                               "\n"
                               "系统开发者：\n"
                               "  王梓丞\n"
                               "  万琦玲\n"
                               "  李俊霖\n"
                               "\n"
                               "系统正在开发中，敬请期待...... \n"));



    //显示在右下角的两个按钮
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));





    //用mainLayout布局所有的元素
    QVBoxLayout *mainLayout = new QVBoxLayout;

    mainLayout->setMenuBar(menuBar);
    mainLayout->addWidget(horizontalGroupBox);
    mainLayout->addWidget(gridGroupBox);

    //暂时没有这个布局，先注释掉
//    mainLayout->addWidget(formGroupBox);
    mainLayout->addWidget(bigEditor);
    mainLayout->addWidget(buttonBox);

    //应用mainLayout
    setLayout(mainLayout);

    setWindowTitle(tr("Bright Mail邮件系统"));
}

void Dialog::createMenu()
{
    //创建最顶层的菜单栏
    menuBar = new QMenuBar;

    fileMenu = new QMenu(tr("文件"), this);
    exitAction = fileMenu->addAction(tr("退出"));
    menuBar->addMenu(fileMenu);

    connect(exitAction, SIGNAL(triggered()), this, SLOT(accept()));
}


void Dialog::createHorizontalGroupBox()
{
    horizontalGroupBox = new QGroupBox(tr("基本功能"));
    QHBoxLayout *layout = new QHBoxLayout;


    fir_buttons[0] = new QPushButton(tr("收邮件"));
    fir_buttons[1] = new QPushButton(tr("写邮件"));
    fir_buttons[2] = new QPushButton(tr("已发送"));
    fir_buttons[3] = new QPushButton(tr("已删除"));
    fir_buttons[4] = new QPushButton(tr("草稿箱"));
    fir_buttons[5] = new QPushButton(tr("联系人"));

    for(int i = 0; i < NumButtons; i++)
    {
        layout->addWidget(fir_buttons[i]);
    }

    horizontalGroupBox->setLayout(layout);

    /*----------连接按钮的槽函数----------*/
    connect(fir_buttons[0], SIGNAL(clicked(bool)), this, SLOT(fir_buttons1_clicked()));
    connect(fir_buttons[1], SIGNAL(clicked(bool)), this, SLOT(fir_buttons2_clicked()));
    connect(fir_buttons[2], SIGNAL(clicked(bool)), this, SLOT(fir_buttons3_clicked()));
    connect(fir_buttons[3], SIGNAL(clicked(bool)), this, SLOT(fir_buttons4_clicked()));
    connect(fir_buttons[4], SIGNAL(clicked(bool)), this, SLOT(fir_buttons5_clicked()));
    connect(fir_buttons[5], SIGNAL(clicked(bool)), this, SLOT(fir_buttons6_clicked()));
    /*----------连接按钮的槽函数----------*/
}


void Dialog::createGridGroupBox()
{
    gridGroupBox = new QGroupBox(tr("拓展功能"));

    QGridLayout *layout = new QGridLayout;



    sec_buttons[0] = new QPushButton(tr("QSocket通信"));
    sec_buttons[1] = new QPushButton(tr("QTcpServer传送文件"));
    sec_buttons[2] = new QPushButton(tr("QSql连接数据库"));

    for (int i = 0; i < NumGridRows; ++i)
    {
        labels[i] = new QLabel(tr("Line %1:").arg(i + 1));
//        lineEdits[i] = new QLineEdit;

        layout->addWidget(labels[i], i + 1, 0);
//        layout->addWidget(lineEdits[i], i + 1, 1);
        layout->addWidget(sec_buttons[i], i + 1, 1);
    }


    smallEditor = new QTextEdit;
    smallEditor->setPlainText(tr("这里用Qt实现的小功能：\n"
                                 "\n"
                                 "开发者：\n"
                                 "  李俊霖\n"));
    //设置文字编辑器为只读
    smallEditor->setReadOnly(true);

    layout->addWidget(smallEditor, 0, 2, 4, 1);

    layout->setColumnStretch(1, 10);
    layout->setColumnStretch(2, 20);
    gridGroupBox->setLayout(layout);


    /*----------连接按钮的槽函数----------*/
    connect(sec_buttons[0], SIGNAL(clicked(bool)), this, SLOT(sec_buttons1_clicked()));
    connect(sec_buttons[1], SIGNAL(clicked(bool)), this, SLOT(sec_buttons2_clicked()));
    connect(sec_buttons[2], SIGNAL(clicked(bool)), this, SLOT(sec_buttons3_clicked()));
    /*----------连接按钮的槽函数----------*/

}


void Dialog::createFormGroupBox()
{
//    formGroupBox = new QGroupBox(tr("Form layout"));
//    QFormLayout *layout = new QFormLayout;
//    layout->addRow(new QLabel(tr("Line 1:")), new QLineEdit);
//    layout->addRow(new QLabel(tr("Line 2, long text:")), new QComboBox);
//    layout->addRow(new QLabel(tr("Line 3:")), new QSpinBox);
//    formGroupBox->setLayout(layout);
}




/*----------连接按钮的槽函数----------*/
void Dialog::fir_buttons1_clicked()
{
    p_newRec = new RecEmail;
    p_newRec->show();
}


void Dialog::fir_buttons2_clicked()
{

}


void Dialog::fir_buttons3_clicked()
{
    p_newDeli = new Deliver;
    p_newDeli->show();
}


void Dialog::fir_buttons4_clicked()
{
    p_newDeleted = new Deleted;
    p_newDeleted->show();
}


void Dialog::fir_buttons5_clicked()
{
    p_newDraft = new DraftBox;
    p_newDraft->show();
}


void Dialog::fir_buttons6_clicked()
{
    p_newFriend = new Friends;
    p_newFriend->show();
}


void Dialog::sec_buttons1_clicked()
{
    p_newClientWidget = new ClientWidget;
    p_newServerWidget = new ServerWidget;

    p_newClientWidget->show();
    p_newServerWidget->show();
}


void Dialog::sec_buttons2_clicked()
{

}


void Dialog::sec_buttons3_clicked()
{

}
/*----------连接按钮的槽函数----------*/
