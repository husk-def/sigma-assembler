#include "tokenizer.h"

int
get_word(const char *source, int where, char *ret, int sourcesize)
{
    int     e;
    char    temp[20];
    if (where >= sourcesize) {
        return -1;
    } else {
        e = sscanf(&source[where], " %s", temp);
    }
    //e = sscanf(source, " %s", temp);
    if (e > 19) {
        return -1;  
    } else {
        /* here, everything should be fine, correct me */
        strncpy(ret, temp, 20);
    }
    return (where + e);
}
