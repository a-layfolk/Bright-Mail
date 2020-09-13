#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <string>

// #define SERVER_IP "127.0.0.1"
// #define SERVER_IP "192.168.119.128"
#define SERVER_IP "0.0.0.0"
#define SERVER_PORT 8887
#define BUFFER_SIZE 4095
#define MAX_THREADS 2
using namespace std;
int num = 0;
char *Recive_Data(int clnt_sock)
{
    int read_len;
    char buffer[BUFFER_SIZE];
    char *s = new char[100000];
    char *cursor = s;
    while ((read_len = read(clnt_sock, buffer, BUFFER_SIZE))>0)
    {
        for (int i = 0; i < read_len; i++)
        {
            cursor[i] = buffer[i];
        }
        num += read_len;
        cursor += BUFFER_SIZE;
        memset(buffer, 0, BUFFER_SIZE);
        if (read_len < BUFFER_SIZE)
        {
            break;
        }
    }
    // num = strlen(s);
    return s;
}
void *User_connect(void *args)
{
    int clnt_sock = *(int *)args;
    while (1)
    {
        num = 0;
        char *JSON = Recive_Data(clnt_sock);
        cout << JSON << endl;
        cout << num << endl;
        /* code */
        delete JSON;
    }
}

int main(int argc, char const *argv[])
{
    //套接字类型、TCP还是UDP（SOCK_STREAM是TCP，表示链接的；SOCK_DGRAM是UDP，表示无连接），协议（一般设置为0，表示默认）
    int server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    server_addr.sin_port = htons(SERVER_PORT);

    //bind：把电脑真正的网络地址和套接字绑定在一起
    bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));

    //listen：bind后，queue_size（允许多少个链接请求排入队列）
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
        pthread_t tid;
        pthread_create(&tid, NULL, User_connect, (void *)&(clnt_sock));
    }

    return 0;
}
