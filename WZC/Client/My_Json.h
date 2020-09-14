#ifndef MY_JSON
#define MY_JSON
#include <string>
#include <string.h>
#include <iostream>
#include <stdio.h>
using namespace std;
namespace My_Json
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
    namespace Rq_Type
    {
        const char command[] = "command";
        const char sign_in[] = "sign_in";
        const char sign_up[] = "sign_up";
        // const char [] = "";
        // const char [] = "";
        // const char [] = "";

    } // namespace Rq_Type

    string Creat_Key(const char *key_name, const char *value, bool with_comma);

    string Creat_Key_int(const char *key_name, int value, bool with_comma);

} // namespace My_Json
namespace Data_Bag
{
    using namespace My_Json;
    char *DataBag_Sign_in(const char *username, const char *password);
    char *DataBag_Sign_up(const char *username, const char *password, const char *phoneum);

    char *DataBag_Exit();
    char *Data_Bag_Success();
    char *Data_Bag_Error(const char *error_info);
} // namespace Data_Bag
#endif