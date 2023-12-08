#include "global.h"
#include "scan.h"
#include "parse.h"

char pgmname[120] = "input.pas";
pgm_s *prog;

void lextest()
{
	while (gettok() != ENDFILE)
		;
}

int main(int argc, char *argv[])
{
	msg("compiler %s start, version %s\n", PL0_NAME, PL0_VERSION);
	if (argc < 2) {
		msg("usage: ./%s <filename>\n", PL0_NAME);
		exit(1);
	}

	strcpy(pgmname, argv[argc - 1]);
	init(pgmname);

	// lextest();
	prog = parse();

	msg("done\n");
	return 0;
}
