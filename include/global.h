#ifndef _GLOBAL_H_
#define _GLOBAL_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "debug.h"

// consts
extern char *PL0C_NAME;
extern char *PL0C_VERSION;
extern char PL0C_PROGNAME[];

// print control
extern bool echo;

// compile phase
extern phase_t phase;
// source code file
extern FILE *source;
// target assembly file
extern FILE *target;

// source file line number, column number
extern int lineno;
extern int colmno;

// Initialization
void init(int argc, char *argv[]);

// Lexical

// Syntax
typedef struct _pgm_struct pgm_s;
// program AST
extern pgm_s *prog;
pgm_s *parse(void);

#endif /* End of _GLOBAL_H_ */
