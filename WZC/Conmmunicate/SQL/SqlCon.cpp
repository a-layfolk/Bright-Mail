#include "SqlCon.h"
#include "mysql/mysql.h"
#include <stdio.h>
#pragma comment(lib, "libmysql.lib")

MYSQL *con = mysql_init(NULL);

char *mysql::get_user_id(const char *username, const char *phonenum)
{
	char *query = new char[100];
	char *userId = NULL;
	MYSQL_RES *res = NULL;
	MYSQL_ROW row = NULL;
	unsigned int numFields = 0;
	sprintf(query, "select * from UserTable where userName='%s' and  telephone= '%s'", username, phonenum);
	if (!mysql_query(con, query))
	{
		res = mysql_store_result(con);
		row = mysql_fetch_row(res);
		numFields = mysql_num_fields(res);
	}
	else
	{
		printf("MySQL query error : %s\n", mysql_error(con));
		userId = (char *)"false";
	}
	return userId;
}

char *mysql::get_time()
{
	char *query = new char[100];
	char *time;
	MYSQL_RES *res = NULL;
	MYSQL_ROW row = NULL;
	sprintf(query, "select now();");
	if (!mysql_query(con, query))
	{
		res = mysql_store_result(con);
		row = mysql_fetch_row(res);
		time = row[1];
	}
	else
	{
		printf("MySQL query error : %s\n", mysql_error(con));
		time = NULL;
	}
	return time;
}

char *mysql::get_user_name(const char *userId)
{
	char *query = new char[100];
	char *username;
	MYSQL_RES *res = NULL;
	MYSQL_ROW row = NULL;
	sprintf(query, "select userName from UserTable where userId=%s;", userId);
	if (!mysql_query(con, query))
	{
		res = mysql_store_result(con);
		row = mysql_fetch_row(res);
		username = row[1];
	}
	else
	{
		printf("MySQL query error : %s\n", mysql_error(con));
		username = NULL;
	}
	return username;
}

void mysql::connect(const char *ip, const char *username, const char *password, const char *db, const int port)
{
	mysql_init(con);
	if (!mysql_real_connect(con, ip, username, password, db, port, NULL, 0))
	{
		printf("MySQL connect error : %s\n", mysql_error(con)); //需要加上这个，因为这个是操作失败时返回显示
		getchar();
		exit(1);
	}
	else
	{
		cout << "connect okk" << endl;
	}
}

bool mysql::sign_in(const char *username, const char *password)
{
	char *query = new char[100];
	MYSQL_RES *res = NULL;
	MYSQL_ROW row = NULL;

	sprintf(query, "select * from UserTable where userName='%s' and  password= '%s'", username, password);
	mysql_query(con, query);
	res = mysql_store_result(con);

	if (!(row = mysql_fetch_row(res)))
	{
		printf("login error : %s\n", mysql_error(con)); //需要加上这个，因为这个是操作失败时返回显示
		// getchar();
		return false;
	}
	else
	{
		cout << "login okk" << endl;
		return true;
	}
}

bool mysql::sign_up(const char *username, const char *password, const char *phoneum)
{
	char *query = new char[100];
	sprintf(query, "insert into UserTable(userName,password,telephone) values('%s','%s','%s');", username, password, phoneum);
	if (mysql_query(con, query))
	{

		printf("sign-up error : %s\n", mysql_error(con));
		return false;
	}
	else
	{

		printf("sign u okkk\n");
		return true;
	}
}

/*
*/
EMAIL_INFO *mysql::get_email_info(const char *userId, const char *emailType)
{
	EMAIL_INFO *emailInfo = new EMAIL_INFO[200];
	char *query = new char[500];
	char *targetUserName = NULL;
	sprintf(query, "select emailTitle,targetUserId,emailTime,emailId from EmailTable where ownerId=%s and emailType='%s';", userId, emailType);
	MYSQL_RES *res = NULL;
	MYSQL_ROW row = NULL;
	unsigned int numFields = 0;
	if (mysql_query(con, query))
	{
		printf("get_email_info error : %s\n", mysql_error(con));
	}
	else
	{
		res = mysql_store_result(con);

		//Debug打印数据集内容
		int i = 0;
		while ((row = mysql_fetch_row(res)) != NULL)
		{
			emailInfo[i].emailId = row[3];
			emailInfo[i].emailTitle = row[0];
			emailInfo[i].emailTime = row[2];
			emailInfo[i].targetUsername = get_user_name(row[1]);
		}
	}
	return emailInfo;
}

