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

#define SERVER_PORT 8887
#define BUFFER_SIZE 4095
int ChRead(char *&cursor, char *buffer, int buffer_size)
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

int Connect(const char *server_ip)
{

    ///定义客户端sock
    int sock_cli = socket(AF_INET, SOCK_STREAM, 0);

    ///定义sockaddr_in
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERVER_PORT);          ///服务器端口
    servaddr.sin_addr.s_addr = inet_addr(server_ip); ///服务器ip,链接服务器
    ///连接服务器，成功返回0，错误返回-1
    if (connect(sock_cli, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("connect");
        exit(1);
    }
    return sock_cli;
}

int Send_Data(char *data, int sock_cli)
{
    int read_len = 0;
    char sendbuf[BUFFER_SIZE]; //buffer不能超过200
    while ((read_len = ChRead(data, sendbuf, BUFFER_SIZE)))
    {
        send(sock_cli, sendbuf, read_len, 0); ///发送
    }
    // close(sock_cli);
    return sock_cli;
}
int main()
{

    //输入服务器ip
    char *server_ip = new char(12);
    std::cout << "input server ip:" << std::endl;
    std::cin >> server_ip;
    getchar();
    int c = Connect(server_ip);
    char *fuck = new char[20000];
    while (1)
    {
        std::cin >> fuck;
        int t = Send_Data(fuck, c);
    }
    close(c);
    return 0;
}