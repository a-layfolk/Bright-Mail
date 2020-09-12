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

User_Space::User_Space(int client_sock)
{
    this->client_sock = client_sock;
    this->SQL = new mysql(CONFIG::sql_ip, CONFIG::sql_user, CONFIG::sql_password, CONFIG::sql_db, CONFIG::server_port);
}
User_Space::~User_Space()
{
    close(this->client_sock);
}

int User_Space::Send_Success()
{

    write(this->client_sock, "success", CONFIG::buffer_size);
    return 0;
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

        while ((read_len = recv(this->client_sock, buffer, CONFIG::buffer_size, 0)) > 0)
        {
            fwrite(buffer, sizeof(char), read_len, out_file);
            memset(buffer, 0, sizeof(buffer));
        }
    }
    fclose(out_file);
}

int User_Space::Send_To_Client(char *data)
{
    return 0;
}

int User_Space::Request_Judge(char *data_bag)
{
    Document d;
    d.Parse(data_bag);
    char *request_type = new char((const char)d["request_type"].GetString());
    if (strcmp(request_type, "file") == 0)
    {
        char file_path[30] = "./recived/";
        strcat(file_path, d["file_name"].GetString());
        this->Write_File(file_path);
        this->Send_Success();

        return CONFIG::file;
    }
    else if (strcmp(request_type, "mail") == 0)
    {

        this->Send_Success();
        char *content = this->Get_Content();
        Document *JSON = new Document();
        JSON->Parse(content);
        //数据库操作，存入邮件,ID居然是整形？
        this->SQL->add_email_to_db((*JSON)["ownerId"].GetInt(), (*JSON)["targetId"].GetInt(), (*JSON)["email_type"].GetString(), (*JSON)["email_title"].GetString(), (*JSON)["email_content"].GetString());
        delete JSON;
        return CONFIG::mail_to_DB;
    }
    else if (strcmp(request_type, "sign") == 0)
    {
        this->Send_Success();
        char *content = this->Get_Content();
        Document *JSON = new Document();
        JSON->Parse(content);
        //数据库操作，用户登陆//这里还需要返回客户端信息

        //还需要再解析一下包,判断是登陆还是注册
        this->SQL->sign_in((*JSON)["username"].GetString(), (*JSON)["password"].GetString());


        this->SQL->sign_up((*JSON)["username"].GetString(), (*JSON)["password"].GetString(), (*JSON)["phoneum"].GetString());

        delete JSON;
    }
    else
    {
        std::cout << "Request Judge Failed" << std::endl;
        this->Send_Success(); //send一个faild没完成
        return -1;
    }
}

//把这个当main写
int User_Space::Exe()
{
    int data_len = 0;
    char buffer[CONFIG::data_bag_size];

    //接收请求
    data_len = read(this->client_sock, buffer, CONFIG::data_bag_size);

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

char *User_Space::Get_Content()
{
    int read_len = 0;

    char buffer[CONFIG::buffer_size];
    std::string *str = new std::string;

    while ((read_len = read(this->client_sock, buffer, CONFIG::buffer_size)) > 0)
    {
        *str += buffer;
        memset(buffer, 0, CONFIG::buffer_size);
    }
    char *JSON = new char[(*str).size()];
    str->copy(JSON, (*str).size(), 0);
    delete str;
    return JSON;
}