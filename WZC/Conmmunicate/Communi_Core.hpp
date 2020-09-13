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
#include "rapidjson/reader.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "SQL/SqlCon.h"
#include "JSON_Maker.hpp"

namespace COMMUNI
{
    namespace CONFIG
    {
        const char server_ip[] = "127.0.0.1";
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

        //直接输入socket的代号
        Communi_Core(int client_socket_number);

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
            sign_in,
            sign_up,
            file,
            mail,
            list,
            operate

        };
    } // namespace CONFIG
    class Server_Core : private COMMUNI::Communi_Core
    {
    private:
        int Insert_Email(rapidjson::Document &d);

        int Send_Email(rapidjson::Document &d);

        int Request_Analysis()
        {
            //接收请求包
            char *data_bag = this->Recive_Data();
            rapidjson::Document d;
            d.Parse(data_bag);
            const char *rq_type = d[JSON_Maker::Key_Type::request_type].GetString();
            if (strcmp(rq_type, "insert_email") == 0)
            {
                Insert_Email(d);
            }
        /* data */

            //拆包
            //判断request_type

            delete data_bag;
            return 0;
        }

        char *user_ip;
        mysql SQL;

    public:
        Server_Core(int client_socket);
        ~Server_Core();

        bool Sign()
        {
            for (int i = 0; i < 5; i++)
            {
                //接收请求包
                char *sign = this->Recive_Data();
                bool is_passed = false;
                //解析请求包
                /*
                rapidjson::Document d;
                d.Parse(sign);
                if (strcmp(d[JSON_Maker::Key_Type::request_type].GetString(), "sign_up") == 0)
                {
                    is_passed = SQL.sign_up(d[JSON_Maker::Key_Type::sql_username].GetString(), d[JSON_Maker::Key_Type::sql_password].GetString(), d[JSON_Maker::Key_Type::sql_phoneum].GetString());
                }
                else if (strcmp(d[JSON_Maker::Key_Type::request_type].GetString(), "sign_in") == 0)
                {
                    is_passed = SQL.sign_in(d[JSON_Maker::Key_Type::sql_username].GetString(), d[JSON_Maker::Key_Type::sql_password].GetString());
                }
                else if (strcmp(d[JSON_Maker::Key_Type::request_type].GetString(), "operate") == 0)
                {
                    std::cout << "User Sign Canceled" << std::endl;
                    //用户取消操作退出线程
                    break;
                }
                */
                //释放请求包的内存
                delete sign;
                if (is_passed)
                {
                    this->Send_Data("success");
                    //给服务器发信息
                    return true;
                }
                else
                {
                    this->Send_Data("failed");
                    char info[3];
                    sprintf(info, "%d", i);
                    this->Send_Data(info);
                }
            }
            //给服务器发未成功信息
            return false;
        }

        //用户通信进程
        int Exe()
        {
        }
    };

} // namespace SERVER

namespace CLIENT
{
    namespace CONFIG
    {
        const char *server_ip = COMMUNI::CONFIG::server_ip;
        const int server_port = COMMUNI::CONFIG::server_port;
        const int buffer_size = 100;
        const int data_bag_size = 1024;

    } // namespace CONFIG
    class Client_Core : private COMMUNI::Communi_Core
    {
    private:
        /* data */
        //服务器是否回传成功的消息
        bool Server_Success()
        {
            char *str = this->Recive_Data();
            if (strcmp(str, "success") == 0)
            {
                delete str;
                return true;
            }
            delete str;
            return false;
        }

    public:
        Client_Core();
        Client_Core(const char *target_ip);

        //向服务器发送结束操作的信息
        void End_Connect()
        {
            char *JSON = JSON_Maker::Creat_DataBag_End_Connect();
            this->Send_Data(JSON);
            delete JSON;
        }
        ~Client_Core();

        //返回还剩几次登陆机会,返回-1则是登陆成功
        int Sign_in(char *username, char *password);
        //返回还剩几次登陆机会
        int Sign_up(char *username, char *password, char *phoneum);
    };

} // namespace CLIENT