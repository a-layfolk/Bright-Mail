#include "Communi_Core.hpp"
#include <iostream>
int main(int argc, char const *argv[])
{
    CLIENT::Client_Core CC;
    char user_name[20] = "fuck";
    char password[20] = "mother";
    do
    {
        std::cout << "input username:" << std::endl;
        std::cin >> user_name;
        std::cout << "input password:" << std::endl;
        std::cin >> password;
    } while (CC.Sign_in(user_name, password) != -1);

    return 0;
}
