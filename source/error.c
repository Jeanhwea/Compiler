#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "debug.h"
#include "error.h"

void quit(char *file, int line, const char *func, int errno, char *msg)
{
	char *prefix = "QUIT";
	if (errno == EABORT) {
		prefix = "ABORT";
	} else if (errno == EPANIC) {
		prefix = "PANIC";
	}

	fprintf(stderr, "%s: %s:%d %s(): %s\n", prefix, file, line, func, msg);

	exit(errno);
}
