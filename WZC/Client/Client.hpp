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
namespace CLIENT_TO_SOCKET
{
    //存放各种配置常量
    namespace CONFIG
    {
        const char server_ip[] = "127.0.0.1";
        const int server_port = 8888;
        const int buffer_size = 100;

    } // namespace CONFIG

    // client的socket类
    class client_socket
    {
    private:
        int clnt_socket;

    public:
        //默认构造函数：直接使用CONFIG中的ip和端口
        client_socket();
        ~client_socket();

        //输入文件地址（文本文件），类读取文件中内容并发送给服务器
        int text_file_transfer(const char *file_path);
        int file_transfer(const char *file_path);
    };

} // namespace CLIENT_TO_SOCKET
