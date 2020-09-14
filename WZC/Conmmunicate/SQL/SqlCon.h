#ifndef SQLCON_H
#define SQLCON_H
#include <string>
#include <iostream>
#include "mysql/mysql.h"
#pragma comment(lib, "libmysql.lib")
using namespace std;

typedef struct EMAIL_INFO
{
	char *emailTitle;
	char *targetUsername;
	char *emailTime;
	char *emailId;
} EMAIL_INFO;

typedef struct CONTATCT_INFO
{
	char *userId;
	char *userName;
	char *telephone;

} CONTACT_INFO;

typedef struct EMAIL_FILE_PATH
{

	char *filePath;

} EMAIL_FILE_PATH;

typedef struct EMAIL_CONTENT
{
	char *emailTitle;
	char *emailContent;
	char *emailType;
	char *targetUsername;
	char *emailTime;

} EMAIL_CONTENT;

class mysql
{

public:
	/*
	通过 用户名 及 电话 获取用户ID
	返回 用户ID(char*)
	*/
	char *get_user_id(const char *username, const char *phonenum);
	char *get_time();
	char *get_user_name(const char *userId);

	/*
	数据库连接
	参数：ip,username,psw,db,port
	*/
	void connect(const char *ip, const char *username, const char *password, const char *db, const int port);

	/*
	用户登录
	返回布尔值，成功为true,失败为false
	*/
	bool sign_in(const char *username, const char *password);

	/*
	用户注册
	返回布尔值，成功为true，失败为false
	*/
	bool sign_up(const char *username, const char *password, const char *phoneum);

	/*
	相关邮件信息预加载
	 返回  标题，发件人，时间
	*/
	EMAIL_INFO *get_email_info(const char *userId, const char *emailType);
	/*
	好友信息预加载
	返回好友用户名，好友电话
	*/
	CONTACT_INFO *get_contact_info(const char *userId);
	/*
	数据库内邮件具体信息获得
	返回 所有信息
	*/
	EMAIL_CONTENT *get_one_email(const char *emailId, const char *ownerId);

	/*
	发送邮件操作
	返回布尔值 成功返回ture,失败返回false
	*/
	void add_email_to_db(const char *ownerId, const char *targetId, const char *email_type, const char *email_title, const char *email_content);

	/*
	修改原有邮件
	*/
	bool change_email_content(const char *emailId, const char *ownerId, const char *targetId, const char *emailType, const char *emailTitle, const char *emailContent, const char *attachedFilePath);

	/*
	改变邮件状态
	返回布尔值 成功true 失败false
	*/
	bool change_email_state(const char *emailId, const char *newState);

	/*
	增加好友
	返回布尔值 成功返回true，失败返回false
	*/
	bool add_contact_info(const char *userId, const char *contactname, const char *phonenum);

	/*
	删除好友
	返回布尔值 成功返回true，失败返回false
	*/
	bool delete_contatc_info(const char *userId, const char *contactname, const char *phonenum);
	/*
	获得邮件附件路径
	*/
	EMAIL_FILE_PATH * get_email_filepath(const char*emailId,int * num);
	/*
	删除邮件路径,先查找以前的，若存在则删除，再直接添加
	*/
	bool alter_email_filepath(const char*emailId,EMAIL_FILE_PATH *filePath,int * num);

	void close();
};

#endif // !SQLCON_H
