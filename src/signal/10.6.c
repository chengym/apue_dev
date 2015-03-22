#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <signal.h>

static volatile sig_atomic_t sigflag; /* set nonzero by sig handler */
static sigset_t newmask, oldmask, zeromask;

static void sig_usr(int signo)/* one signal handler for SIGUSR1 and SIGUSR2 */
{
    sigflag = 1;
}

void TELL_WAIT(void)
{
    if (signal(SIGUSR1, sig_usr) == SIG_ERR)
        perror("signal(SIGUSR1) error");
    if (signal(SIGUSR2, sig_usr) == SIG_ERR)
        perror("signal(SIGUSR2) error");
    sigemptyset(&zeromask);
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGUSR1);
    sigaddset(&newmask, SIGUSR2);

    /*
     * Block SIGUSR1 and SIGUSR2, and save current signal mask.
     */
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
        perror("SIG_BLOCK error");
}

void TELL_PARENT(pid_t pid)
{
    kill(pid, SIGUSR2);/* tell parent we're done */
}

void WAIT_PARENT(void)
{
    while (sigflag == 0)
        sigsuspend(&zeromask);/* and wait for parent */
    sigflag = 0;

    /*
     * Reset signal mask to original value.
     */
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
        perror("SIG_SETMASK error");
}

void TELL_CHILD(pid_t pid)
{
    kill(pid, SIGUSR1);/* tell child we're done */
}

void WAIT_CHILD(void)
{
    while (sigflag == 0)
        sigsuspend(&zeromask);/* and wait for child */
    sigflag = 0;

    /*
     * Reset signal mask to original value.
     */
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
        perror("SIG_SETMASK error");
}

int main()
{
    pid_t child_pid;
    int   fd;

    fd = open("./foo", O_RDWR | O_CREAT, 00644);
    if (-1 == fd)
        perror("./foo");

    child_pid = fork();
    if (0 > child_pid) {
        perror("fork");
    }

    if (0 == child_pid) {
        /* child */
        sleep(2);
        for (;;) {
            sleep(1);
            TELL_WAIT();
            TELL_PARENT(getppid());
            WAIT_PARENT();
            printf("this is child pid = %ld\n", getppid());
        }
    } else {
        /* parent */
        for (;;) {
            TELL_WAIT();
            WAIT_CHILD();
            printf("this is parent pid = %ld\n", getppid());
            TELL_CHILD(child_pid);
        }
    }
}


