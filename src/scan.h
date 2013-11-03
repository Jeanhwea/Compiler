/**
 * File: scan.h
 * Date: Nov 4, 2013
 * Author: Jeanhwea
 */

#ifndef SCAN_H

#define SCAN_H

/* MAXTOKENSIZE is the max length of a token */
#define MAXTOKENSIZE 256

/* tokenString array stores the lexeme of each token */
extern char tokenString[MAXTOKENSIZE + 1];

/* function getToken return the next token in source file */
TokenType getToken(void);

#endif /* end of include guard: SCAN_H */
