#include "error.h"
#include "global.h"
#include "util.h"

// constants
char *PL0C_NAME = "pl0c";
char *PL0C_VERSION = "v0.13.6";
char PL0C_PROGNAME[4096];
char PL0C_TARGET[4096];

// debug
bool echo = FALSE;
bool silent = FALSE;

// files
FILE *source = NULL;
FILE *target = NULL;

phase_t phase = INIT;
int errnum = 0;

void pl0c_read_args(int argc, char *argv[])
{
	if (argc < 2) {
		msg("usage: %s source.pas\n", argv[0]);
		exit(EARGMT);
	}
	strcpy(PL0C_PROGNAME, argv[argc - 1]);
	strcpy(PL0C_TARGET, PL0C_PROGNAME);
	chgsuf(PL0C_TARGET, ".s", ".pas");
}

void pl0c_init_file(char *name)
{
	// Open Source Code File
	source = fopen(name, "r");
	if (source == NULL) {
		panic("source file not found!");
	}
	msg("reading file %s\n", name);

	// Open Target File
	target = fopen(name, "w");
	if (target == NULL) {
		panic("target file not found!");
	}
	msg("open target file %s\n", name);
}

// init
void init(int argc, char *argv[])
{
	pl0c_read_args(argc, argv);
	pl0c_init_file(PL0C_PROGNAME);
	chkerr("init fail and exit.");
	phase = LEXICAL;
}
