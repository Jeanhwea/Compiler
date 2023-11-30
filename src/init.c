#include <stdio.h>
#include "global.h"

char *PL0_NAME = "pl0c";
char *PL0_VERSION = "v0.11.0";

phase_t phase = INIT;

FILE *source = NULL;
FILE *target = NULL;

// Open Source Code File
void pl0_open_source(char *pgm)
{
	source = fopen(pgm, "r");
	if (source == NULL) {
		panic("source file not found!");
	}
	msg("reading file %s\n", pgm);
}

void init(char *pgm)
{
	pl0_open_source(pgm);
}
