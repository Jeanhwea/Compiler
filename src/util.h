/**
 * File: util.h
 * Date: Nov 4, 2013
 * Author: Jeanhwea
 */

#ifndef UTIL_H

#define UTIL_H

#include "scan.h"
#include <stdarg.h>
/* print token type */
void printToken(TokenType, const char *);

/* allocate and copy a string */
char *copyString(char *);

/* a bundle print function */
void headPr(char *cont);
void innerPr(int n, ...);
void innerIdnPr(int n, ...);
void innerlnPr(int n, ...);
void innerIdnlnPr(int n, ...);
void innerIntPr(int val);
void innerCharPr(char val);
void tailPr(char *cont);

#endif /* end of include guard: UTIL_H */
