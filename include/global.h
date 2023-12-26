#ifndef _GLOBAL_H_
#define _GLOBAL_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "debug.h"
#include "limits.h"

// consts
extern char PL0E_NAME[];
extern char PL0E_VERSION[];
extern char PL0E_INPUT[];
extern char PL0E_ASSEM[];
extern char PL0E_OBJECT[];
extern char PL0E_TARGET[];

// option
extern bool PL0E_OPT_KEEP_NASM_FILE;
extern bool PL0E_OPT_KEEP_OBJECT_FILE;
extern bool PL0E_OPT_SET_TARGET_NAME;

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

// main entry function name
#define MAINFUNC "_start"

// Initialization init.c
void init(int argc, char *argv[]);

// Lexical
// hold source file line buffer in scan.c
extern char linebuf[MAXLINEBUF];
extern int bufsize;
token_t gettok(void);

// Syntax
// prog root, syntax tree, in parse.c
extern pgm_node_t *ast;
pgm_node_t *parse(void);

// Semantic
// in analysis.c
void analysis();

#endif /* End of _GLOBAL_H_ */
