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
 * deinitializes list nodes starting from where_to_start
 */
void
deinit_list_from(node_t* where_to_start)
{
    node_t* temp1;
    node_t* temp2;
    temp1 = where_to_start;
    do {
        temp2 = temp1->next;
        free(temp1);
        temp1 = temp2;
    } while (temp2->next != NULL);
    free(temp2);
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
    while (temp->next != NULL) {
        temp = temp->next;
    }
    return temp;
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

