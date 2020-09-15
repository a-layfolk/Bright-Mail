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
#include "Dependencies/SqlCon.h"
#include "Server_Core.h"

using namespace DataBag;
using namespace My_Json;
using namespace rapidjson;

namespace SERVER
{
    Server_Core::Server_Core(int client_socket) : COMMUNI::Communi_Core(client_socket)
    {
        this->SQL.connect(CONFIG::sql_ip, CONFIG::sql_user, CONFIG::sql_password, CONFIG::sql_db, CONFIG::sql_port);
    }

    Server_Core::~Server_Core()
    {
        this->SQL.close();
    }

    void Server_Core::Send_Success()
    {
        char *DB = DataBag::DataBag_Success();
        cout << "success data:" << DB << endl;
        this->Send_Data(DB);
        delete DB;
    }
    void Server_Core::Send_Error(const char *error_info)
    {
        char *DB = DataBag::DataBag_Error(error_info);
        this->Send_Data(DB);
        delete DB;
    }

    bool Server_Core::Sign(Document &d, bool is_sign_in)
    {

        bool is_passed = false;
        if (is_sign_in)
        {
            is_passed = SQL.sign_in(d[Key_Type::sql_username].GetString(), d[Key_Type::sql_password].GetString()); //错误处理？
        }
        else
        {
            is_passed = SQL.sign_up(d[Key_Type::sql_username].GetString(), d[Key_Type::sql_password].GetString(), d[Key_Type::sql_phoneum].GetString());
        }

        if (is_passed)
        {
            cout << "pass!" << endl; //debug
            this->Send_Success();
            return true;
        }
        else
        {
            cout << "no pass!" << endl; //debug
            if (is_sign_in)
            {
                this->Send_Error("User not exsist!");
            }
            else
            {
                this->Send_Error("Sign up failed!");
            }
        }
        return false;
    }

    int Server_Core::Add_Email(rapidjson::Document &d)
    {
        SQL.add_email_to_db(d["ownerId"].GetString(), d["targetId"].GetString(), d["email_type"].GetString(), d["email_title"].GetString(), d["email_content"].GetString()); //错误处理？
        this->Send_Success();
    }
    int Server_Core::Add_Contact(rapidjson::Document &d)
    {
        SQL.add_contact_info(d["userId"].GetString(), d["contactname"].GetString(), d["phonenum"].GetString());
        this->Send_Success();
    }
    int Server_Core::Add_File(rapidjson::Document &d)
    {
        return 0;
    }
    int Server_Core::Return_Email_Detail(rapidjson::Document &d)
    {
    }
    int Server_Core::Return_Email_List(rapidjson::Document &d)
    {
    }
    int Server_Core::Return_Contact_List(rapidjson::Document &d)
    {
    }

    int Server_Core::Request_Analysis()
    {
        int wrong_num = 0;
        while (1)
        {
            //接收请求包
            cout << "into request" << endl;
            char *databag = this->Recive_Data();
            rapidjson::Document d;
            ParseResult ok = d.Parse(databag); //解析的错误处理
            if (!ok)
            {
                //解析失败，这玩意不是JSON
                // close(this->clnt_socket);
                if (databag != NULL)
                {
                    delete databag;
                }

                cout << "This is not a Json-data bag!" << endl;
                break;
            }
            else
            {
                //其余的返回信息都在对应功能函数内写
                //哈夫曼树1、请求列表 2、请求内容 3、请求信件 4、通讯录操作 5、发送信件 6、登陆操作
                const char *rq_type = d[Key_Type::request_type].GetString();
                if (strcmp(rq_type, Rq_Type::command) == 0)
                {
                    if (strcmp(d[Key_Type::command_type].GetString(), "exit") == 0)
                    {
                        // close(this->clnt_socket);
                        delete databag;
                        break;
                    }
                    else
                    {
                        delete databag;
                        break;
                    }
                }
                else if (strcmp(rq_type, Rq_Type::sd_mail) == 0)
                {
                    this->Add_Email(d);
                }
                else if (strcmp(rq_type, Rq_Type::sd_contact) == 0)
                {
                    this->Add_Contact(d);
                }

                else if (strcmp(rq_type, Rq_Type::sign_in) == 0)
                {
                    Sign(d, true);
                }
                else if (strcmp(rq_type, Rq_Type::sign_up) == 0)
                {
                    Sign(d, false);
                }
                /* data */

                //拆包
                //判断request_type
            }
            delete databag;
        }
        return 0;
    }
    int Server_Core::Exe()
    {

        this->Request_Analysis();
    }

}; // namespace SERVER
