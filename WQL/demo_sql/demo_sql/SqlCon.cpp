#include "SqlCon.h"
#include "mysql.h"
#include<stdio.h>
#pragma comment(lib,"libmysql.lib")
MYSQL* con = mysql_init(NULL);

const char* mysql::get_user_id(const char* username, const char* phonenum)
{
	char* query = new char[100];
	char* user_id;
	MYSQL_RES* res = NULL;
	MYSQL_ROW row = NULL;
	unsigned int 	numFields = 0;
	sprintf_s(query, sizeof(char) * 100, "select * from UserTable where userName='%s' and  telephone= '%s'", username, phonenum);
	if (!mysql_query(con, query)) {
		res = mysql_store_result(con);
		row = mysql_fetch_row(res);
		numFields = mysql_num_fields(res);
		for (int i = 0; i < numFields; i++) {
			printf("%s\n", row[i]);
		}
	}
	else {
		printf("MySQL query error : %s\n", mysql_error(con));
		exit(1);
	}
	return "helo";
	return nullptr;
}

void mysql::connect(const char* ip, const char* username, const char* password, const char* db, const int port)
{
	mysql_init(con);
	if (!mysql_real_connect(con, ip, username, password, db, port, NULL, 0)) {
		printf("MySQL connect error : %s\n", mysql_error(con));  //需要加上这个，因为这个是操作失败时返回显示
		getchar();
		exit(1);
	}
	else {
		cout << "connect okk" << endl;
	}
}






bool mysql::sign_in(const char* username, const char* password)
{
	char* query = new char[100];
	MYSQL_RES* res = NULL;
	MYSQL_ROW row = NULL;
	
	sprintf_s(query, sizeof(char) * 100, "select * from UserTable where userName='%s' and  password= '%s'", username, password);
	mysql_query(con, query);
	res = mysql_store_result( con);

	if (!(row=mysql_fetch_row(res))) {
		printf("login error : %s\n", mysql_error(con));  //需要加上这个，因为这个是操作失败时返回显示
		getchar();
		return false;
	}
	else {
		cout << "login okk" << endl;
		return true;
	}
	
}

bool mysql::sign_up(const char* username, const char* password, const char* phoneum)
{
	char* query = new char[100];
	sprintf_s(query, sizeof(char) * 100, "insert into UserTable(userName,password,telephone) values('%s','%s','%s');", username, password, phoneum);
	if (mysql_query(con, query)) {
	
		printf("sign-up error : %s\n", mysql_error(con));
		return false;
	}
	else {

		printf("sign u okkk\n");
		return true;
	}

	
}

/*

*/
MYSQL_RES*   mysql::get_email_info(const int userId, const char* emailType)
{
	char* query = new char[500];
	sprintf_s(query, sizeof(char) * 500, "select emailId,emailTitle,emailState,emailTime from EmailTable where ownerId=%d and emailType='%s';",userId, emailType);
	MYSQL_RES* res = NULL;
	MYSQL_ROW row = NULL;
	unsigned int 	numFields = 0;

	if (mysql_query(con, query)) {
		printf("get_email_info error : %s\n", mysql_error(con));
		exit(1);
	}
	else {
		res = mysql_store_result(con);

		//Debug打印数据集内容
		while ((row = mysql_fetch_row(res)) != NULL) {
			numFields = mysql_num_fields(res);
			for (int i = 0; i < numFields; i++) {
				printf("%s\n", row[i]);
			}
		}
	
		return res;

	}
	
}
CONTACT_INFO* contact_info = new CONTACT_INFO[200];

void mysql::get_contact_info(const int userId)
{
	
	char* query = new char[500];
	sprintf_s(query, sizeof(char) * 500, "select contactId from ContactTable where userId=%d ;", userId);
	MYSQL_RES* res = NULL;
	MYSQL_ROW row = NULL;
	unsigned int 	numFields = 0;

	if (mysql_query(con, query)) {
		printf("select_contact_id error : %s\n", mysql_error(con));
		exit(1);
	}
	else {
		res = mysql_store_result(con);
		//Debug打印数据集内容
		numFields = mysql_num_fields(res);
		while ((row = mysql_fetch_row(res)) != NULL) {
			
			
			for (int i = 0; i < numFields; i++) {
				MYSQL_RES* res_1 = NULL;
				MYSQL_ROW row_1 = NULL;
				unsigned int 	numFields_1 = 0;
				sprintf_s(query, sizeof(char) * 500, "select userId,UserName,telephone from UserTable where userId=%s ;", row[i]);

				if (mysql_query(con, query)) {
					printf("select_contact_info error : %s\n", mysql_error(con));
					exit(1);
				}
				else {
					res_1 = mysql_store_result(con);
					
				
					int j = 1;
					while ((row_1 = mysql_fetch_row(res_1)) != NULL) {
						numFields_1 = mysql_num_fields(res_1);
						for (int i = 0; i < numFields_1; i++) {
							printf("%s  ", row_1[i]);
						
							//Debug打印数据集内容
						}
						printf("\n");
					}
				}
			}
			
		}

	}

}

void mysql::get_one_email(const int emailId,const int ownerId)
{
	char* query = new char[500];
	MYSQL_RES* res= NULL;
	MYSQL_ROW row = NULL;
	unsigned int 	numFields_1 = 0;
	sprintf_s(query, sizeof(char) * 500, "select * from EmailTable where emailId=%d and ownerId=%d ;", emailId,ownerId);

	if (mysql_query(con, query)) {
		printf("select_contact_info error : %s\n", mysql_error(con));
		exit(1);
	}
	else {
		res = mysql_store_result(con);

		//Debug打印数据集内容
		while ((row = mysql_fetch_row(res)) != NULL) {
			numFields_1 = mysql_num_fields(res);
			for (int i = 0; i < numFields_1; i++) {
				printf("%s  ", row[i]);

			}
			printf("\n");
		}
	}
}

void mysql::add_email_to_db(const int ownerId, const int targetId, const char* email_type,const char* email_title, const char* email_content)
{
	char* query = new char[2048];
	sprintf_s(query, sizeof(char) * 2048, "insert into EmailTable(ownerId,TargetUserId,emailTitle,emailType,emailContent)values(%d,%d,'%s','%s','%s');", ownerId, targetId, email_title,email_type,email_content);
	if (mysql_query(con, query)) {

		printf("insert error : %s\n", mysql_error(con));
		
	}
	else {

		printf("insert email okkk okkk\n");
		
	}

}


void mysql::close()
{
	
	mysql_close(con);
}
