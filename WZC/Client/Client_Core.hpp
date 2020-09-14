#include <iostream>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h> //socket函数
#include <sys/types.h>
#include <fcntl.h> //oepn函数
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h> //read,write
#include <signal.h>

#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/reader.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include "My_Json.hpp"
#include "Communi_Core.hpp"

using namespace My_Json;
using namespace Data_Bag;
using namespace rapidjson;

namespace CLIENT
{
    namespace CONFIG
    {
        const char server_ip[] = "123.57.176.139";
        const int server_port = APP_PORT;
        const int buffer_size = BUFFER_SIZE;

    } // namespace CONFIG
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
                delete data_bag;
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
                cout << "解析：" << data_bag << endl;
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

        //向服务器发送结束线程的信息
        void Send_Exit()
        {
            char *data_bag = Data_Bag::DataBag_Exit();
            this->Send_Data(data_bag);
            delete data_bag;
            close(this->clnt_socket);
        }

        ~Client_Core(){}

        int Sign_in(char *username, char *password)
        {
            //发送请求包
            char *JSON = DataBag_Sign_in(username, password);
            this->Send_Data(JSON);
            delete JSON;
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
                    delete error_info;
                }

                return -1;
            }
        }
        int Sign_up(char *username, char *password, char *phoneum)
        {
            //发送请求包
            char *JSON = DataBag_Sign_up(username, password, phoneum);
            this->Send_Data(JSON);
            delete JSON;
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
                    delete error_info;
                }
                // delete error_info;
                return -1;
            }
        }

    }; // namespace CLIENT
} // namespace CLIENT