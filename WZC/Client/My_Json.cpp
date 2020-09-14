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
        str += value;
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

    string Creat_Key_int(const char *key_name, int value, bool with_comma)
    {
        string str;
        str.push_back('\"');
        str += key_name;
        str += "\":";
        // str += std::to_string(value);
        //int转换成字符串
        if (with_comma)
        {
            str.push_back(',');
        }
        return str;
    }
} // namespace My_Json
namespace Data_Bag
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

    char *Data_Bag_Success()
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
        cout << JSON << endl;
        return JSON;
    }

    char *Data_Bag_Error(const char *error_info)
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
        cout << JSON << endl; //debug
        return JSON;
    }
} // namespace Data_Bag