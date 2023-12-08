#ifndef _DEBUG_H_
#define _DEBUG_H_
#include <stdio.h>
#include <stdlib.h>

void quit(const char *file, const int line, const char *func, const char *msg);

#define EPANIC 996
#define EABORT 997

#define msg(fmt, args...) printf(fmt, ##args)

#define dbg(fmt, args...)                                                      \
	printf("%s:%d %s(): " fmt, __FILE__, __LINE__, __func__, ##args)

// panic function
#define panic(msg)                                                             \
	do {                                                                   \
		fprintf(stderr, "PANIC: %s:%d %s(): %s\n", __FILE__, __LINE__, \
			__func__, msg);                                        \
		exit(EPANIC);                                                  \
	} while (0)

// debug function
#define unlikely()                                                             \
	do {                                                                   \
		quit(__FILE__, __LINE__, __func__, "UNLIKELY");                \
	} while (0)
#endif /* End of _DEBUG_H_ */
