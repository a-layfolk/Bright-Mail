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
#include "Server_Core.h"

using namespace SERVER;
void *User_Thread(void *args)
{
    cout << "Thread create" << endl;
    //创建了用户操作
    // Server_Core Usr(*(int *)args);
    int socket = *(int *)args;
    Server_Core *Usr = new Server_Core(socket);
    Usr->Exe();
    delete Usr;
    close(*(int *)args);
    cout << "Thread close" << endl;
    pthread_exit(0);
}

int main(int argc, char const *argv[])
{

    //服务器端socket创建
    int server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(CONFIG::server_ip);
    server_addr.sin_port = htons(CONFIG::server_port);
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
        cout << "acc" << endl;
        //连接成功提示
        if (clnt_sock >= 0)
        {
            std::cout << "successful" << std::endl;
            pthread_t tid;
            pthread_create(&tid, NULL, User_Thread, (void *)&(clnt_sock));
        }

        // struct sockaddr_in sa;
        // int len = sizeof(sa);
        // if (!getpeername(sockfd, (struct sockaddr *)&sa, &len))
        // {
        //     printf("对方IP：%s ", inet_ntoa(sa.sin_addr));
        //     printf("对方PORT：%d ", ntohs(sa.sin_port));可以写进Server_Core内
        // }

        //创建多线程
    }

    return 0;
}
