#ifndef FILES_H
#define FILES_H

#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

int get_file_size(const char *path);

int get_program(const char *path, char *ret, int retsize);

#endif /* FILES_H */
