#include "Communi_Core.hpp"
#include <iostream>
int main(int argc, char const *argv[])
{
    CLIENT::Client_Core CC("0.0.0.0");
    char user_name[20] = "fuck";
    char password[20] = "mother";
    for (int i = 0; i < 5; i++)
    {
        std::cout << "input username:" << std::endl;
        std::cin >> user_name;
        std::cout << "input password:" << std::endl;
        std::cin >> password;
        std::cout << CC.Sign_in(user_name, password) << std::endl;
    }

    return 0;
}
