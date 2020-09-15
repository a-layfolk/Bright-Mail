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

#include "../Dependencies/rapidjson/rapidjson.h"
#include "../Dependencies/rapidjson/document.h"
#include "../Dependencies/rapidjson/reader.h"
#include "../Dependencies/rapidjson/writer.h"
#include "../Dependencies/rapidjson/stringbuffer.h"
#include "../Dependencies/Communi_Core.h"
#include "../Dependencies/SqlCon.h"



namespace SERVER
{
    //服务器配置
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

    class Server_Core : protected COMMUNI::Communi_Core
    {
    private:
        void Send_Error(const char *error_info);
        void Send_Success();

        bool Sign(rapidjson::Document &d, bool is_sign_in);
        
        int Add_Email(rapidjson::Document &d);
        int Add_Contact(rapidjson::Document &d);
        //?
        int Add_File(rapidjson::Document &d);

        int Return_Email_Detail(rapidjson::Document &d);
        int Return_Email_List(rapidjson::Document &d);
        int Return_Contact_List(rapidjson::Document &d);

        //?
        int Return_File(rapidjson::Document &d);



        int Request_Analysis();
        char *user_ip;
        mysql SQL;

    public:
        Server_Core(int client_socket);
        ~Server_Core();

        int Exe();
    };

} // namespace SERVER