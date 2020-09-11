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
    struct CONFIG
    {
        const char *server_ip;
        const static int server_port = 8888;
        CONFIG()
        {
            this->server_ip = "127.0.0.1";
        }
    };
    class client_socket
    {
    private:
        int clnt_socket;

    public:
        //默认构造函数：直接使用CONFIG中的ip和端口
        client_socket();
        ~client_socket();

        //输入文件地址
        int transfer_content_file(const char *file_path);
    };

} // namespace CLIENT_TO_SOCKET
