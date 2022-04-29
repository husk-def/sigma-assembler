#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include "token.h"
#include "list.h"
#include <string.h>

#define MAX_ADDR 256

/*
 *  for saving adresses of labels
 */
typedef struct {
    char    label[10];
    int     addr;
} label_addr_t;

/*
 *  for error checking
 */
typedef enum {
    ALL_OK = 0,
    UNEXPECTED_TYPE,
    REPEAT_LABEL,
    UNEXPECTED_EOF
} err_t;

int
syntax_analysis(node_t *root);

void
replace_labels(node_t *root);

int
eat(token_type_t type);

int
check_err();

void
DEBUG_print(int val);

void Q(void);
void D(void);
void P(void);
void M(void);
void I(void);
void L(void);

#endif /* PARSER_H */
