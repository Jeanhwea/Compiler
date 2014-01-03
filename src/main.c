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
#include "symtab.h"
#include "quad.h"
#include "elf.h"
#include "dag.h"
#include "bblock.h"
#include "fgraph.h"

FILE *source;
FILE *listing;
FILE *code;
FILE *stablist;
FILE *asmlist;
FILE *errlist;
FILE *tiplist;
FILE *astlist;
FILE *daglist;
FILE *asmoptim;
int lineno = 0;
int runlevel = 3;

BOOL TraceScan = TRUE;
BOOL PrintSource = TRUE;
BOOL ShowAST = TRUE;
BOOL ShowTip = TRUE;
BOOL ShowQuad = TRUE;

char pgm[120] = "input.pas";
int fnlen;
char *codef;
char *listingf;
char *stablistf;
char *asmlistf;
char *astlistf;
char *asmoptimf;

void do_compile(void)
{
	int state;
	pid_t pid;
	if ((pid = fork()) < 0) {
		fprintf(stderr, "can not fork");
		exit(1);
	}
	if (pid == 0) {
		execl("/usr/bin/nasm", "nasm", "-g", "-f", "elf", asmlistf, (char *)0);
	} else {
		wait(&state);
	}
}

void do_link(void)
{
	int state;
	pid_t pid;
	char *objfile;
	char *outputfile;
	outputfile = (char *)calloc(fnlen + 1, sizeof(char));
	objfile = (char *)calloc(fnlen + 3, sizeof(char));
	strncpy(outputfile, pgm, fnlen);
	strncpy(objfile, pgm, fnlen);
	strcat(objfile, ".o");
	if ((pid = fork()) < 0) {
		fprintf(stderr, "can not fork");
		exit(1);
	}
	if (pid == 0) {
		execl("/usr/bin/gcc", "gcc","-g", "-o", outputfile, objfile, (char *)0);
	} else {
		wait(&state);
	}
}

int main(int argc, const char *argv[])
{
	PgmSP ast; /* abstract syntax tree */
	BOOL debug = FALSE;
	BOOL optim = FALSE;
	BOOL compile_and_link = FALSE;

	fprintf(stdout, "compiler version 0.9.9 starting ...\n");
	if (argc < 2) {
		fprintf(stdout, "usage: ./compiler <filename>\n");
		exit(1);
	}
	strcpy(pgm,argv[argc-1]);
	source = fopen(pgm, "r");
	if (source == NULL) {
		fprintf(stderr, "File `%s` not found\n", pgm);
		exit(1);
	}
	if (strchr(pgm, '.') == NULL) {
		strcat(pgm, ".pas");
	}
	fnlen = strcspn(pgm, ".");

	if (argv[argc-2][0] == 'd') {
		debug = TRUE;
		listing = stdout;
		code = stdout;
		stablist = stdout;
	} else if (argv[argc-2][0] == 'o') {
		debug = TRUE;
		optim = TRUE;
		listing = stdout;
		code = stdout;
		stablist = stdout;
	} else if (argv[argc-2][0] == 's') {
		// optimation without debug flag
		optim = TRUE;
		listing = stdout;
		code = stdout;
		stablist = stdout;
	} else if (argv[argc-2][0] == 'c') {
		compile_and_link = TRUE;
		listing = stdout;
		code = stdout;
		stablist = stdout;
	} 
	daglist = stdout;
	errlist = stderr;
	tiplist = stderr;

	asmlistf = (char *)calloc(fnlen + 5, sizeof(char));
	strncpy(asmlistf, pgm, fnlen);
	strcat(asmlistf, ".asm");
	asmlist = fopen(asmlistf, "w");
	if (asmlist == NULL) {
		fprintf(stderr, "Unable to open %s\n", asmlistf);
		exit(1);
	}

	if (optim) {
		asmoptimf = (char *)calloc(fnlen + 16, sizeof(char));
		strncpy(asmoptimf, pgm, fnlen);
		strcat(asmoptimf, ".optim.asm");
		asmoptim = fopen(asmoptimf, "w");
		if (asmoptim == NULL) {
			fprintf(stderr, "Unable to open %s\n", asmoptimf);
			exit(1);
		}

	}

	astlistf = (char *)calloc(fnlen + 5, sizeof(char));
	strncpy(astlistf, pgm, fnlen);
	strcat(astlistf, ".xml");
	astlist = fopen(astlistf, "w");
	if (astlist == NULL) {
		fprintf(stderr, "Unable to open %s\n", astlistf);
		exit(1);
	}
	
	if (!debug) {
		codef = (char *)calloc(fnlen + 6, sizeof(char));
		strncpy(codef, pgm, fnlen);
		strcat(codef, ".qaud");
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

		stablistf = (char *)calloc(fnlen + 5, sizeof(char));
		strncpy(stablistf, pgm, fnlen);
		strcat(stablistf, ".stb");
		stablist = fopen(stablistf, "w");
		if (stablist == NULL) {
			fprintf(stderr, "Unable to open %s\n", stablistf);
			exit(1);
		}
	}
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
	// add optimization
	if (optim) {
		print_all_variables();
		fclose(asmlist);
		// redirection normal asm file
		// into optimational asm file
		asmlist = asmoptim;
		make_fgraph();
		// elf_optim();
		dataflow();
		global_reg_alocate();
	}
	fclose(source);
	if(!optim) fclose(asmlist);
	fclose(astlist);
	if (!debug) {
		fclose(code);
		fclose(listing);
		fclose(stablist);
	}
	if (optim) {
		fclose(asmoptim);
	}
	if (compile_and_link) {
		do_compile();
		do_link();
	}
	fprintf(stdout, "__ done __\n");
	return 0;
}
