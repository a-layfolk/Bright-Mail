#ifndef SQL_C_H
#define SQL_C_H
#include <stdio.h>
#include "mysql/mysql.h"
#include "../Dependencies/My_Json.h"
#include "../Dependencies/rapidjson/stringbuffer.h"
#include "../Dependencies/rapidjson/writer.h"
#include "../Dependencies/rapidjson/rapidjson.h"
using namespace DataBag;
using namespace My_Json;
using namespace rapidjson;
class Sql_Core
{
private:
    MYSQL *con;
    const char *ip;
    const char *username;
    const char *password;
    const char *db;
    int port;

    //输入用户姓名和用户手机返回对应的用户Id，如果找到则返回字符串，未查询到则返回NULL
    char *Get_User_Id(const char *telephone)
    {
        char *query = new char[100];
        char *userId = NULL;
        MYSQL_RES *res = NULL;
        MYSQL_ROW row = NULL;
        sprintf(query, "select * from User where telephone= '%s';", telephone);
        if (!mysql_query(con, query))
        {
            delete[] query;
            res = mysql_store_result(con);
            row = mysql_fetch_row(res);
            userId = new char[100];
            if (row != NULL)
            {
                strcpy(userId, row[0]);
            }
            else
            {
                cout << "User not pass" << endl;
            }
            return userId;
        }
        else
        {
            printf("MySQL query error : %s\n", mysql_error(con));
            delete[] query;
            return NULL;
        }
    }

public:
    Sql_Core(const char *ip, const char *username, const char *password, const char *db, const int port)
    {
        this->ip = ip;
        this->username = username;
        this->password = password;
        this->db = db;
        this->port = port;
        con = mysql_init(NULL);
    }
    ~Sql_Core() {}
    bool Connect()
    {
        mysql_init(con);
        if (!mysql_real_connect(con, ip, username, password, db, port, NULL, 0))
        {
            printf("MySQL connect error : %s\n", mysql_error(con)); //需要加上这个，因为这个是操作失败时返回显示
            getchar();
            return false;
        }
        else
        {
            cout << "connect okk" << endl;
            return true;
        }
    }
    void Close()
    {

        mysql_close(con);
    }

    //登录或注册后返回用户的Id，查到后返回ID，否则返回false
    char *Sign_In(const char *userName, const char *password)
    {
        char *query = new char[100];
        char *userId = NULL;
        MYSQL_RES *res = NULL;
        MYSQL_ROW row = NULL;
        sprintf(query, "select * from User where userName='%s' and  password= '%s';", userName, password);
        if (!mysql_query(con, query))
        {
            delete[] query;
            res = mysql_store_result(con);
            row = mysql_fetch_row(res);
            userId = new char[100];
            if (row != NULL)
            {
                strcpy(userId, row[0]);
            }
            else
            {
                cout << "User not pass" << endl;
            }
            return userId;
        }
        else
        {
            printf("MySQL query error : %s\n", mysql_error(con));
            delete[] query;
            return NULL;
        }
    }

    //如果电话被注册，返回NULL
    char *Sign_Up(const char *userName, const char *password, const char *telephone)
    {
        char *query = new char[100];
        MYSQL_RES *res = NULL;
        MYSQL_ROW row = NULL;

        //检查电话是否被注册
        sprintf(query, "select * from User where telephone='%s';", telephone);

        if (!mysql_query(con, query))
        {
            res = mysql_store_result(con);
            row = mysql_fetch_row(res);
            if (row != NULL)
            {
                cout << "Telephone Number has been signed up!" << endl;
                delete[] query;
                return NULL;
            }
        }
        else
        {
            cout << "Error!" << endl;
            printf("MySQL query error : %s\n", mysql_error(con));
            delete[] query;
            return NULL;
        }

        sprintf(query, "insert into User(userName,password,telephone) values('%s','%s','%s');", userName, password, telephone);
        if (mysql_query(con, query))
        {
            printf("sign-up error : %s\n", mysql_error(con));
            delete[] query;
            return NULL;
        }
        else
        {
            printf("sign up okkk\n");
            delete[] query;
            // return this->Get_User_Id(username, password);
            return this->Get_User_Id(telephone);
        }
    }

