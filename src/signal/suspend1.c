#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#include <stdio.h>
#include <stdlib.h>

#include <errno.h>

/*
 * sigsuspend的整个原子操作过程为：
 * (1) 设置新的mask阻塞当前进程；
 * (2) 收到信号，恢复原先mask；
 * (3) 调用该进程设置的信号处理函数；
 * (4) 待信号处理函数返回后，sigsuspend返回。
 */

static void sig_int(int);

static void pr_mask(const char *str)
{
    sigset_t sigset;
    int errno_save;

    errno_save = errno;         /* we can be called by signal handlers */
    if (sigprocmask(0, NULL, &sigset) < 0) {
        perror("sigprocmask error");
    } else {
        printf("%s", str);
        if (sigismember(&sigset, SIGINT))
            printf(" SIGINT");
        if (sigismember(&sigset, SIGQUIT))
            printf(" SIGQUIT");
        if (sigismember(&sigset, SIGUSR1))
            printf(" SIGUSR1");
        if (sigismember(&sigset, SIGALRM))
            printf(" SIGALRM");

        /* remaining signals can go here  */

        printf("\n");
    }

    errno = errno_save;         /* restore errno */
}

int main(void)
{
    sigset_t newmask, oldmask, waitmask;

    pr_mask("program start: ");

    if (signal(SIGINT, sig_int) == SIG_ERR)
        perror("signal(SIGINT) error");
    sigemptyset(&waitmask);
    sigaddset(&waitmask, SIGUSR1);
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGINT);

    /*
     * Block SIGINT and save current signal mask.
     */
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
        perror("SIG_BLOCK error");

    /*
     * Critical region of code.
     */
    pr_mask("in critical region: ");

    /*
     * Pause, allowing all signals except SIGUSR1.
     */
    if (sigsuspend(&waitmask) != -1)
        perror("sigsuspend error");

    pr_mask("after return from sigsuspend: ");

    /*
     * Reset signal mask which unblocks SIGINT.
     */
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
        perror("SIG_SETMASK error");

    /*
     * And continue processing ...
     */
    pr_mask("program exit: ");

    exit(0);
}

static void sig_int(int signo)
{
    pr_mask("\nin sig_int: ");
}
