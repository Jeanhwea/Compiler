#include "global.h"
#include "scan.h"

char pgmname[120] = "input.pas";

int main(int argc, char *argv[])
{
	msg("compiler %s starts\n", PL0_VERSION);
	if (argc < 2) {
		msg("usage: ./pl0c <filename>\n");
		exit(1);
	}

	strcpy(pgmname, argv[argc - 1]);
	init(pgmname);

	get_token();
	return 0;
}
