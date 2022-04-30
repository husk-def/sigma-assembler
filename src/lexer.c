
#include "lexer.h"


// static inline int
// skip_until_c(char c, const char *what)
// {
//     int a = 0;
//     while (what[a++] != c) {}
//     return a;
// }


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


int
dtobs(char* value)
{
    int     val = atoi(value);
    int     th;
    int     i = 0x8000;
    int     cnt = 0;
    value[16] = 0;
    while (i) {
        th = (val & i) == i;
        i >>= 1;
        value[cnt++] = th + '0';
        printf("%d", th);  
    }
    return 1;
}


int
htod(char* value)
{
    int where = 1;
    int current_num;
    int sum = 0;
    int i = 0;
    /* go to the end of string */
    while (value[++where] != 0) {}
    where--;
    puts("");
    while (where >= 2) {
        current_num = (value[where] > '9') ? (10 + (value[where] - 'a')) : (value[where] - '0');
        sum += current_num << (i++ * 4);
        --where;
    }
    return sum;
}

/*
int
dtobs(char* value)
{
    int     val = atoi(value);
    int     th;
    int     i = 0x8000;
    int     cnt = 0;
    value[16] = 0;
    while (i) {
        th = (val & i) == i;
        i >>= 1;
        value[cnt++] = th + '0';
        printf("%d", th);  
    }
    return 1;
}*/

int
htobs(char* value)
{
    int val = htod(value);
    int     th;
    int     i = 0x8000;
    int     cnt = 0;
    value[16] = 0;
    while (i) {
        th = (val & i) == i;
        i >>= 1;
        value[cnt++] = th + '0';
        printf("%d", th);  
    }
    return 1;
}


int
convert_literals(node_t* begin)
{
    node_t* node = begin;
    while (node != NULL) {
        switch (node->val.type) {
            case T_LITERAL_DECIMAL:
                dtobs(node->val.value);
                break;
            case T_LITERAL_HEXADECIMAL:
                htobs(node->val.value);
                break;
            default:
                break;
        }
    }
}
