#include "global.h"
#include "util.h"
#include <string.h>

char prtbuf[PRTBUFSIZE];

// duplicate string, this function will alloc a new memory
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

// change suffix: from => to, str
void chgsuf(char *str, char *to, char *from)
{
	char buf[MAXSTRBUF];
	char *pos;
	while ((pos = strstr(str, from)) != NULL) {
		// prepare prefix
		strncpy(buf, str, pos - str);
		buf[pos - str] = '\0';

		// append new suffix
		strcat(buf, to);

		// copy to dest str
		strcpy(str, buf);
	}
}

char numbuf[32];
char *itoa(int num)
{
	sprintf(numbuf, "%d", num);
	return numbuf;
}
