/**
 * File: scan.h
 * Date: Nov 4, 2013
 * Author: Jeanhwea
 */

#ifndef SCAN_H

#define SCAN_H

typedef enum {
	/* book-keeping tokens */
	ENDFILE, ERROR,
	/* reserved words */
	ARRAY, BEGIN, CHAR, CONST, DO, DOWNTO, ELSE, END,
	FOR, FUNCTION, IF, INTEGER, OF, PROCEDURE, READ,
	REPEAT, THEN, TO, UNTIL, VAR, WRITE,
	/* muticharacter tokens */
	ID, CH, UNS, STRING,
	/* special symbol */
	PLUS, MINUS, STAR, OVER, EQU, LST, LEQ, GTT, GEQ,
	NEQ, COMMA, SEMI, ASSIGN, LPAR, RPAR, LBRA, RBRA,
	LBBR, RBBR, SQUO, DQUO, COLON, DOT
} TokenType;

/* MAXTOKENSIZE is the max length of a token */
#define MAXTOKENSIZE 256

/* tokenString array stores the lexeme of each token */
extern char tokenString[MAXTOKENSIZE + 1];
/* hold current token location, which line */
extern int tokenLocation;

/* function getToken return the next token in source file */
TokenType getToken(void);

void printToken(TokenType , const char *);

#endif /* end of include guard: SCAN_H */
