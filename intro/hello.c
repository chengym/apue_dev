#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
    pid_t pid;

    pid = vfork();
    if (0 == pid) { 
        printf("this is child PID - %ld\n", (long)getpid());
        return 0;
    }

    printf("this is parent PID - %ld and child PID - %ld\n",
            (long) getpid(), (long)pid);
    exit(0);
}
