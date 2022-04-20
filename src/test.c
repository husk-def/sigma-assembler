
#include "files.h"
#include "list.h"
#include "token.h"
#include "preprocessor.h"

int
main(void)
{
    /* variables */
    char            word[21];
    int             check;
    FILE*           fp;
        /* points to the beginning of a list, should not be changed! */
    node_t*         ls_begin = init_list();          
    node_t*         node;
    node_t*         pnode;
        /* hardcoded path, todo change this */
        /* use command line arguments for input and output */
    const char*     path = "./example/e1.assembly";
    const char*     lower_path = "./example/e1_lower.assembly";
    const char*     lower_uncomment_path = "./example/e1_lower_uncomment.assembly";

    node = ls_begin;
    
    /* implementation */

    export_add_trailing_newline(path);

    export_lower_case(path, lower_path);

    export_uncommented(lower_path, lower_uncomment_path);


    fp = fopen(lower_uncomment_path, "r");

        /* leaves an extra token at the end */
    while ((check = fscanf(fp, " %s", word)) > 0) {
        printf(".%s.\n", word);
        strcpy(node->val.value, word);
		node->val.type = get_token_type(node->val.value);
        pnode = node;
        node = list_expand(node);
    }
        /* remove that extra token */
    deinit_list_from(&node);
    //free(node);
    pnode->next = NULL;

    node = ls_begin;

    printf("\n\nprint token info part\n\n");
    while(node != NULL) {
        print_token_info(node->val);
        node = get_next(node);
    }

    deinit_list_from(&ls_begin);
    fclose(fp);
    exit(0);
}
