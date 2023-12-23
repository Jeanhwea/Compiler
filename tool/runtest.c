#include "global.h"
#include "debug.h"
#include "glob.h"

#define MAXOUTPUT 4096
char actual[MAXOUTPUT];
char expect[MAXOUTPUT];

void runtest()
{
	FILE *fp;

	fp = popen("ls -l", "r");
	if (fp == NULL) {
		panic("fail to runtest.");
	}

	while (fgets(actual, MAXOUTPUT - 1, fp) != NULL) {
		printf("%s", actual);
	}

	pclose(fp);
}

void getpas()
{
	glob_t glob_result;
	glob("test/*.pas", GLOB_TILDE, NULL, &glob_result);

	int i;
	for (i = 0; i < glob_result.gl_pathc; ++i) {
		printf("%s\n", glob_result.gl_pathv[i]);
	}

	globfree(&glob_result);
}

int main(int argc, char *argv[])
{
	// runtest();
	getpas();
	return 0;
}
