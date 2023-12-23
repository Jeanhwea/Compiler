#include "global.h"
#include "debug.h"
#include "glob.h"
#include "stdio.h"
#include "util.h"

#define MAXCASE 100
#define MAXNAMELEN 1024
int ncase = 0;
char cases[MAXCASE][MAXNAMELEN];

#define MAXOUTPUT 4096
char actual[MAXOUTPUT];
char expect[MAXOUTPUT];

void gettests()
{
	glob_t glob_result;
	glob("./benchmark/*.pas", GLOB_TILDE, NULL, &glob_result);

	int i;
	for (i = 0; i < glob_result.gl_pathc; ++i) {
		strncpy(cases[ncase++], glob_result.gl_pathv[i], MAXNAMELEN);
	}

	globfree(&glob_result);
}

void build(int id)
{
	char cmd[4096];
	sprintf(cmd, "./pl0c %s", cases[id]);
	system(cmd);
}

void test(int id)
{
	FILE *fe, *fa;

	char expt[MAXNAMELEN];
	strncpy(expt, cases[id], MAXNAMELEN);
	chgsuf(expt, ".pas", ".txt");

	fe = fopen(expt, "r");
	if (fe == NULL) {
		panic("fail to open expected file.");
	}

	char exeu[MAXNAMELEN];
	strncpy(exeu, cases[id], MAXNAMELEN);
	chgsuf(exeu, ".pas", ".run");

	fa = popen(exeu, "r");
	if (fa == NULL) {
		panic("fail to runtest.");
	}

	while (fgets(actual, MAXOUTPUT - 1, fa) != NULL) {
		printf("%s", actual);
	}

	pclose(fe);
	pclose(fa);
}

int main(int argc, char *argv[])
{
	gettests();
	for (int i = 0; i < ncase; ++i) {
		build(i);
		test(i);
	}
	return 0;
}
