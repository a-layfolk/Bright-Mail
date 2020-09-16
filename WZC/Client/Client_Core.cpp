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
#include "Client_Core.h"

using namespace My_Json;
using namespace DataBag;
using namespace rapidjson;

namespace CLIENT
{
    using namespace DataBag;

    EMAIL_INFO *Client_Core::Json_To_Email_List(const char *JSON, int *list_size)
    {
        Document d;
        ParseResult ok = d.Parse(JSON);
        cout << "1" << endl;
        EMAIL_INFO *CI = NULL;
        if (!ok)
        {
            cout << "2" << endl;
        }
        else
        {
            cout << "1" << endl;
            if (d.HasMember("info"))
            {
                cout << "1" << endl;
                if (d["info"].IsArray())
                {
                    cout << "1" << endl;
                    if (d["info"].Size() > 0 && d["info"][0].HasMember("emailTitle") && d["info"][0].HasMember("targetUsername") && d["info"][0].HasMember("emailTime") && d["info"][0].HasMember("emailId"))
                    {

                        cout << "2" << endl;
                        int size = d["info"].Size();
                        cout << "3" << endl;
                        *list_size = size;
                        cout << "size:" << size << endl;
                        cout << d["info"].Size() << endl;
                        CI = new EMAIL_INFO[size];
                        cout << "4" << endl;
                        for (int i = 0; i < d["info"].Size(); i++)
                        {
                            CI[i].emailTitle = new char[d["info"][i]["emailTitle"].GetStringLength()];
                            strcpy(CI[i].emailTitle, d["info"][i]["emailTitle"].GetString());

                            CI[i].targetUsername = new char[d["info"][i]["targetUsername"].GetStringLength()];
                            strcpy(CI[i].targetUsername, d["info"][i]["targetUsername"].GetString());

                            CI[i].emailTime = new char[d["info"][i]["emailTime"].GetStringLength()];
                            strcpy(CI[i].emailTime, d["info"][i]["emailTime"].GetString());

                            CI[i].emailId = new char[d["info"][i]["emailId"].GetStringLength()];
                            strcpy(CI[i].emailId, d["info"][i]["emailId"].GetString());
                        }
                    }
                }
            }
        }
        return CI;
    }

    CONTATCT_INFO *Client_Core::Json_To_Contact_List(const char *JSON, int *list_size)
    {
        Document d;
        ParseResult ok = d.Parse(JSON);
        CONTATCT_INFO *CI = NULL;
        bool is_ok = false;
        if (!ok)
        {
            is_ok = false;
        }
        else
        {
            if (d.HasMember("info") && d.HasMember("size"))
            {
                if (d["info"].IsArray())
                {
                    if (d["info"].Size() > 0 && d["info"][0].HasMember("telephone") && d["info"][0].HasMember("userId") && d["info"][0].HasMember("userName"))
                    {

                        int size = d["size"].GetInt();
                        *list_size = size;
                        CI = new CONTATCT_INFO[size];
                        for (int i = 0; i < d["info"].Size(); i++)
                        {
                            CI[i].telephone = new char[d["info"][i]["telephone"].GetStringLength()];
                            strcpy(CI[i].telephone, d["info"][i]["telephone"].GetString());

                            CI[i].userId = new char[d["info"][i]["userId"].GetStringLength()];
                            strcpy(CI[i].userId, d["info"][i]["userId"].GetString());

                            CI[i].userName = new char[d["info"][i]["userName"].GetStringLength()];
                            strcpy(CI[i].userName, d["info"][i]["userName"].GetString());
                        }
                        is_ok = true;
                    }
                }
            }
        }
        if (is_ok)
        {
            return CI;
        }
        else
        {
            return NULL;
        }
    }

