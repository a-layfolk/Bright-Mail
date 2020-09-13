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

    class User_Space
    {
    private:
        int client_socket;
        mysql *SQL;
        //判断请求类型，处理对应数据包头后返回请求类型
        int Request_Judge(char *data_bag);

        //模仿read，content输入需要读取的字符串，并将读取的内容转移至较小的buffer中，方便数据包的分批发送。函数返回读取的字节数。注意，content在传入函数后会发生改变
        int ChRead(char *content, char *buffer, int buffer_size);

        //接收文件并存储到指定位置
        int Write_File(char *save_path);

    public:
        User_Space(int client_sock);
        ~User_Space();

        //登陆函数
        bool Sign();
        
        //给客户端发送数据
        int Send_Data(const char *data);

        //取得客户端数据，数据格式为JSON的字符串
        char *Recive_Data();

        //给客户端发送文件
        int Send_File(const char *file_path);

        //接收客户端端发送的文件
        int Recive_File();

        //重载，save_path是文件保存的地址
        int Recive_File(char *save_path);

        //把用户线程交给此函数
        int Exe();
    };

} // namespace SERVER_CORE
