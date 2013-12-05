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
FILE *stablist;
FILE *asmlist;
FILE *errlist;
FILE *tiplist;
FILE *astlist;
int lineno = 0;
int runlevel = 3;

BOOL TraceScan = FALSE;
BOOL PrintSource = TRUE;
BOOL ShowAST = TRUE;
BOOL ShowTip = TRUE;
BOOL ShowQuad = TRUE;

int main(int argc, const char *argv[])
{
	PgmSP ast; /* abstract syntax tree */
	char pgm[120] = "input.pas";
	char *codef;
	char *listingf;
	char *stablistf;
	char *asmlistf;
	char *astlistf;
	int fnlen;
	if (argc < 2) {
		fprintf(stdout, "usage: ./compiler <filename>\n");
		exit(1);
	}
	strcpy(pgm,argv[argc-1]);
	source = fopen(pgm, "r");
	if (source == NULL) {
		fprintf(stderr, "File %s not found\n", pgm);
		exit(1);
	}
	if (strchr(pgm, '.') == NULL) {
		strcat(pgm, ".pas");
	}
	fnlen = strcspn(pgm, ".");

	codef = (char *)calloc(fnlen + 3, sizeof(char));
	strncpy(codef, pgm, fnlen);
	strcat(codef, ".q");
	code = fopen(codef, "w");
	if (code == NULL) {
		fprintf(stderr, "Unable to open %s\n", codef);
		exit(1);
	}

	listingf = (char *)calloc(fnlen + 5, sizeof(char));
	strncpy(listingf, pgm, fnlen);
	strcat(listingf, ".lst");
	listing = fopen(listingf, "w");
	if (listing == NULL) {
		fprintf(stderr, "Unable to open %s\n", listingf);
		exit(1);
	}

	asmlistf = (char *)calloc(fnlen + 5, sizeof(char));
	strncpy(asmlistf, pgm, fnlen);
	strcat(asmlistf, ".asm");
	asmlist = fopen(asmlistf, "w");
	if (asmlist == NULL) {
		fprintf(stderr, "Unable to open %s\n", asmlistf);
		exit(1);
	}

	astlistf = (char *)calloc(fnlen + 5, sizeof(char));
	strncpy(astlistf, pgm, fnlen);
	strcat(astlistf, ".xml");
	astlist = fopen(astlistf, "w");
	if (astlist == NULL) {
		fprintf(stderr, "Unable to open %s\n", astlistf);
		exit(1);
	}

	stablistf = (char *)calloc(fnlen + 5, sizeof(char));
	strncpy(stablistf, pgm, fnlen);
	strcat(stablistf, ".stb");
	stablist = fopen(stablistf, "w");
	if (stablist == NULL) {
		fprintf(stderr, "Unable to open %s\n", stablistf);
		exit(1);
	}

	if (argv[argc-2][0] == 'd') {
		listing = stdout;
		code = stdout;
		stablist = stdout;
	}
	errlist = stderr;
	tiplist = stderr;
	if (runlevel > 2) {
		ast = parse();
	} else {
		exit(1);
	}
	if (runlevel > 1) {
		analyse(ast);
		coder(ast);
	} else {
		exit(1);
	}
	if (runlevel > 0) {
		elf();
	} else {
		exit(1);
	}
	fclose(source);
	fclose(code);
	fclose(asmlist);
	fclose(astlist);
	fclose(listing);
	fclose(stablist);
	fclose(errlist);
	fclose(tiplist);
	return 0;
}
