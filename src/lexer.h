#ifndef LEXER_H
#define LEXER_H

#include "list.h"
#include <stdlib.h>
#include <math.h>

int
lexical_analysis(const char* path, node_t* ls_begin);

/*
 * decimal to binary string
 */
int
dtobs(char* value);


int
htod(char* value);


int
htobs(char* value);


int
btod(char* value);


int
btobs(char* value);


int
convert_literals(node_t* begin);

#endif /* LEXER_H */
