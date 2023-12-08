#ifndef _DEBUG_H_
#define _DEBUG_H_
#include "error.h"

void quit(char *file, int line, const char *func, int errno, char *msg);

#define msg(fmt, args...) printf(fmt, ##args)

#define dbg(fmt, args...)                                                      \
	printf("%s:%d %s(): " fmt, __FILE__, __LINE__, __func__, ##args)

// panic function
#define panic(msg) quit(__FILE__, __LINE__, __func__, EPANIC, msg);

// debug function
#define unlikely() quit(__FILE__, __LINE__, __func__, EABORT, "unlikely case");

#endif /* End of _DEBUG_H_ */
