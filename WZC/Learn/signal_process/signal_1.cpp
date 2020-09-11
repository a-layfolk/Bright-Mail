#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
//SIGINT - 中断信号
//SIGKILL - 杀死信号
void fuck(int sig)
{
    printf("fuck %d\n", sig);
}
void ouch(int sig)
{
    //接受Ctrl+C后函数会跳转到这里
    printf("OUCH! –I got signal %d\n", sig);
    // signal(SIGINT, SIG_DFL);//第二次接受SIGINT的时候使程序停止
    signal(SIGINT, SIG_DFL); //第二次接受SIGINT的时候使程序停止 接受到sig之前会一直停在这里？或者说sig只能被注册一次
}
int main(int argc, char const *argv[])
{
    //使用signal相当于告诉程序,以后接收到这个信号后要跳转到ouch(一个handler函数)
    signal(SIGINT, ouch); //接受到SIGINT(中断信号)后，跳转到ouch//然后立即执行完函数内语句
    signal(SIGALRM, fuck);
    while (1)
    {
        printf("hello\n");
        sleep(1);
        alarm(1);
    }

    // signal(SIGINT, ouch);
    return 0;
}
