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

#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/reader.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include "SQL/SqlCon.h"
#include "Communi_Core.hpp"

#include "My_Json.hpp"
using namespace Data_Bag;
using namespace My_Json;
using namespace rapidjson;

namespace COMMUNI
{
    Communi_Core::Communi_Core(const char *server_ip)
    {
        this->clnt_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        struct sockaddr_in clnt_addr;
        clnt_addr.sin_family = AF_INET;
        clnt_addr.sin_addr.s_addr = inet_addr(server_ip);
        clnt_addr.sin_port = htons(CONFIG::server_port);
        if (connect(this->clnt_socket, (sockaddr *)&clnt_addr, sizeof(clnt_addr)) == 0)
        {
            std::cout << "Connect success" << std::endl;
        }
        else
        {
            //是否需要放一个信号？
            perror("connect");
            exit(-1);
        }
    }

    Communi_Core::Communi_Core(int client_socket_number)
    {
        this->clnt_socket = client_socket_number;
    }

    Communi_Core::~Communi_Core()
    {
        // close(this->clnt_socket);
    }

    //为了保证字符串一直向后读取，传入的data指针会移动
    int Communi_Core::ChRead(char *&cursor, char *buffer, int buffer_size)
    {
        int Bytes = 0;
        for (int i = 0; i < buffer_size; i++)
        {
            if (*cursor == 0)
            {
                buffer[i] = 0;
                break;
            }
            buffer[i] = *cursor;
            cursor++;
            Bytes++;
        }
        return Bytes;
    }
    char *Communi_Core::Get_File_Name(const char *file_path)
    {
        int len = strlen(file_path);
        char *file_name = new char[len];
        char file_name_rev[len];
        int name_size = 0;
        int i = len;
        while (1)
        {
            if (file_path[i] == '/' || i <= 0)
            {
                file_name_rev[name_size] = 0;
                break;
            }
            file_name_rev[name_size] = file_path[i];
            name_size++;
            i--;
        }
        for (int i = 0; i < name_size; i++)
        {
            file_name[i] = file_name_rev[name_size - 1 - i];
        }
        file_name[name_size] = 0;
        return file_name;
    }

    //file得单方面接收
    int Communi_Core::Send_File(const char *file_path)
    {

        //写一个发送文件名的？
        FILE *fp;
        fp = fopen((char *)file_path, "rb");
        if (fp == NULL)
        {
            std::cout << "ERROR" << std::endl;
            return -1;
        }
        else
        {
            char buffer[CONFIG::buffer_size];
            int read_len;
            while ((read_len = fread(buffer, sizeof(char), CONFIG::buffer_size, fp)) != 0)
            {
                write(this->clnt_socket, buffer, read_len);
                if (read_len < CONFIG::buffer_size)
                {
                    break;
                }
            }
            fclose(fp);
            return 0;
        }
    }

    char *Communi_Core::Recive_Data()
    {
        int read_len;
        char buffer[CONFIG::buffer_size];
        char *s = new char[2 * CONFIG::buffer_size]; //动态内存分配的算法可以秀一下
        char *cursor = s;
        while ((read_len = read(this->clnt_socket, buffer, CONFIG::buffer_size)) > 0)
        {
            strcpy(cursor, buffer);
            cursor += read_len; //这样写是对的吗
            memset(buffer, 0, CONFIG::buffer_size);
            if (read_len < CONFIG::buffer_size)
            {
                break;
            }
        }
        return s;
    }

    int Communi_Core::Send_Data(const char *data)
    {
        int read_len = 0;
        char buffer[CONFIG::buffer_size];
        char *t_d = (char *)data;
        while ((read_len = this->ChRead(t_d, buffer, CONFIG::buffer_size)) > 0)
        {
            write(this->clnt_socket, buffer, read_len);
            memset(buffer, 0, CONFIG::buffer_size);
            if (read_len < CONFIG::buffer_size)
            {
                break;
            }
        }
        return 0;
    }