    char *Get_Time()
    {
        char *query = new char[100];
        char *time = new char[30];
        MYSQL_RES *res = NULL;
        MYSQL_ROW row = NULL;
        sprintf(query, "select now();");
        mysql_query(con, query);

        res = mysql_store_result(con);
        row = mysql_fetch_row(res);
        strcpy(time, row[0]);

        delete[] query;
        return time;
    }
    //添加邮件
    bool Add_Email(const char *myId, const char *targetTelephone, const char *emailType, const char *emailTitle, const char *emailContent, const char *attachedFile)
    {
        char *query = new char[5000];
        char *time = this->Get_Time();
        if (attachedFile == NULL)
        {
            sprintf(query, "Insert into Email(myId,targetTelephone,emailType,emailTitle,emailContent,emailTime)values(%s,'%s','%s','%s','%s','%s');", myId, targetTelephone, emailType, emailTitle, emailContent, time);
        }
        else
        {
            sprintf(query, "Insert into Email(myId,targetTelephone,emailType,emailTitle,emailContent,emailTime,attachedFile)values(%s,'%s','%s','%s','%s','%s','%s');", myId, targetTelephone, emailType, emailTitle, emailContent, time, attachedFile);
        }

        delete[] time;

        if (mysql_query(con, query))
        {
            printf("insert error : %s\n", mysql_error(con));
            delete[] query;
            return false;
        }
        else
        {

            printf("insert email okkk okkk\n");
            delete[] query;
            return true;
        }
    }
    bool Add_Recived_Email(const char *targetTelephone, const char *emailTitle, const char *emailContent, const char *attachedFile)
    {
        char *query = new char[5000];
        char *time = this->Get_Time();
        char *myId = this->Get_User_Id(targetTelephone);
        if (attachedFile == NULL)
        {

            sprintf(query, "Insert into Email(myId,targetTelephone,emailType,emailTitle,emailContent,emailTime)values(%s,'%s','%s','%s','%s','%s');", myId, targetTelephone, "received_unread", emailTitle, emailContent, time);
        }
        else
        {
            sprintf(query, "Insert into Email(myId,targetTelephone,emailType,emailTitle,emailContent,emailTime,attachedFile)values(%s,'%s','%s','%s','%s','%s','%s);", myId, targetTelephone, "received_unread", emailTitle, emailContent, time, attachedFile);
        }

        delete[] time;

        if (mysql_query(con, query))
        {
            printf("insert error : %s\n", mysql_error(con));
            delete[] query;
            return false;
        }
        else
        {

            printf("insert email okkk okkk\n");
            delete[] query;
            return true;
        }
    }

    bool Add_Contact(const char *userId, const char *targetName, const char *targetTelephone)
    {
        MYSQL_RES *res = NULL;
        MYSQL_ROW row = NULL;
        char *targetId = NULL;
        targetId = this->Get_User_Id(targetTelephone);
        if (targetId != NULL)
        {
            char *query = new char[1000];
            sprintf(query, "select * from Contact where userId='%s' and targetId='%s';", userId, targetId);

            if (!mysql_query(con, query))
            {
                res = mysql_store_result(con);
                row = mysql_fetch_row(res);
                if (row == NULL)
                {
                    sprintf(query, "insert into Contact(userId,targetId) values(%s,%s);", userId, targetId);
                    mysql_query(con, query);
                }
                delete[] query;
                delete[] targetId;
                return true;
            }
            else
            {
                cout << "Error!" << endl;
                printf("MySQL query error : %s\n", mysql_error(con));
                delete[] query;
                delete[] targetId;
                return false;
            }
        }
        else
            cout << "Insert Fail" << endl;
        return false;
    }

