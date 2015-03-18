#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#define OPEN_MAX 256

void set_fl(int fd, int flags)
{                               /* flags are file status flags to turn on */
    int val;

    if ((val = fcntl(fd, F_GETFL, 0)) < 0)
        printf("fcntl F_GETFL error");

    printf("OPEN_MAX: %d\n", OPEN_MAX);
    val |= flags;               /* turn on flags */

    if (fcntl(fd, F_SETFL, val) < 0)
        printf("fcntl F_SETFL error");
}
