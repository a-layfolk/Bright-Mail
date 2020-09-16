#include "SqlCon.h"
#include "mysql/mysql.h"
#include <cstring>
#include <stdio.h>

#pragma comment(lib, "libmysql.lib")



void mysql::De_EMAIL_INFO(EMAIL_INFO *ptr)
{
	delete ptr->emailId;
	delete ptr->emailTime;
	delete ptr->emailTitle;
	delete ptr->targetUsername;
}

void mysql::De_CONTACT_INFO(DataBag::CONTATCT_INFO *ptr)
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
	emailInfo->emailContent = mycpy(row[1]);
	emailInfo->emailTitle = mycpy(row[0]);
	emailInfo->emailType = mycpy(row[2]);
	delete[] query;
	return emailInfo;
}

void mysql::De_EMAIL_CONTENT(EMAIL_CONTENT *ptr)
{

	delete[] ptr;
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
	cout << "2" << endl;
	contactId = get_user_id(phonenum);
	cout << "3" << endl;
	if (contactId != "false")
	{
		cout << "4" << endl;
		char *query = new char[100];
		sprintf(query, "insert into ContactTable(userId,contactId) values(%s,%s);", userId, contactId);
		cout << "5" << endl;
		mysql_query(con, query);
		cout << "6" << endl;
		delete[] query;
		cout << "7" << endl;
		delete[] contactId;
		return true;
	}
	else
	{
		delete[] contactId;
		cout << "8" << endl;
		return false;
	}
	delete[] contactId;
	cout << "9" << endl;
	return true;
}

bool mysql::Delete_contatc_info(const char *userId, const char *contactname, const char *phonenum)
{
	char *contactId = NULL;
	contactId = get_user_id(phonenum);
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

	filePath = mycpy(row[0]);

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