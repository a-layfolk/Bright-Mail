#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include "Server.hpp"
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/reader.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace SERVER_CORE;
using namespace rapidjson;

/*服务器操作顺序：
1、客户端发送请求头
2、若成功解析请求头，服务器向客户端发送'success'
3、客户端向服务器发送内容数据
*/

User_Space::User_Space(int client_sock)
{
    this->client_sock = client_sock;
}
User_Space::~User_Space()
{
    close(this->client_sock);
}

int User_Space::Send_Success()
{

    write(this->client_sock, "success", CONFIG::buffer_size);
    return 0;
}

int User_Space::Write_File(char *save_path)
{
    char buffer[CONFIG::buffer_size];
    memset(buffer, 0, CONFIG::buffer_size);

    //debug path
    std::cout << save_path << std::endl;

    int read_len = 0;
    FILE *out_file = NULL;
    out_file = fopen(save_path, "wb+");

    if (out_file == NULL)
    {
        std::cout << "File Save ERROR" << std::endl;
    }
    else
    {

        while ((read_len = recv(this->client_sock, buffer, CONFIG::buffer_size, 0)) > 0)
        {
            fwrite(buffer, sizeof(char), read_len, out_file);
            memset(buffer, 0, sizeof(buffer));
        }
    }
    fclose(out_file);
}

int User_Space::Send_To_Client(char *data)
{
    return 0;
}

int User_Space::Request_Judge(char *data_bag)
{
    Document d;
    d.Parse(data_bag);

    if (strcmp(d["request_type"].GetString(), "file") == 0)
    {
        char file_path[30] = "./recived/";
        strcat(file_path, d["file_name"].GetString());
        this->Write_File(file_path);
        this->Send_Success();

        return CONFIG::file;
    }
    else
    {
        std::cout << "Request Judge Failed" << std::endl;
        this->Send_Success(); //send一个faile过去
        return -1;
    }
}

//把这个当main写
int User_Space::Exe()
{
    int data_len = 0;
    char buffer[CONFIG::data_bag_size];

    //接收请求
    data_len = read(this->client_sock, buffer, CONFIG::data_bag_size);

    int judge = this->Request_Judge(buffer);

    switch (judge)
    {
    case CONFIG::file:
        //文件处理
        std::cout << "file saved" << std::endl;
        break;
    case CONFIG::mail_to_DB:

        break;

    default:
        break;
    }

    //接收内容
}