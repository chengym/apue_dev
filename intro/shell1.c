#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>

#define	MAXLINE	4096

int main(void)
{
    char buf[MAXLINE];
    pid_t pid;
    int status;

    printf("%% ");
    while (fgets(buf, MAXLINE, stdin) != NULL) {
        if (buf[strlen(buf) - 1] == '\n')
            buf[strlen(buf) - 1] = 0;

        if ((pid = fork()) < 0) {
            printf("fork: %s\n", strerror(errno));
        } else if (pid == 0) {
            if (-1 == execlp(buf, buf, (char*)0)) {
                printf("execlp: %s\n", strerror(errno));
            }
            exit(127);
        }

        printf("%% ");
        /* parent */
        if ((pid = waitpid(pid, &status, 0)) < 0) {
            printf("waitpid: %s\n", strerror(errno));
        }
    }

    exit(0);
}
