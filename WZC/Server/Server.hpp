#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/reader.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "SQL/SqlCon.h"

namespace SERVER_CORE
{
    namespace CONFIG
    {
        const char server_ip[] = "0.0.0.0";
        const int server_port = 8888;
        const int buffer_size = 100;
        const int data_bag_size = 1024;
        const char sql_ip[] = "123.57.176.139";
        const char sql_user[] = "root";
        const char sql_password[] = "1233";
        const char sql_db[] = "Email_schema";
        const int sql_port = 3306;

        enum request_type
        {
            sign,
            file,
            mail_to_DB,
            mail_send_to_client,
            list

        };
    } // namespace CONFIG

    //用户连接后其线程的各种操作
    // void *User_Thread(void *args);

    class User_Space
    {
    private:
        int client_sock;
        mysql *SQL;
        //判断请求类型，处理对应数据包头后返回请求类型
        int Request_Judge(char *data_bag);

        //接收文件并存储到指定位置
        int Write_File(char *save_path);

        //返回给服务器"success"的请求
        int Send_Success();

        //接收内容,返回值是字符串之类的？
        // int Get_Content();

        //一堆DB操作

        //数据传输给客户端
        int Send_To_Client(char *);

    public:
        User_Space(int client_sock);
        ~User_Space();

        //获取超长的内容数据包
        char *Get_Content();

        //程序把执行权交给用户线程
        int Exe();
    };

} // namespace SERVER_CORE
