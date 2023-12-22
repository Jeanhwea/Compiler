#include "error.h"
#include "global.h"
#include "util.h"

// constants
char PL0E_NAME[32] = "pl0c";
char PL0E_VERSION[32] = "v0.15.2";
char PL0E_INPUT[4096] = "input.pas";
char PL0E_ASSEM[4096] = "input.s";
char PL0E_OBJECT[4096] = "input.o";
char PL0E_TARGET[4096] = "a.out";

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
	strcpy(PL0E_INPUT, argv[argc - 1]);
	strcpy(PL0E_ASSEM, PL0E_INPUT);
	strcpy(PL0E_OBJECT, PL0E_INPUT);
	strcpy(PL0E_TARGET, PL0E_INPUT);
	chgsuf(PL0E_ASSEM, ".s", ".pas");
	chgsuf(PL0E_OBJECT, ".o", ".pas");
	chgsuf(PL0E_TARGET, ".run", ".pas");
}

void pl0c_init_file()
{
	// Open Source Code File
	source = fopen(PL0E_INPUT, "r");
	if (source == NULL) {
		panic("source file not found!");
	}
	msg("reading file %s\n", PL0E_INPUT);

	// Open Target File
	target = fopen(PL0E_ASSEM, "w");
	if (target == NULL) {
		panic("target file not found!");
	}
	msg("open target file %s\n", PL0E_ASSEM);
}

// init
void init(int argc, char *argv[])
{
	pl0c_read_args(argc, argv);
	pl0c_init_file();
	chkerr("init fail and exit.");
	phase = LEXICAL;
}
