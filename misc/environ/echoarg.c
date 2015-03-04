#include "apue.h"

int main(int argc, char *argv[], char *argp[])
{
    int i;

    for (i = 0; i < argc; i++)  /* echo all command-line args */
        printf("argv[%d]: %s\n", i, argv[i]);
    for (i = 0; i < 10; i++)  /* echo all command-line args */
    printf("argp[%d]: %s\n", i, argp[i]);
    exit(0);
}
