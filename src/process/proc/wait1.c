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
    pid_t pid;
    int status;

    if ((pid = fork()) < 0) {
        perror("fork");
        return -1;
    } else if (pid == 0) {
        /* child */
        exit(7);
    }

    if (wait(&status) != pid) {
        /* wait for child */
        perror("wait");
        return -1;
    }
    pr_exit(status);            

    if ((pid = fork()) < 0) {
        perror("fork");
        return -1;
    } else if (pid == 0) {
        /* child */
        /* generates SIGABRT */
        abort();                
    }

    if (wait(&status) != pid) {
        /* wait for child */
        perror("wait");
        return -1;
    }
    pr_exit(status);

    if ((pid = fork()) < 0) {
        perror("fork");
        return -1;
    } else if (pid == 0) {
        /* child */
        status /= 0;            /* divide by 0 generates SIGFPE */
    }

    if (wait(&status) != pid) {
        /* wait for child */
        perror("wait");
        return -1;
    }
    pr_exit(status);

    exit(0);
}
