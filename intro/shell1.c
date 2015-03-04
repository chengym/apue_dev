#include "apue.h"
#include <sys/wait.h>

int main(void)
{
    char buf[MAXLINE];          /* from apue.h */
    pid_t pid;
    int status;

    printf("%% ");              /* print prompt (printf requires %% to print %) */
    while (fgets(buf, MAXLINE, stdin) != NULL) {
        if (buf[strlen(buf) - 1] == '\n')
            buf[strlen(buf) - 1] = 0;   /* replace newline with null */

        if ((pid = fork()) < 0) {
            apue_print("fork error");
        } else if (pid == 0) {  /* child */
            execlp(buf, buf, (char *) 0);
            apue_print("couldn't execute: %s", buf);
            exit(127);
        }

        /* parent */
        if ((pid = waitpid(pid, &status, 0)) < 0)
            apue_print("waitpid error");
        printf("%% ");
    }
    exit(0);
}
