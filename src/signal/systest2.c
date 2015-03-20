#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#include <stdio.h>
#include <stdlib.h>


static void sig_int(int signo)
{
    printf("caught SIGINT\n");
}

static void sig_chld(int signo)
{
    printf("caught SIGCHLD\n");
}

int main(void)
{
    if (signal(SIGINT, sig_int) == SIG_ERR)
        perror("signal(SIGINT) error");
    if (signal(SIGCHLD, sig_chld) == SIG_ERR)
        perror("signal(SIGCHLD) error");
    if (system("/bin/ed") < 0)
        perror("system() error");
    exit(0);
}
