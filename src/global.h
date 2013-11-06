/**
 * File: global.h
 * Date: Nov 3, 2013
 * Author: Jeanhwea 
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
#define MAXRESERVED 21

typedef enum {
	/* book-keeping tokens */
	ENDFILE, ERROR,
	/* reserved words */
	ARRAY, BEGIN, CHAR, CONST, DO, DOWNTO, ELSE, END,
	FOR, FUNCTION, IF, INTEGER, OF, PROCEDURE, READ,
	REPEAT, THEN, TO, UNTIL, VAR, WRITE,
	/* muticharacter tokens */
	ID, CH, NUM, STRING,
	/* special symbol */
	PLUS, MINUS, STAR, OVER, EQU, LST, LEQ, GTT, GEQ,
	NEQ, COMMA, SEMI, ASSIGN, LPAR, RPAR, LBRA, RBRA,
	LBBR, RBBR, SQUO, DQUO, COLON, DOT
} TokenType;

extern FILE *source; /* source code text file */
extern FILE *listing; /* listing output text file */
extern FILE *code; /* code text file */

extern int lineno; /* source line number for listing */

typedef enum {
	StmtK, ExpK
} NodeKind;
typedef enum {
	AssignK, IfK, ReapetK, CallK, CompK, ReadK, WriteK,
	ForK, NullK
} StmtKind;
typedef enum {
	OpK
} ExprKind;
typedef enum {
	Void
} ExpType;

#define MAXCHILDREN 3
typedef struct _TreeNode {
	struct _TreeNode *child[MAXCHILDREN];
	struct _TreeNode *sibling;
	int lineno;
	NodeKind nodekind;
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

extern int PrintSource;
extern int TraceScan;
#endif /* end of include guard: GLOBAL_H */
