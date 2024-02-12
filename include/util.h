#ifndef _UTIL_H_
#define _UTIL_H_
#include "limits.h"
#include "common.h"
#include <stdio.h>
#include <string.h>

extern char prtbuf[MAXSTRBUF];

// strcat + sprintf
#define appendf(s, fmt, args...)                                               \
	do {                                                                   \
		sprintf(prtbuf, fmt, ##args);                                  \
		strcat(s, prtbuf);                                             \
	} while (0)

void strcopy(char *d, char *s);
void chgsuf(char *str, char *to, char *from);
char *itoa(int num);
bool chkcmd(char *cmd);
#endif /* End of _UTIL_H_ */
