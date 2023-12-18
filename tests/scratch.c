#include "global.h"
#include "x86.h"

int main(int argc, char *argv[])
{
	for (int i = 0; i < 2; ++i) {
		reg_t *r = aquire();
		msg("r = %s\n", r->name);
	}

	for (int i = 0; i < 8; ++i) {
		reg_t *r = aquire();
		msg("r = %s\n", r->name);
		putreg(r);
	}
	return 0;
}
