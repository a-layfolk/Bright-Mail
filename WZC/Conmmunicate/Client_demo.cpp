#include "Communi_Core.hpp"
#include <iostream>
#include <string.h>
int main(int argc, char const *argv[])
{
    CLIENT::Client_Core CC("123.57.176.139");
    // CLIENT::Client_Core CC;
    // CLIENT::Client_Core CC("0.0.0.0");
    const char *request = argv[1];
    if (argv[1] == NULL)
    {
        request = "sign_in";
    }

    char user_name[20];
    char password[20];
    char telephone[20];
    int rt_val = -1;
    // CC.Send_Exit();
    // return 0;
    std::cout << "input username:" << std::endl;
    std::cin >> user_name;
    std::cout << "input password:" << std::endl;
    std::cin >> password;
    if (strcmp(request, "sign_in") == 0)
    {
        rt_val = CC.Sign_in(user_name, password);
    }
    else if (strcmp(request, "sign_up") == 0)
    {
        std::cout << "input telephone:" << std::endl;
        std::cin >> telephone;
        rt_val = CC.Sign_up(user_name, password, telephone);
    }
    if (rt_val < 0)
    {
        cout << "login fail" << endl;
    }
    else
    {
        cout << "login success" << endl;
    }
    CC.Send_Exit();
    return 0;
}
