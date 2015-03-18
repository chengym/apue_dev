#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

static void pr_exit(int status)
{
    if (WIFEXITED(status))
        printf("normal termination, exit status = %d\n", WEXITSTATUS(status));
    else if (WIFSIGNALED(status))
        printf("abnormal termination, signal number = %d%s\n", WTERMSIG(status),
#ifdef	WCOREDUMP
               WCOREDUMP(status) ? " (core file generated)" : "");
#else
               "");
#endif
    else if (WIFSTOPPED(status))
        printf("child stopped, signal number = %d\n", WSTOPSIG(status));
}

int main(void)
{
    int status;

    if ((status = system("date")) < 0)
        perror("system()");

    pr_exit(status);

    if ((status = system("nosuchcommand")) < 0)
        perror("system()");

    pr_exit(status);

    if ((status = system("who; exit 44")) < 0)
        perror("system()");

    pr_exit(status);

    exit(0);
}