    //服务器是否回传成功的消息.如果传回的是失败，则在error_info中填入失败信息
    bool Client_Core::Recive_Success(char *error_info)
    {
        char *data_bag = this->Recive_Data();
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

    //以后如果返回的成功信息有别的，可以在这里加
    char *Client_Core::Recive_Success_Data(char *error_info)
    {
        char *data_bag = this->Recive_Data();
        Document *d = this->Return_Analysis(data_bag);
        char *extra = NULL;
        if (d->HasMember("id"))
        {
            extra = new char[(*d)["id"].GetStringLength()];
            strcpy(extra, (*d)["id"].GetString());
        }
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
                    return extra;
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

        return extra;
    }

    //解析返回的信息，记得delete包！
    rapidjson::Document *Client_Core::Return_Analysis(char *data_bag)
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

    Client_Core::Client_Core() : COMMUNI::Communi_Core(CLIENT::CONFIG::server_ip) {}
    Client_Core::Client_Core(const char *target_ip) : COMMUNI::Communi_Core(target_ip) {}
    Client_Core::~Client_Core() {}

    //向服务器发送结束线程的信息
    void Client_Core::Send_Exit()
    {
        char *data_bag = DataBag::DataBag_Exit();
        this->Send_Data(data_bag);
        delete[] data_bag;
        close(this->clnt_socket);
    }
    char *Client_Core::Sign_in(const char *username, const char *password)
    {
        char *id = NULL;
        //发送请求包
        char *JSON = DataBag_Sign_in(username, password);
        this->Send_Data(JSON);
        delete[] JSON;
        char *error_info = new char[100];
        if ((id = this->Recive_Success_Data(error_info)) != NULL)
        {
            cout << "success log in" << endl;
            // return 0;
        }
        else
        {
            cout << "Error:";
            if (error_info != NULL)
            {
                cout << error_info << endl;
                delete[] error_info;
            }

            // return -1;
        }
        return id;
    }
    char *Client_Core::Sign_up(const char *username, const char *password, const char *phoneum)
    {
        //发送请求包
        char *id = NULL;
        char *JSON = DataBag_Sign_up(username, password, phoneum);
        this->Send_Data(JSON);
        delete[] JSON;
        char *error_info = new char[100];
        if ((id = this->Recive_Success_Data(error_info)) != NULL)
        {
            // return 0;
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
            // return -1;
        }
        return id;
    }

    //发送邮件，输入指定内容为服务器插入邮件，返回值为-1时表示注册不成功，返回0为成功
    int Client_Core::Send_Mail(const char *ownerId, const char *targetId, const char *email_type, const char *email_title, const char *email_content)
    {
        char *JSON = DataBag_Sd_Mail(ownerId, targetId, email_type, email_title, email_content);
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

            return -1;
        }
    }

    //新建联系人，返回值为-1时表示注册不成功，返回0为成功
    int Client_Core::Send_Contact(const char *userId, const char *targetName, const char *targetTelephone)
    {
        char *JSON = DataBag_Sd_Contact(userId, targetName, targetTelephone);
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

            return -1;
        }
    }

    //返回万琦玲式结构数组，详情看定义，第三个参数list_size会返回列表大小
    EMAIL_INFO *Client_Core::Get_Mail_List(const char *userId, const char *emailType, int *list_size)
    {
        char *Request = DataBag_Rq_List(userId, emailType);
        this->Send_Data(Request);
        delete[] Request;
        char *JSON = this->Recive_Data();
        cout << JSON << endl;
        EMAIL_INFO *EI = this->Json_To_Email_List(JSON, list_size);
        delete[] JSON;
        return EI;
    }

    //返回万琦玲式结构体，详情看定义
    EMAIL_CONTENT *Client_Core::Get_Mail_Detail(const char *emailId, const char *ownerId)
    {
        char *Request = DataBag_Rq_Mail(emailId, ownerId);
        this->Send_Data(Request);
        delete[] Request;
        char *JSON = this->Recive_Data();
        EMAIL_CONTENT *EC = NULL;
        Document d;
        d.Parse(JSON);
        if (d.HasParseError())
        {
        }
        else
        {
            if (d.HasMember("emailContent") && d.HasMember("emailTime") && d.HasMember("emailTitle") && d.HasMember("emailType") && d.HasMember("targetUsername"))
            {
                EC = new EMAIL_CONTENT;
                EC->emailContent = new char[d["emailContent"].GetStringLength()];
                strcpy(EC->emailContent, d["emailContent"].GetString());

                EC->emailTime = new char[d["emailTime"].GetStringLength()];
                strcpy(EC->emailTime, d["emailTime"].GetString());

                EC->emailTitle = new char[d["emailTitle"].GetStringLength()];
                strcpy(EC->emailTitle, d["emailTitle"].GetString());

                EC->emailType = new char[d["emailType"].GetStringLength()];
                strcpy(EC->emailType, d["emailType"].GetString());

                EC->targetUsername = new char[d["targetUsername"].GetStringLength()];
                strcpy(EC->targetUsername, d["targetUsername"].GetString());
            }
        }
        delete[] JSON;
        return EC;
    }

    //返回万琦玲式结构数组，详情看定义，第三个参数list_size会返回列表大小
    CONTATCT_INFO *Client_Core::Get_Contact(const char *userId, int *list_size)
    {
        char *Request = DataBag_Rq_Contact(userId);
        this->Send_Data(Request);
        // cout << Request << endl;
        delete[] Request;

        char *JSON = this->Recive_Data();
        cout << "RCV:JSON:" << JSON << endl; //debug
        CONTATCT_INFO *EI = this->Json_To_Contact_List(JSON, list_size);
        delete[] JSON;
        return EI;
    }

    //接收文件如何处理待商榷，先做不带附件的吧
    int Client_Core::Send_File(const char *file_path)
    {
        char *file_name = this->Get_File_Name(file_path);
        char *Request = DataBa_Sd_File_Simple(file_name);
        this->Send_Data(Request);
        char *error = new char[10];
        this->Recive_Success(error);
        this->Sd_File(file_path);
        this->Recive_Success(error);
        delete[] file_name;
        delete[] Request;
        return 0;
    }

    //最好添加个文件名
    int Client_Core::Get_File()
    {
        char *Request = DataBag_Rq_File_Simple();
        this->Send_Data(Request);
        this->Recive_File("MY_FILE_CLIENT");
        delete[] Request;
        return 0;
    }

} // namespace CLIENT