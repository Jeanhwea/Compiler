/**
 * File: util.h
 * Date: Nov 4, 2013
 * Author: Jeanhwea
 */

#ifndef UTIL_H

#define UTIL_H

#include "scan.h"
/* print token type */
void printToken(TokenType, const char *);

/* allocate and copy a string */
char *copyString(char *);

void printHead(char *);
void printTail(char *);
void printInner(int, ...);
void printInnerInt(int);
#endif /* end of include guard: UTIL_H */
