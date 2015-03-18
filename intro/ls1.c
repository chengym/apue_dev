#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_NAME_SZ 2048
static uint32_t num = 0;
static int IS_DIR(const char *path)
{
    struct stat st;
    lstat(path, &st);
    return S_ISDIR(st.st_mode);
}

/* recurrence a dir and list the common file */
static void _walk_for_dir(const char *path)
{
    DIR             *pdir = NULL;
    struct dirent   *pdirent = NULL;
    char temp[MAX_NAME_SZ] = {0};

    pdir = opendir(path);
    if (!pdir) {
        perror("opendir");
        goto end;
    }

    while (NULL != (pdirent = readdir(pdir))) {
        if (0 == strcmp(pdirent->d_name, ".") ||
                0 == strcmp(pdirent->d_name, "..")) {
            continue;
        }

        if ('/' != *(path + strlen(path) - 1)) {
            strcat((char *) path, "/");
        }
        sprintf(temp, "%s%s", path, pdirent->d_name);

        if (IS_DIR(temp)) {
            _walk_for_dir(temp);
        } else {
            num++;
            printf(" %s\n", temp);
        }
    }

end:
    closedir(pdir);
    return;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("usage: ls directory_name");
        return -1;
    }

    _walk_for_dir(argv[1]);

    printf("====== file num: %d\n", num);
    return 0;
}
