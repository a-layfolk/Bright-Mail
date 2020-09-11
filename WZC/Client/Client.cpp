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
    CLIENT_TO_SOCKET::CONFIG CONF;
    clnt_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct sockaddr_in clnt_addr;
    clnt_addr.sin_family = AF_INET;
    clnt_addr.sin_addr.s_addr = inet_addr(CONF.server_ip);
    clnt_addr.sin_port = htons(CLIENT_TO_SOCKET::CONFIG::server_port);
    if (connect(clnt_socket, (sockaddr *)&clnt_addr, sizeof(clnt_addr)) == 0)
    {
        std::cout << "Connect success" << std::endl;
    }
    else
    {
        perror("connect");
        exit(-1);
    }
}

CLIENT_TO_SOCKET::client_socket::~client_socket()
{
    close(this->clnt_socket);
}

int CLIENT_TO_SOCKET::client_socket::transfer_content_file(const char *file_path)
{
    int file = open(file_path, O_RDWR);
    int buffer_size = 100;
    char buffer[100];
    char recv_buff[buffer_size];
    int len = 0;
    while ((len = read(file, buffer, 100)) > 0)
    {
        write(this->clnt_socket, buffer, len);
        read(clnt_socket, recv_buff, strlen(buffer));
        memset(buffer, 0, 100);
    }
    close(file);
}