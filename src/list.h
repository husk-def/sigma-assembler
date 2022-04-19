#ifndef LIST_H
#define LIST_H

#include "token.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct node_t {
    token_t         val;
    struct node_t*  next;
} node_t;


node_t*
init_list(void);


void
deinit_list_from(node_t** where_to_start);


node_t*
get_next(node_t* current);


node_t*
list_seek_end(node_t* current);


node_t*
list_expand(node_t* current);





#endif /* LIST_H */