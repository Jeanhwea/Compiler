#ifndef _UTIL_H_
#define _UTIL_H_
#include <stdio.h>
#include <string.h>

char *dupstr(char *s);

#define PRTBUFSIZE 4096
extern char prtbuf[PRTBUFSIZE];

// strcat + sprintf
#define appendf(s, fmt, args...)                                               \
	do {                                                                   \
		sprintf(prtbuf, fmt, ##args);                                  \
		strcat(s, prtbuf);                                             \
	} while (0)

#endif /* End of _UTIL_H_ */
