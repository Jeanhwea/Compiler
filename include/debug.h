#ifndef _DEBUG_H_
#define _DEBUG_H_
#include "error.h"

void quit(char *file, int line, const char *func, int errno, char *msg);

// print message
#define msg(fmt, args...)                                                      \
	do {                                                                   \
		if (silent) {                                                  \
			printf(fmt, ##args);                                   \
		}                                                              \
	} while (0)

// debug print message
#define dbg(fmt, args...)                                                      \
	do {                                                                   \
		if (echo) {                                                    \
			printf("%s:%d %s(): " fmt, __FILE__, __LINE__,         \
			       __func__, ##args);                              \
		}                                                              \
	} while (0)

// panic function
#define panic(msg) quit(__FILE__, __LINE__, __func__, EPANIC, msg);

// debug unlikely case function
#define unlikely() quit(__FILE__, __LINE__, __func__, EABORT, "unlikely case");
#define nevernil(p)                                                            \
	do {                                                                   \
		if (!p) {                                                      \
			unlikely();                                            \
		}                                                              \
	} while (0)

#endif /* End of _DEBUG_H_ */
