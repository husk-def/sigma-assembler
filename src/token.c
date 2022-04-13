#include "token.h"

void
print_token_info(token_t t)
{
    printf("value: %s\ntoken type: %d\nline: %d\n", 
        t.value, 
        t.type, 
        t.line);
    printf("*********************************\n");
}