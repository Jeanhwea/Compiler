#include "global.h"
#include "util.h"

char prtbuf[PRTBUFSIZE];

char *dupstr(char *s)
{
	int n;
	char *t;
	if (s == NULL) {
		return NULL;
	}
	n = strlen(s) + 1;
	t = (char *)malloc(n * sizeof(char));
	if (t == NULL) {
		panic("OUT_OF_MEMERY");
	}
	strcpy(t, s);
	return t;
}
