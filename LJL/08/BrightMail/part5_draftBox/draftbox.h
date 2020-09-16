#ifndef DRAFTBOX_H
#define DRAFTBOX_H

#include <QWidget>
#include <QTableWidget>

class DraftBox : public QWidget
{
    Q_OBJECT

public:
    DraftBox(QWidget *parent = 0);
    ~DraftBox();

signals:
//    void self_signal_draft(QString targetName, QString title);

private slots:
    void tableDoubleClicked_send_slot(QModelIndex);   //双击一行跳转的槽函数

public:
    QTableWidget *emailWidget;              //设置表格为全局变量，这样槽函数就可以访问它
};

#endif // DRAFTBOX_H
