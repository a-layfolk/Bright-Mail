#include <iostream>
#include <string>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h> //socket函数
#include <sys/types.h>
#include <fcntl.h> //oepn函数
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h> //read,write
#include <signal.h>
#include <stdlib.h>

#include "Dependencies/rapidjson/rapidjson.h"
#include "Dependencies/rapidjson/document.h"
#include "Dependencies/rapidjson/reader.h"
#include "Dependencies/rapidjson/writer.h"
#include "Dependencies/rapidjson/stringbuffer.h"

#include "Dependencies/Communi_Core.h"
#include "Dependencies/My_Json.h"
#include "Client_Core.h"

using namespace My_Json;
using namespace DataBag;
using namespace rapidjson;

namespace CLIENT
{
    using namespace DataBag;
    class Client_Core : protected COMMUNI::Communi_Core
    {
    private:
        //服务器是否回传成功的消息.如果传回的是失败，则在error_info中填入失败信息
        bool Recive_Success(char *error_info)
        {
            char *data_bag = this->Recive_Data();
            // cout << "recived bag:" << data_bag << endl;
            Document *d = this->Return_Analysis(data_bag);
            bool rt_val = false;
            if (d != NULL)
            {
                cout << (*d)[Key_Type::request_type].GetString() << endl;
                if (strcmp((*d)[Key_Type::request_type].GetString(), Rq_Type::command) == 0)
                {
                    if (strcmp((*d)[Key_Type::command_type].GetString(), "error") == 0)
                    {
                        const char *ei = (*d)["error_info"].GetString();
                        cout << ei << endl;
                        strcpy(error_info, ei);
                        cout << error_info << endl;
                    }
                    else if (strcmp((*d)[Key_Type::command_type].GetString(), "success") == 0)
                    {
                        cout << "success" << endl;
                        rt_val = true;
                    }
                }
                delete d;
            }
            else
            {
                cout << "No data bag!" << endl;
                strcpy(error_info, "No data bag!");
            }
            if (data_bag != NULL)
            {
                delete[] data_bag;
            }

            return rt_val;
        }

        //解析返回的信息，记得delete包！
        rapidjson::Document *Return_Analysis(char *data_bag)
        {
            Document *d = new Document;
            ParseResult ok = d->Parse(data_bag);
            if (!ok)
            {
                return NULL;
            }
            else
            {
                return d;
            }
        }

    public:
        Client_Core() : COMMUNI::Communi_Core(CLIENT::CONFIG::server_ip) {}
        Client_Core(const char *target_ip) : COMMUNI::Communi_Core(target_ip) {}
        ~Client_Core() {}

        //向服务器发送结束线程的信息
        void Send_Exit()
        {
            char *data_bag = DataBag::DataBag_Exit();
            this->Send_Data(data_bag);
            delete[] data_bag;
            close(this->clnt_socket);
        }
        int Sign_in(const char *username, const char *password)
        {
            //发送请求包
            char *JSON = DataBag_Sign_in(username, password);
            this->Send_Data(JSON);
            delete[] JSON;
            char *error_info = new char[100];
            if (this->Recive_Success(error_info))
            {
                cout << "success log in" << endl; //debug
                return 0;
            }
            else
            {
                cout << "Error:";
                if (error_info != NULL)
                {
                    cout << error_info << endl;
                    delete[] error_info;
                }

                return -1;
            }
        }
        int Sign_up(const char *username, const char *password, const char *phoneum)
        {
            //发送请求包
            char *JSON = DataBag_Sign_up(username, password, phoneum);
            this->Send_Data(JSON);
            delete[] JSON;
            char *error_info = new char[100];
            if (this->Recive_Success(error_info))
            {
                return 0;
            }
            else
            {
                cout << "Error:";
                if (error_info != NULL)
                {
                    cout << error_info << endl;
                    delete[] error_info;
                }
                // delete error_info;
                return -1;
            }
        }

        //发送邮件，输入指定内容为服务器插入邮件，返回值为-1时表示注册不成功，返回0为成功
        int Send_Mail(const char *ownerId, const char *targetId, const char *email_type, const char *email_title, const char *email_content)
        {
            char *JSON = DataBag_Sd_Mail(ownerId, targetId, email_type, email_title, email_content);
            this->Send_Data(JSON);
            delete[] JSON;

            char *error_info = new char[100];
            if (this->Recive_Success(error_info))
            {
                cout << "success log in" << endl; //debug
                return 0;
            }
            else
            {
                cout << "Error:";
                if (error_info != NULL)
                {
                    cout << error_info << endl;
                    delete[] error_info;
                }

                return -1;
            }
        }

        //新建联系人，返回值为-1时表示注册不成功，返回0为成功
        int Send_Contact(const char *userId, const char *contactname, const char *phonenum)
        {
            char *JSON = DataBag_Sd_Contact(userId, contactname, phonenum);
            this->Send_Data(JSON);
            delete[] JSON;

            char *error_info = new char[100];
            if (this->Recive_Success(error_info))
            {
                cout << "success log in" << endl; //debug
                return 0;
            }
            else
            {
                cout << "Error:";
                if (error_info != NULL)
                {
                    cout << error_info << endl;
                    delete[] error_info;
                }

                return -1;
            }
        }

        //返回万琦玲式结构数组，详情看定义，第三个参数list_size会返回列表大小
        EMAIL_INFO *Get_Mail_List(const char *userId, const char *emailType, int *list_size)
        {
            EMAIL_INFO *EI = new EMAIL_INFO[200];
            *list_size = 200;
            return EI;
        }

        //返回万琦玲式结构体，详情看定义
        EMAIL_CONTENT *Get_Mail_Detail(const char *emailId, const char *ownerId)
        {
            EMAIL_CONTENT *EC = new EMAIL_CONTENT;
            return EC;
        }

        //返回万琦玲式结构数组，详情看定义，第三个参数list_size会返回列表大小
        CONTATCT_INFO *Get_Contact(const char *userId, int *list_size)
        {
            CONTATCT_INFO *CI = new CONTATCT_INFO[200];
            *list_size = 200;
            return CI;
        }

        //接收文件如何处理待商榷，先做不带附件的吧
        int Send_File() {}
        char *Get_File_Info() {}
    }; // namespace CLIENT
} // namespace CLIENT