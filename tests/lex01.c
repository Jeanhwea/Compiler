#include "global.h"
#include "scan.h"

int main(int argc, char *argv[])
{
	echo = TRUE;
	init(argc, argv);

	token_t tok;
	while ((tok = gettok()) != ENDFILE) {
		msg("line: %s\n", linebuf);
	}

	return 0;
}
