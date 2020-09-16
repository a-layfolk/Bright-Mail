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

#include "Communi_Core.h"

//通信核心
namespace COMMUNI
{
    //模仿read，content输入需要读取的字符串，并将读取的内容转移至较小的buffer中，方便数据包的分批发送。函数返回读取的字节数。注意，cursor在传入函数后会发生改变
    int Communi_Core::ChRead(char *&cursor, char *buffer, int buffer_size)
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

    int Communi_Core::Write_File(const char *save_path)
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
                std::cout << "writing" << std::endl; //debug
                if (read_len < CONFIG::buffer_size)
                {
                    break;
                }
            }
        }
        fclose(out_file);
        return 0;
    }

    //获取对应路径下文件的名字
    char *Communi_Core::Get_File_Name(const char *file_path)
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

    int clnt_socket;
    //输入服务器地址,连接服务器
    Communi_Core::Communi_Core(const char *server_ip)
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
    Communi_Core::Communi_Core(int client_socket_number)
    {
        this->clnt_socket = client_socket_number;
    }

    Communi_Core::~Communi_Core(){};

    //给服务器发送数据，send后记得将原字符串删除！
    int Communi_Core::Send_Data(const char *data)
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
    char *Communi_Core::Recive_Data()
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
    int Communi_Core::Sd_File(const char *file_path)
    {
        write(this->clnt_socket, "MY_FILE", CONFIG::buffer_size);
        //写一个发送文件名的？
        FILE *fp;
        fp = fopen((char *)file_path, "rb");
        if (fp == NULL)
        {
            write(this->clnt_socket, "Failed", CONFIG::buffer_size);
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

    //save_path是文件保存的地址
    int Communi_Core::Recive_File(const char *save_path)
    {
        char buffer[CONFIG::buffer_size];
        read(this->clnt_socket, buffer, CONFIG::buffer_size);
        if (strcmp(buffer, "Failed") == 0)
        {
            return -1;
        }
        return this->Write_File(save_path);
    }
}; // namespace COMMUNI