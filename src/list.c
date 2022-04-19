#include "list.h"


/*
 * initializes list
 */
node_t*
init_list(void)
{
    node_t* new;
    new = (node_t*)malloc(1 * sizeof(node_t));
    new->next = NULL;
    return new;
}

/*
 * deinitializes list nodes starting from where_to_start excluding where_to_start
 */
void
deinit_list_from(node_t** where_to_start)
{
    node_t* temp1;
    /*if (temp1 == (node_t*)NULL) {
        return;
    } else {
        temp2 = *temp1;
        free(temp1);
        deinit_list_from(temp2.next);
    }*/
    while (*where_to_start != NULL) {
        temp1 = *where_to_start;
        *where_to_start = (*where_to_start)->next;
        temp1->next = NULL;
        free(temp1);
    }
    
}

/*
 * returns next node in line
 */
node_t*
get_next(node_t* current)
{
    if (current->next == NULL) {
        printf("list: cant go further - next = NULL\n");
    }
    return current->next;
}

/*
 * seeks end of list
 */
node_t*
list_seek_end(node_t* current)
{
    node_t* temp = current;
    node_t* tprev;
    while (temp != NULL) {
        tprev = temp;
        temp = temp->next;
    }
    return tprev;
}

/*
 * returns new node
 */
node_t*
list_expand(node_t* current)
{
    node_t* new;
    node_t* temp = list_seek_end(current);
    new = (node_t*)malloc(1 * sizeof(node_t));
    temp->next = new;
    new->next = NULL;
    return new;
}

