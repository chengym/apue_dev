#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int i;
    char **ptr;
    extern char **environ;

    /* echo all command-line args */
    for (i = 0; i < argc; i++) {
        printf("argv[%d]: %s\n", i, argv[i]);
    }

    /* and all env strings */
    for (ptr = environ; *ptr != 0; ptr++) {
        printf("%s\n", *ptr);
    }

    return 0;
}
