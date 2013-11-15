/**
 * FILE: main.c
 * Date: Nov 3, 2012
 * Author: Jeanhwea
 */

#include "global.h"
#include "util.h"
#include "scan.h"
#include "parse.h"
#include "analyse.h"

FILE *source;
FILE *listing;
FILE *errlist;
FILE *tiplist;
int lineno = 0;

BOOL TraceScan = FALSE;
BOOL PrintSource = FALSE;
BOOL ShowAST = TRUE;
BOOL ShowTip = FALSE;

int main(int argc, const char *argv[])
{
	PgmSP ast; /* abstract syntax tree */
	char pgm[120] = "input.pas";
	if (argc != 2) {
		fprintf(stdout, "usage: ./compiler <filename>\n");
		exit(1);
	}
	strcpy(pgm,argv[1]);
	source = fopen(pgm, "r");
	if (source == NULL) {
		fprintf(stderr, "File %s not found\n", pgm);
		exit(1);
	}
	listing = stdout;
	errlist = stderr;
	tiplist = stderr;
	ast = parse();
	analyse(ast);
	fclose(source);
	/*
	 *fclose(listing);
	 *fclose(errlist);
	 *fclose(tiplist);
	 */
	return 0;
}
