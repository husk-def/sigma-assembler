
#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 

void
export_add_trailing_newline(const char* path);


void
to_lower_case(char* input, int progsize);


void
export_lower_case(const char* input_path, const char* output_path);


void
export_uncommented(const char* path_in, const char* path_out);


/*static inline void
skip_until_c(char c, FILE *fp);*/


#endif /* PREPROCESSOR_H */