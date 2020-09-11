#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#define BUFFERSIZE 100
int main(int argc, char const *argv[])
{
    //argv[1],argc[2]
    char file_path[100];
    // std::cout << "input file path" << std::endl;
    // std::cin >> file_path;

    FILE *fp, *out_file = NULL;

    fp = fopen(argv[1], "rb");

    out_file = fopen(argv[2], "wb+");

    if (fp == NULL || out_file == NULL)
    {
        std::cout << "ERROR" << std::endl;
    }

    unsigned char buffer[BUFFERSIZE];
    int len;

    //这样写完后生成的文件没有执行权限
    while ((len = fread(buffer, sizeof(unsigned char), BUFFERSIZE, fp)) != 0)
    {
        /* code */
        fwrite(buffer, sizeof(unsigned char), len, out_file);
    }

    fclose(fp);
    fclose(out_file);
    return 0;
}
