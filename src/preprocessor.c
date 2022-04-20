#include "preprocessor.h"
#include "files.h"

static inline void
skip_until_c(char c, FILE *fp)
{
    while (fgetc(fp) != c) {}
}


void
export_add_trailing_newline(const char* path)
{
    FILE    *fp;
    fp = fopen(path, "r+");
    fseek(fp, 0, SEEK_END);
    fputc('\n', fp);
    fclose(fp);
}


void
to_lower_case(char* input, int progsize)
{
    int     i = 0;
    while (input[i] != 0) {
        if (i >= progsize) {
            //printf("bug in to_lower_case, i >= progsize, continue. =%c;\n", input[i]);
            break;
        }
        input[i] = tolower(input[i]);
        //printf("%c\n", input[i]);
        ++i;
    }
}


void
export_lower_case(const char* input_path, const char* output_path)
{
    FILE    *fp_in;
    FILE    *fp_out;
    int     input_file_size;
    char    *temp;

    fp_in = fopen(input_path, "r");
    fp_out = fopen(output_path, "w");

    input_file_size = get_file_size(input_path);

    /* create temporary memory to hold a program */
    temp = (char*)malloc(input_file_size * sizeof(char));

    fread(temp, input_file_size, sizeof(char), fp_in);
    to_lower_case(temp, input_file_size);
    fwrite(temp, sizeof(char), input_file_size, fp_out);
    //fputs()

    /* cleanup */
    fclose(fp_out);
    fclose(fp_in);
    free(temp);
}


void
export_uncommented(const char* path_in, const char* path_out)
{
    FILE    *fp_in;
    FILE    *fp_out;
    char    m;

    fp_in = fopen(path_in, "r");
    fp_out = fopen(path_out, "w");

    while ((m = fgetc(fp_in)) != EOF) {
        if (m == ';') {
            /* single line comment, ends with \n */
            skip_until_c('\n', fp_in);
            //printf("skip_until_\\n going\n");
        } else if (m == '[') {
            /* multiline comment - ends with ] */
            skip_until_c(']', fp_in);
            //printf("skip_unitl_] going\n");
        } else {
            /* important part of program */
            fputc(m, fp_out);
            //printf("important: %c\n", m);
        }
    }
    

    /* cleanup */
    fclose(fp_in);
    fclose(fp_out);
}




