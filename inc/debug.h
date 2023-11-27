#ifndef _DEBUG_H_
#define _DEBUG_H_
#include <stdio.h>
#include <stdlib.h>

#define EPANIC 996

#define dbg(fmt, args...)                                                      \
	printf("%s:%d %s(): " #fmt "\n", __FILE__, __LINE__, __func__, ##args)

#define panic(msg)                                                             \
	do {                                                                   \
		fprintf(stderr, "%s:%d %s(): %s\n", __FILE__, __LINE__,        \
			__func__, msg);                                        \
		exit(EPANIC);                                                  \
	} while (0)

#endif /* End of _DEBUG_H_ */