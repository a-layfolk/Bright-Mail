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
        close(this->clnt_socket);
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
            //debug

            buffer[i] = *cursor;
            cursor++;
            Bytes++;
        }
        // std::cout << "Bytes:" << Bytes << (int)*data << endl;
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
        char *s = new char[10000]; //动态内存分配的算法可以秀一下
        char *cursor = s;
        while ((read_len = read(this->clnt_socket, buffer, CONFIG::buffer_size)) > 0)
        {
            strcpy(cursor, buffer);
            cursor += CONFIG::buffer_size;
            memset(buffer, 0, CONFIG::buffer_size);
            if (read_len < CONFIG::buffer_size)
            {
                break;
            }
        }
        cout << s << endl; //debug
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
            cout << "send buffer" << buffer << endl;
            // write(this->clnt_socket, buffer, read_len);
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
    bool Server_Core::Sign()
    {
        for (int i = 0; i < 3; i++)
        {

            //接收请求包
            cout << "start" << endl;
            char *sign = this->Recive_Data();
            std::cout << "sign end recived Data" << sign << std::endl; //debug
            bool is_passed = false;
            //解析请求包
            rapidjson::Document d;
            d.Parse(sign);
            if (strcmp(d[Key_Type::request_type].GetString(), "sign_up") == 0)
            {
                is_passed = SQL.sign_up(d[Key_Type::sql_username].GetString(), d[Key_Type::sql_password].GetString(), d[Key_Type::sql_phoneum].GetString());
            }
            else if (strcmp(d[Key_Type::request_type].GetString(), "sign_in") == 0)
            {
                is_passed = SQL.sign_in(d[Key_Type::sql_username].GetString(), d[Key_Type::sql_password].GetString());
            }
            else if (strcmp(d[Key_Type::request_type].GetString(), "operate") == 0)
            {
                std::cout << "User Sign Canceled" << std::endl;
                //用户取消操作退出线程
            }
            //释放请求包的内存
            delete sign;
            if (is_passed)
            {
                this->Send_Data("success");
                //给服务器发信息
                return true;
            }
            else
            {
            }
            //给服务器发未成功信息
        }

        return false;
    }

    int Server_Core::Exe()
    {
    }
    int Server_Core::Request_Analysis()
    {
        //接收请求包
        char *data_bag = this->Recive_Data();
        rapidjson::Document d;
        d.Parse(data_bag);
        const char *rq_type = d[Key_Type::request_type].GetString();
        if (strcmp(rq_type, "insert_email") == 0)
        {
            // Insert_Email(d);
        }
        /* data */

        //拆包
        //判断request_type

        delete data_bag;
        return 0;
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

    bool Client_Core::Server_Success()
    {
        char *data = this->Recive_Data();
        std::cout << "success" << std::endl; //debug
        if (strcmp(data, "success") == 0)
        {
            return true;
        }
        return false;
    }

    int Client_Core::Sign_in(char *username, char *password)
    {
        //发送请求包
        char *JSON = DataBag_Sign_in(username, password);

        this->Send_Data(JSON);
        delete JSON;

        //接受消息
        // if (this->Server_Success())
        // {
        //     return -1;
        // }
        // else
        // {
        //     //再接收一次消息
        //     char *str = this->Recive_Data();
        //     int remain = str[0] - '0';
        //     delete str;
        //     return remain;
        // }
    }

    //返回还剩几次登陆机会
    int Client_Core::Sign_up(char *username, char *password, char *phoneum)
    {
        //发送请求包
        char *JSON = DataBag_Sign_up(username, password, phoneum);
        // char *JSON = NULL;
        this->Send_Data(JSON);
        delete JSON;

        if (this->Server_Success())
        {
            return -1;
        }
        else
        {
            //再接收一次消息
            char *str = this->Recive_Data();
            int remain = str[0] - '0';
            delete str;
            return remain;
        }
    }
} // namespace CLIENT