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

#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/reader.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#define APP_PORT 8888
#define BUFFER_SIZE 4000
//客户端配置
namespace CLIENT
{
    namespace CONFIG
    {
        const char server_ip[] = "123.57.176.139";
        const int server_port = APP_PORT;
        const int buffer_size = BUFFER_SIZE;

    } // namespace CONFIG

} // namespace CLIENT

//服务器配置
namespace SERVER
{
    namespace CONFIG
    {
        const char server_ip[] = "0.0.0.0";
        const int server_port = APP_PORT;
        const int buffer_size = BUFFER_SIZE;

        // const char sql_ip[] = "123.57.176.139";
        const char sql_ip[] = "0.0.0.0";
        const char sql_user[] = "root";
        const char sql_password[] = "1233";
        const char sql_db[] = "Email_schema";
        const int sql_port = 3306;
    } // namespace CONFIG

} // namespace SERVER

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

        int Write_File(char *save_path);

        //获取对应路径下文件的名字
        char *Get_File_Name(const char *file_path);

    public:
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

        //给服务器发送文件
        int Send_File(const char *file_path);

        //接收服务器端发送的文件
        int Recive_File();

        //重载，save_path是文件保存的地址
        int Recive_File(char *save_path);
    };
} // namespace COMMUNI

//客户端代码
namespace CLIENT
{
    class Client_Core : protected COMMUNI::Communi_Core
    {
    private:
        //服务器是否回传成功的消息.如果传回的是失败，则在error_info中填入失败信息
        bool Recive_Success(char *error_info);
        //解析返回的信息，记得delete包！
        rapidjson::Document *Return_Analysis(char *data_bag);

    public:
        Client_Core();
        Client_Core(const char *target_ip);

        //向服务器发送结束线程的信息
        void Send_Exit();

        ~Client_Core();

        int Sign_in(char *username, char *password);
        int Sign_up(char *username, char *password, char *phoneum);

    }; // namespace CLIENT
} // namespace CLIENT
