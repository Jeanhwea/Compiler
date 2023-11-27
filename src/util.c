#include "common.h"

FILE pl0_open_file(char *name)
{
	FILE *f = fopen(name, "r");
	if (f == NULL) {
		panic("fail to open file");
	}
}
