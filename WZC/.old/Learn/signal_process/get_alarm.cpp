#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void al(int sig)
{
    printf("I was alarmed!!\n");
}

int main(int argc, char const *argv[])
{
    //使用signal相当于告诉程序,以后接收到这个信号后要跳转到ouch(一个handler函数)
    signal(SIGALRM, al);
    while (1)
    {
        // printf("hello\n");
        // alarm(1);
        sleep(1);
    }
    return 0;
}