#include "parser.h"
#include "list.h"
#include "token.h"
#include <stdio.h>
#include <string.h>

label_addr_t	addr_arr[MAX_ADDR];
var_addr_t		var_addr[MAX_ADDR];
err_t			err = ALL_OK;
node_t			*prev;
node_t			*curr;
int				line_num = 0;

/*
 *  starts parsing, returns if successful
 */
int
syntax_analysis(node_t *root)
{
	curr = root;
	for (int i = 0; i < MAX_ADDR; i++) {
		strcpy(addr_arr[i].label, ".");
		addr_arr[i].addr = -1;
	}
	//DEBUG_print(-100);
	Q();
	return err;
}

/*
 *	replaces labels with their binary adress
 */
void
replace_labels(node_t *root)
{
	char new_val[30];

	curr = root;
	while(curr != NULL) {
		if(curr->val.type == T_LABEL) {
			for(int i = 0; i < MAX_ADDR; i++) {
				if(!strcmp(curr->val.value, addr_arr[i].label)) {
					sprintf(new_val, "%d", addr_arr[i].addr);
					strcpy(curr->val.value, new_val);
					dtobs(curr->val.value);
				}
			}
		}
		curr = curr->next;
	}
}

/*
 *	writes to output file
 */
int
parse(node_t *root, char *path)
{
	FILE *fp;

	fp = fopen(path, "w");
	if (fp == NULL) {
		return 1;
	}
	
	curr = root;
	int all = 0;
	int var = 0;
	char var_s[40];
	char temp[40];

	/* writes .data to file */
	while (strcmp(curr->val.value, ".prog")) {
		switch (curr->val.type) {
			case T_DATA: {
				fprintf(fp, "%s\n", curr->val.value);
			}
			break;
			case T_ALLOCATE: {
				all = 1;
			}
			break;
			case T_LITERAL_BINARY: {
				if (all) {
					fprintf(fp, "0 %s\n", var_s);
					for (int i = 1; i < binary_to_decimal(curr->val.value); i++) {
						fprintf(fp, "0\n");
					}
					all = 0;
					var = 0;
				}
				else if (var) {
					fprintf(fp, "%s %s\n", curr->val.value, var_s);
					var = 0;
				}
			}
			break;
			case T_VARIABLE: {
				strcpy(var_s, curr->val.value);
				var = 1;
			}
			default:;
		}
		curr = get_next(curr);
	}

	curr = root;

	while (strcmp(curr->val.value, ".prog")) {
		curr = get_next(curr);
	}

	/* change to machine code */
	while(curr != NULL) {
		switch (curr->val.type) {
			case T_LD: {
				strcpy(curr->val.value, "011000");
			}
			break;
			case T_ST: {
				strcpy(curr->val.value, "011001");
			}
			break;
			case T_JMP: {
				strcpy(curr->val.value, "011011");
			}
			break;
			case T_BEQ: {
				strcpy(curr->val.value, "011100");
			}
			break;
			case T_BNE: {
				strcpy(curr->val.value, "011101");
			}
			break;
			case T_ADD: {
				strcpy(curr->val.value, "100000");
			}
			break;
			case T_SUB: {
				strcpy(curr->val.value, "100001");
			}
			break;
			case T_MUL: {
				strcpy(curr->val.value, "100010");
			}
			break;
			case T_DIV: {
				strcpy(curr->val.value, "100011");
			}
			break;
			case T_CMPEQ: {
				strcpy(curr->val.value, "100100");
			}
			break;
			case T_CMPLT: {
				strcpy(curr->val.value, "100101");
			}
			break;
			case T_CMPLE: {
				strcpy(curr->val.value, "100110");
			}
			break;
			case T_AND: {
				strcpy(curr->val.value, "101000");
			}
			break;
			case T_OR: {
				strcpy(curr->val.value, "101001");
			}
			break;
			case T_XOR: {
				strcpy(curr->val.value, "101010");
			}
			break;
			case T_XNOR: {
				strcpy(curr->val.value, "101011");
			}
			break;
			case T_SHL: {
				strcpy(curr->val.value, "101100");
			}
			break;
			case T_SHR: {
				strcpy(curr->val.value, "101101");
			}
			break;
			case T_SRA: {
				strcpy(curr->val.value, "101110");
			}
			break;
			case T_ADDC: {
				strcpy(curr->val.value, "110000");
			}
			break;
			case T_SUBC: {
				strcpy(curr->val.value, "110001");
			}
			break;
			case T_MULC: {
				strcpy(curr->val.value, "110010");
			}
			break;
			case T_DIVC: {
				strcpy(curr->val.value, "110011");
			}
			break;
			case T_CMPEQC: {
				strcpy(curr->val.value, "110100");
			}
			break;
			case T_CMPLTC: {
				strcpy(curr->val.value, "110101");
			}
			break;
			case T_CMPLEC: {
				strcpy(curr->val.value, "110110");
			}
			break;
			case T_ANDC: {
				strcpy(curr->val.value, "111000");
			}
			break;
			case T_ORC: {
				strcpy(curr->val.value, "111001");
			}
			break;
			case T_XORC: {
				strcpy(curr->val.value, "111010");
			}
			break;
			case T_XNORC: {
				strcpy(curr->val.value, "111011");
			}
			break;
			case T_SHLC: {
				strcpy(curr->val.value, "111100");
			}
			break;
			case T_SHRC: {
				strcpy(curr->val.value, "111101");
			}
			break;
			case T_SRAC: {
				strcpy(curr->val.value, "111110");
			}
			break;
			case T_PROG: {
				sprintf(temp, "%s\n", curr->val.value);
				strcpy(curr->val.value, temp);
			}
			break;
			case T_VARIABLE: {
				strcpy(curr->val.value, get_var_addr(curr->val.value));
			}
			break;
			case T_REG00:
			case T_REG01:
			case T_REG02:
			case T_REG03:
			case T_REG04:
			case T_REG05:
			case T_REG06:
			case T_REG07:
			case T_REG08:
			case T_REG09: {
				int num = 0;
				num += (curr->val.value[1] - '0');
				sprintf(temp, "%d", num);
				dtobs(temp);
				sprintf(curr->val.value, "%c%c%c%c%c", temp[11], temp[12], temp[13], temp[14], temp[15]);
			}
			break;
			case T_REG10:
			case T_REG11:
			case T_REG12:
			case T_REG13:
			case T_REG14:
			case T_REG15:
			case T_REG16:
			case T_REG17:
			case T_REG18:
			case T_REG19:
			case T_REG20:
			case T_REG21:
			case T_REG22:
			case T_REG23:
			case T_REG24:
			case T_REG25:
			case T_REG26:
			case T_REG27:
			case T_REG28:
			case T_REG29:
			case T_REG30:
			case T_REG31: {
				int num = 0;
				num += (curr->val.value[1] - '0') * 10;
				num += (curr->val.value[2] - '0');
				sprintf(temp, "%d", num);
				dtobs(temp);
				sprintf(curr->val.value, "%c%c%c%c%c", temp[11], temp[12], temp[13], temp[14], temp[15]);
			}
			default:;
		}
		curr = get_next(curr);	
	}

	curr = root;
	int line = 0;
	int pline = line;
	long where = ftell(fp);
	long diff = where;

	while (strcmp(curr->val.value, ".prog\n")) {
		curr = get_next(curr);
	}

	/* writes .prog to file */
	while (curr != NULL) {
		line = curr->val.line;
		if(curr->val.type == T_PROG) {
			fprintf(fp, "%s", curr->val.value);
			where = ftell(fp);
		}
		else {
			if(pline != line) {
				diff = ftell(fp) - where;
				if (diff < 32) {
					for(int i = diff; i < 32; i++) {
						fprintf(fp, "0");
					}
				}
				fprintf(fp, "\n");
				where = ftell(fp);
				pline = line;
			}
			fprintf(fp, "%s", curr->val.value);
		}
		curr = get_next(curr);
	}

	fclose(fp);
}

