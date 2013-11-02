/**
 * File: global.h
 * Date: Nov 3, 2013
 * AUTHOR: Jeanhwea 
 */

#ifndef GLOBAL_H

#define GLOBAL_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

/* MAXRESERVED = the number of reserved words */
#define MAXRESERVED 8

typedef enum {
	/* book-keeping tokens */
	ENDFILE, ERROR,
	/* reserved words */
	IF, THEN, ELSE, END, REPEAT, UNTIL, READ, WRITE,
	/* muticharacter tokens */
	ID, NUM,
	/* special symbol */
	ASSIGN, EQ, LT, PLUS, MINUS, TIMES, OVER, LPAREN, RPAREN, SEMI
} TokenType;

typedef struct _TreeNode {
	struct _TreeNode *child[MAXCHILDREN];
	struct _TreeNode *sibling;
	int lineno;
	NodoKind nodekind;
	union {
		StmtKind stmt;
		ExprKind expr;
	} kind;
	union {
		TokenType op;
		int val;
		char *name;
	} attr;
	ExpType type;
} TreeNode;

#endif /* end of include guard: GLOBAL_H */
