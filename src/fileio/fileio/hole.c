#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#define	FILE_MODE	(S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main(void)
{
    int fd;
    struct stat buf;

    if ((fd = creat("file.hole", FILE_MODE)) < 0)
        perror("creat error");

    if (write(fd, buf1, 10) != 10)
        perror("buf1 write error");

    if (lseek(fd, 16384, SEEK_SET) == -1)
        perror("lseek error");

    if (write(fd, buf2, 10) != 10)
        perror("buf2 write error");

    if (0 != fstat(fd, &buf)) {
        perror("fstat");
    }

    printf("buf.st_size 0x%x\n", buf.st_size);

    exit(0);
}
