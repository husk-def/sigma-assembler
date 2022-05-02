#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"
#include "list.h"

#define MAX_ADDR 256

/*
 *  for saving addresses of labels
 */
typedef struct {
    char    label[30];
    int     addr;
} label_addr_t;

/*
 *	for saving addresses of vars
 */
typedef struct {
	char	var[30];
	int		addr;
} var_addr_t;

/*
 *  for error checking
 */
typedef enum {
    ALL_OK = 0,
    UNEXPECTED_TYPE,
    REPEAT_LABEL,
	REPEAT_VARIABLE
} err_t;

int
syntax_analysis(node_t *root);

void
replace_labels(node_t *root);

int
parse(node_t *root, char* path);

int
eat(token_type_t type);

int
get_line_num();

char*
get_var_addr(char *var);

int
check_err(void);

int
binary_to_decimal(char*);

void
DEBUG_print(int val);

void Q(void);
void D(void);
void P(void);
void M(void);
void I(void);
void L(void);

#endif /* PARSER_H */
