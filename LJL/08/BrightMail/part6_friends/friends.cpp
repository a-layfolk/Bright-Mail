
#include <QDebug>
#include <QJsonDocument>
#include <QByteArray>
#include <QVariant>
#include <QMap>
#include <QString>
#include <QJsonObject>



#include <QtWidgets>
#include "friends.h"


Friends::Friends(QWidget *parent)
    : QWidget(parent)
{

/*-------------------------设置文本和按钮-------------------------*/
    QLabel *nameLabel = new QLabel(tr("姓名:"));
    nameLine = new QLineEdit;
    nameLine->setReadOnly(true);

    QLabel *addressLabel = new QLabel(tr("电话:"));
    addressText = new QTextEdit;
    addressText->setReadOnly(true);

    addButton = new QPushButton(tr("添加"));

    editButton = new QPushButton(tr("编辑"));
    editButton->setEnabled(false);
    removeButton = new QPushButton(tr("删除"));
    removeButton->setEnabled(false);
    findButton = new QPushButton(tr("查找"));
    findButton->setEnabled(false);
    submitButton = new QPushButton(tr("提交"));
    submitButton->hide();
    cancelButton = new QPushButton(tr("取消"));
    cancelButton->hide();

    nextButton = new QPushButton(tr("下一个"));
    nextButton->setEnabled(false);
    previousButton = new QPushButton(tr("上一个"));
    previousButton->setEnabled(false);

    loadButton = new QPushButton(tr("导入"));

    loadButton->setToolTip(tr("导入一个存储联系人和电话的json文件"));

    saveButton = new QPushButton(tr("保存"));

    saveButton->setToolTip(tr("保存联系人到一个json文件中"));
/*-------------------------设置文本和按钮-------------------------*/


/*-------------------------新建查询的子窗口------------------------*/
    saveButton->setEnabled(false);

    dialog = new FindDialog(this);
/*-------------------------新建查询的子窗口------------------------*/



/*-------------------------添加按钮的槽函数-------------------------*/
    connect(addButton, SIGNAL(clicked()), this, SLOT(addContact()));
    connect(submitButton, SIGNAL(clicked()), this, SLOT(submitContact()));
    connect(editButton, SIGNAL(clicked()), this, SLOT(editContact()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));
    connect(removeButton, SIGNAL(clicked()), this, SLOT(removeContact()));
    connect(findButton, SIGNAL(clicked()), this, SLOT(findContact()));
    connect(nextButton, SIGNAL(clicked()), this, SLOT(next()));
    connect(previousButton, SIGNAL(clicked()), this, SLOT(previous()));
    connect(loadButton, SIGNAL(clicked()), this, SLOT(loadFromFile()));
    connect(saveButton, SIGNAL(clicked()), this, SLOT(saveToFile()));
/*-------------------------添加按钮的槽函数-------------------------*/



/*--------------------------添加布局--------------------*/
    QVBoxLayout *buttonLayout1 = new QVBoxLayout;
    buttonLayout1->addWidget(addButton);
    buttonLayout1->addWidget(editButton);
    buttonLayout1->addWidget(removeButton);
    buttonLayout1->addWidget(findButton);
    buttonLayout1->addWidget(submitButton);
    buttonLayout1->addWidget(cancelButton);
    buttonLayout1->addWidget(loadButton);
    buttonLayout1->addWidget(saveButton);
    buttonLayout1->addStretch();

    QHBoxLayout *buttonLayout2 = new QHBoxLayout;
    buttonLayout2->addWidget(previousButton);
    buttonLayout2->addWidget(nextButton);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(nameLabel, 0, 0);
    mainLayout->addWidget(nameLine, 0, 1);
    mainLayout->addWidget(addressLabel, 1, 0, Qt::AlignTop);
    mainLayout->addWidget(addressText, 1, 1);
    mainLayout->addLayout(buttonLayout1, 1, 2);
    mainLayout->addLayout(buttonLayout2, 2, 1);
/*--------------------------添加布局--------------------*/

    setLayout(mainLayout);
    setWindowTitle(tr("联系人"));
}

void Friends::addContact()
{
    oldName = nameLine->text();
    oldAddress = addressText->toPlainText();

    nameLine->clear();
    addressText->clear();

    updateInterface(AddingMode);
}

void Friends::editContact()
{
    oldName = nameLine->text();
    oldAddress = addressText->toPlainText();

    updateInterface(EditingMode);
}

void Friends::submitContact()
{
    QString name = nameLine->text();
    QString address = addressText->toPlainText();

    if (name.isEmpty() || address.isEmpty())
    {
        QMessageBox::information(this, tr("空文本"),
            tr("请添加用户名和电话"));
        return;
    }

    if (currentMode == AddingMode)
    {

        if (!contacts.contains(name)) {
            contacts.insert(name, address);
            QMessageBox::information(this, tr("添加成功"),
                tr("\"%1\" 已经被添加到联系人").arg(name));
        } else {
            QMessageBox::information(this, tr("添加失败"),
                tr("对不起, \"%1\" 已经存在于联系人中").arg(name));
        }
    } else if (currentMode == EditingMode) {

        if (oldName != name) {
            if (!contacts.contains(name)) {
                QMessageBox::information(this, tr("编辑成功"),
                    tr("\"%1\" 已经修改到联系人").arg(oldName));
                contacts.remove(oldName);
                contacts.insert(name, address);
            } else {
                QMessageBox::information(this, tr("编辑失败"),
                    tr("对不起, \"%1\" 已经存在于联系人中").arg(name));
            }
        } else if (oldAddress != address) {
            QMessageBox::information(this, tr("编辑成功"),
                tr("\"%1\" 已经修改到联系人").arg(name));
            contacts[name] = address;
        }
    }

    updateInterface(NavigationMode);
}

