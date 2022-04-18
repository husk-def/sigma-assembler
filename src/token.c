#include "token.h"

const char token_s[72][10] = {
    /* registers */
	"r1",
	"r2",
	"r3",
	"r4",
	"r5",
	"r6",
	"r7",
	"r8",
	"r9",
	"r10",
	"r11",
	"r12",
	"r13",
	"r14",
	"r15",
	"r16",
	"r17",
	"r18",
	"r19",
	"r20",
	"r21",
	"r22",
	"r23",
	"r24",
	"r25",
	"r26",
	"r27",
	"r28",
	"r29",
	"r30",
	"r31",
	/* instructions */
	"ld",
	"st",
	"jmp",
	"beq",
	"bne",
	"add",
	"sub",
	"mul",
	"div",
	"cmpeq",
	"cmplt",
	"cmple",
	"and",
	"orc",
	"xor",
	"xnor",
	"shl",
	"shr",
	"sra",
	"addc",
	"subc",
	"mulc",
	"divc",
	"cmpeqc",
	"cmpltc",
	"cmplec",
	"andc",
    "orc",
    "xorc",
    "xnorc",	
	"shlc",
	"shrc",
	"srac",
	/* directives */
	".prog",
	".data",
	/* memory stuff */
	"allocate",
    /* dont use this */
    "reg",
    "variable",
    "literal",
    "label",
    "error"
};

int is_all_num(const char *s) {
    int i = 0;
    while (s[i] != 0) {
        if (s[i] - 0 <= 57 && s[i] - 0 >= 48) {
            ++i;
        } else {
            return 0;
        }
    }
    return 1;
}

void
print_token_info(token_t t)
{
    if (t.type <= T_ERR) {
        printf("value: %s;\ntoken type: %d;\nline: %d;\ntoken_s: %s;\n", 
            t.value, 
            (int)t.type, 
            t.line,
            token_s[(int)t.type]);
        printf("*********************************\n");
    }
}

token_type_t
get_token_type(const char *word)
{
    int iter;
    printf("token = %s;\n", word);
    for (iter = T_REG01; iter <= T_ALLOCATE; ++iter) {
        if (strcmp(word, token_s[iter]) == 0) {
            return (token_type_t)iter;
        }
    }
    /* if here - either variable name, label or literal */
    if (word[0] == ':') {
        /* label (e.g. :lab) */
        return T_LABEL;
    } else if (word[0] == '_') {
        /* variable (e.g. _var) */
        return T_VARIABLE;
    } else if (is_all_num(word)) {
        /* literal (e.g. 1234) */
        return T_LITERAL;
    } else {
        /* no match, error */
        printf("error in %s;\n", word);
        return T_ERR;
    }
}
