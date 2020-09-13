#include <sstream>
#include <iostream>
int main(int argc, char const *argv[])
{
    int read_len = 0;

    std::string *str = new std::string;
    char buffer[20];
    for (int i = 0; i < 5; i++)
    {
        std::cin >> buffer;
        *str += buffer;
    }

    char *JSON = new char[(*str).size()];
    str->copy(JSON, (*str).size(), 0);
    delete str;
    std::cout << JSON << std::endl;
    return 0;
}
