#ifndef _GLOBAL_H_
#define _GLOBAL_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "parse.h"
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
// source code file
extern FILE *source;
// target assembly file
extern FILE *target;

// Initialization init.c
void init(int argc, char *argv[]);

// Lexical
// hold source file line buffer in scan.c
#define BUFLEN 4096
extern char linebuf[BUFLEN];
extern int bufsize;
extern int lineno;
extern int colmno;

// Syntax
// prog as AST, in parse.c
extern pgm_node_t *prog;
pgm_node_t *parse(void);

// Semantic
// in analysis.c

#endif /* End of _GLOBAL_H_ */
