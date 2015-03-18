#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
    if (chdir("/tmp") < 0)
        perror("chdir failed");
    printf("chdir to /tmp succeeded\n");
    exit(0);
}
