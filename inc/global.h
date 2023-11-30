#ifndef _GLOBAL_H_
#define _GLOBAL_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "debug.h"

// PL0 meta data
extern char *PL0_NAME;
extern char *PL0_VERSION;

// compile phase
extern phase_t phase;
// source code file
extern FILE *source;
// target assembly file
extern FILE *target;

// source file line number, column number
extern int lineno;
extern int colmno;

void init(char *pgm);
#endif /* End of _GLOBAL_H_ */