/*
 *	converts binary string to decimal int
 */
int
binary_to_decimal(char* binary)
{
	int ret = 0;
	int mx = 0x8000; /* 16 bit number */
	char *c = binary;
	while((*c) != 0) {
		ret += mx * ((*c) - '0');
		mx = mx >> 1;
		c++;
	}
	//DEBUG_print(-50);
	return ret;
}

/*
 *	for testing purposes
 */
void
DEBUG_print(int val)
{
	printf("TOKEN: %s | LINE: %d | ID: %d\n", curr->val.value, line_num, val);
}

/*
 *  checks type of token and moves on
 */
int
eat(token_type_t type)
{
	if (curr->val.type == type || (type == T_REG && curr->val.type <= T_REG31)) {
		curr->val.line = line_num;
		//DEBUG_print(-4);
		prev = curr;
		curr = get_next(curr);
		err = ALL_OK;
		return 1;
	}
	
	curr->val.line = line_num;
	err = UNEXPECTED_TYPE;
	//DEBUG_print(-3);
	return 0;
}

/*
 *	for retrieving where the program stopped
 */
int
get_line_num()
{
	return line_num;
}

/*
 *	get address of variable
 */
char*
get_var_addr(char *var)
{
	for(int i = 0; i < MAX_ADDR; i++) {
		if(!strcmp(var, var_addr[i].var)) {
			sprintf(var, "%d", var_addr[i].addr);
			dtobs(var);
			return var;
		}
	}

	return NULL;
}

