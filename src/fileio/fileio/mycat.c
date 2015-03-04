#include "apue.h"

#define	BUFFSIZE	4096

int main(void)
{
    int n;
    char buf[BUFFSIZE];

    while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
        if (write(STDOUT_FILENO, buf, n) != n)
            apue_print("write error");

    if (n < 0)
        apue_print("read error");

    exit(0);
}
