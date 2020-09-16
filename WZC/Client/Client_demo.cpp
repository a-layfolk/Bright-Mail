#include "Client_Core.h"
#include <iostream>
#include <string.h>
#include "../Dependencies/My_Json.h"
using namespace std;

int main(int argc, char const *argv[])
{
    // CLIENT::Client_Core CC("123.57.176.139");
    // CLIENT::Client_Core CC;
    CLIENT::Client_Core CC("0.0.0.0");
    const char *request = argv[1];
    char *id;
    if (argv[1] == NULL)
    {
        request = "sign_in";
    }

    char user_name[20];
    char password[20];
    char telephone[20];

    std::cout << "input username:" << std::endl;
    std::cin >> user_name;
    std::cout << "input password:" << std::endl;
    std::cin >> password;
    if (strcmp(request, "sign_in") == 0)
    {
        id = CC.Sign_in(user_name, password);
    }
    else if (strcmp(request, "sign_up") == 0)
    {
        std::cout << "input telephone:" << std::endl;
        std::cin >> telephone;
        id = CC.Sign_up(user_name, password, telephone);
    }
    cout << id;
    if (id == NULL)
    {
        cout << "login fail" << endl;
    }
    else
    {
        cout << "scd operate" << endl;
        //发送邮件成功
        // CC.Send_Mail(id, "1589", "send", "DEBUG Hai mei nong", "tai keng die le CPP");
        // CC.Send_Mail(id, "188", "send", "FR beautiful", "yeah yeah yeah");

        // 添加联系人成功
        // CC.Send_Contact(id,"STR","1589");
        // CC.Send_Contact(id,"FR","188");
        //获取邮件详情成功
        DataBag::EMAIL_CONTENT *EC =
            CC.Get_Mail_Detail(id, "1");
        cout << EC->emailContent << EC->emailTime << EC->emailTitle << EC->emailType << EC->fileName << EC->targetUsername << endl;

        //获取联系人成功
        // int size;
        // DataBag::CONTATCT_INFO *CI = CC.Get_Contact(id, &size);
        // for (int i = 0; i < size; i++)
        // {
        //     cout << CI[i].telephone <<"id:"<< CI[i].userId <<"name:"<< CI[i].userName << endl;
        // }

        //

        // 获取邮件列表成功
        // int size = 0;
        // DataBag::EMAIL_INFO *EI = CC.Get_Mail_List(id, "send", &size);
        // cout << "size:" << size << endl;
        // if (EI == NULL)
        // {
        //     cout << "fuck" << endl;
        // }

        // for (int i = 0; i < size; i++)
        // {
        //     if ((EI + i) != NULL)
        //     {
        //         cout << EI[i].emailTime << "id:" << EI[i].emailId << "title:" << EI[i].emailTitle << "target:" << EI[i].targetUsername << endl;
        //     }
        // }

        //获取联系人成功
        // int size;
        // DataBag::CONTATCT_INFO *CI = CC.Get_Contact(id, &size);
        // for (int i = 0; i < size; i++)
        // {
        //     cout << CI[i].telephone << CI[i].userId << CI[i].userName << endl;
        // }

        // CC.
    }

    CC.Send_Exit();
    return 0;
}