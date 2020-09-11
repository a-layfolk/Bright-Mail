#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
namespace Server_Core
{
    namespace CONFIG
    {
        const char *server_ip = "0.0.0.0";
        const int server_port = 8888;
        const int buffer_size = 100;
        const int data_bag_size = 1024;
        enum request_type
        {
            sign,
            file,
            mail_to_client,
            mail_to_DB,
            list

        };
    } // namespace CONFIG

    //用户连接后其线程的各种操作
    // void *User_Thread(void *args);

    class User_Space
    {
    private:
        int client_sock;

        //判断请求类型
        int Request_Judge(char *buffer);

        //接收内容,返回值是字符串之类的？
        int Get_Content();

        //一堆DB操作

        //数据传输给客户端
        int Send_To_Client(char *);

    public:
        User_Space(int client_sock);
        ~User_Space();

        //程序把执行权交给用户线程
        int Exe();
    };

} // namespace Server_Core
