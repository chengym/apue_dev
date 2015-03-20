#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

/*
 *      getpid();
 *      getppid();
 *
 *      fork();
 *      vfork();
 *
 *      wait();
 *      waitpid();
 *      waitid();
 *      wait3();
 *      wait4();
 *
 *      execl();
 *      execv();
 *      execle();
 *      execve();
 *      execlp();
 *      execvp();
 *
 * */
int globvar = 6;
char buf[] = "a write to stdout\n";

int main(void)
{
    int var;
    pid_t pid;

    var = 88;
    if (write(STDOUT_FILENO, buf, sizeof(buf) - 1) != sizeof(buf) - 1) {
        perror("write");
        return -1;
    }

    printf("before fork\n");
    if ((pid = fork()) < 0) {
        perror("fork error");
        return -1;
    } else if (pid == 0) {
        /* child */
        globvar++;
        var++;
    } else {
        /* parents */
        sleep(1);
    }

    printf("pid = %ld, glob = %d, var = %d\n", (long) getpid(), globvar, var);
    exit(0);
}
