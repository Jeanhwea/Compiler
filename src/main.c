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
int runlevel = 1;

BOOL TraceScan = TRUE;
BOOL PrintSource = TRUE;
BOOL ShowAST = TRUE;
BOOL ShowTip = TRUE;
BOOL ShowQuad = TRUE;

int main(int argc, const char *argv[])
{
	PgmSP ast; /* abstract syntax tree */
	char pgm[120] = "input.pas";
	char *codef;
	char *stablistf;
	char *asmlistf;
	char *astlistf;
	int fnlen;
	if (argc != 2) {
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

	listing = stdout;
	errlist = stderr;
	tiplist = stderr;
	ast = parse();
	analyse(ast);
	coder(ast);
	elf();
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
