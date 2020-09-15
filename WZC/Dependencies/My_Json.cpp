#include "My_Json.h"
#include <string>
#include <string.h>
#include <iostream>
#include <stdio.h>
using namespace std;
namespace My_Json
{
    string Creat_Key(const char *key_name, const char *value, bool with_comma)
    {
        string str;
        str.push_back('\"');
        str += key_name;
        str += "\":\"";
        if (value != NULL)
        {
            str += value;
        }
        else
        {
            str += "null";
        }

        if (with_comma)
        {
            str += "\",";
        }
        else
        {
            str.push_back('\"');
        }
        return str;
    }
    //创建其余空键值的函数？

    //用字符串表示int
    string Creat_Key_int(const char *key_name, const char *value, bool with_comma)
    {
        string str;
        str.push_back('\"');
        str += key_name;
        str += "\":";
        str += value;
        if (with_comma)
        {
            str.push_back(',');
        }
        return str;
    }
} // namespace My_Json
namespace DataBag
{
    using namespace My_Json;
    char *DataBag_Sign_in(const char *username, const char *password)
    {
        string *str = new string;
        str->push_back('{');

        *str += Creat_Key(Key_Type::request_type, Rq_Type::sign_in, true);

        *str += Creat_Key(Key_Type::sql_username, username, true);
        *str += Creat_Key(Key_Type::sql_password, password, false);

        str->push_back('}');

        char *JSON = new char[(*str).size()];
        memset(JSON, 0, (*str).size());
        strcpy(JSON, (*str).c_str());
        delete str;
        // cout << "data_bag:" << JSON << endl; //debug
        return JSON;
    }

    char *DataBag_Sign_up(const char *username, const char *password, const char *phoneum)
    {
        string *str = new string;
        str->push_back('{');

        *str += Creat_Key(Key_Type::request_type, Rq_Type::sign_up, true);

        *str += Creat_Key(Key_Type::sql_username, username, true);
        *str += Creat_Key(Key_Type::sql_password, password, true);
        *str += Creat_Key(Key_Type::sql_phoneum, phoneum, false);

        str->push_back('}');

        char *JSON = new char[(*str).size()];
        strcpy(JSON, (*str).c_str());
        delete str;
        return JSON;
    }

    char *DataBag_Exit()
    {
        string *str = new string;
        str->push_back('{');

        *str += Creat_Key(Key_Type::request_type, Rq_Type::command, true);
        *str += Creat_Key(Key_Type::command_type, "exit", false);

        str->push_back('}');

        char *JSON = new char[(*str).size()];
        strcpy(JSON, (*str).c_str());
        delete str;
        return JSON;
    }

    char *DataBag_Success()
    {
        string *str = new string;
        str->push_back('{');

        *str += Creat_Key(Key_Type::request_type, Rq_Type::command, true);
        *str += Creat_Key(Key_Type::command_type, "success", true);
        *str += Creat_Key("error_info", "success", false);

        str->push_back('}');

        int l = str->length();
        char *JSON = new char[l];
        memset(JSON, 0, l);
        strcpy(JSON, str->c_str());
        delete str;
        return JSON;
    }

    char *DataBag_Error(const char *error_info)
    {
        string *str = new string;
        str->push_back('{');

        *str += Creat_Key(Key_Type::request_type, Rq_Type::command, true);
        *str += Creat_Key(Key_Type::command_type, "error", true);
        *str += Creat_Key("error_info", error_info, false);

        str->push_back('}');

        char *JSON = new char[(*str).size()];
        strcpy(JSON, (*str).c_str());
        delete str;
        return JSON;
    }

    char *DataBag_Sd_Mail(const char *ownerId, const char *targetId, const char *email_type, const char *email_title, const char *email_content)
    {
        string *str = new string;
        str->push_back('{');

        *str += Creat_Key(Key_Type::request_type, Rq_Type::sd_mail, true);
        *str += Creat_Key("ownerId", ownerId, true);
        *str += Creat_Key("targetId", targetId, true);
        *str += Creat_Key("email_type", email_type, true);
        *str += Creat_Key("email_title", email_title, true);
        *str += Creat_Key("email_content", email_content, false);

        str->push_back('}');

        char *JSON = new char[(*str).size()];
        strcpy(JSON, (*str).c_str());
        delete str;
        return JSON;
    }
    char *DataBag_Sd_Mail_Server_Core(const char *emailTitle, const char *emailContent, const char *email_type, const char *targetUsername, const char *emailTime)
    {
        string *str = new string;
        str->push_back('{');

        *str += Creat_Key(Key_Type::request_type, Rq_Type::sd_mail, true);
        *str += Creat_Key("emailTitle", emailTitle, true);
        *str += Creat_Key("emailContent", emailContent, true);
        *str += Creat_Key("email_type", email_type, true);
        *str += Creat_Key("targetUsername", targetUsername, true);
        *str += Creat_Key("emailTime", emailTime, false);

        str->push_back('}');

        char *JSON = new char[(*str).size()];
        strcpy(JSON, (*str).c_str());
        delete str;
        return JSON;
    }
    char *DataBa_Sd_File(const char *ownerId, const char *emailId, const char *fileName)
    {
        string *str = new string;
        str->push_back('{');

        *str += Creat_Key(Key_Type::request_type, Rq_Type::sd_file, true);
        *str += Creat_Key("ownerId", ownerId, true);
        *str += Creat_Key("emailId", emailId, true);
        *str += Creat_Key("fileName", fileName, false);

        str->push_back('}');

        char *JSON = new char[(*str).size()];
        strcpy(JSON, (*str).c_str());
        delete str;
        return JSON;
    }

