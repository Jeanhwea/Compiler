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
extern bool silent;

// compiler phase
extern phase_t phase;
extern int errnum;

// source code file
extern FILE *source;
extern int lineno;
extern int colmno;
// target assembly file
extern FILE *target;

// Initialization init.c
void init(int argc, char *argv[]);

// Lexical
// hold source file line buffer in scan.c
#define MAXLINEBUF 4096
extern char linebuf[MAXLINEBUF];
extern int bufsize;
token_t gettok(void);

// Syntax
// prog as AST, in parse.c
extern pgm_node_t *prog;
pgm_node_t *parse(void);

// Semantic
// in analysis.c
void analysis();

#endif /* End of _GLOBAL_H_ */
