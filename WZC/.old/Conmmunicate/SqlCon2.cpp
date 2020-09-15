#include "SqlCon2.h"
#include "mysql/mysql.h"
#include <cstring>
#include <stdio.h>

#pragma comment(lib, "libmysql.lib")

MYSQL *con = mysql_init(NULL);

char *mysql::get_user_id(const char *username, const char *phonenum)
{
	char *query = new char[100];
	char *userId = new char[100];
	MYSQL_RES *res;
	MYSQL_ROW row;

	sprintf(query, "select userId from UserTable where userName='%s' and  telephone= '%s'", username, phonenum);
	mysql_query(con, query);

	res = mysql_store_result(con);
	row = mysql_fetch_row(res);

	userId = row[0];

	delete[] query;
	return userId;
}

char *mysql::get_time()
{
	char *query = new char[100];
	char *time = new char[30];
	MYSQL_RES *res = NULL;
	MYSQL_ROW row = NULL;
	sprintf(query, "select now();");
	mysql_query(con, query);

	res = mysql_store_result(con);
	row = mysql_fetch_row(res);
	time = row[0];

	delete[] query;
	return time;
}

char *mysql::get_user_name(const char *userId)
{
	char *query = new char[100];
	char *username;
	MYSQL_RES *res = NULL;
	MYSQL_ROW row = NULL;
	sprintf(query, "select userName from UserTable where userId=%s;", userId);
	mysql_query(con, query);

	res = mysql_store_result(con);
	row = mysql_fetch_row(res);
	username = row[0];

	delete[] query;
	return username;
}

void mysql::connect(const char *ip, const char *username, const char *password, const char *db, const int port)
{
	mysql_init(con);
	if (!mysql_real_connect(con, ip, username, password, db, port, NULL, 0))
	{
		printf("MySQL connect error : %s\n", mysql_error(con));
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
		delete[] query;
		return false;
	}
	else
	{
		delete[] query;
		return true;
	}
}

bool mysql::sign_up(const char *username, const char *password, const char *phoneum)
{
	char *query = new char[100];
	sprintf(query, "insert into UserTable(userName,password,telephone) values('%s','%s','%s');", username, password, phoneum);
	mysql_query(con, query);
	delete[] query;
	return true;
}

/*
*/
EMAIL_INFO *mysql::get_email_info(const char *userId, const char *emailType, int *num)
{
	EMAIL_INFO *emailInfo = new EMAIL_INFO[200];
	char *query = new char[200];
	sprintf(query, "select emailTitle,TargetUserId,emailTime,emailId from EmailTable where ownerId=%s and emailType='%s';", userId, emailType);
	MYSQL_RES *res;
	MYSQL_ROW row;
	mysql_query(con, query);
	res = mysql_store_result(con);

	int i = 0;
	while ((row = mysql_fetch_row(res)) != NULL)
	{

		emailInfo[i].emailId = row[3];
		emailInfo[i].emailTitle = row[0];
		emailInfo[i].emailTime = row[2];
		emailInfo[i].targetUsername = get_user_name(row[1]);

		i++;
	}
	if (i)
		*num = i + 1;
	else
		*num = 0;

	delete[] query;
	return emailInfo;
}

void mysql::De_EMAIL_INFO(EMAIL_INFO *ptr)
{

	delete ptr;
}

CONTACT_INFO *mysql::get_contact_info(const char *userId, int *num)
{
	CONTACT_INFO *contactInfo = new CONTACT_INFO[200];
	char *query = new char[500];
	sprintf(query, "select contactId from ContactTable where userId= %s ;", userId);
	MYSQL_RES *res;
	MYSQL_ROW row;
	mysql_query(con, query);
	res = mysql_store_result(con);
	int j = 0;
	while ((row = mysql_fetch_row(res)) != NULL)
	{

		MYSQL_RES *res_1;
		MYSQL_ROW row_1;
		sprintf(query, "select userId,UserName,telephone from UserTable where userId=%s ;", row[0]);
		mysql_query(con, query);
		res_1 = mysql_store_result(con);

		while ((row_1 = mysql_fetch_row(res_1)) != NULL)
		{
			contactInfo[j].userId = row_1[0];
			contactInfo[j].userName = row_1[1];
			contactInfo[j].telephone = row_1[2];
			j++;
		}
		if (j)
			*num = j;
		else
			*num = 0;
	}
	delete[] query;

	return contactInfo;
}

void mysql::De_CONTACT_INFO(CONTACT_INFO *ptr)
{

	delete[] ptr;
}

