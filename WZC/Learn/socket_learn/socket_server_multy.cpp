#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#define SKT_SERVER_IP "127.0.0.1"
#define SKT_SERVER_PORT 8888
#define BUFFER_SIZE 100
#define MAX_THREADS 20

void *User_connect(void *args)
{
    int clnt_sock = *(int *)args;
    char buffer[BUFFER_SIZE];
    while (1)
    {
        memset(buffer, 0, sizeof(buffer));
        int len = recv(clnt_sock, buffer, BUFFER_SIZE, 0);
        fputs(buffer, stdout);
        if (buffer[0] != '\n')
        {
            char ma[6];
            memset(ma, 0, 6);
            strcpy(ma, "吗?\n");
            for (int i = 0; i < 6; i++)
            {
                buffer[len + i - 1] = ma[i];
            }
        }
        send(clnt_sock, buffer, strlen(buffer), 0);
    }
}

int main(int argc, char const *argv[])
{
    //套接字类型、TCP还是UDP（SOCK_STREAM是TCP，表示链接的；SOCK_DGRAM是UDP，表示无连接），协议（一般设置为0，表示默认）
    int server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(SKT_SERVER_IP);
    server_addr.sin_port = htons(SKT_SERVER_PORT);
    bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));

    //bind：把电脑真正的网络地址和套接字绑定在一起

    //listen：bind后，queue_size（允许多少个链接请求排入队列）
    listen(server_socket, 20);

    //客户端套接字
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);

    //accept接受服务器的套接字 多客户端需要多线程？
    pthread_t tids[MAX_THREADS];
    int i = 0;
    while (1)
    {
        int clnt_sock = accept(server_socket, (struct sockaddr *)&clnt_addr, &clnt_addr_size);
        if (clnt_sock >= 0)
        {
            std::cout << "successful" << std::endl;
            pthread_create(&tids[i++], NULL, User_connect, (void *)&(clnt_sock));
        } //加个没连接成功的
    }

    return 0;
}
