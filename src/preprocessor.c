#include "preprocessor.h"

void
to_lower_case(char* input, int progsize)
{
    int     i = 0;
    while (input[i] != 0) {
        if (i >= progsize) {
            printf("bug in to_lower_case, i >= progsize, continue.\n");
        }
        input[i] = tolower(input[i]);
        ++i;
    }
}


void
export_lower_case(const char* input, const char* path, int progsize)
{
    FILE    *fp;
    /* create a new file */
    fp = fopen(path, "w");
    fwrite(input, sizeof(char), progsize, fp);
    fclose(fp);
}


void
export_uncommented(const char* path_in, const char* path_out)
{
    FILE    *fp_in, *fp_out;

    fp_in = fopen(path_in, "r");
    fp_out = fopen(path_out, "w");


    fclose(fp_in);
    fclose(fp_out);
}

