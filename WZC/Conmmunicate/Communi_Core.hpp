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

namespace COMMUNI
{
    namespace CONFIG
    {
        // const char server_ip[] = "127.0.0.1";
        const int server_port = 8888;
        const int buffer_size = 100;
        const int data_bag_size = 1024;

    } // namespace CONFIG

    class Communi_Core
    {
    private:
        int clnt_socket;

        //模仿read，content输入需要读取的字符串，并将读取的内容转移至较小的buffer中，方便数据包的分批发送。函数返回读取的字节数。注意，content在传入函数后会发生改变
        int ChRead(char *content, char *buffer, int buffer_size);

        int Write_File(char *save_path);

        //获取对应路径下文件的名字
        char *Get_File_Name(const char *file_path);

    public:
        //输入服务器地址,连接服务器
        Communi_Core(const char *server_ip);

        ~Communi_Core();

        //给服务器发送数据
        int Send_Data(const char *data);

        //取得服务器数据，数据格式为JSON的字符串
        char *Recive_Data();

        //给服务器发送文件
        int Send_File(const char *file_path);

        //接收服务器端发送的文件
        int Recive_File();

        //重载，save_path是文件保存的地址
        int Recive_File(char *save_path);
    };
} // namespace COMMUNI

namespace SERVER
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
    class Server_Core : private Communi_Core
    {
    private:
        /* data */
    public:
        Server_Core(/* args */);
        ~Server_Core();
    };

    Server_Core::Server_Core() : Communi_Core(SERVER::CONFIG::server_ip)
    {
    }

    Server_Core::~Server_Core()
    {
    }

} // namespace SERVER

namespace CLIENT
{
    namespace CONFIG
    {
        const char server_ip[] = "127.0.0.1";
        const int server_port = 8888;
        const int buffer_size = 100;
        const int data_bag_size = 1024;

    } // namespace CONFIG
    class Client_Core : private Communi_Core
    {
    private:
        /* data */
    public:
        Client_Core(/* args */);
        ~Client_Core();
    };

    Client_Core::Client_Core(/* args */)
    {
    }

    Client_Core::~Client_Core()
    {
    }

} // namespace CLIENT