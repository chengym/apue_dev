#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/dir.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

static int IS_DIR(const char *path)
{
    struct stat st;
    lstat(path, &st);
    return S_ISDIR(st.st_mode);
}

static void _walk_for_each(const char *path,
        char(*file_path)[PATH_MAX], unsigned int *idx, bool type)
{
    char         temp[PATH_MAX] = {0};
    DIR             *pdir = NULL;
    struct dirent   *pdirent = NULL;

    pdir = opendir(path);
    if (!pdir) {
        printf("opendir error:%s\n", path);
        goto end;
    }

    while (NULL != (pdirent = readdir(pdir))) {
        if (0 == strcmp(pdirent->d_name, ".") ||
                0 == strcmp(pdirent->d_name, "..")) {
            continue;
        }

        if ('/' != *(path + strlen(path) - 1)) {
            strcat((char*)path, "/");
        }
        sprintf(temp, "%s%s", path, pdirent->d_name);

        if (IS_DIR(temp)) {
            _walk_for_each(temp, file_path, idx, type ? true : false);
        } else {
            /* XXX user could specified his own filter rules */
            if (type == true) {
                memset(file_path + (*idx), 0, PATH_MAX);
                memcpy(file_path + (*idx), temp, strlen(temp));
            }
            (*idx)++;
        }
    }

end:
    if (!pdir)
        closedir(pdir);
    return;
}

static bool _walk_dir(char *dir_path,
        char(*file_path)[PATH_MAX], unsigned int * num, bool type)
{
    char     path[PATH_MAX] = {0};
    char     parents[PATH_MAX] = {0};
    char     *p = NULL;
    unsigned int    i, index = 0;
    char *ret_ptr;
    int   ret_value;
    bool  ret = false;

    ret_ptr = getcwd(path, PATH_MAX);
    assert(NULL != ret_ptr);

    if (!dir_path) {
        printf("NULL dir path\n");
        goto _finish_walk_dir;
    }
    if ((!file_path && type) || (!num && false == type)) {
        printf("invalid useage\n");
        goto _finish_walk_dir;
    }

    if (!IS_DIR(dir_path)) {
        printf("dir_path = %s is not directory\n", dir_path);
        goto _finish_walk_dir;
    }

    if (0 == strcmp(dir_path, ".")) {
        dir_path = path;
    }
    if (0 == strcmp(dir_path, "..")) {
        strncpy(parents, path, strlen(path));
        p = strrchr(parents, '/');
        *p = '\0';
        dir_path = parents;
    }

    _walk_for_each(dir_path, file_path, &index, type);

    if (false == type) {
        *num = index;
    } else {
        for (i = 0; i < index; i++)
            printf("file_path[%d]\t= %s\n", i, (char *) (file_path + i));
    }

    ret = true;

_finish_walk_dir:
    ret_value = chdir(path);
    assert(0 != ret_value);

    return ret;
}

static bool _wkdir_get_file_num(char *dir_path, unsigned int *file_num)
{
    return _walk_dir(dir_path, NULL, file_num, false);
}

static bool _wkdir_get_file_path(char *dir_path, char (*file_path)[PATH_MAX])
{
    return _walk_dir(dir_path, file_path, NULL, true);
}

int main(int argc, char **argv)
{
    bool        ret;
    unsigned int    file_num = 0;
    char     (*mp)[PATH_MAX] = NULL;

    if (2 != argc) {
        printf("usage: walk_dir <pathname>\n");
        goto _finish;
    }

    ret = _wkdir_get_file_num(argv[1], &file_num);
    if (!ret) {
        printf("fail to get file num\n");
        goto _finish;
    }
    if (!file_num) {
        printf("NO file in your specified path\n");
        goto _finish;
    }

    printf("file_num = %d\n", file_num);
    mp = (char(*)[PATH_MAX]) malloc(PATH_MAX * file_num);
    if (!mp) {
        printf("out-of-memory\n");
        goto _finish;
    }
    ret = _wkdir_get_file_path(argv[1], mp);
    if (!ret) {
        printf("fail to get file path\n");
        goto _finish;
    }

    free(mp);
    return 0;

_finish:
    if (mp)
        free(mp);
    return -1;
}
