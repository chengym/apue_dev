#include "apue.h"
#include <dirent.h>

int main(int argc, char *argv[])
{
    DIR *dp;
    struct dirent *dirp;

    if (argc != 2) {
        apue_print("usage: ls directory_name");
        exit(-1);
    }

    if ((dp = opendir(argv[1])) == NULL)
        apue_print("can't open %s", argv[1]);
    while ((dirp = readdir(dp)) != NULL)
        apue_print("%s\n", dirp->d_name);

    closedir(dp);
    exit(0);
}
