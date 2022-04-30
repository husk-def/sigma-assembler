
#include "lexer.h"
#include "token.h"

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
    int     i = 0x8000;             /* 16 bits */
    int     cnt = 0;
    value[16] = 0;
    while (i) {
        th = (val & i) == i;
        i >>= 1;
        value[cnt++] = th + '0';
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
    --where;
    /* go until 0x part */
    while (where >= 2) {
        current_num = (value[where] > '9') ? (10 + (value[where] - 'a')) : (value[where] - '0');
        sum += current_num << (i++ * 4);
        --where;
    }
    return sum;
}


int
htobs(char* value)
{
    int val = htod(value);
    int     th;
    int     i = 0x8000;             /* 16 bits */
    int     cnt = 0;
    value[16] = 0;
    while (i) {
        th = (val & i) == i;
        i >>= 1;
        value[cnt++] = th + '0';
    }
    return 1;
}


int
btod(char* value)
{
    int where = 1;
    int current_num;
    int sum = 0;
    int i = 0;
    /* go to the end of string */
    while (value[++where] != 0) {}
    --where;
    /* go until 0b part */
    while (where >= 2) {
        current_num = value[where] - '0';
        sum += current_num << i++;
        --where;
    }
    return sum;
}


int
btobs(char* value)
{
    int val = btod(value);
    int     th;
    int     i = 0x8000;             /* 16 bits */
    int     cnt = 0;
    value[16] = 0;
    while (i) {
        th = (val & i) == i;
        i >>= 1;
        value[cnt++] = th + '0';
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
                node->val.type = T_LITERAL_BINARY;
                break;
            case T_LITERAL_HEXADECIMAL:
                htobs(node->val.value);
                node->val.type = T_LITERAL_BINARY;
                break;
            case T_LITERAL_BINARY:
                btobs(node->val.value);
                node->val.type = T_LITERAL_BINARY;
                break;
            default:
                break;
        }
        node = node->next;
    }
    return 1;
}