void Friends::cancel()
{
    nameLine->setText(oldName);
    addressText->setText(oldAddress);
    updateInterface(NavigationMode);
}

void Friends::removeContact()
{
    QString name = nameLine->text();
    QString address = addressText->toPlainText();

    if (contacts.contains(name))
    {

        int button = QMessageBox::question(this,
            tr("确定删除"),
            tr("你确定要删除 \"%1\"吗?").arg(name),
            QMessageBox::Yes | QMessageBox::No);

        if (button == QMessageBox::Yes)
        {

            previous();
            contacts.remove(name);

            QMessageBox::information(this, tr("删除成功"),
                tr("\"%1\"已经被移除联系人").arg(name));
        }
    }

    updateInterface(NavigationMode);
}

void Friends::next()
{
    QString name = nameLine->text();
    QMap<QString, QString>::iterator i = contacts.find(name);

    if (i != contacts.end())
        i++;

    if (i == contacts.end())
        i = contacts.begin();

    nameLine->setText(i.key());
    addressText->setText(i.value());
}

void Friends::previous()
{
    QString name = nameLine->text();
    QMap<QString, QString>::iterator i = contacts.find(name);

    if (i == contacts.end()) {
        nameLine->clear();
        addressText->clear();
        return;
    }

    if (i == contacts.begin())
        i = contacts.end();

    i--;
    nameLine->setText(i.key());
    addressText->setText(i.value());
}

void Friends::findContact()
{
    dialog->show();

    if (dialog->exec() == 1) {
        QString contactName = dialog->getFindText();

        if (contacts.contains(contactName)) {
            nameLine->setText(contactName);
            addressText->setText(contacts.value(contactName));
        } else {
            QMessageBox::information(this, tr("找不到"),
                tr("对不起, \"%1\" 不在通讯录中.").arg(contactName));
            return;
        }
    }

    updateInterface(NavigationMode);
}

void Friends::updateInterface(Mode mode)
{
    currentMode = mode;

    switch (currentMode) {

    case AddingMode:
    case EditingMode:

        nameLine->setReadOnly(false);
        nameLine->setFocus(Qt::OtherFocusReason);
        addressText->setReadOnly(false);

        addButton->setEnabled(false);
        editButton->setEnabled(false);
        removeButton->setEnabled(false);

        nextButton->setEnabled(false);
        previousButton->setEnabled(false);

        submitButton->show();
        cancelButton->show();

        loadButton->setEnabled(false);
        saveButton->setEnabled(false);
        break;

    case NavigationMode:

        if (contacts.isEmpty()) {
            nameLine->clear();
            addressText->clear();
        }

        nameLine->setReadOnly(true);
        addressText->setReadOnly(true);
        addButton->setEnabled(true);

        int number = contacts.size();
        editButton->setEnabled(number >= 1);
        removeButton->setEnabled(number >= 1);
        findButton->setEnabled(number > 2);
        nextButton->setEnabled(number > 1);
        previousButton->setEnabled(number > 1);

        submitButton->hide();
        cancelButton->hide();

        loadButton->setEnabled(true);
        saveButton->setEnabled(number >= 1);
        break;
    }
}



void Friends::saveToFile()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("保存联系人"), "",
        tr("联系人 (*.json);;All Files (*)"));


    if (fileName.isEmpty())
        return;
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(this, tr("无法打开文件"),
                file.errorString());
            return;
        }




        //把QMap(String, String)转换为json
        QMap<QString, QString>::iterator i = contacts.begin();
        QMap<QString, QVariant> newData = QMap<QString, QVariant>();
        while(i != contacts.end())
        {
            QString tmpKey = i.key();
            QVariant tmpValue = (QVariant)i.value();
            newData.insert(tmpKey, tmpValue);

            i++;
        }

        QJsonDocument doc=QJsonDocument::fromVariant(newData);
        QByteArray jba=doc.toJson();
        QString jsonString = QString(jba);

        file.write(jba);
        file.close();
        qDebug() << jsonString;
    }
}


















void Friends::loadFromFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("打开联系人"), "",
        tr("联系人 (*.json);;All Files (*)"));

    if (fileName.isEmpty())
        return;
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(this, tr("无法打开文件"),
                file.errorString());
            return;
        }



        //读取json文件然后转换为QMap<String, String>

            QByteArray data=file.readAll();
            file.close();

            //使用json文件对象加载字符串

             QJsonParseError json_error;
             QJsonDocument jsonDoc(QJsonDocument::fromJson(data, &json_error));

             if(json_error.error != QJsonParseError::NoError)
             {
                 qDebug() << "json error!";
                 return;
             }

             contacts.clear();   // clear existing contacts

             QJsonObject rootObj = jsonDoc.object();
             QStringList keys = rootObj.keys();
             for(int i = 0; i < keys.size(); i++)
             {
                 QString tmpKey = keys.at(i);
                 QString tmpValue = rootObj.value(keys.at(i)).toString();

                 contacts.insert(tmpKey, tmpValue);
             }


        if (contacts.isEmpty()) {
            QMessageBox::information(this, tr("文件中没有内容"),
                tr("你打开的是一个空文件"));
        } else {
            QMap<QString, QString>::iterator i = contacts.begin();
            nameLine->setText(i.key());
            addressText->setText(i.value());
        }
    }

    updateInterface(NavigationMode);
}

