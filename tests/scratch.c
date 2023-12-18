#include "global.h"
#include "x86.h"

int main(int argc, char *argv[])
{
	for (int i = 0; i < 2; ++i) {
		reg_t *r = ralloc();
		msg("r = %s\n", r->name);
	}

	for (int i = 0; i < 8; ++i) {
		reg_t *r = ralloc();
		msg("r = %s\n", r->name);
		rfree(r);
	}
	return 0;
}
