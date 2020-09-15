#include "Client_Core.h"
#include <iostream>
#include <string.h>
#include "../Dependencies/My_Json.h"
using namespace std;

int main(int argc, char const *argv[])
{
    CLIENT::Client_Core CC("0.0.0.0");
    // CLIENT::Client_Core CC;
    // CLIENT::Client_Core CC("0.0.0.0");
    const char *request = argv[1];
    if (argv[1] == NULL)
    {
        request = "sign_in";
    }

    char user_name[20];
    char password[20];
    char telephone[20];
    int rt_val = -1;
    // CC.Send_Exit();
    // return 0;

    std::cout << "input username:" << std::endl;
    std::cin >> user_name;
    std::cout << "input password:" << std::endl;
    std::cin >> password;
    if (strcmp(request, "sign_in") == 0)
    {
        rt_val = CC.Sign_in(user_name, password);
    }
    else if (strcmp(request, "sign_up") == 0)
    {
        std::cout << "input telephone:" << std::endl;
        std::cin >> telephone;
        rt_val = CC.Sign_up(user_name, password, telephone);
    }
    if (rt_val < 0)
    {
        cout << "login fail" << endl;
    }
    else
    {
        cout << "scd operate" << endl;
        // char operate[10];
        // // cout << "input operate" << endl;
        // // cin >> operate;
        // char one[10];
        // char two[10];
        // char three[10];
        // cin >> one;
        // cin >> two;
        // cin >> three;
        // CC.

        // cout<<"联系人"<<endl;
        // /*------------------获取联系人列表测试-------------------
        // */
        // int size;
        // DataBag::CONTATCT_INFO *CI = CC.Get_Contact("usrid", &size);
        // cout << "size:" << size << endl;
        // for (int i = 0; i < size; i++)
        // {
        //     cout << CI[i].telephone << CI[i].userId << CI[i].userName << endl;
        // }

        // cout<<"获取邮件"<<endl;
        // /*------------------获取邮件测试-------------------
        // */
        // DataBag::EMAIL_CONTENT *EC = CC.Get_Mail_Detail("email_id", "owner_id");
        // if (EC != NULL)
        // {
        //     cout << EC->emailContent << EC->emailTime << EC->emailTitle << EC->emailType << EC->targetUsername << endl;
        // }
        // else
        // {
        //     cout << "hhhh" << endl;
        // }

        // cout<<"邮件列表"<<endl;
        // /*------------------获取邮件列表测试-------------------
        // */
        // int size2;
        // DataBag::EMAIL_INFO *EI = CC.Get_Mail_List("userid", "emaityoe", &size2);
        // for (int i = 0; i < size2; i++)
        // {
        //     cout << EI[i].emailId << EI[i].emailTime << EI[i].emailTitle << EI[i].targetUsername << endl;
        // }

        // cout<<"添加联系人"<<endl;
        // /*------------------添加联系人-------------------
        // */
        // CC.Send_Contact("user_id", "contact_name", "phone_num");

        cout << "发送邮件" << endl;
        /*------------------发送邮件-------------------
        */
        char ownerId[10];
        char targetId[10];
        char emailType[10];
        char emailTitle[10];
        char emailContent[10];
        cin >> ownerId;
        cin >> targetId;
        cin >> emailType;
        cin >> emailTitle;
        cin >> emailContent;
        
        CC.Send_Mail("ownerId", "targetId", "email_type", "email_title", "email_content");
    }
    // signal(SIGINT, );
    CC.Send_Exit();
    return 0;
}
//所有ID都改为电话号码
//ownerId=>ownerTele
//targetId=>targetTele