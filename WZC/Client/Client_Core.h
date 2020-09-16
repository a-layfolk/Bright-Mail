#ifndef CLC_H
#define CLC_H
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

#include "../Dependencies/rapidjson/rapidjson.h"
#include "../Dependencies/rapidjson/document.h"
#include "../Dependencies/rapidjson/reader.h"
#include "../Dependencies/rapidjson/writer.h"
#include "../Dependencies/rapidjson/stringbuffer.h"
#include "../Dependencies/My_Json.h"
#include "../Dependencies/Communi_Core.h"

namespace CLIENT
{
    using namespace DataBag;
    namespace CONFIG
    {
        const char server_ip[] = "123.57.176.139";
        const int server_port = APP_PORT;
        const int buffer_size = BUFFER_SIZE;

    } // namespace CONFIG
    class Client_Core : protected COMMUNI::Communi_Core
    {
    private:
        //客户端调用者不可见部分
        //服务器是否回传成功的消息.如果传回的是失败，则在error_info中填入失败信息
        bool Recive_Success(char *error_info);

        CONTATCT_INFO *Json_To_Contact_List(const char *JSON, int *list_size);
        EMAIL_INFO *Json_To_Email_List(const char *JSON, int *list_size);

        //解析返回的信息，记得delete包！
        rapidjson::Document *Return_Analysis(char *data_bag);

    public:
        Client_Core();
        //重载，可直接连接到指定IP中
        Client_Core(const char *target_ip);

        ~Client_Core();

        //向服务器发送结束线程的信息
        void Send_Exit();

        //登陆请求，返回值为NULL时表示登陆不成功，成功时返回用户id
        char* Sign_in(const char *username, const char *password);
        //注册请求，返回值为NULL时表示注册不成功，成功时返回用户id
        char* Sign_up(const char *username, const char *password, const char *phoneum);

        //发送邮件，输入指定内容为服务器插入邮件，返回值为-1时表示注册不成功，返回0为成功
        int Send_Mail(const char *ownerId, const char *targetId, const char *email_type, const char *email_title, const char *email_content);
        
        //发送邮件，输入指定内容为服务器插入邮件，返回值为-1时表示注册不成功，返回0为成功
        int Send_Mail_With_File(const char *ownerId, const char *targetId, const char *email_type, const char *email_title, const char *email_content,const char*file_name);

        //新建联系人，返回值为-1时表示注册不成功，返回0为成功
        int Send_Contact(const char *userId, const char *contactname, const char *phonenum);

        //返回万琦玲式结构数组，详情看定义，第三个参数list_size会返回列表大小
        EMAIL_INFO *Get_Mail_List(const char *userId, const char *emailType, int *list_size);

        //返回万琦玲式结构体，详情看定义
        EMAIL_CONTENT *Get_Mail_Detail(const char *emailId, const char *ownerId);

        //返回万琦玲式结构数组，详情看定义，第三个参数list_size会返回列表大小
        CONTATCT_INFO *Get_Contact(const char *userId, int *list_size);

        //接收文件如何处理待商榷，先做不带附件的吧


        //输入相对地址或者绝对地址//email id我自己查，SQL add todb时会返回
        int Send_File(const char *file_path);//我需要

        //在执行文件当前目录放文件
        int Get_File();

    }; // namespace CLIENT
} // namespace CLIENT
#endif