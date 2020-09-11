#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
int main(int argc, char const *argv[])
{
    pid_t pid, pid2;
    const char *message;
    int n;
    printf("fork program staring\n");
    pid = fork();
    switch (pid)
    {
    case -1:
        perror("fork failed");
        exit(1);
        break;
    case 0: //子进程运行区域
        message = "This is the child";
        for (int i = 0; i < 3; i++)
        {
            printf("fuck you\n");
            sleep(1);
        }
        n = 5;
        pid2 = fork();
        std::cout << "pid2:" << pid2 << std::endl;
        for (int i = 0; i < 3; i++)
        {
            sleep(1);
            std::cout << "pid2" << std::endl;
        }

        break;
    default:
        int status;
        puts(message);
        wait(&status);
        message = "This is the parent ";
        puts(message);
        printf("%d", status);
        n = 3;
        break;
    }
    // for (; n > 0; n--)
    // {
    //     puts(message);
    //     sleep(1);
    // }

    return 0;
}
