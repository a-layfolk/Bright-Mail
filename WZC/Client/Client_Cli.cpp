#include "Client_Core.h"
#include <iostream>
#include <string.h>
#include "../Dependencies/My_Json.h"
using namespace std;
#define usu_size 25
int main(int argc, char const *argv[])
{
    CLIENT::Client_Core CC("0.0.0.0");
    char command_one[usu_size];
    char command_two[usu_size];
    char command_three[usu_size];
    char command_four[usu_size];
    char command_long[10000];
    std::cout << "欢迎来到Bright Mail命令行版" << endl;
    std::cout << "您好！请先登陆或注册！" << endl;
    std::cout << "输入对应指令完成操作" << endl;
    cout << "登陆:sign_in     "
         << "注册:sign_up" << endl;
    cin >> command_one;

    cout << "请输入用户名:" << endl;
    cin >> command_two;
    cout << "请输入密码:" << endl;
    cin >> command_three;
    char *id;
    if (strcpy(command_one, "sign_up") == 0)
    {
        cout << "请输入电话号码:" << endl;
        cin >> command_one;
        id = CC.Sign_up(command_two, command_three, command_one);
    }
    else
    {
        id = CC.Sign_in(command_two, command_three);
    }
    if (id == NULL)
    {
        cout << "登陆失败！" << endl;
        CC.Send_Exit();
        exit(1);
    }
    else
    {
        while (1)
        {

            std::cout << "输入对应指令完成操作" << endl;
            cout << "写邮件:w_mail   "
                 << "收件箱:rc_mail  "
                 << "已发送:sd_mail  "
                 << "联系人:contact  "
                 << "添加联系人:ad_contact\n"
                 << "退出程序:exit"
                 << endl;
            cin >> command_one;
            int size = 0;
            if (strcmp(command_one, "w_mail") == 0)
            {
                cout << "输入联系人电话号码:" << endl;
                cin >> command_two;
                cout << "输入邮件标题:" << endl;
                cin >> command_three;
                cout << "输入邮件内容:" << endl;
                cin >> command_long;
                cout << "是否要发附件？ yes/no" << endl;
                cin >> command_four;
                if (strcmp(command_four, "yes") == 0)
                {
                    cout << "请输入文件路径:" << endl;
                    cin >> command_four;
                    CC.Send_Mail_With_File(id, command_two, "sended", command_three, command_long, command_four);
                }
                else
                {
                    CC.Send_Mail(id, command_two, "sended", command_three, command_long);
                }
            }
            else if (strcmp(command_one, "rc_mail") == 0)
            {
            Email_List:
                size = 0;
                DataBag::EMAIL_INFO *EI = CC.Get_Mail_List(id, "received_unread", &size);
                for (int i = 0; i < size; i++)
                {
                    if (EI != NULL)
                    {
                        cout << "-------------------------------------------------------------" << endl;
                        cout << " |邮件id:" << EI[i].emailId << " |发件人:" << EI[i].targetUsername << " |邮件标题:" << EI[i].emailTitle << " |接收时间:" << EI[i].emailTime << endl;
                        cout << "-------------------------------------------------------------" << endl;
                    }
                }
                if (EI != NULL)
                {
                    delete[] EI;
                }

                std::cout << "输入对应指令完成操作" << endl;
                cout << "输入邮件ID查看信件:id <id的值>     返回上一页:return   刷新:refresh" << endl;
                cin >> command_one;
                if (strcmp(command_one, "id") == 0)
                {
                    cin >> command_two;
                    DataBag::EMAIL_CONTENT *EC = CC.Get_Mail_Detail(command_two, id);
                    if (EC != NULL)
                    {
                        cout << "-------------------------------------------------------------" << endl;
                        cout << EC->emailTitle << endl;
                        cout << "-------------------------------------------------------------" << endl;
                        cout << EC->emailContent << endl;
                        cout << "-------------------------------------------------------------" << endl;
                        cout << "发件人:" << EC->targetUsername << endl;
                        cout << EC->emailTime << endl;
                        cout << "-------------------------------------------------------------" << endl;
                        delete EC;
                    }
                    std::cout << "输入对应指令完成操作" << endl;
                    cout << "返回上一页:return" << endl;
                    cin >> command_one;
                    goto Email_List;
                }
                else if (strcmp(command_one, "refresh") == 0)
                {
                    goto Email_List;
                }
                else
                {
                    continue;
                }
            }

            else if (strcmp(command_one, "sd_mail") == 0)
            {
            Email_List2:
                DataBag::EMAIL_INFO *EI = CC.Get_Mail_List(id, "sended", &size);
                for (int i = 0; i < size; i++)
                {
                    if (EI + i != NULL)
                    {
                        cout << "-------------------------------------------------------------" << endl;
                        cout << " |邮件id:" << EI[i].emailId << " |发件人:" << EI[i].targetUsername << " |邮件标题:" << EI[i].emailTitle << " |接收时间:" << EI[i].emailTime << endl;
                        cout << "-------------------------------------------------------------" << endl;
                    }
                }
                if (EI != NULL)
                {
                    delete[] EI;
                }
                cout << "输入邮件ID查看信件:id <id的值> 返回上一页:return" << endl;
                cin >> command_one;
                if (strcmp(command_one, "id") == 0)
                {
                    cin >> command_two;
                    DataBag::EMAIL_CONTENT *EC = NULL;
                    EC = CC.Get_Mail_Detail(command_two, id);
                    if (EC != NULL)
                    {
                        cout << "-------------------------------------------------------------" << endl;
                        cout << EC->emailTitle << endl;
                        cout << "-------------------------------------------------------------" << endl;
                        cout << EC->emailContent << endl;
                        cout << "-------------------------------------------------------------" << endl;
                        cout << "发件人:" << EC->targetUsername << endl;
                        cout << EC->emailTime << endl;
                        cout << "-------------------------------------------------------------" << endl;
                        delete EC;
                    }
                    std::cout << "输入对应指令完成操作" << endl;
                    cout << "返回上一页:return" << endl;
                    cin >> command_one;
                    goto Email_List2;
                }
                else if (strcmp(command_one, "refresh") == 0)
                {
                    goto Email_List;
                }
                else
                {
                    continue;
                }
            }
            else if (strcmp(command_one, "contact") == 0)
            {
                DataBag::CONTATCT_INFO *CI = CC.Get_Contact(id, &size);
                for (int i = 0; i < size; i++)
                {
                    if (CI + i != NULL)
                    {
                        cout << "-------------------------------------------------------------" << endl;
                        cout << " |联系人姓名:" << CI[i].userName << " |电话号码:" << CI[i].telephone << " |" << endl;
                        cout << "-------------------------------------------------------------" << endl;
                    }
                }
                delete[] CI;
            }
            else if (strcmp(command_one, "ad_contact") == 0)
            {
                cout << "请输入联系人姓名:" << endl;
                cin >> command_one;
                cout << "请输入联系人电话:" << endl;
                cin >> command_two;
                CC.Send_Contact(id, command_one, command_two);
            }
            else if (strcmp(command_one, "exit") == 0)
            {
                CC.Send_Exit();
                break;
            }
            else
            {
                cout << "指令有误！" << endl;
                continue;
            }
        }
    }

    return 0;
}
