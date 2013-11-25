/**
 * FILE: main.c
 * Date: Nov 3, 2012
 * Author: Jeanhwea
 */

#include "global.h"
#include "scan.h"
#include "util.h"
#include "parse.h"
#include "analyse.h"
#include "code.h"
#include "elf.h"

FILE *source;
FILE *listing;
FILE *code;
FILE *asmlist;
FILE *errlist;
FILE *tiplist;
int lineno = 0;

BOOL TraceScan = FALSE;
BOOL PrintSource = FALSE;
BOOL ShowAST = FALSE;
BOOL ShowTip = FALSE;
BOOL ShowQuad = TRUE;

int main(int argc, const char *argv[])
{
	PgmSP ast; /* abstract syntax tree */
	char pgm[120] = "input.pas";
	int i;
	if (argc < 2) {
		fprintf(stdout, "usage: ./compiler <filename>\n");
		exit(1);
	}
	if (argc > 2) {
		for (i = 0; i < strlen(argv[argc-2]); i++) {
			if (argv[argc-2][i] == 's') {
				TraceScan = TRUE;
			} else if (argv[argc-2][i] == 'p') {
				PrintSource = TRUE;
			} else if (argv[argc-2][i] == 'a') {
				ShowAST = TRUE;
			} else if (argv[argc-2][i] == 't') {
				ShowTip = TRUE;
			}
		}
	}
	strcpy(pgm,argv[argc-1]);
	source = fopen(pgm, "r");
	if (source == NULL) {
		fprintf(stderr, "File %s not found\n", pgm);
		exit(1);
	}
	listing = stderr;
	code = stderr;
	asmlist = stdout;
	errlist = stderr;
	tiplist = stderr;
	ast = parse();
	analyse(ast);
	coder(ast);
	elf();
	fclose(source);
	/*
	 *fclose(listing);
	 *fclose(errlist);
	 *fclose(tiplist);
	 */
	return 0;
}