    char *Get_Email_List_JSON(const char *userId, const char *emailType)
    {
        rapidjson::StringBuffer s;
        rapidjson::Writer<rapidjson::StringBuffer> writer(s);
        writer.StartObject();
        writer.Key(Key_Type::request_type);
        writer.String(Rq_Type::sd_list);
        writer.Key("info");
        writer.StartArray();
        char *query = new char[1000];
        sprintf(query, "select emailTitle,targetTelephone,emailTime,emailId from Email where myId=%s and emailType='%s';", userId, emailType);
        MYSQL_RES *res;
        MYSQL_ROW row;

        cout << "query:" << query << endl;
        mysql_query(con, query);
        res = mysql_store_result(con);
        delete[] query;

        int size = 0;
        while ((row = mysql_fetch_row(res)) != NULL)
        {
            size++;
            writer.StartObject();

            writer.Key("emailTitle");
            writer.String((char *)row[0]);

            writer.Key("targetUsername");
            writer.String((char *)row[1]);

            writer.Key("emailTime");
            writer.String((char *)row[2]);
            writer.Key("emailId");
            writer.String((char *)row[3]);

            writer.EndObject();
        }
        writer.EndArray();

        // writer.Key("size");
        // writer.Int(2);

        writer.EndObject();
        int J_size = strlen(s.GetString() + 1);

        char *JSON = new char[J_size];
        strncpy(JSON, s.GetString(), J_size - 1);
        return JSON;
        // char *JSON = new char[s.GetSize()];
        // strcpy(JSON, s.GetString());
        // std::cout << JSON;
        // return JSON;
    }

    char *Get_Email_Detail_JSON(const char *emailId)
    {
        // string *str = new string;
        // str->push_back('{');

        // *str += Creat_Key(Key_Type::request_type, Rq_Type::sd_mail, true);
        char *query = new char[1000];
        MYSQL_ROW row;
        // cout << "1" << endl;
        StringBuffer s;
        rapidjson::Writer<rapidjson::StringBuffer> writer(s);
        writer.StartObject();
        writer.Key(Key_Type::request_type);
        writer.String(Rq_Type::rq_mail);

        cout << "1" << endl;
        snprintf(query, 1000, "select  Email.emailTitle, Email.emailContent, Bright_Mail.User.userName,Email.emailType,Email.emailTime,Email.attachedFile from Email,User where emailId=%s AND Email.targetTelephone= Bright_Mail.User.telephone;", emailId);
        mysql_query(con, query);
        cout << query << endl;
        delete[] query;
        cout << "1" << endl;
        if (row != NULL)
        {

            MYSQL_RES *res = mysql_store_result(con);
            row = mysql_fetch_row(res);
            int num = mysql_num_fields(res);
            writer.Key("emailTitle");
            writer.String(row[0]);

            writer.Key("emailContent");
            writer.String(row[1]);

            writer.Key("targetUsername");
            writer.String(row[2]);

            writer.Key("emailType");
            writer.String(row[3]);

            writer.Key("emailTime");

            writer.String(row[4]);
            writer.EndObject();
            int J_size = strlen(s.GetString() + 1);

            char *JSON = new char[J_size];
            strncpy(JSON, s.GetString(), J_size - 1);
            return JSON;
        }
        return NULL;
    }

    char *Get_Contact_List_JSON(const char *userId)
    {
        string *str = new string;
        str->push_back('{');
        *str += Creat_Key(Key_Type::request_type, Rq_Type::sd_list, true);
        *str += "\"info\":[";

        char *query = new char[1000];
        sprintf(query, "select targetId from Contact where userId= %s ;", userId);
        MYSQL_RES *res;
        MYSQL_ROW row;
        mysql_query(con, query);
        res = mysql_store_result(con);

        int size = 0;
        while ((row = mysql_fetch_row(res)) != NULL)
        {

            MYSQL_RES *res_1;
            MYSQL_ROW row_1;
            sprintf(query, "select userId,UserName,telephone from User where userId=%s ;", row[0]);
            mysql_query(con, query);
            res_1 = mysql_store_result(con);

            while ((row_1 = mysql_fetch_row(res_1)) != NULL)
            {
                if (size != 0)
                {
                    str->push_back(',');
                }
                char *tag = Contact_List_Tag(row_1[0], row_1[1], row_1[2]);
                *str += tag;
                delete[] tag;
                size++;
            }
        }

        str->push_back(']');
        char *size_temp = new char[10];
        sprintf(size_temp, ",\"size\":%d", size);
        *str += size_temp;
        delete size_temp;

        str->push_back('}');
        char *JSON = new char[(*str).size()];
        strcpy(JSON, (*str).c_str());
        delete str;
        return JSON;
        delete[] query;
        return JSON;
    }
};

#endif