#include "common.h"
#include "debug.h"

void quit(const char *file, const int line, const char *func, const char *msg)
{
	fprintf(stderr, "ABORT: %s:%d %s(): %s\n", file, line, func, msg);
	exit(EABORT);
}
