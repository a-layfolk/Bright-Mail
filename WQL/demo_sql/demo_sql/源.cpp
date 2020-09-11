
#include"iostream"
#include"SqlCon.h"
using namespace std;
int main() {
	
	mysql mysql;
	mysql.connect("123.57.176.139", "root", "1233", "Email_schema", 3306);
	//mysql.sign_in("Mike", "12345");
	//mysql.get_user_id("join", "110");
	//mysql.sign_up("Maria", "111", "120");
	//mysql.get_email_info(1, "receive_read");
	//mysql.get_contact_info(1);
	//mysql.get_one_email(1, 1);
	//mysql.add_email_to_db(1, 2, "third", "send","nothing special");
	mysql.close();
	
	
	
	
}