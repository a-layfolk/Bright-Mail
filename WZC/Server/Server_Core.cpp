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

#include "../Dependencies/rapidjson/rapidjson.h"
#include "../Dependencies/rapidjson/document.h"
#include "../Dependencies/rapidjson/reader.h"
#include "../Dependencies/rapidjson/writer.h"
#include "../Dependencies/rapidjson/stringbuffer.h"
#include "../Dependencies/Communi_Core.h"
#include "../Dependencies/My_Json.h"
#include "../Dependencies/Sql_Core.h"

#include "Server_Core.h"

using namespace DataBag;
using namespace My_Json;
using namespace rapidjson;

namespace SERVER
{
    Server_Core::Server_Core(int client_socket) : COMMUNI::Communi_Core(client_socket)
    {
        SQL = new Sql_Core(CONFIG::sql_ip, CONFIG::sql_user, CONFIG::sql_password, CONFIG::sql_db, CONFIG::sql_port);
        this->SQL->Connect();
    }

    Server_Core::~Server_Core()
    {
        SQL->Close();
        cout << "SQL end" << endl;
        delete SQL;
    }

    void Server_Core::Send_Success()
    {
        char *DB = DataBag::DataBag_Success();
        cout << "success data:" << DB << endl;
        this->Send_Data(DB);
        delete DB;
    }
    void Server_Core::Send_Success_sign(const char *id)
    {
        char *DB = DataBag::DataBag_Success_sign(id);
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

        char *user_id;
        if (is_sign_in)
        {
            user_id = SQL->Sign_In(d[Key_Type::sql_username].GetString(), d[Key_Type::sql_password].GetString());

            // SQL.sign_in(d[Key_Type::sql_username].GetString(), d[Key_Type::sql_password].GetString()); //错误处理？
        }
        else
        {
            user_id = SQL->Sign_Up(d[Key_Type::sql_username].GetString(), d[Key_Type::sql_password].GetString(), d[Key_Type::sql_phoneum].GetString());
            // is_passed = SQL.sign_up(d[Key_Type::sql_username].GetString(), d[Key_Type::sql_password].GetString(), d[Key_Type::sql_phoneum].GetString());
        }

        if (user_id != NULL)
        {
            cout << "pass!" << endl; //debug
            this->Send_Success_sign(user_id);
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
        if (d.HasMember("ownerId") && d.HasMember("targetTelephone") && d.HasMember("emailType") && d.HasMember("emailTitle") && d.HasMember("emailContent"))
        {
            if (d.HasMember("attachedFile"))
            {
                SQL->Add_Email(d["ownerId"].GetString(), d["targetTelephone"].GetString(), d["emailType"].GetString(), d["emailTitle"].GetString(), d["emailContent"].GetString(), d["attachedFile"].GetString());
                SQL->Add_Recived_Email(d["targetTelephone"].GetString(), d["emailTitle"].GetString(), d["emailContent"].GetString(), d["attachedFile"].GetString());
            }
            else
            {
                SQL->Add_Recived_Email(d["targetTelephone"].GetString(), d["emailTitle"].GetString(), d["emailContent"].GetString(), NULL);

                SQL->Add_Email(d["ownerId"].GetString(), d["targetTelephone"].GetString(), d["emailType"].GetString(), d["emailTitle"].GetString(), d["emailContent"].GetString(), NULL);
            }
            cout << "sending" << endl;
            this->Send_Success();
            cout << "sended" << endl;
            return 0;
        }
        else
        {
            cout << "JSON ERROR" << endl; //debug
            this->Send_Error("JSON ERROR");
            return -1;
        }
    }
    int Server_Core::Add_Contact(rapidjson::Document &d)
    {
        if (d.HasMember("userId") && d.HasMember("targetName") && d.HasMember("targetTelephone"))
        {
            SQL->Add_Contact(d["userId"].GetString(), d["targetName"].GetString(), d["targetTelephone"].GetString());
            this->Send_Success();
            return 0;
        }
        else
        {
            cout << "JSON ERROR" << endl; //debug
            this->Send_Error("JSON ERROR");
            return -1;
        }
    }

    int Server_Core::Return_Email_Detail(rapidjson::Document &d)
    {
        if (d.HasMember("emailId")) //这里数据库还没写
        {
            cout << "in here" << endl;
            char *JSON = SQL->Get_Email_Detail_JSON(d["emailId"].GetString());
            if (JSON == NULL)
            {
                return -1;
            }

            this->Send_Data(JSON);
            delete[] JSON;
            return 0;
        }
        else
        {
            cout << "JSON ERROR" << endl; //debug
            this->Send_Error("JSON ERROR");
            return -1;
        }
    }
    int Server_Core::Return_Email_List(rapidjson::Document &d)
    {
        int size = 0; //debug size需要可变
        if (d.HasMember("userId") && d.HasMember("emailType"))
        {
            char *JSON = SQL->Get_Email_List_JSON(d["userId"].GetString(), d["emailType"].GetString());
            this->Send_Data(JSON);
            delete[] JSON;
            return 0;
        }
        else
        {
            cout << "JSON ERROR" << endl; //debug
            this->Send_Error("JSON ERROR");
            return -1;
        }
    }

    int Server_Core::Return_Contact_List(rapidjson::Document &d)
    {
        if (d.HasMember("userId"))
        {
            char *JSON = SQL->Get_Contact_List_JSON(d["userId"].GetString());
            this->Send_Data(JSON);
            delete[] JSON;
            return 0;
        }
        else
        {
            cout << "JSON ERROR" << endl; //debug
            this->Send_Error("JSON ERROR");
            return -1;
        }
    }

    int Server_Core::Add_File(rapidjson::Document &d)
    {
        this->Send_Success();
        this->Recive_File("MY_FILE");
        this->Send_Success();
    }
    int Server_Core::Return_File(rapidjson::Document &d)
    {
        this->Sd_File("./MY_FILE");
        this->Recive_Data();
    }
    int Server_Core::Request_Analysis()
    {
        int wrong_num = 0;
        while (1)
        {
            //接收请求包
            char *databag = this->Recive_Data();
            cout << "databag" << databag << endl;
            rapidjson::Document d;
            ParseResult ok = d.Parse(databag); //解析的错误处理
            if (!ok)
            {
                //解析失败，这玩意不是JSON
                // close(this->clnt_socket);
                if (databag != NULL)
                {
                    delete[] databag;
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
                        delete[] databag;
                        break;
                    }
                    else
                    {
                        delete[] databag;
                        break;
                    }
                }
                //请求邮件列表
                else if (strcmp(rq_type, Rq_Type::rq_list) == 0)
                {
                    this->Return_Email_List(d);
                }
                //请求联系人列表
                else if (strcmp(rq_type, Rq_Type::rq_contact) == 0)
                {
                    this->Return_Contact_List(d);
                }
                //请求单个邮件
                else if (strcmp(rq_type, Rq_Type::rq_mail) == 0)
                {
                    this->Return_Email_Detail(d);
                }
                //请求添加邮件
                else if (strcmp(rq_type, Rq_Type::sd_mail) == 0)
                {
                    this->Add_Email(d);
                }
                //请求添加联系人
                else if (strcmp(rq_type, Rq_Type::sd_contact) == 0)
                {
                    this->Add_Contact(d);
                }
                //请求登陆
                else if (strcmp(rq_type, Rq_Type::sign_in) == 0)
                {
                    Sign(d, true);
                }
                //请求注册
                else if (strcmp(rq_type, Rq_Type::sign_up) == 0)
                {
                    Sign(d, false);
                }
                else if (strcmp(rq_type, Rq_Type::sd_file) == 0)
                {
                    this->Add_File(d);
                }
                else if (strcmp(rq_type, Rq_Type::sd_file))
                {
                    this->Return_File(d);
                }

                /* data */

                //拆包
                //判断request_type
            }
            delete[] databag;
        }
        return 0;
    }
    int Server_Core::Exe()
    {

        this->Request_Analysis();
    }
}; // namespace SERVER
