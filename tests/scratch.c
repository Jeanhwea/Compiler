#include "global.h"
#include "x86.h"

int main(int argc, char *argv[])
{
	int i;
	for (i = 0; i < 2; ++i) {
		reg_t *r = allocreg();
		msg("r = %s\n", r->name);
	}

	for (i = 0; i < 8; ++i) {
		reg_t *r = allocreg();
		msg("r = %s\n", r->name);
		freereg(r);
	}
	return 0;
}
