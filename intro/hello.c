#include "apue.h"

int main(void)
{
    pid_t pid;

    pid = fork();
    if (0 == pid) { 
        APUE_DEBUG_E("hello world from child process ID %ld\n", (long) getpid());
        exit(0);
    }
    APUE_DEBUG_E("hello world from parents %d child process ID %ld\n", (long) getpid(), pid);
    exit(0);
}
