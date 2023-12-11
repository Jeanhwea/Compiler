#include <stdio.h>
#include "global.h"

// constants
char *PL0C_NAME = "pl0c";
char *PL0C_VERSION = "v0.11.4";
char PL0C_PROGNAME[4096];

// debug
bool echo = TRUE;

// files
FILE *source = NULL;
FILE *target = NULL;

phase_t phase = INIT;

// inner
pgm_s *prog;

void pl0c_init_args(int argc, char *argv[])
{
	if (argc < 2) {
		msg("usage: ./%s <filename>\n", PL0C_NAME);
		exit(1);
	}
	strcpy(PL0C_PROGNAME, argv[argc - 1]);
}

void pl0c_init_file(char *pgm)
{
	// Open Source Code File
	source = fopen(pgm, "r");
	if (source == NULL) {
		panic("source file not found!");
	}
	msg("reading file %s\n", pgm);
}

// init
void init(int argc, char *argv[])
{
	pl0c_init_args(argc, argv);
	pl0c_init_file(PL0C_PROGNAME);
}
