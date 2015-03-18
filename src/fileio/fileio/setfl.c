#include "apue.h"
#include <fcntl.h>
#include <unistd.h>

void set_fl(int fd, int flags)
{                               /* flags are file status flags to turn on */
    int val;

    if ((val = fcntl(fd, F_GETFL, 0)) < 0)
        apue_print("fcntl F_GETFL error");

    printf("OPEN_MAX: %d\n", OPEN_MAX);
    val |= flags;               /* turn on flags */

    if (fcntl(fd, F_SETFL, val) < 0)
        apue_print("fcntl F_SETFL error");
}
