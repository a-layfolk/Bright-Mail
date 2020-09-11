#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
int main(int argc, char const *argv[])
{
    char *fp = new char(30);
    std::cout << "input file path:" << std::endl;
    std::cin >> fp;

    int file=open(fp, O_RDONLY);

    char *buffer = new char(100);
    read(file, buffer, sizeof(buffer));

    
    
    std::cout << buffer;

    return 0;
}
