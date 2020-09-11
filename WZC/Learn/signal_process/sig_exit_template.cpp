#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void process_quit_sig(int sig)
{
    printf("\nquit app\n");
    exit(0);
}
int main(int argc, char const *argv[])
{
    signal(SIGINT, process_quit_sig);

    while (1)
    {
        sleep(1);
    }

    return 0;
}
