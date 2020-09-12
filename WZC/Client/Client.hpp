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
    class Client_Socket
    {
    private:
        int client_socket;

        //模仿read，content输入需要读取的字符串，并将读取的内容转移至较小的buffer中，方便数据包的分批发送。函数返回读取的字节数。注意，content在传入函数后会发生改变
        int ChRead(char *content, char *buffer, int buffer_size);
        int Send_data_bag(char *data_bag);

        //输入文件地址（任意文件），并发送给服务器
        int Send_File(const char *file_path);
        
        int Write_File(char *save_path);

        //获取对应路径下文件的名字
        char *Get_File_Name(const char *file_path);

    public:
        //默认构造函数：直接使用CONFIG中的ip和端口
        Client_Socket();
        //输入服务器地址,连接服务器
        Client_Socket(const char *server_ip);

        ~Client_Socket();

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

} // namespace CLIENT_CORE
