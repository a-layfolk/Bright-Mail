#include "Dependencies/SqlCon.h"
#include "mysql/mysql.h"
#include <stdio.h>
#include <string.h>
#include "My_Json.h"
#pragma comment(lib, "libmysql.lib")

MYSQL *con = mysql_init(NULL);
using namespace DataBag;
char *mysql::get_user_id(const char *phonenum)
{
	char *value = new char[200];
	strcpy(value, "user_id");
	return value;
}

char *mysql::get_time()
{

	char *value = new char[200];
	strcpy(value, "time");
	return value;
}

char *mysql::get_user_name(const char *userId)
{

	char *value = new char[200];
	strcpy(value, "user_name");
	return value;
}

void mysql::connect(const char *ip, const char *username, const char *password, const char *db, const int port)
{
}

bool mysql::sign_in(const char *username, const char *password)
{
	if (strcmp(username, "pass") == 0 || strcmp(password, "pass") == 0)
	{
		return true;
	}
	return false;
}

bool mysql::sign_up(const char *username, const char *password, const char *phoneum)
{
	if (strcmp(username, "pass") == 0 || strcmp(password, "pass") == 0)
	{
		return true;
	}
	return false;
}

/*
*/

//email info size?
EMAIL_INFO *mysql::get_email_info(const char *userId, const char *emailType, int *num)
{
	*num = 2;
	EMAIL_INFO *emailInfo = new EMAIL_INFO[2];
	for (int i = 0; i < 2; i++)
	{
		emailInfo[i].emailId = NULL;
		emailInfo[i].emailTime = NULL;
		emailInfo[i].emailTime = NULL;
		emailInfo[i].targetUsername = NULL;
	}

	return emailInfo;
}

DataBag::CONTATCT_INFO *mysql::get_contact_info(const char *userId, int *num)
{
	*num = 2;
	DataBag::CONTATCT_INFO *contactInfo = new DataBag::CONTATCT_INFO[2];
	for (int i = 0; i < 2; i++)
	{
		contactInfo[i].telephone = NULL;
		contactInfo[i].userId = NULL;
		contactInfo[i].userName = NULL;
	}

	return contactInfo;
}

EMAIL_CONTENT *mysql::get_one_email(const char *emailId, const char *ownerId)
{
	EMAIL_CONTENT *EC = new EMAIL_CONTENT;
	EC->targetUsername = NULL;
	EC->emailType = NULL;
	EC->emailTitle = NULL;
	EC->emailTime = NULL;
	EC->emailContent = NULL;
	return EC;
}

//判断呢？

//返回emailId
char *mysql::add_email_to_db(const char *ownerId, const char *targetId, const char *email_type, const char *email_title, const char *email_content)
{
	char *E_id = new char[10];
	strcpy(E_id, "1111");
	return E_id;
}

bool mysql::change_email_content(const char *emailId, const char *ownerId, const char *targetId, const char *emailType, const char *emailTitle, const char *emailContent)
{
	return true;
}

bool mysql::change_email_state(const char *emailId, const char *newType)
{

	if ((strcmp(emailId, "pass") == 0 || strcmp(newType, "pass") == 0))
	{
		return true;
	}
	return false;
}

bool mysql::add_contact_info(const char *userId, const char *contactname, const char *phonenum)
{
	return true;
}

bool mysql::Delete_contatc_info(const char *userId, const char *contactname, const char *phonenum)
{
	return true;
}
// EMAIL_FILE_PATH *mysql::get_email_filepath(const char *emailId, int *num)
// {
// 	*num = 1;
// 	EMAIL_FILE_PATH *filePath = new EMAIL_FILE_PATH[200];
// 	strcpy(filePath[0].filePath, "filePath");
// 	return filePath;
// }
//????这是做什么的？删除文件？
// bool mysql::alter_email_filepath(const char *emailId, EMAIL_FILE_PATH *filePath, int *num)
// {
// 	return true;
// }

void mysql::close()
{
}