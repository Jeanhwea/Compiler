#include "global.h"
#include "scan.h"

int main(int argc, char *argv[])
{
	echo = FALSE;
	init(argc, argv);
	int counter = 0;

	token_t tok;
	while ((tok = gettok()) != ENDFILE) {
		int i;
		for (i = 0; i < 80; ++i) {
			msg("-");
		}
		msg("\n");
		msg("%03d: %s", lineno, linebuf);

		int toksize = strlen(tokbuf);
		int start = colmno - toksize;
		msg("     ");
		for (i = 0; i < bufsize; ++i) {
			if (i < start) {
				msg(" ");
			} else if (i < start + toksize) {
				msg("^");
			} else {
				break;
			}
		}
		msg("\n");

		msg("     ");
		for (i = 0; i < start + toksize; ++i) {
			msg(" ");
		}
		msg("`--(%d)-- ", ++counter);
		msg("token=%d, buf=[%s]\n", tok, tokbuf);
	}

	return 0;
}
