#include "global.h"
#include "scan.h"

int main(int argc, char *argv[])
{
	echo = FALSE;
	init(argc, argv);

	token_t tok;
	while ((tok = gettok()) != ENDFILE) {
		for (int i = 0; i < 80; ++i) {
			msg("-");
		}
		msg("\n");
		msg("LINE%03d: %s", lineno, linebuf);

		int toksize = strlen(tokbuf);
		int start = colmno - toksize;
		msg("         ");
		for (int i = 0; i < bufsize; ++i) {
			if (i < start) {
				msg(" ");
			} else if (i < start + toksize) {
				msg("^");
			} else {
				break;
			}
		}
		msg("\n");

		msg("         ");
		for (int i = 0; i < start + toksize; ++i) {
			msg(" ");
		}
		msg("`-- ");
		msg("token=%d, tokbuf=[%s]\n", tok, tokbuf);
	}

	return 0;
}
