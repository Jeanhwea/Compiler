#include "global.h"
#include "scan.h"

int main(int argc, char *argv[])
{
	echo = FALSE;
	init(argc, argv);

	token_t tok;
	while ((tok = gettok()) != ENDFILE) {
		msg("line%03d: %s", lineno, linebuf);
		for (int i = 0; i < colmno + 7; ++i) {
			msg(" ");
		}
		msg("^ token=%d, buf=%s\n", tok, tokbuf);
	}

	return 0;
}
