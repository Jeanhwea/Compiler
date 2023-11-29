#include <stdio.h>
#include "global.h"

char *PL0_VERSION = "v0.10.1";

phase_t phase = INIT;

FILE *source = NULL;
FILE *target = NULL;

int lineno = 0;
