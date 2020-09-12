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
#include "Client.hpp"
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/reader.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace CLIENT_CORE;

Client_socket::Client_socket()
{
    clnt_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct sockaddr_in clnt_addr;
    clnt_addr.sin_family = AF_INET;
    clnt_addr.sin_addr.s_addr = inet_addr(CONFIG::server_ip);
    clnt_addr.sin_port = htons(CONFIG::server_port);
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
Client_socket::Client_socket(const char *server_ip)
{
    clnt_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct sockaddr_in clnt_addr;
    clnt_addr.sin_family = AF_INET;
    clnt_addr.sin_addr.s_addr = inet_addr(server_ip);
    clnt_addr.sin_port = htons(CONFIG::server_port);
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

Client_socket::~Client_socket()
{
    close(this->clnt_socket);
}

bool Client_socket::Server_success()
{
    char buffer[CONFIG::buffer_size];
    recv(this->clnt_socket, buffer, CONFIG::buffer_size, 0);
    if (strcmp(buffer, "success") == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int Client_socket::Send_text_file(const char *file_path)
{
    int file = open(file_path, O_RDWR);
    char buffer[CONFIG::buffer_size];
    char recv_buff[CONFIG::buffer_size];
    int read_len = 0;

    //读到多少个字节发多少个字节，否则会把文件尾部奇奇怪怪的东西发过来
    while ((read_len = read(file, buffer, 100)) > 0)
    {
        write(this->clnt_socket, buffer, read_len);
        read(clnt_socket, recv_buff, strlen(buffer));
        memset(buffer, 0, 100);
    }
    close(file);
    return 0;
}

//file得单方面接收
int Client_socket::Send_file(const char *file_path)
{
    FILE *fp;
    fp = fopen((char *)file_path, "rb");
    if (fp == NULL)
    {
        std::cout << "ERROR" << std::endl;
        return -1;
    }
    else
    {
        char buffer[CONFIG::buffer_size];
        int read_len;
        while ((read_len = fread(buffer, sizeof(char), CONFIG::buffer_size, fp)) != 0)
        {
            write(this->clnt_socket, buffer, read_len);
        }
        fclose(fp);
        return 0;
    }
}

int Client_socket::ChRead(char *content, char *buffer, int buffer_size)
{
    int Bytes = 0;
    for (int i = 0; i < buffer_size; i++)
    {
        if (*content == 0)
        {
            buffer[i] = 0;
            break;
        }

        buffer[i] = *content;
        content++;
        Bytes++;
    }
    return Bytes;
}

int Client_socket::Send_data_bag(char *data_bag)
{
    if (strlen(data_bag) < CONFIG::data_bag_size)
    {
        char data_bag_expand[CONFIG::data_bag_size];
        memset(data_bag_expand, 0, CONFIG::data_bag_size);
        strcpy(data_bag_expand, data_bag);
        write(this->clnt_socket, data_bag_expand, CONFIG::data_bag_size);
    }
    else
    {
        write(this->clnt_socket, data_bag, CONFIG::data_bag_size);
    }

    return 0;
}

int Client_socket::Send_to_server(char *request_type, char *content)
{
    if (strcmp(request_type, "file") == 0)
    {
        //获取文件名
        int len = strlen(content);
        char file_name[20];
        char file_name_rev[20];
        int name_size = 0;
        int i = len;
        while (1)
        {
            if (content[i] == '/' || i <= 0)
            {
                file_name_rev[name_size] = 0;
                break;
            }
            file_name_rev[name_size] = content[i];
            name_size++;
            i--;
        }
        for (int i = 0; i < name_size; i++)
        {
            file_name[i] = file_name_rev[name_size - 1 - i];
        }
        file_name[name_size] = 0;
        char data_bag[CONFIG::data_bag_size];
        memset(data_bag, 0, CONFIG::data_bag_size);
        snprintf(data_bag, CONFIG::data_bag_size, "{\"request_type\": \"file\",\"file_name\":\"%s\"}", file_name);
        this->Send_data_bag(data_bag);

        //收到服务器返回的确认信息

        // if (true)
        if (this->Server_success())
        {
            //给服务器发送内容包
            this->Send_file(content);
        }
        else
        {
            std::cout << "Server didn't accept transfer request for file" << std::endl;
        }
    }
    else
    {
        char *t = request_type;
        int read_len;
        char buffer[CONFIG::buffer_size];

        //发送第一个数据包
        this->Send_data_bag(request_type);

        //收到服务器返回的确认信息
        // recv(this->clnt_socket, buffer, CONFIG::buffer_size, 0);

        // if (this->Server_success())
        if (true)
        {
            //给服务器发送内容包
            char *t = content;
            while ((read_len = this->ChRead(t, buffer, CONFIG::buffer_size)))
            {
                write(this->clnt_socket, buffer, read_len);
            }
        }
        else
        {
            std::cout << "Server didn't accept transfer request for content" << std::endl;
        }
    }
}

char *Client_socket::Recive_json()
{
    int read_len = 0;

    char buffer[CONFIG::buffer_size];
    std::string *str = new std::string;

    while ((read_len = read(this->clnt_socket, buffer, CONFIG::buffer_size)) > 0)
    {
        *str += buffer;
        memset(buffer, 0, CONFIG::buffer_size);
    }
    char *JSON = new char[(*str).size()];
    str->copy(JSON, (*str).size(), 0);
    delete str;
    return JSON;
}

int Client_socket::Write_file(char *save_path)
{
    //debug path
    std::cout << save_path << std::endl;

    int read_len = 0;
    FILE *out_file = NULL;
    out_file = fopen(save_path, "wb+");
    char buffer[CONFIG::buffer_size];
    if (out_file == NULL)
    {
        std::cout << "File Save ERROR" << std::endl;
        return -1;
    }
    else
    {
        while ((read_len = recv(this->clnt_socket, buffer, CONFIG::buffer_size, 0)) > 0)
        {
            fwrite(buffer, sizeof(char), read_len, out_file);
            memset(buffer, 0, sizeof(buffer));
        }
    }
    fclose(out_file);
    return 0;
}

int Client_socket::Recive_file()
{
    char request_buffer[CONFIG::data_bag_size];
    memset(request_buffer, 0, CONFIG::data_bag_size);
    recv(this->clnt_socket, request_buffer, CONFIG::buffer_size, 0);
    rapidjson::Document d;
    d.Parse(request_buffer);

    char file_path[30] = "./recived/";
    strcat(file_path, d["file_name"].GetString());
    return this->Write_file(file_path);
}

int Client_socket::Recive_file(char *save_path)
{
    char request_buffer[CONFIG::data_bag_size];
    memset(request_buffer, 0, CONFIG::data_bag_size);
    recv(this->clnt_socket, request_buffer, CONFIG::buffer_size, 0);
    return this->Write_file(save_path);
}