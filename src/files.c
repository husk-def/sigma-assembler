#include "files.h"

int get_file_size(const char *path)
{
    struct stat st;
    stat(path, &st);
    return st.st_size;
}

int get_program(const char *path, char *ret, int retsize)
{
    FILE    *fp;
    int     ie;
    fp = fopen(path, "r");
    if (fp == NULL) {
        ie = 0;
    } else {
        /* should read a whole file */
        if (fread(ret, retsize, sizeof(char), fp) != retsize) {
            /* error */
            ie = -1;
        } else {
            ie = retsize;
        }
    }
    return ie;
}


