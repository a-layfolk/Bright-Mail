#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>

#define SERVER_PORT 8888
#define BUFFER_SIZE 100

int main()
{
    ///定义客户端sock
    int sock_cli = socket(AF_INET, SOCK_STREAM, 0);

    ///定义sockaddr_in
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERVER_PORT); ///服务器端口

    //输入服务器ip
    char *server_ip = new char(12);
    std::cout << "input server ip:" << std::endl;
    std::cin >> server_ip;
    getchar();

    servaddr.sin_addr.s_addr = inet_addr(server_ip); ///服务器ip,链接服务器

    ///连接服务器，成功返回0，错误返回-1
    if (connect(sock_cli, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("connect");
        exit(1);
    }

    char sendbuf[BUFFER_SIZE]; //buffer不能超过200
    char recvbuf[BUFFER_SIZE];
    while (fgets(sendbuf, sizeof(sendbuf), stdin) != NULL)
    {
        send(sock_cli, sendbuf, strlen(sendbuf), 0); ///发送
        recv(sock_cli, recvbuf, sizeof(recvbuf), 0); ///接收
        std::cout << recvbuf << std::endl;
        if (strcmp(sendbuf, "exit\n") == 0)
            break;
        memset(sendbuf, 0, sizeof(sendbuf));
        memset(recvbuf, 0, sizeof(recvbuf));
    }

    close(sock_cli);
    return 0;
}