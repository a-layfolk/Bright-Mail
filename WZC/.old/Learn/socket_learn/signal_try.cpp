#include <signal.h>
#include <stdio.h>
#include <unistd.h>
void ouch(int sig)
{
    printf("OUCH! -l got signal %d\n", sig);
    signal(SIGINT, SIG_DFL);
}
int main(int argc, char const *argv[])
{
    signal(SIGINT, ouch);
    while (1)
    {
        printf("hello world\n");
        sleep(1);
    }
    return 0;
}
