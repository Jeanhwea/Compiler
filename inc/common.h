#ifndef _COMMON_H_
#define _COMMON_H_
#include <stdio.h>
#include <stdlib.h>

extern char *PL0_VERSION;

#define panic(fmt, args...)                                                    \
	do {                                                                   \
		fprintf(stderr, "%s:%d %s(): " #fmt "\n", __FILE__, __LINE__,  \
			__func__, ##args);                                     \
		exit(123);                                                     \
	} while (0)

#endif /* End of _COMMON_H_ */
