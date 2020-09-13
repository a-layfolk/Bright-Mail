#ifndef _TEST_H_
#define _TEST_H_
#include <string>
using namespace std;
namespace JSON_Maker
{
    namespace Key_Type
    {
        const char request_type[] = "request_type";

        const char command_type[] = "command_type";

        const char sql_username[] = "username";
        const char sql_password[] = "password";
        const char sql_phoneum[] = "phoneum";
        const char sql_emailType[] = "emailType";
        const char sql_userId[] = "userId";
        const char sql_emailTitle[] = "emailTitle";
        const char sql_emailContent[] = "emailContent";
        const char sql_emailTime[] = "emailTime";
        const char sql_attachedFilePath[] = "attachedFilePath";
        const char sql_targetUsername[] = "targetUsername";
        const char sql_targetId[] = "targetId";
        const char sql_ownerId[] = "ownerId";
        const char sql_contactname[] = "contactname";
        const char sql_newState[] = "newState";
    } // namespace Key_Type

    string Creat_Key(const char *key_name, const char *value, bool with_comma);
    string Creat_Key_int(const char *key_name, int value, bool with_comma);

    char *Creat_DataBag_Sign_in(char *username, char *password);
    char *Creat_DataBag_Sign_up(char *username, char *password, char *phoneum);
    char *Creat_DataBag_End_Connect();
} // namespace JSON_Maker

#endif