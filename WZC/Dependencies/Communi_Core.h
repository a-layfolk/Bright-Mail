#ifndef COM_CORE_H
#define COM_CORE_H

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

#define APP_PORT 8888
#define BUFFER_SIZE 4000

//通信核心
namespace COMMUNI
{
    //通信核心配置
    namespace CONFIG
    {
        const int server_port = APP_PORT;
        const int buffer_size = BUFFER_SIZE;

    } // namespace CONFIG

    class Communi_Core
    {
    private:
        //模仿read，content输入需要读取的字符串，并将读取的内容转移至较小的buffer中，方便数据包的分批发送。函数返回读取的字节数。注意，cursor在传入函数后会发生改变
        int ChRead(char *&cursor, char *buffer, int buffer_size);

        int Write_File(const char *save_path);

    protected:
        //获取对应路径下文件的名字
        char *Get_File_Name(const char *file_path);
        int clnt_socket;
        //输入服务器地址,连接服务器
        Communi_Core(const char *server_ip);
        //直接输入socket的代号
        Communi_Core(int client_socket_number);
        ~Communi_Core();

        //给服务器发送数据，send后记得将原字符串删除！
        int Send_Data(const char *data);

        //取得服务器数据，数据格式为JSON的字符串
        char *Recive_Data();

        //给服务器发送文件,返回文件的名字
        int Sd_File(const char *file_path);

        //接收服务器端发送的文件
        // int Recive_File();

        //重载，save_path是文件保存的地址
        int Recive_File(const char *save_path);
    };
} // namespace COMMUNI

#endif