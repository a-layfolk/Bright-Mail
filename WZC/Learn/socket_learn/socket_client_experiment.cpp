#include <iostream>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h> //socket函数
#include <sys/types.h>
#include <fcntl.h> //oepn函数
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h> //read,write
#include <signal.h>

int file;
void ouch(int sig)
{
    printf("OUCH! –I got signal %d\n", sig);
    close(file);
    signal(SIGINT, SIG_DFL);
}
int main(int argc, char const *argv[])
{
    signal(SIGINT, ouch);

    int clnt_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in clnt_addr;
    clnt_addr.sin_family = AF_INET;
    clnt_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    clnt_addr.sin_port = htons(8888);

    if (connect(clnt_socket, (sockaddr *)&clnt_addr, sizeof(clnt_addr)) == 0)
    {
        std::cout << "Connect success" << std::endl;
    }
    else
    {
        perror("connect");
        return -1;
    }
    int buffer_size = 100;
    char send_buff[buffer_size];
    char recv_buff[buffer_size];

    file = open("./client_recive.txt", O_RDWR);

    while (1)
    {

        //检测客户端是否断开链接 未完成

        memset(send_buff, 0, buffer_size);
        memset(recv_buff, 0, buffer_size);
        std::cin >> send_buff;
        // send(clnt_socket, send_buff, buffer_size, 0);
        write(clnt_socket, send_buff, buffer_size); //用write代替send

        write(file, send_buff, strlen(send_buff)); //向文件中写入数据

        // recv(clnt_socket, recv_buff, sizeof(recv_buff), 0);
        read(clnt_socket, recv_buff, buffer_size); //用read替换recv
        std::cout << recv_buff << std::endl;
    }
    // close(file);

    return 0;
}
