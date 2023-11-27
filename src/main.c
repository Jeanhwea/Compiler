#include "common.h"
#include "debug.h"
#include "global.h"

FILE *fsource;

int main(int argc, char *argv[])
{
	printf("compiler %s starts\n", PL0_VERSION);
	dbg("xxx phase = %d", phase);
	panic("ppp");
	dbg("yyy y = %d", 2);
	return 0;
}