/*
 *  checks for errors
 */
int
check_err(void)
{
	if (err) {
		//DEBUG_print(-1);
		return 1;
	}

	return 0;
}

void
Q(void)
{
	//DEBUG_print(-1);
	if (check_err()) {
		return;
	}
	else if (eat(T_DATA)) {	
		line_num = 0;
		D();
		line_num = 0;
		eat(T_PROG);
		P();
	}
	else {
		line_num = 0;
		eat(T_PROG);
		P();
	}
}

void
D(void)
{
	//DEBUG_print(0);

	if (check_err()) {
		return;
	}
	else {
		M();
	}
}

void
P(void)
{
	//DEBUG_print(1);

	if (check_err()) {
		return;
	}
	else if(curr->val.type == T_LABEL) {
		L();
		I();
	}
	else {
		I();
	}
}

void
M(void)
{
	//DEBUG_print(2);
	if (check_err()) {
		return;
	}

	if(eat(T_VARIABLE)) {
		eat(T_LITERAL_BINARY);
		line_num += 1;
	}
	else if(eat(T_ALLOCATE)) {
		eat(T_VARIABLE);
		int to_increase = binary_to_decimal(curr->val.value);
		eat(T_LITERAL_BINARY);
		line_num += to_increase;
	}

	if(curr->val.type == T_VARIABLE || curr->val.type == T_ALLOCATE) {
		M();
	}
}

