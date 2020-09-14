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
#define BUFFER_SIZE 1000

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
        int ChRead(char *&cursor, char *buffer, int buffer_size)
        {
            int Bytes = 0;
            for (int i = 0; i < buffer_size; i++)
            {
                if (*cursor == 0)
                {
                    buffer[i] = 0;
                    break;
                }
                buffer[i] = *cursor;
                cursor++;
                Bytes++;
            }
            return Bytes;
        }

        int Write_File(char *save_path)
        {
            //debug path
            std::cout << save_path << std::endl;

            int read_len = 0;
            FILE *out_file = NULL;
            out_file = fopen(save_path, "wb+");
            char buffer[CONFIG::buffer_size];
            if (out_file == NULL)
            {
                std::cout << "File Save ERROR" << std::endl;
                return -1;
            }
            else
            {
                while ((read_len = recv(this->clnt_socket, buffer, CONFIG::buffer_size, 0)) > 0)
                {
                    fwrite(buffer, sizeof(char), read_len, out_file);
                    memset(buffer, 0, sizeof(buffer));
                }
            }
            fclose(out_file);
            return 0;
        }

        //获取对应路径下文件的名字
        char *Get_File_Name(const char *file_path)
        {
            int len = strlen(file_path);
            char *file_name = new char[len];
            char file_name_rev[len];
            int name_size = 0;
            int i = len;
            while (1)
            {
                if (file_path[i] == '/' || i <= 0)
                {
                    file_name_rev[name_size] = 0;
                    break;
                }
                file_name_rev[name_size] = file_path[i];
                name_size++;
                i--;
            }
            for (int i = 0; i < name_size; i++)
            {
                file_name[i] = file_name_rev[name_size - 1 - i];
            }
            file_name[name_size] = 0;
            return file_name;
        }

    public:
        int clnt_socket;
        //输入服务器地址,连接服务器
        Communi_Core(const char *server_ip)
        {
            this->clnt_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
            struct sockaddr_in clnt_addr;
            clnt_addr.sin_family = AF_INET;
            clnt_addr.sin_addr.s_addr = inet_addr(server_ip);
            clnt_addr.sin_port = htons(CONFIG::server_port);
            if (connect(this->clnt_socket, (sockaddr *)&clnt_addr, sizeof(clnt_addr)) == 0)
            {
                std::cout << "Connect success" << std::endl;
            }
            else
            {
                //是否需要放一个信号？
                perror("connect");
                exit(-1);
            }
        }
        //直接输入socket的代号
        Communi_Core(int client_socket_number)
        {
            this->clnt_socket = client_socket_number;
        }

        ~Communi_Core(){};

        //给服务器发送数据，send后记得将原字符串删除！
        int Send_Data(const char *data)
        {
            int read_len = 0;
            char buffer[CONFIG::buffer_size];
            char *t_d = (char *)data;
            while ((read_len = this->ChRead(t_d, buffer, CONFIG::buffer_size)) > 0)
            {
                write(this->clnt_socket, buffer, read_len);
                memset(buffer, 0, CONFIG::buffer_size);
                if (read_len < CONFIG::buffer_size)
                {
                    break;
                }
            }
            return 0;
        }

        //取得服务器数据，数据格式为JSON的字符串
        char *Recive_Data()
        {
            int read_len;
            char buffer[CONFIG::buffer_size];
            char *s = new char[2 * CONFIG::buffer_size]; //动态内存分配的算法可以秀一下
            memset(s, 0, 2 * CONFIG::buffer_size);
            char *cursor = s;
            memset(buffer, 0, CONFIG::buffer_size);
            while ((read_len = read(this->clnt_socket, buffer, CONFIG::buffer_size)) > 0)
            {
                strcpy(cursor, buffer);
                // sprintf(s, "%s", cursor);
                cursor += read_len; //这样写是对的吗
                memset(buffer, 0, CONFIG::buffer_size);
                if (read_len < CONFIG::buffer_size)
                {
                    break;
                }
            }
            return s;
        }

        //给服务器发送文件
        int Send_File(const char *file_path)
        {

            //写一个发送文件名的？
            FILE *fp;
            fp = fopen((char *)file_path, "rb");
            if (fp == NULL)
            {
                std::cout << "ERROR" << std::endl;
                return -1;
            }
            else
            {
                char buffer[CONFIG::buffer_size];
                int read_len;
                while ((read_len = fread(buffer, sizeof(char), CONFIG::buffer_size, fp)) != 0)
                {
                    write(this->clnt_socket, buffer, read_len);
                    if (read_len < CONFIG::buffer_size)
                    {
                        break;
                    }
                }
                fclose(fp);
                return 0;
            }
        }

        //接收服务器端发送的文件
        int Recive_File()
        {
            char request_buffer[CONFIG::buffer_size];
            memset(request_buffer, 0, CONFIG::buffer_size);
            recv(this->clnt_socket, request_buffer, CONFIG::buffer_size, 0);
            rapidjson::Document d;
            d.Parse(request_buffer);

            char file_path[30] = "./recived/";
            strcat(file_path, d["file_name"].GetString());
            return this->Write_File(file_path);
        }

        //重载，save_path是文件保存的地址
        int Recive_File(char *save_path)
        {
            char request_buffer[CONFIG::buffer_size];
            memset(request_buffer, 0, CONFIG::buffer_size);
            recv(this->clnt_socket, request_buffer, CONFIG::buffer_size, 0);
            return this->Write_File(save_path);
        }
    };
} // namespace COMMUNI