EMAIL_CONTENT *mysql::get_one_email(const char *emailId, const char *ownerId)
{

	char *query = new char[300];
	MYSQL_ROW row;
	EMAIL_CONTENT *emailInfo = new EMAIL_CONTENT[1];
	sprintf(query, "select  emailTitle, emailContent, emailType from EmailTable where emailId= %s ;", emailId);
	mysql_query(con, query);

	MYSQL_RES *res = mysql_store_result(con);
	row = mysql_fetch_row(res);
	int num = mysql_num_fields(res);
	emailInfo->emailContent = row[1];
	emailInfo->emailTitle = row[0];
	emailInfo->emailType = row[2];
	delete[] query;
	return emailInfo;
}

void mysql::De_EMAIL_CONTENT(EMAIL_CONTENT *ptr)
{

	delete[] ptr;
}

char *mysql::add_email_to_db(const char *ownerId, const char *targetId, const char *email_type, const char *email_title, const char *email_content)
{
	MYSQL_RES *res;
	MYSQL_ROW row;
	char *query = new char[2048];
	char *time = mysql::get_time();
	sprintf(query, "insert into EmailTable(ownerId,TargetUserId,emailTitle,emailType,emailContent,emailTime)values(%s,%s,'%s','%s','%s','%s');", ownerId, targetId, email_title, email_type, email_content, time);
	mysql_query(con, query);
	sprintf(query, "select emailId from EmailTable where emailTime='%s';", time);
	mysql_query(con, query);
	res = mysql_store_result(con);
	row = mysql_fetch_row(res);
	//	delete[] time;
	delete[] query;
	return row[0];
}

bool mysql::change_email_content(const char *emailId, const char *ownerId, const char *targetId, const char *emailType, const char *emailTitle, const char *emailContent)
{
	char *query = new char[200];
	char *nowtime = get_time();
	sprintf(query, "update EmailTable set emailTitle='%s',emailContent='%s',TargetUserId=%s,emailTime='%s' where emailId=%s;", emailTitle, emailContent, targetId, nowtime, emailId);
	mysql_query(con, query);
	delete[] query;
	return true;
}

bool mysql::change_email_state(const char *emailId, const char *newType)
{

	char *query = new char[200];
	char *nowtime = get_time();
	sprintf(query, "update EmailTable set emailType='%s',emailTime='%s' where emailId=%s;", newType, nowtime, emailId);
	mysql_query(con, query);

	delete[] query;
	return true;
}

bool mysql::add_contact_info(const char *userId, const char *contactname, const char *phonenum)
{
	char *contactId = NULL;
	contactId = get_user_id(contactname, phonenum);

	if (contactId != "false")
	{
		char *query = new char[100];
		sprintf(query, "insert into ContactTable(userId,contactId) values(%s,%s);", userId, contactId);
		mysql_query(con, query);
		delete[] query;
		return true;
	}
	else
	{
		return false;
	}
	return true;
}

bool mysql::Delete_contatc_info(const char *userId, const char *contactname, const char *phonenum)
{
	char *contactId = NULL;
	contactId = get_user_id(contactname, phonenum);
	if (contactId != "false")
	{
		char *query = new char[100];
		sprintf(query, "delete from ContactTable where userId=%s and contactId=%s;", userId, contactId);

		mysql_query(con, query);
	
			delete[] query;
			return true;
		
	}
	else
	{
		return false;
	}
}
char *mysql::get_email_filepath(const char *emailId)
{
	char *filePath = new char[200];
	char *query = new char[500];
	MYSQL_RES *res = NULL;
	MYSQL_ROW row = NULL;

	sprintf(query, "select filePath  from EmailFilePath where emailId=%s;", emailId);

	mysql_query(con, query);

	res = mysql_store_result(con);
	row = mysql_fetch_row(res);

	filePath = row[0];

	delete[] query;
	return filePath;
}

void mysql::De_EMAIL_FILE_PATH(char *ptr)
{

	delete[] ptr;
}

bool mysql::alter_email_filepath(const char *emailId, char *filePath)
{
	char *query = new char[500];
	MYSQL_RES *res = NULL;
	MYSQL_ROW row = NULL;
	sprintf(query, "delete  from EmailFilePath where emailId=%s;", emailId);

	mysql_query(con, query);

	sprintf(query, "insert into EmailFilePath (emailId,filePath) values(%s,'%s');", emailId, filePath);
	mysql_query(con, query);

	delete[] query;
	return true;
}

void mysql::close()
{

	mysql_close(con);
}