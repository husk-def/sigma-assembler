#include "parser.h"
#include "list.h"
#include "token.h"
#include <stdio.h>
#include <string.h>

label_addr_t addr_arr[MAX_ADDR];
err_t err = ALL_OK;
node_t *prev;
node_t *curr;
int line_num = 0;

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
	DEBUG_print(-100);
	Q();
	return err;
}

void
replace_labels(node_t *root)
{
	char *new_val;

	curr = root;
	while(curr != NULL) {
		if(curr->val.type == T_LABEL) {
			for(int i = 0; i < MAX_ADDR; i++) {
				if(!strcmp(curr->val.value, addr_arr[i].label)) {
					sprintf(new_val, "%d", addr_arr[i].addr);
					strcpy(curr->val.value, new_val);
				}
			}
		}
		curr = curr->next;
	}
}

/*
 *	converts binary string to decimal int
 */
int
btod(char* binary)
{
	int ret = 0;
	DEBUG_print(-50);
	int i = 0;
	char *c = binary;
	while(c[i] != 0) {
		if(c[i] == '1') {
			ret += 1 << i;
		}
		i++;
	}
	DEBUG_print(-50);
	printf("%d\n", ret);
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
		DEBUG_print(-4);
		prev = curr;
		curr = get_next(curr);
		err = ALL_OK;
		return 1;
	}
	
	curr->val.line = line_num;
	err = UNEXPECTED_TYPE;
	DEBUG_print(-3);
	return 0;
}

/*
 *  checks for errors
 */
int
check_err(int true_end)
{
	/* EOF error check */
	if((curr->val.type == T_END && !true_end) || curr == NULL) {
		DEBUG_print(-2);
		err = UNEXPECTED_EOF;
		return 1;
	}

	/* EOF check */
	if(curr->val.type == T_END && true_end) {
		DEBUG_print(-10);
		return 1;
	}

	/* others */
	if (err) {
		DEBUG_print(-1);
		return 1;
	}

	return 0;
}

void
Q(void)
{
	DEBUG_print(-1);
	if (check_err(0)) {
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
	DEBUG_print(0);

	if (check_err(0)) {
		return;
	}
	else {
		M();
	}
}

void
P(void)
{
	DEBUG_print(1);

	if (check_err(0)) {
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
	DEBUG_print(2);
	if (check_err(0)) {
		return;
	}

	if(eat(T_VARIABLE)) {
		eat(T_LITERAL_BINARY);
		line_num += 1;
	}
	else if(eat(T_ALLOCATE)) {
		eat(T_VARIABLE);
		int to_increase = btod(curr->val.value);
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
	DEBUG_print(3);
	if (check_err(0)) {
		return;
	}

	switch(curr->val.type) {
		case T_LD: {
			eat(T_LD);
			eat(T_REG);
			eat(T_REG);
			eat(T_REG);
		}
		break;
		case T_ST: {
			eat(T_ST);
			eat(T_REG);
			eat(T_REG);
			eat(T_REG);
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
	}

	line_num += 1;

	if (check_err(1)) {
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
	DEBUG_print(4);
	if (check_err(0)) {
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
	deinit_list_from(prev);
}
