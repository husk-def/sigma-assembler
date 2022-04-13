#include "tokenizer.h"
#include "files.h"
#include "list.h"
#include "token.h"

int
calculate_hashsum(const char* s)
{
    char    c;
    int     i = 0;
    int     g = 1;
    int     sum = 0;

    while ((c = s[i]) != 0) {
        sum += (c + 0) * g;
        ++i;
        g += 2;
    }
    return sum;    
}

const char s[][10] = {
	/* error */
	"ERR",
	/* directives */
	"PROG",
	"DATA",
	/* memory stuff */
	"RESERVE", 
	"NAME",
	"SIZE",
	/* instructions */
	"LD",
	"ST",
	"JMP",
	"BEQ",
	"BNE",
	"ADD",
	"SUB",
	"MUL",
	"DIV",
	"CMPEQ",
	"CMPLT",
	"CMPLE",
	"AND",
	"OR",
	"XOR",
	"XNOR",
	"SHL",
	"SHR",
	"SRA",
	"ADDC",
	"SUBC",
	"MULC",
	"DIVC",
	"CMPEQC",
	"CMPLTC",
	"CMPLEC",
	"ANDC",
	"ORC",
	"XORC",
	"XNORC",
	"SHLC",
	"SHRC",
	"SRAC",
	/* registers */
	"REG01",
	"REG02",
	"REG03",
	"REG04",
	"REG05",
	"REG06",
	"REG07",
	"REG08",
	"REG09",
	"REG10",
	"REG11",
	"REG12",
	"REG13",
	"REG14",
	"REG15",
	"REG16",
	"REG17",
	"REG18",
	"REG19",
	"REG20",
	"REG21",
	"REG22",
	"REG23",
	"REG24",
	"REG25",
	"REG26",
	"REG27",
	"REG28",
	"REG29",
	"REG30",
	"REG31",
	/* universal, should not be used except for eat purposes */
	"REG"
};

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
        /* points to the beginning of a list, SHOULD NOT BE CHANGED */
    node_t*         ls_begin;             
    node_t*         node;
        /* hardcoded path, todo change this */
    const char*     path = "/home/rtrk/Documents/ra211-2019-assembler/sigma-assembler/example/e1.assembly";

    ls_begin = init_list();
    node = ls_begin;
    
    /* implementation */
    progsize = get_file_size(path);
    printf("progsize = %d\n", progsize);

    program = (char*)malloc((progsize + 1) * sizeof(char));
    get_program(path, program, progsize);
    printf("program\n%s\n", program);

    fp = fopen(path, "r");

        /* leaves an extra token at the end */
    while((check = fscanf(fp, " %s", word)) > 0) {
        printf(".%s.\n", word);
        strcpy(node->val.value, word);
        node = list_expand(node);
    }

    node = ls_begin;

    while(node != NULL) {
        print_token_info(node->val);
        node = get_next(node);
    }

    deinit_list_from(ls_begin);

        /* should be gibberish */
    print_token_info(ls_begin->val);

    // for (i = 32; i < 128; ++i) {
    //     printf("%c ", (char)i);
    // }

    //printf("\n\n********************\n\n%c", (char)48);

    int sums[71];

    for (i = 0; i <= 70; ++i) {
        sums[i] = calculate_hashsum(s[i]);
        printf("sum of %s is %d\n", s[i], sums[i]);
    }

    for (i = 0; i <= 70; ++i) {
        sums[i] = calculate_hashsum(s[i]);
        printf("%d\n", sums[i]);
    }

    exit(0);
}
