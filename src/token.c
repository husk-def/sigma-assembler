#include "token.h"

const char token_s[79][25] = {
    /* registers */
	"^r0$",
	"^r1$",
	"^r2$",
	"^r3$",
	"^r4$",
	"^r5$",
	"^r6$",
	"^r7$",
	"^r8$",
	"^r9$",
	"^r10$",
	"^r11$",
	"^r12$",
	"^r13$",
	"^r14$",
	"^r15$",
	"^r16$",
	"^r17$",
	"^r18$",
	"^r19$",
	"^r20$",
	"^r21$",
	"^r22$",
	"^r23$",
	"^r24$",
	"^r25$",
	"^r26$",
	"^r27$",
	"^r28$",
	"^r29$",
	"^r30$",
	"^r31$",
	/* instructions */
	"^ld$",
	"^st$",
	"^jmp$",
	"^beq$",
	"^bne$",
	"^add$",
	"^sub$",
	"^mul$",
	"^div$",
	"^cmpeq$",
	"^cmplt$",
	"^cmple$",
	"^and$",
	"^or$",
	"^xor$",
	"^xnor$",
	"^shl$",
	"^shr$",
	"^sra$",
	"^addc$",
	"^subc$",
	"^mulc$",
	"^divc$",
	"^cmpeqc$",
	"^cmpltc$",
	"^cmplec$",
	"^andc$",
    "^orc$",
    "^xorc$",
    "^xnorc$",	
	"^shlc$",
	"^shrc$",
	"^srac$",
	"^nop$",
	/* directives */
	"^.prog$",
	"^.data$",
	/* memory stuff */
	"^allocate$",
	/* decimal literal */
	"^-?[0-9]{1,16}$",
	/* hexadecimal literal */
	"^0x[0-9a-fA-F]{1,8}$",
	/* binary literal */
	"^0b[0-1]{1,16}$",
	/* variable */
	"^_[0-9a-zA-Z]{1,20}$",
	/* label */
	"^:[0-9a-zA-Z]{1,20}$",
    /* dont use this */
    "reg",
    "error"
};


static regex_t regexes[REGEX_COUNT];

int
is_all_num(const char *s) {
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


int
generate_regexes(void)
{
	int which;
	int reti;
	for (which = T_REG00; which <= T_LABEL; ++which) { /* watch out for +3 !!!!!!!!!!!!!!! */ /* check with t_literal later */
		if ((reti = regcomp(&regexes[which], token_s[which], REG_EXTENDED | REG_ICASE)) != 0) {
			printf("could not compile regex: %s\n", token_s[which]);
            which = T_ERR;
            return 1;
		}
	}
	printf("generate_regexes done.\n");
	return 0;
}


void
free_regexes(void)
{
	int which;
	for (which = T_REG00; which <= T_LABEL; ++which) {
		regfree(&regexes[which]);
	}
	printf("free_regexes done.\n");
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
    int		which;
	int		reti;
    for (which = T_REG00; which <= T_LABEL; ++which) {
        if ((reti = regexec(&regexes[which], word, 0, NULL, 0) == 0)) {
				/* match */
				return which;
		}
		/* else continue searching */
    }
	return T_ERR;
}
