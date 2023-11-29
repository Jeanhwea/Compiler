#include "common.h"
#include "debug.h"
#include "global.h"

char pgmname[120] = "input.pas";

int main(int argc, char *argv[])
{
	msg("compiler %s starts\n", PL0_VERSION);
	if (argc < 2) {
		msg("usage: ./pl0c <filename>\n");
		exit(1);
	}

	strcpy(pgmname, argv[argc - 1]);
	msg("read source file: %s\n", pgmname);
	init(pgmname);

	panic("ppp");
	dbg("yyy y = %d", 2);
	return 0;
}
