#include "global.h"
#include "scan.h"

int main(int argc, char *argv[])
{
	echo = TRUE;
	init(argc, argv);

	token_t tok;
	while ((tok = gettok()) != ENDFILE) {
		msg("line %02d: %s\n", lineno, linebuf);
	}

	return 0;
}
