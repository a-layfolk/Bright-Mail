#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include "Server.hpp"
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/reader.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "SQL/SqlCon.h"

using namespace SERVER_CORE;
using namespace rapidjson;

/*服务器操作顺序：
1、客户端发送请求头
2、若成功解析请求头，服务器向客户端发送'success'
3、客户端向服务器发送内容数据
*/

User_Space::User_Space(int client_socket)
{
    this->client_socket = client_socket;
    this->SQL = new mysql(CONFIG::sql_ip, CONFIG::sql_user, CONFIG::sql_password, CONFIG::sql_db, CONFIG::server_port);
}
User_Space::~User_Space()
{
    close(this->client_socket);
}

int User_Space::ChRead(char *file_path, char *buffer, int buffer_size)
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

int User_Space::Write_File(char *save_path)
{
    char buffer[CONFIG::buffer_size];
    memset(buffer, 0, CONFIG::buffer_size);

    //debug path
    std::cout << save_path << std::endl;

    int read_len = 0;
    FILE *out_file = NULL;
    out_file = fopen(save_path, "wb+");

    if (out_file == NULL)
    {
        std::cout << "File Save ERROR" << std::endl;
    }
    else
    {

        while ((read_len = recv(this->client_socket, buffer, CONFIG::buffer_size, 0)) > 0)
        {
            fwrite(buffer, sizeof(char), read_len, out_file);
            memset(buffer, 0, sizeof(buffer));
        }
    }
    fclose(out_file);
}

int User_Space::Request_Judge(char *data_bag)
{
}

//把这个当main写
int User_Space::Exe()
{
    int data_len = 0;
    char buffer[CONFIG::data_bag_size];

    //接收请求
    data_len = read(this->client_socket, buffer, CONFIG::data_bag_size);

    int judge = this->Request_Judge(buffer);

    switch (judge)
    {
    case CONFIG::file:
        //文件处理
        std::cout << "file saved" << std::endl;
        break;
    case CONFIG::mail_to_DB:

        break;

    default:
        break;
    }

    //接收内容
}

char *User_Space::Recive_Data()
{
    int read_len = 0;

    char buffer[CONFIG::buffer_size];
    std::string *str = new std::string;

    while ((read_len = read(this->client_socket, buffer, CONFIG::buffer_size)) > 0)
    {
        *str += buffer;
        memset(buffer, 0, CONFIG::buffer_size);
    }
    char *JSON = new char[(*str).size()];
    str->copy(JSON, (*str).size(), 0);
    delete str;
    return JSON;
}

bool User_Space::Sign()
{
    
}