#include "global.h"
#include "limits.h"
#include "util.h"
#include <string.h>

// for appendf(...)
char prtbuf[MAXSTRBUF];

void strcopy(char *d, char *s)
{
	strncpy(d, s, MAXSTRLEN);
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
