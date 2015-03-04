#include "apue.h"

int main(void)
{
    pid_t pid;

    pid = fork();
    if (0 == pid) { 
        apue_print("this is child PID - %ld\n", (long)getpid());
        exit(0);
    }

    apue_print("this is parent PID - %ld and child PID - %ld\n",
            (long) getpid(), (long)pid);
    exit(0);
}
