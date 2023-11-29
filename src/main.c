#include "global.h"
#include "scan.h"

char pgmname[120] = "input.pas";

int main(int argc, char *argv[])
{
	msg("%s %s start\n", PL0_NAME, PL0_VERSION);
	if (argc < 2) {
		msg("usage: ./pl0c <filename>\n");
		exit(1);
	}

	strcpy(pgmname, argv[argc - 1]);
	init(pgmname);

	while (get_token() != ENDFILE)
		;
	return 0;
}
