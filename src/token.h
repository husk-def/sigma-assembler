#ifndef TOKEN_H
#define TOKEN_H

#include <stdio.h>

// typedef enum {
// 	PROG,
// 	DATA,
// 	RESERVE,
// 	NAME,
// 	SIZE,
// 	INSTRUCTION,
// 	REGISTER
// } token_class_t;

typedef enum {
	/* error */
	ERR = 0,
	/* directives */
	PROG,
	DATA,
	/* memory stuff */
	RESERVE, 
	NAME,
	SIZE,
	/* instructions */
	LD,
	ST,
	JMP,
	BEQ,
	BNE,
	ADD,
	SUB,
	MUL,
	DIV,
	CMPEQ,
	CMPLT,
	CMPLE,
	AND,
	OR,
	XOR,
	XNOR,
	SHL,
	SHR,
	SRA,
	ADDC,
	SUBC,
	MULC,
	DIVC,
	CMPEQC,
	CMPLTC,
	CMPLEC,
	ANDC,
	ORC,
	XORC,
	XNORC,
	SHLC,
	SHRC,
	SRAC,
	/* registers */
	REG01,
	REG02,
	REG03,
	REG04,
	REG05,
	REG06,
	REG07,
	REG08,
	REG09,
	REG10,
	REG11,
	REG12,
	REG13,
	REG14,
	REG15,
	REG16,
	REG17,
	REG18,
	REG19,
	REG20,
	REG21,
	REG22,
	REG23,
	REG24,
	REG25,
	REG26,
	REG27,
	REG28,
	REG29,
	REG30,
	REG31,
	/* universal, should not be used except for eat purposes */
	REG
} token_type_t;


typedef struct {
    char            value[10];
    //token_class_t   class;
    token_type_t    type;
    int             line;
} token_t;

/* ! " # $ % & ' ( ) * + , - . / 0 1 2 3 4 5 6 7 8 9 : ; < = > ? @ A B C D E F G H I J K L M N O P Q R S T U V W X Y Z [ \ ] ^ _ ` a b c d e f g h i j k l m n o p q r s t u v w x y z { | } ~*/

void
print_token_info(token_t t);

#endif /* TOKEN_H */