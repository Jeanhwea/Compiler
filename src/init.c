#include <stdio.h>
#include "global.h"

char *PL0_NAME = "pl0c";
char *PL0_VERSION = "v0.11.0";

phase_t phase = INIT;

FILE *source = NULL;
FILE *target = NULL;

int lineno = 0;

void open_source_file(char *pgm)
{
	source = fopen(pgm, "r");
	if (source == NULL) {
		panic("source file not found!");
	}
	msg("reading file %s\n", pgm);
}

void init(char *pgm)
{
	open_source_file(pgm);
}
