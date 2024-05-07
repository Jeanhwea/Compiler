#include "common.h"
#include "debug.h"
#include "error.h"
#include "global.h"
#include "limits.h"
#include "util.h"
#include <string.h>
#include <unistd.h>

// constants
char PL0E_NAME[MAXSTRLEN] = "pcc";
char PL0E_VERSION[MAXSTRLEN] = "v1.2.1";
char PL0E_INPUT[MAXSTRLEN] = "input.pas";
char PL0E_ASSEM[MAXSTRLEN] = "input.s";
char PL0E_OBJECT[MAXSTRLEN] = "input.o";
char PL0E_TARGET[MAXSTRLEN] = "a.out";

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
FILE *asmble = NULL;

phase_t phase = INIT;
int errnum = 0;

void pl0c_read_args(int argc, char *argv[])
{
	int i;
	for (i = 1; i < argc; ++i) {
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
		if (strlen(argv[i]) > 0 && argv[i][0] != '-') {
			strcpy(PL0E_INPUT, argv[i]);
		}
	}
	dbg("current input file %s\n", PL0E_INPUT);
}

void pl0c_startup_message()
{
	msg("compiler %s start, version %s\n", PL0E_NAME, PL0E_VERSION);
}

void pl0c_init_file()
{
	if (access(PL0E_INPUT, R_OK)) {
		msg("cannot read file %s\n", PL0E_INPUT);
		exit(EARGMT);
	}

	strcpy(PL0E_ASSEM, PL0E_INPUT);
	chgsuf(PL0E_ASSEM, ".s", ".pas");
	strcpy(PL0E_OBJECT, PL0E_INPUT);
	chgsuf(PL0E_OBJECT, ".o", ".pas");
	if (!PL0E_OPT_SET_TARGET_NAME) {
		strcpy(PL0E_TARGET, PL0E_INPUT);
		chgsuf(PL0E_TARGET, ".run", ".pas");
	}

	source = fopen(PL0E_INPUT, "r");
	if (!source) {
		panic("SOURCE_FILE_NOT_FOUND");
	}
	msg("reading file %s\n", PL0E_INPUT);
}

// init
void init(int argc, char *argv[])
{
	pl0c_read_args(argc, argv);

	pl0c_startup_message();

	pl0c_init_file();

	chkerr("init fail and exit.");
	phase = LEXICAL;
}
