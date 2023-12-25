#include "common.h"
#include "debug.h"
#include "error.h"
#include "global.h"
#include "util.h"
#include <string.h>

// constants
char PL0E_NAME[32] = "pl0c";
char PL0E_VERSION[32] = "v0.15.6";
char PL0E_INPUT[4096] = "input.pas";
char PL0E_ASSEM[4096] = "input.s";
char PL0E_OBJECT[4096] = "input.o";
char PL0E_TARGET[4096] = "a.out";

// options
bool PL0E_OPT_QUIET = FALSE;
bool PL0E_OPT_VERBOSE = FALSE;
bool PL0E_OPT_KEEP_NASM_FILE = FALSE;
bool PL0E_OPT_KEEP_OBJECT_FILE = FALSE;
bool PL0E_OPT_SET_TARGET_NAME = FALSE;

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

	for (int i = 0; i < argc; ++i) {
		if (!strcmp("-q", argv[i])) {
			PL0E_OPT_QUIET = TRUE;
			echo = FALSE;
			silent = TRUE;
			continue;
		}
		if (!strcmp("-v", argv[i])) {
			PL0E_OPT_VERBOSE = TRUE;
			echo = TRUE;
			silent = FALSE;
			continue;
		}
		if (!strcmp("-s", argv[i])) {
			PL0E_OPT_KEEP_NASM_FILE = TRUE;
			continue;
		}
		if (!strcmp("-c", argv[i])) {
			PL0E_OPT_KEEP_OBJECT_FILE = TRUE;
			continue;
		}
		if (!strcmp("-o", argv[i])) {
			PL0E_OPT_SET_TARGET_NAME = TRUE;
			i++;
			if (i == argc) {
				panic("should give target file name after -o");
			}
			strcpy(PL0E_TARGET, argv[i]);
			continue;
		}
		strcpy(PL0E_INPUT, argv[i]);
	}

	strcpy(PL0E_ASSEM, PL0E_INPUT);
	chgsuf(PL0E_ASSEM, ".s", ".pas");
	strcpy(PL0E_OBJECT, PL0E_INPUT);
	chgsuf(PL0E_OBJECT, ".o", ".pas");
	if (!PL0E_OPT_SET_TARGET_NAME) {
		strcpy(PL0E_TARGET, PL0E_INPUT);
		chgsuf(PL0E_TARGET, ".run", ".pas");
	}
}

void pl0c_init_file()
{
	source = fopen(PL0E_INPUT, "r");
	if (source == NULL) {
		panic("source file not found!");
	}
	msg("reading file %s\n", PL0E_INPUT);
}

// init
void init(int argc, char *argv[])
{
	pl0c_read_args(argc, argv);
	pl0c_init_file();
	chkerr("init fail and exit.");
	phase = LEXICAL;
}
