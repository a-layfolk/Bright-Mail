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

using namespace Server_Core;

//用户所在的线程的各种操作
void *User_Thread(void *args)
{
    //创建了用户操作
    User_Space Usr_operations(*(int *)args);

    //一个大循环
    Usr_operations.Exe();
}

int main(int argc, char const *argv[])
{

    //服务器端socket创建
    int server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(Server_Core::CONFIG::server_ip);
    server_addr.sin_port = htons(Server_Core::CONFIG::server_port);
    bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_socket, 20);

    while (1)
    {
        //限制连接量,未完成

        //客户端套接字
        struct sockaddr_in clnt_addr;
        socklen_t clnt_addr_size = sizeof(clnt_addr);

        //accept接受服务器的套接字 多客户端需要多线程
        int clnt_sock = accept(server_socket, (struct sockaddr *)&clnt_addr, &clnt_addr_size);

        //连接成功提示
        if (clnt_sock >= 0)
        {
            std::cout << "successful" << std::endl;
        }

        //创建多线程
        pthread_t tid;
        pthread_create(&tid, NULL, User_Thread, (void *)&(clnt_sock));
    }

    return 0;
}
