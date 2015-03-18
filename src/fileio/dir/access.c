#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("usage: a.out <pathname>\n");
        return -1;
    }

    if (access(argv[1], R_OK) < 0)
        perror("access");
    else
        printf("read access OK\n");

    if (open(argv[1], O_RDONLY) < 0)
        perror("open");
    else
        printf("open for reading OK\n");

    exit(0);
}
