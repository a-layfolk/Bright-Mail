#include "Communi_Core.hpp"
#include <iostream>
int main(int argc, char const *argv[])
{
    CLIENT::Client_Core CC("0.0.0.0");
    char user_name[20];
    char password[20];

    std::cout << "input username:" << std::endl;
    std::cin >> user_name;
    std::cout << "input password:" << std::endl;
    std::cin >> password;
    cout << user_name << '\n'
         << password << endl;
    int val = CC.Sign_in(user_name, password);
    if (val < 0)
    {
        cout << "login false" << endl;
    }
    else
    {
        cout << "login true" << endl;
    }

    return 0;
}
