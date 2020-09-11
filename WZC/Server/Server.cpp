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

Server_Core::User_Space::User_Space(int client_sock)
{
    this->client_sock = client_sock;
}

int Server_Core::User_Space::Get_Content()
{
    char buffer[Server_Core::CONFIG::buffer_size];
    int data_len = 0;
}

//把这个当main写
int Server_Core::User_Space::Exe()
{
    int data_len = 0;
    char buffer[Server_Core::CONFIG::buffer_size];

    //接收请求
    data_len = read(this->client_sock, buffer, Server_Core::CONFIG::buffer_size);
    int judge = this->Request_Judge(buffer);

    switch (judge)
    {
    case Server_Core::CONFIG::file:
        //文件处理
        break;
    case Server_Core::CONFIG::mail_to_DB:

        //客户端发来的信件
        while ((data_len = read(this->client_sock, buffer, Server_Core::CONFIG::buffer_size)) > 0)
        {
            //数据都存在buffer中
            std::cout << buffer << std::endl;

            //DB操作

            //返回数据
            char *datas;
            this->Send_To_Client(datas);

            memset(buffer, 0, sizeof(buffer));
        }

        break;

    default:
        break;
    }

    //接收内容
}