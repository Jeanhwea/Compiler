/**
 * FILE: main.c
 * Date: Nov 3, 2012
 * Author: Jeanhwea
 */

#include "global.h"
#include "util.h"
#include "scan.h"

FILE *source;
FILE *listing;
int lineno = 0;

int TraceScan = TRUE;
int PrintSource = TRUE;

int main(int argc, const char *argv[])
{
	TreeNode *ast; /* abstract syntax tree */
	char pgm[120] = "input.pas";
	char tkn[120] = "11061191_token.txt";
	TokenType t;
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
//	listing = fopen(tkn,"w");
//	if (listing == NULL) {
//		fprintf(stderr, "File %s cannot be created\n", tkn);
//		exit(1);
//	}
	listing = stdout;
	do {
		t = getToken();
	} while (t != ENDFILE);
	fclose(source);
//	fclose(listing);
}
