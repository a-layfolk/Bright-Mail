#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>

using namespace std;
namespace JSON_Maker
{
    namespace Key_Type
    {
        const char request_type[] = "request_type";
        const char sql_username[] = "username";
        const char sql_password[] = "password";
        const char sql_phoneum[] = "phoneum";
        const char sql_emailType[] = "emailType";
        const char sql_userId[] = "userId";
        const char sql_emailType[] = "emailType";
        const char sql_emailTitle[] = "emailTitle";
        const char sql_emailContent[] = "emailContent";
        const char sql_emailTime[] = "emailTime";
        const char sql_attachedFilePath[] = "attachedFilePath";
        const char sql_userId[] = "userId";
        const char sql_targetUsername[] = "targetUsername";
        const char sql_targetId[] = "targetId";
        const char sql_ownerId[] = "ownerId";
        const char sql_contactname[] = "contactname";
        const char sql_newState[] = "newState";
    } // namespace Key_Type

    string Creat_Key(const char *key_name, const char *value, bool with_comma)
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
    string Creat_Key(const char *key_name, int value, bool with_comma)
    {
        string str;
        str.push_back('\"');
        str += key_name;
        str += "\':";
        str += std::to_string(value);
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

        *str += Creat_Key(Key_Type::request_type, "sign_in", true);

        *str += Creat_Key(Key_Type::sql_username, username, true);
        *str += Creat_Key(Key_Type::sql_password, password, false);

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

        *str += Creat_Key(Key_Type::request_type, "sign_up", true);

        *str += Creat_Key(Key_Type::sql_username, username, true);
        *str += Creat_Key(Key_Type::sql_password, password, true);
        *str += Creat_Key(Key_Type::sql_phoneum, phoneum, false);

        str->push_back('}');

        char *JSON = new char[(*str).size()];
        str->copy(JSON, (*str).size(), 0);
        delete str;
        return JSON;
    }
} // namespace JSON_Maker
