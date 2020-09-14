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
        const char sd_mail[] = "sd_mail";
        const char sd_file[] = "sd_file";
        const char sd_list[] = "sd_list";
        const char sd_contact[] = "sd_contact";
        const char rq_mail[] = "rc_mail";
        const char rq_file[] = "rc_file";
        const char rq_contact[] = "rc_contact";
        const char rq_list[] = "rc_list";

    } // namespace Rq_Type

    string Creat_Key(const char *key_name, const char *value, bool with_comma);

    string Creat_Key_int(const char *key_name, const char *value, bool with_comma);

} // namespace My_Json
namespace DataBag
{
    char *DataBag_Sign_in(const char *username, const char *password);
    char *DataBag_Sign_up(const char *username, const char *password, const char *phoneum);

    char *DataBag_Exit();
    char *DataBag_Success();
    char *DataBag_Error(const char *error_info);

    char *DataBag_Sd_Mail(const char *ownerId, const char *targetId, const char *email_type, const char *email_title, const char *email_content);
    char *DataBa_Sd_File(const char *ownerId, const char *emailId, const char *fileName);

    //需要做一个可以制造JSON列表的函数
    char *DataBag_Sd_Contact(const char *userId, const char *contactname, const char *phonenum);

    //需要做一个可以制造JSON列表的函数
    char *DataBag_Sd_List(const char *emailTitle, const char *targetUsername, const char *emailTime, const char *emailId);

    char *DataBag_Rq_Mail(const char *emailId, const char *ownerId);

    //先查mailId对应的文件数和文件名，再通过文件名来接收文件
    char *DataBag_Rq_File(const char *ownerId, const char *emailId, const char *fileName);

    char *DataBag_Rq_Contact(const char *userId);
    char *DataBag_Rq_List(const char *userId, const char *emailType);

    //写制作数组的
} // namespace DataBag
#endif