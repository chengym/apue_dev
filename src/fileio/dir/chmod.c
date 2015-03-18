#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include <sys/stat.h>

int main(void)
{
    struct stat statbuf;

    /* turn on set-group-ID and turn off group-execute */

    if (stat("foo", &statbuf) < 0)
        perror("stat error for foo");

    printf("foo, before st_mode: 0x%x\n", statbuf.st_mode);
    if (chmod("foo", (statbuf.st_mode & ~S_IXGRP) | S_ISGID) < 0)
        perror("chmod error for foo");

    printf("foo, after st_mode: 0x%x\n", statbuf.st_mode);

    /* set absolute mode to "rw-r--r--" */
    if (stat("bar", &statbuf) < 0)
        perror("stat error for foo");
    printf("bar, before st_mode: 0x%x\n", statbuf.st_mode);

    if (chmod("bar", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) < 0)
        perror("chmod error for bar");

    printf("bar, after st_mode: 0x%x\n", statbuf.st_mode);

    exit(0);
}
