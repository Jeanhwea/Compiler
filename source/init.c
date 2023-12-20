#include "error.h"
#include "global.h"
#include "util.h"

// constants
char PL0C_NAME[32] = "pl0c";
char PL0C_VERSION[32] = "v0.14.0";
char PL0C_INPUT[4096] = "input.pas";
char PL0C_ASSEM[4096] = "input.s";
char PL0C_OBJECT[4096] = "input.o";
char PL0C_TARGET[4096] = "a.out";

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
	strcpy(PL0C_INPUT, argv[argc - 1]);
	strcpy(PL0C_ASSEM, PL0C_INPUT);
	strcpy(PL0C_OBJECT, PL0C_INPUT);
	strcpy(PL0C_TARGET, PL0C_INPUT);
	chgsuf(PL0C_ASSEM, ".s", ".pas");
	chgsuf(PL0C_OBJECT, ".o", ".pas");
	chgsuf(PL0C_TARGET, ".run", ".pas");
}

void pl0c_init_file()
{
	// Open Source Code File
	source = fopen(PL0C_INPUT, "r");
	if (source == NULL) {
		panic("source file not found!");
	}
	msg("reading file %s\n", PL0C_INPUT);

	// Open Target File
	target = fopen(PL0C_ASSEM, "w");
	if (target == NULL) {
		panic("target file not found!");
	}
	msg("open target file %s\n", PL0C_ASSEM);
}

// init
void init(int argc, char *argv[])
{
	pl0c_read_args(argc, argv);
	pl0c_init_file();
	chkerr("init fail and exit.");
	phase = LEXICAL;
}