void
I(void)
{
	//DEBUG_print(3);
	if (check_err()) {
		return;
	}

	switch(curr->val.type) {
		case T_LD: {
			eat(T_LD);
			eat(T_REG);
			eat(T_REG);
			eat(T_LITERAL_BINARY);
		}
		break;
		case T_ST: {
			eat(T_ST);
			eat(T_REG);
			eat(T_REG);
			eat(T_LITERAL_BINARY);
		}
		break;
		case T_JMP: {
			eat(T_JMP);
			eat(T_REG);
			eat(T_LABEL);
		}
		break;
		case T_BEQ: {
			eat(T_BEQ);
			eat(T_REG);
			eat(T_REG);
			eat(T_LABEL);
		}
		break;
		case T_BNE: {
			eat(T_BNE);
			eat(T_REG);
			eat(T_REG);
			eat(T_LABEL);
		}
		break;
		case T_ADD: {
			eat(T_ADD);
			eat(T_REG);
			eat(T_REG);
			eat(T_REG);
		}
		break;
		case T_SUB: {
			eat(T_SUB);
			eat(T_REG);
			eat(T_REG);
			eat(T_REG);
		}
		break;
		case T_MUL: {
			eat(T_MUL);
			eat(T_REG);
			eat(T_REG);
			eat(T_REG);
		}
		break;
		case T_DIV: {
			eat(T_DIV);
			eat(T_REG);
			eat(T_REG);
			eat(T_REG);
		}
		break;
		case T_CMPEQ: {
			eat(T_CMPEQ);
			eat(T_REG);
			eat(T_REG);
			eat(T_REG);
		}
		break;
		case T_CMPLT: {
			eat(T_CMPLT);
			eat(T_REG);
			eat(T_REG);
			eat(T_REG);
		}
		break;
		case T_CMPLE: {
			eat(T_CMPLE);
			eat(T_REG);
			eat(T_REG);
			eat(T_REG);
		}
		break;
		case T_AND: {
			eat(T_AND);
			eat(T_REG);
			eat(T_REG);
			eat(T_REG);
		}
		break;
		case T_OR: {
			eat(T_OR);
			eat(T_REG);
			eat(T_REG);
			eat(T_REG);
		}
		break;
		case T_XOR: {
			eat(T_XOR);
			eat(T_REG);
			eat(T_REG);
			eat(T_REG);
		}
		break;
		case T_XNOR: {
			eat(T_XNOR);
			eat(T_REG);
			eat(T_REG);
			eat(T_REG);
		}
		break;
		case T_SHL: {
			eat(T_SHL);
			eat(T_REG);
			eat(T_REG);
			eat(T_REG);
		}
		break;
		case T_SHR: {
			eat(T_SHR);
			eat(T_REG);
			eat(T_REG);
			eat(T_REG);
		}
		break;
		case T_SRA: {
			eat(T_SRA);
			eat(T_REG);
			eat(T_REG);
			eat(T_REG);
		}
		break;
		case T_ADDC: {
			eat(T_ADDC);
			eat(T_REG);
			eat(T_REG);
			eat(T_LITERAL_BINARY);
		}
		break;
		case T_SUBC: {
			eat(T_SUBC);
			eat(T_REG);
			eat(T_REG);
			eat(T_LITERAL_BINARY);
		}
		break;
		case T_MULC: {
			eat(T_MULC);
			eat(T_REG);
			eat(T_REG);
			eat(T_LITERAL_BINARY);
		}
		break;
		case T_DIVC: {
			eat(T_DIVC);
			eat(T_REG);
			eat(T_REG);
			eat(T_LITERAL_BINARY);
		}
		break;
		case T_CMPEQC: {
			eat(T_CMPEQC);
			eat(T_REG);
			eat(T_REG);
			eat(T_LITERAL_BINARY);
		}
		break;
		case T_CMPLTC: {
			eat(T_CMPLTC);
			eat(T_REG);
			eat(T_REG);
			eat(T_LITERAL_BINARY);
		}
		break;
		case T_CMPLEC: {
			eat(T_CMPLEC);
			eat(T_REG);
			eat(T_REG);
			eat(T_LITERAL_BINARY);
		}
		break;
		case T_ANDC: {
			eat(T_ANDC);
			eat(T_REG);
			eat(T_REG);
			eat(T_LITERAL_BINARY);
		}
		break;
		case T_ORC: {
			eat(T_ORC);
			eat(T_REG);
			eat(T_REG);
			eat(T_LITERAL_BINARY);
		}
		break;
		case T_XORC: {
			eat(T_XORC);
			eat(T_REG);
			eat(T_REG);
			eat(T_LITERAL_BINARY);
		}
		break;
		case T_XNORC: {
			eat(T_XNORC);
			eat(T_REG);
			eat(T_REG);
			eat(T_LITERAL_BINARY);
		}
		break;
		case T_SHLC: {
			eat(T_SHLC);
			eat(T_REG);
			eat(T_REG);
			eat(T_LITERAL_BINARY);
		}
		break;
		case T_SHRC: {
			eat(T_SHRC);
			eat(T_REG);
			eat(T_REG);
			eat(T_LITERAL_BINARY);
		}
		break;
		case T_SRAC: {
			eat(T_SRAC);
			eat(T_REG);
			eat(T_REG);
			eat(T_LITERAL_BINARY);
		}
		break;
		case T_END: {
			return;
		}
		break;
		default: err = UNEXPECTED_TYPE;
	}

	line_num += 1;

	if (check_err()) {
		return;
	}
	else if (curr->val.type == T_LABEL) {
		L();
		I();
	}
	else {
		I();
	}
}

void
L(void)
{
	//DEBUG_print(4);
	if (check_err()) {
		return;
	}

	for (int i = 0; i < MAX_ADDR; i++) {
		if (!strcmp(addr_arr[i].label, curr->val.value)) {
			err = REPEAT_LABEL;
			return;
		}
		else if (!strcmp(addr_arr[i].label, ".")) {
			strcpy(addr_arr[i].label, curr->val.value);
			addr_arr[i].addr = line_num*4;
			break;
		}
	}

	node_t *temp = prev;
	eat(T_LABEL);
	temp->next = curr;
	prev->next = NULL;
	free(prev);
}
