
#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void
to_lower_case(char* input, int progsize);


void
export_lower_case(const char* input, const char* path, int progsize);


void
export_uncommented(const char* path_in, const char* path_out);


#endif /* PREPROCESSOR_H */