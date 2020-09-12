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

using namespace Server_Core;
using namespace rapidjson;

User_Space::User_Space(int client_sock)
{
    this->client_sock = client_sock;
}
User_Space::~User_Space()
{
}

int User_Space::Send_To_Client(char *data)
{
    return 0;
}

int User_Space::Request_Judge(char *data_bag)
{
    Document d;
    d.Parse(data_bag);
    if (strcmp(d["request_type"].GetString(), "file"))
    {
        return CONFIG::file;
    }
}

//把这个当main写
int User_Space::Exe()
{
    int data_len = 0;
    char buffer[CONFIG::buffer_size];

    //接收请求
    data_len = read(this->client_sock, buffer, CONFIG::buffer_size);
    int judge = this->Request_Judge(buffer);

    
    switch (judge)
    {
    case CONFIG::file:
        //文件处理
        break;
    case CONFIG::mail_to_DB:
        //客户端发来要传输到数据库的信件

        while ((data_len = read(this->client_sock, buffer, CONFIG::buffer_size)) > 0)
        {
            //数据都存在buffer中
            std::cout << buffer << std::endl;

            //DB操作

            //返回数据
            char *datas;
            // this->Send_To_Client(datas);

            memset(buffer, 0, sizeof(buffer));
        }

        break;

    default:
        break;
    }

    //接收内容
}