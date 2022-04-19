
#include "files.h"
#include "list.h"
#include "token.h"
#include "preprocessor.h"

int
main(void)
{
    /* variables */
    int             i;
    int             progsize;
    char*           program;
    char            word[21];
    int             check;
    FILE*           fp;
        /* points to the beginning of a list, should not be changed! */
    node_t*         ls_begin = init_list();          
    node_t*         node;
        /* hardcoded path, todo change this */
    const char*     path = "/home/rtrk/Documents/ra211-2019-assembler/sigma-assembler/example/e1.assembly";
    const char*     lower_path = "/home/rtrk/Documents/ra211-2019-assembler/sigma-assembler/example/e1_lower.assembly";

    node = ls_begin;
    
    /* implementation */
    progsize = get_file_size(path);
    printf("progsize = %d\n", progsize);

    program = (char*)malloc((progsize + 1) * sizeof(char));
    get_program(path, program, progsize);
    printf("program\n%s\n", program);

    to_lower_case(program, progsize);
    printf("program_lowercase =\n%s\n", program);

    export_lower_case(program, lower_path, progsize);

    node_t *pnode = node;

    fp = fopen(lower_path, "r");

        /* leaves an extra token at the end */
    while ((check = fscanf(fp, " %s", word)) > 0) {
        printf(".%s.\n", word);
        strcpy(node->val.value, word);
		node->val.type = get_token_type(node->val.value);
        pnode = node;
        node = list_expand(node);
    }
        /* remove that extra token */
    //deinit_list_from(&node);
    free(node);
    pnode->next = NULL;

    node = ls_begin;

    printf("\n\nprint token info part\n\n");
    while(node != NULL) {
        if (node != list_seek_end(ls_begin)) {
            print_token_info(node->val);
            node = get_next(node);
        } else {
            break;
        }
    }

    deinit_list_from(&ls_begin);
    fclose(fp);
    exit(0);
}