    int Communi_Core::Write_File(char *save_path)
    {
        //debug path
        std::cout << save_path << std::endl;

        int read_len = 0;
        FILE *out_file = NULL;
        out_file = fopen(save_path, "wb+");
        char buffer[CONFIG::buffer_size];
        if (out_file == NULL)
        {
            std::cout << "File Save ERROR" << std::endl;
            return -1;
        }
        else
        {
            while ((read_len = recv(this->clnt_socket, buffer, CONFIG::buffer_size, 0)) > 0)
            {
                fwrite(buffer, sizeof(char), read_len, out_file);
                memset(buffer, 0, sizeof(buffer));
            }
        }
        fclose(out_file);
        return 0;
    }

    int Communi_Core::Recive_File()
    {
        char request_buffer[CONFIG::buffer_size];
        memset(request_buffer, 0, CONFIG::buffer_size);
        recv(this->clnt_socket, request_buffer, CONFIG::buffer_size, 0);
        rapidjson::Document d;
        d.Parse(request_buffer);

        char file_path[30] = "./recived/";
        strcat(file_path, d["file_name"].GetString());
        return this->Write_File(file_path);
    }

    int Communi_Core::Recive_File(char *save_path)
    {
        char request_buffer[CONFIG::buffer_size];
        memset(request_buffer, 0, CONFIG::buffer_size);
        recv(this->clnt_socket, request_buffer, CONFIG::buffer_size, 0);
        return this->Write_File(save_path);
    }

}; // namespace COMMUNI

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
        char *DB = Data_Bag::Data_Bag_Success();
        cout << "success data:" << DB << endl;
        this->Send_Data(DB);
        delete DB;
    }
    void Server_Core::Send_Error(const char *error_info)
    {
        char *DB = Data_Bag::Data_Bag_Error(error_info);
        this->Send_Data(DB);
        delete DB;
    }

    bool Server_Core::Sign(Document &d, bool is_sign_in)
    {

        bool is_passed = false;
        if (is_sign_in)
        {
            is_passed = SQL.sign_in(d[Key_Type::sql_username].GetString(), d[Key_Type::sql_password].GetString());
            cout << d[Key_Type::sql_username].GetString() << d[Key_Type::sql_password].GetString() << endl; //debug
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

    int Server_Core::Request_Analysis()
    {
        int wrong_num = 0;
        while (1)
        {
            //接收请求包
            char *data_bag = this->Recive_Data();
            rapidjson::Document d;
            ParseResult ok = d.Parse(data_bag); //解析的错误处理
            if (!ok)
            {
                //解析失败，这玩意不是JSON
                wrong_num++;
                sleep(1);
                if (wrong_num > 3)
                {
                    close(this->clnt_socket);
                    break;
                }
                cout << "This is not a Json-data bag!" << endl;
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
                        close(this->clnt_socket);
                        break;
                    }
                }
                else if (strcmp(rq_type, "insert_email") == 0)
                {
                    // Insert_Email(d);
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
            delete data_bag;
        }
        return 0;
    }
    int Server_Core::Exe()
    {

        this->Request_Analysis();
    }

}; // namespace SERVER

namespace CLIENT
{
    Client_Core::Client_Core() : COMMUNI::Communi_Core(CLIENT::CONFIG::server_ip)
    {
    }
    Client_Core::Client_Core(const char *target_ip) : COMMUNI::Communi_Core(target_ip)
    {
    }

    Client_Core::~Client_Core()
    {
    }

    //这个只相当于中间件
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
    void Client_Core::Send_Exit()
    {
        char *data_bag = Data_Bag::DataBag_Exit();
        this->Send_Data(data_bag);
        delete data_bag;
        close(this->clnt_socket);
    }
    //接收成功消息
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
            delete data_bag;
        }

        return rt_val;
    }

    int Client_Core::Sign_in(char *username, char *password)
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

    int Client_Core::Sign_up(char *username, char *password, char *phoneum)
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

} // namespace CLIENT