#include "apue.h"
#include <fcntl.h>

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main(void)
{
    int fd;

    if ((fd = creat("file.hole", FILE_MODE)) < 0)
        apue_print("creat error");

    if (write(fd, buf1, 10) != 10)
        apue_print("buf1 write error");
    /* offset now = 10 */

    if (lseek(fd, 16384, SEEK_SET) == -1)
        apue_print("lseek error");
    /* offset now = 16384 */

    if (write(fd, buf2, 10) != 10)
        apue_print("buf2 write error");
    /* offset now = 16394 */

    exit(0);
}
