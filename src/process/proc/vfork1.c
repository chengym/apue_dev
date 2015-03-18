#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int globvar = 6;

int main(void)
{
    int var;
    pid_t pid;

    var = 88;
    printf("before vfork\n");
    if ((pid = vfork()) < 0) {
        perror("vfork");
        return -1;
    } else if (pid == 0) {
        /* child */
        globvar++;
        var++;
        exit(0);
    }

    /* parent continues here */
    printf("pid = %ld, glob = %d, var = %d\n", (long) getpid(), globvar, var);
    return 0;
}
