#include <string>
#include "JSON_Maker.hpp"
using namespace std;
using namespace JSON_Maker;

string JSON_Maker::Creat_Key(const char *key_name, const char *value, bool with_comma)
{
    string str;
    str.push_back('\"');
    str += key_name;
    str += "\':\"";
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
string Creat_Key_int(const char *key_name, int value, bool with_comma)
{
    string str;
    str.push_back('\"');
    str += key_name;
    str += "\':";
    // str += std::to_string(value);
    //int转换成字符串
    if (with_comma)
    {
        str.push_back(',');
    }
    return str;
}

char *Creat_DataBag_Sign_in(char *username, char *password)
{
    string *str = new string;
    str->push_back('{');

    *str += JSON_Maker::Creat_Key(Key_Type::request_type, "sign_in", true);

    *str += JSON_Maker::Creat_Key(Key_Type::sql_username, username, true);
    *str += JSON_Maker::Creat_Key(Key_Type::sql_password, password, false);

    str->push_back('}');

    char *JSON = new char[(*str).size()];
    str->copy(JSON, (*str).size(), 0);
    delete str;
    return JSON;
}

char *Creat_DataBag_Sign_up(char *username, char *password, char *phoneum)
{
    string *str = new string;
    str->push_back('{');

    *str += JSON_Maker::Creat_Key(Key_Type::request_type, "sign_in", true);

    *str += JSON_Maker::Creat_Key(Key_Type::sql_username, username, true);
    *str += JSON_Maker::Creat_Key(Key_Type::sql_password, password, true);
    *str += JSON_Maker::Creat_Key(Key_Type::sql_phoneum, phoneum, false);

    str->push_back('}');

    char *JSON = new char[(*str).size()];
    str->copy(JSON, (*str).size(), 0);
    delete str;
    return JSON;
}

char *Creat_DataBag_End_Connect()
{
    string *str = new string;
    str->push_back('{');

    *str += JSON_Maker::Creat_Key(Key_Type::request_type, "operate", true);
    *str += JSON_Maker::Creat_Key(Key_Type::command_type, "end_connect", true);

    str->push_back('}');

    char *JSON = new char[(*str).size()];
    str->copy(JSON, (*str).size(), 0);
    delete str;
    return JSON;
}
