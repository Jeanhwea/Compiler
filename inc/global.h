#ifndef _GLOBAL_H_
#define _GLOBAL_H_
#include <stdio.h>
#include <stdlib.h>
#include "common.h"

// current version
extern char *PL0_VERSION;

// compile phase
extern phase_t phase;
// source code file
extern FILE *source;
// target assembly file
extern FILE *target;

#endif /* End of _GLOBAL_H_ */
