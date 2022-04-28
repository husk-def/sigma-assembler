
#include "lexer.h"


int
lexical_analysis(const char* path, node_t* ls_begin)
{
    FILE*   fp;
    int     check;
    char    word[30];
    node_t* node;

    node = ls_begin;

    if ((fp = fopen(path, "r")) == NULL) {
        return 1;
    }
    while ((check = fscanf(fp, " %s", word)) > 0) {
        //printf(".%s.\n", word);
        strcpy(node->val.value, word);
		node->val.type = get_token_type(node->val.value);
        node = list_expand(node);
    }
    /* add an extra END node */
    node->val.type = T_END;

    fclose(fp);
    return 0;
}
