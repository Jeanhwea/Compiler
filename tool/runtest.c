#include <stdio.h>
#include "global.h"
#include "debug.h"
#include "glob.h"
#include "limits.h"
#include "util.h"

#define MAXCASE 100
#define MAXNAMELEN 1024
int ncase = 0;
char cases[MAXCASE][MAXNAMELEN];

#define MAXOUTPUT 4096
char actual[MAXOUTPUT];
char expect[MAXOUTPUT];

void findtest()
{
	glob_t glob_result;
	glob("./test/*.pas", GLOB_TILDE, NULL, &glob_result);

	int i;
	for (i = 0; i < glob_result.gl_pathc; ++i) {
		strncpy(cases[ncase++], glob_result.gl_pathv[i], MAXNAMELEN);
	}

	globfree(&glob_result);
}

void rtrim(char *s)
{
	int len = strlen(s);
	if (s[len - 1] == '\n') {
		s[len - 1] = '\0';
	}
}

void build(int id)
{
	char cmd[MAXSTRBUF];
	sprintf(cmd, "./%s -q %s", PL0E_NAME, cases[id]);
	system(cmd);
}

void test(int id)
{
	FILE *fe, *fa;

	char txt[MAXNAMELEN];
	strncpy(txt, cases[id], MAXNAMELEN);
	chgsuf(txt, ".txt", ".pas");

	fe = fopen(txt, "r");
	if (fe == NULL) {
		panic("fail to open expected file.");
	}

	char exe[MAXNAMELEN];
	strncpy(exe, cases[id], MAXNAMELEN);
	chgsuf(exe, ".run", ".pas");

	fa = popen(exe, "r");
	if (fa == NULL) {
		panic("fail to runtest.");
	}

	while (fgets(expect, MAXOUTPUT - 1, fe) != NULL) {
		if (fgets(actual, MAXOUTPUT - 1, fa) != NULL) {
			rtrim(expect);
			rtrim(actual);

			if (!strncmp(expect, actual, MAXOUTPUT - 1)) {
				continue;
			}
		}

		msg("test case: %s failed.\n", cases[id]);
		goto done;
	}

	while (fgets(actual, MAXOUTPUT - 1, fa) != NULL) {
		rtrim(actual);
		if (strlen(actual) > 0) {
			msg("test case: %s failed.\n", cases[id]);
			goto done;
		}
	}

	// msg("test case: %s pass.\n", cases[id]);
done:
	pclose(fe);
	pclose(fa);
	remove(exe);
}

int main(int argc, char *argv[])
{
	findtest();
	int i;
	for (i = 0; i < ncase; ++i) {
		build(i);
		test(i);
	}
	return 0;
}
