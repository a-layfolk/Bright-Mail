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
#include <stdlib.h>
#include "Client.hpp"

CLIENT_TO_SOCKET::client_socket::client_socket()
{
    clnt_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct sockaddr_in clnt_addr;
    clnt_addr.sin_family = AF_INET;
    clnt_addr.sin_addr.s_addr = inet_addr(CLIENT_TO_SOCKET::CONFIG::server_ip);
    clnt_addr.sin_port = htons(CLIENT_TO_SOCKET::CONFIG::server_port);
    if (connect(clnt_socket, (sockaddr *)&clnt_addr, sizeof(clnt_addr)) == 0)
    {
        std::cout << "Connect success" << std::endl;
    }
    else
    {
        //是否需要放一个信号？
        perror("connect");
        exit(-1);
    }
}

CLIENT_TO_SOCKET::client_socket::~client_socket()
{
    close(this->clnt_socket);
}

int CLIENT_TO_SOCKET::client_socket::text_file_transfer(const char *file_path)
{
    int file = open(file_path, O_RDWR);
    char buffer[CLIENT_TO_SOCKET::CONFIG::buffer_size];
    char recv_buff[CLIENT_TO_SOCKET::CONFIG::buffer_size];
    int read_len = 0;

    //读到多少个字节发多少个字节，否则会把文件尾部奇奇怪怪的东西发过来
    while ((read_len = read(file, buffer, 100)) > 0)
    {
        write(this->clnt_socket, buffer, read_len);
        read(clnt_socket, recv_buff, strlen(buffer));
        memset(buffer, 0, 100);
    }
    close(file);
}