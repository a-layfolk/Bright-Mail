#ifndef SQLCON_H
#define SQLCON_H
#include<string>
#include<iostream>
#include<winsock2.h>
#include"mysql.h"
#pragma comment(lib,"libmysql.lib")
using namespace std;

typedef struct contact_info
{
	char* info[3];
}CONTACT_INFO;

class mysql
{

public:
	int* debug();
	//工具类
	const char* get_user_id(const char* username, const char* phonenum);

	//数据库连接
	void connect(const char* ip, const char* username, const char* password, const char* db, const int port);

	//用户登录与注册
	bool sign_in(const char* username, const char* password);
	
	
	bool sign_up(const char* username, const char* password,const char *phoneum);
	
	//相关信息预览
	
	MYSQL_RES* get_email_info(const int userId,const char* emailType);

	void get_contact_info(const int userId);
	
	void get_one_email(const int emailId,const int ownerId);
	
	//发送邮件操作
	void add_email_to_db(const int ownerId, const int targetId, const char* email_title, const char* email_content);

	
	
	void close();



};

#endif // !SQLCON_H

