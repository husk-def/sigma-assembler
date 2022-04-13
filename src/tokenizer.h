
#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    END_OF_STRING,
    INVALID,
    BUFFER_OVERFLOW,
    FINE
    /* todo continue */
} err_t;

/* 
 * source - string to read from
 * where - index of starting character
 * ret - containing found word (should be at least 20 characters)
 */
int
get_word(const char *source, int where, char *ret, int sourcesize);


#endif /* TOKENIZER_H */
