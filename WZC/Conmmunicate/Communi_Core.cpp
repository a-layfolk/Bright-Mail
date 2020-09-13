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
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/reader.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "Communi_Core.hpp"

using namespace COMMUNI;

Communi_Core::Communi_Core(const char *server_ip)
{
    this->clnt_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct sockaddr_in clnt_addr;
    clnt_addr.sin_family = AF_INET;
    clnt_addr.sin_addr.s_addr = inet_addr(server_ip);
    clnt_addr.sin_port = htons(CONFIG::server_port);
    if (connect(this->clnt_socket, (sockaddr *)&clnt_addr, sizeof(clnt_addr)) == 0)
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

Communi_Core::~Communi_Core()
{
    close(this->clnt_socket);
}

char *Communi_Core::Get_File_Name(const char *file_path)
{
    int len = strlen(file_path);
    char *file_name = new char[len];
    char file_name_rev[len];
    int name_size = 0;
    int i = len;
    while (1)
    {
        if (file_path[i] == '/' || i <= 0)
        {
            file_name_rev[name_size] = 0;
            break;
        }
        file_name_rev[name_size] = file_path[i];
        name_size++;
        i--;
    }
    for (int i = 0; i < name_size; i++)
    {
        file_name[i] = file_name_rev[name_size - 1 - i];
    }
    file_name[name_size] = 0;
    return file_name;
}

//file得单方面接收
int Communi_Core::Send_File(const char *file_path)
{

    //写一个发送文件名的？
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

int Communi_Core::ChRead(char *file_path, char *buffer, int buffer_size)
{
    int Bytes = 0;
    for (int i = 0; i < buffer_size; i++)
    {
        if (*file_path == 0)
        {
            buffer[i] = 0;
            break;
        }

        buffer[i] = *file_path;
        file_path++;
        Bytes++;
    }
    return Bytes;
}

char *Communi_Core::Recive_Data()
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

int Communi_Core::Write_File(char *save_path)
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

int Communi_Core::Recive_File()
{
    char request_buffer[CONFIG::data_bag_size];
    memset(request_buffer, 0, CONFIG::data_bag_size);
    recv(this->clnt_socket, request_buffer, CONFIG::buffer_size, 0);
    rapidjson::Document d;
    d.Parse(request_buffer);

    char file_path[30] = "./recived/";
    strcat(file_path, d["file_name"].GetString());
    return this->Write_File(file_path);
}

int Communi_Core::Recive_File(char *save_path)
{
    char request_buffer[CONFIG::data_bag_size];
    memset(request_buffer, 0, CONFIG::data_bag_size);
    recv(this->clnt_socket, request_buffer, CONFIG::buffer_size, 0);
    return this->Write_File(save_path);
}