CONTACT_INFO *mysql::get_contact_info(const char *userId)
{
	CONTACT_INFO *contactInfo = new CONTACT_INFO[200];

	char *query = new char[500];
	sprintf(query, "select contactId from ContactTable where userId=%s ;", userId);
	MYSQL_RES *res = NULL;
	MYSQL_ROW row = NULL;
	if (mysql_query(con, query))
	{
		printf("select_contact_id error : %s\n", mysql_error(con));
	}
	else
	{
		res = mysql_store_result(con);
		//Debug打印数据集内容
		while ((row = mysql_fetch_row(res)) != NULL)
		{

			MYSQL_RES *res_1 = NULL;
			MYSQL_ROW row_1 = NULL;
			unsigned int numFields_1 = 0;
			sprintf(query, "select userId,UserName,telephone from UserTable where userId=%s ;", row[0]);

			if (mysql_query(con, query))
			{
				printf("select_contact_info error : %s\n", mysql_error(con));
			}
			else
			{
				res_1 = mysql_store_result(con);
				int j = 0;
				while ((row_1 = mysql_fetch_row(res_1)) != NULL)
				{
					contactInfo[j].userId = row_1[0];
					contactInfo[j].userName = row_1[2];
					contactInfo[j].telephone = row_1[3];
				}
			}
		}
	}
	return contactInfo;
}

EMAIL_CONTENT *mysql::get_one_email(const char *emailId, const char *ownerId)
{
	EMAIL_CONTENT *emailContent;
	char *query = new char[500];
	MYSQL_RES *res = NULL;
	MYSQL_ROW row = NULL;
	unsigned int numFields_1 = 0;
	sprintf(query, "select  emailTitle, emailContent, emailType, targetUsername, emailTime, attachedFilePath  from EmailTable where emailId=%s and ownerId=%s ;", emailId, ownerId);

	if (mysql_query(con, query))
	{
		printf("select_contact_info error : %s\n", mysql_error(con));
	}
	else
	{
		res = mysql_store_result(con);
		while ((row = mysql_fetch_row(res)) != NULL)
		{
			emailContent->emailTitle = row[0];
			emailContent->emailContent = row[1];
			emailContent->emailType = row[2];
			emailContent->targetUsername = row[3];
			emailContent->emailTime = row[4];
			emailContent->attachedFilePath = row[5];
		}
	}
	return emailContent;
}

void mysql::add_email_to_db(const char *ownerId, const char *targetId, const char *email_type, const char *email_title, const char *email_content)
{
	char *query = new char[2048];
	sprintf(query, "insert into EmailTable(ownerId,TargetUserId,emailTitle,emailType,emailContent)values(%s,%s,'%s','%s','%s');", ownerId, targetId, email_title, email_type, email_content);
	if (mysql_query(con, query))
	{

		printf("insert error : %s\n", mysql_error(con));
	}
	else
	{

		printf("insert email okkk okkk\n");
	}
}

bool mysql::change_email_content(const char *emailId, const char *ownerId, const char *targetId, const char *emailType, const char *emailTitle, const char *emailContent, const char *attachedFilePath)
{
	char *query = new char[200];
	char *nowtime = get_time();
	sprintf(query, "update EmailTable set emailTitle=%s,emailContent='%s',TargetUserId=%s,emailTime='%s' ,attachedFilePath=%s,where emailId=%s;", emailTitle, emailContent, targetId, nowtime, attachedFilePath, emailId);
	if (mysql_query(con, query))
	{

		printf("change email content error: %s\n", mysql_error(con));
		return false;
	}
	return true;
}

bool mysql::change_email_state(const char *emailId, const char *newType)
{

	char *query = new char[200];
	char *nowtime = get_time();
	sprintf(query, "update EmailTable set emailType='%s',emailTime='%s' where emailId=%s;", newType, nowtime, emailId);
	if (mysql_query(con, query))
	{

		printf("change email type : %s\n", mysql_error(con));
		return false;
	}
	else
	{

		return true;
	}
}

bool mysql::add_contact_info(const char *userId, const char *contactname, const char *phonenum)
{
	char *contactId = NULL;
	contactId = get_user_id(contactname, phonenum);
	if (contactId != "false")
	{
		char *query = new char[100];
		sprintf(query, "insert into ContactTable(userId,contactId) values(%s,%s);", userId, contactId);

		if (mysql_query(con, query))
		{

			printf("add contact user error : %s\n", mysql_error(con));
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		printf("不存在该用户\n");
		return false;
	}
}

bool mysql::delete_contatc_info(const char *userId, const char *contactname, const char *phonenum)
{
	char *contactId = NULL;
	contactId = get_user_id(contactname, phonenum);
	if (contactId != "false")
	{
		char *query = new char[100];
		sprintf(query, "delete from ContactTable where userId=%s and contactId=%s;", userId, contactId);

		if (mysql_query(con, query))
		{

			printf("delete contact user error : %s\n", mysql_error(con));
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		printf("不存在该用户\n");
		return false;
	}
}

void mysql::close()
{

	mysql_close(con);
}