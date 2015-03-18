#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    pid_t pid;

    if ((pid = fork()) < 0) {
        perror("fork");
        return -1;
    } else if ( 0 == pid) {
        /* child */
        if (execl("/home/sar/bin/testinterp",
                  "testinterp", "myarg1", "MY ARG2", (char *) 0) < 0)
            perror("execl");
    }

    if (waitpid(pid, NULL, 0) < 0) {
        perror("waitpid");
    }

    exit(0);
}
