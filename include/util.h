#ifndef _UTIL_H_
#define _UTIL_H_
#include <stdio.h>
#include <string.h>

#define MAXSTRBUF 4096
#define PRTBUFSIZE 4096
extern char prtbuf[PRTBUFSIZE];

// strcat + sprintf
#define appendf(s, fmt, args...)                                               \
	do {                                                                   \
		sprintf(prtbuf, fmt, ##args);                                  \
		strcat(s, prtbuf);                                             \
	} while (0)

char *dupstr(char *s);
void chgsuf(char *str, char *to, char *from);
char *itoa(int num);
#endif /* End of _UTIL_H_ */
