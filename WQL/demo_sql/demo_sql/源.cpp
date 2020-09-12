
#include"iostream"
#include"SqlCon.h"
using namespace std;
int main() {
	
	mysql mysql;
	mysql.connect("123.57.176.139", "root", "1233", "Email_schema", 3306);
	mysql.sign_in("Mike", "12345");
	mysql.close();
	
	
	
	
}