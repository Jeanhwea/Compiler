#include "debug.h"
#include <stdlib.h>
#include <stdio.h>

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

int main(int argc, char *argv[])
{
	runtest();
	return 0;
}
