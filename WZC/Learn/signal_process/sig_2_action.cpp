#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
void ouch(int sig)
{
    printf("OUCH ! – I got signal % d\n", sig);
    switch (sig)
    {
    case 14:
        printf("you get alarmed\n");
        break;
    case 2:
        printf("you will stop process!\n");
        exit(0);
        break;
    default:
        break;
    }
}
int main()
{
    struct sigaction act; //sigaction相当于可以自定义传入的信号，把自定义的信号（封装在sa_flags）中，传入ouch函数中
    act.sa_handler = ouch;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 2; //可以自己传这个的值
    sigaction(SIGINT, &act, 0);

    struct sigaction act2;
    act2.sa_handler = ouch;
    act2.sa_flags = 17;
    sigaction(SIGALRM, &act2, 0);
    while (1)
    {
        printf("Hello World !\n");
        sleep(1);
        alarm(1);
    }
}