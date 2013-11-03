/**
 * FILE: main.c
 * Date: Nov 3, 2012
 * Author: Jeanhwea
 */

#include <global.h>
#include <util.h>
#include <scan.h>

int main(int argc, const char *argv[])
{
	TreeNode *ast; /* abstract syntax tree */
	char pgm[120] = "foo.pas";
	source = fopen(pgm, "r");
	if (source == NULL) {
		fprintf(stderr, "File %s not found\n", pgm);
		exit(1);
	}
	return 0;
}