    char *Mail_List_Tag(const char *emailTitle, const char *targetUsername, const char *emailTime, const char *emailId)
    {
        string *str = new string;
        str->push_back('{');

        *str += Creat_Key(Key_Type::request_type, Rq_Type::sd_list, true);
        *str += Creat_Key("emailTitle", emailTitle, true);
        *str += Creat_Key("targetUsername", targetUsername, true);
        *str += Creat_Key("emailTime", emailTime, true);
        *str += Creat_Key("emailId", emailId, false);

        str->push_back('}');

        char *JSON = new char[(*str).size()];
        strcpy(JSON, (*str).c_str());
        delete str;
        return JSON;
    }
    char *DataBag_Sd_Mail_List(int size, DataBag::EMAIL_INFO *E_info)
    {
        string *str = new string;
        str->push_back('{');
        *str += Creat_Key(Key_Type::request_type, Rq_Type::sd_list, true);
        char *size_tag = new char[20];
        sprintf(size_tag, "\"size\":%d,\"info\":[", size);
        *str += size_tag;
        delete size_tag;
        for (int i = 0; i < size; i++)
        {
            char *tag = Mail_List_Tag(((EMAIL_INFO *)E_info + i)->targetUsername, ((EMAIL_INFO *)E_info + i)->targetUsername, ((EMAIL_INFO *)E_info + i)->emailTime, ((EMAIL_INFO *)E_info + i)->emailId);
            *str += tag;
            delete[] tag;
            if (i != size - 1)
            {
                str->push_back(',');
            }
        }
        str->push_back(']');
        str->push_back('}');
        char *JSON = new char[(*str).size()];
        strcpy(JSON, (*str).c_str());
        delete str;
        return JSON;
    }
    char *DataBag_Sd_Contact_List(int size, DataBag::CONTATCT_INFO *C_info)
    {
        string *str = new string;
        str->push_back('{');
        *str += Creat_Key(Key_Type::request_type, Rq_Type::rq_contact, true);
        char *size_tag = new char[20];
        sprintf(size_tag, "\"size\":%d,\"info\":[", size);
        *str += size_tag;
        delete size_tag;
        for (int i = 0; i < size; i++)
        {
            char *tag = DataBag_Sd_Contact(((CONTATCT_INFO *)C_info + i)->userId, ((CONTATCT_INFO *)C_info + i)->userName, ((CONTATCT_INFO *)C_info + i)->telephone);
            *str += tag;
            delete[] tag;
            if (i != size - 1)
            {
                str->push_back(',');
            }
        }
        str->push_back(']');
        str->push_back('}');
        char *JSON = new char[(*str).size()];
        strcpy(JSON, (*str).c_str());
        delete str;
        return JSON;
    }
    char *DataBag_Sd_Contact(const char *userId, const char *contactname, const char *phonenum)
    {
        string *str = new string;
        str->push_back('{');

        *str += Creat_Key(Key_Type::request_type, Rq_Type::sd_contact, true);
        *str += Creat_Key("userId", userId, true);
        *str += Creat_Key("contactname", contactname, true);
        *str += Creat_Key("phonenum", phonenum, false);

        str->push_back('}');

        char *JSON = new char[(*str).size()];
        strcpy(JSON, (*str).c_str());
        delete str;
        return JSON;
    }

    char *DataBag_Rq_Mail(const char *emailId, const char *ownerId)
    {
        string *str = new string;
        str->push_back('{');

        *str += Creat_Key(Key_Type::request_type, Rq_Type::rq_mail, true);
        *str += Creat_Key("emailId", emailId, true);
        *str += Creat_Key("ownerId", ownerId, false);

        str->push_back('}');

        char *JSON = new char[(*str).size()];
        strcpy(JSON, (*str).c_str());
        delete str;
        return JSON;
    }

    //先查mailId对应的文件数和文件名，再通过文件名来接收文件
    char *DataBag_Rq_File(const char *ownerId, const char *emailId, const char *fileName)
    {
        string *str = new string;
        str->push_back('{');

        *str += Creat_Key(Key_Type::request_type, Rq_Type::rq_file, true);
        *str += Creat_Key("ownerId", ownerId, true);
        *str += Creat_Key("emailId", emailId, true);
        *str += Creat_Key("fileName", fileName, false);

        str->push_back('}');

        char *JSON = new char[(*str).size()];
        strcpy(JSON, (*str).c_str());
        delete str;
        return JSON;
    }

    char *DataBag_Rq_Contact(const char *userId)
    {
        string *str = new string;
        str->push_back('{');

        *str += Creat_Key(Key_Type::request_type, Rq_Type::rq_contact, true);
        *str += Creat_Key("userId", userId, false);

        str->push_back('}');

        char *JSON = new char[(*str).size()];
        strcpy(JSON, (*str).c_str());
        delete str;
        return JSON;
    }
    char *DataBag_Rq_List(const char *userId, const char *emailType)
    {

        string *str = new string;
        str->push_back('{');
        *str += Creat_Key(Key_Type::request_type, Rq_Type::rq_list, true);

        *str += Creat_Key("userId", userId, true);
        *str += Creat_Key("emailType", emailType, false);

        str->push_back('}');

        char *JSON = new char[(*str).size()];
        strcpy(JSON, (*str).c_str());
        delete str;
        return JSON;
    }
} // namespace DataBag