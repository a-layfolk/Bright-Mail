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
namespace CLIENT_CORE
{
    //存放各种配置常量
    namespace CONFIG
    {
        const char server_ip[] = "127.0.0.1";
        const int server_port = 8888;
        const int buffer_size = 100;
        const int data_bag_size = 1024;

    } // namespace CONFIG

    // client的socket类
    class Client_socket
    {
    private:
        int clnt_socket;

        //模仿read，content输入需要读取的字符串，并将读取的内容转移至较小的buffer中，方便数据包的分批发送。函数返回读取的字节数。注意，content在传入函数后会发生改变
        int ChRead(char *content, char *buffer, int buffer_size);
        int Send_data_bag(char *data_bag);

        //确认服务器返回信息"success",正确返回值为true,错误为fals

        //输入文件地址（文本文件），类读取文件中内容并发送给服务器
        int Send_text_file(const char *file_path);

        //输入文件地址（任意文件），并发送给服务器
        int Send_file(const char *file_path);

        //接收服务器反馈请求，如果反馈成功，则为true，否则为false
        bool Server_success();
        int Write_file(char *save_path);

    public:
        //默认构造函数：直接使用CONFIG中的ip和端口
        Client_socket();
        //输入服务器地址
        Client_socket(const char *server_ip);
        ~Client_socket();

        //给服务器发送数据。request_type分为文件"file"和其他类型。如果request_type为file，则content输入文件路径;若为其他，则request_type填入头数据包,*大小为1024*，content填入发送的内容
        int Send_to_server(char *request_type, char *content);

        //返回JSON格式的字符串内容，记得delete！
        char *Recive_json();
        //重载，return_val为返回数据包的类型
        // char *Recive_json(int *return_val);

        //接收服务器端发送的文件
        int Recive_file();
        //重载，save_path是文件保存的地址
        int Recive_file(char *save_path);
    };

} // namespace CLIENT_CORE
