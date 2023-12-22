#include "global.h"
#include "scan.h"

int main(int argc, char *argv[])
{
	echo = FALSE;
	init(argc, argv);

	token_t tok;
	int seq = 0;
	char *indent = "              ";
	while ((tok = gettok()) != ENDFILE) {
		int i;
		for (i = 0; i < 80; ++i) {
			msg("-");
		}
		msg("\n");
		msg("#%03d LINE%03d: %s", ++seq, lineno, linebuf);

		int toksize = strlen(tokbuf);
		int start = colmno - toksize;
		msg("%s", indent);
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

		msg("%s", indent);
		for (i = 0; i < start + toksize; ++i) {
			msg(" ");
		}
		msg("`-- ");
		msg("token=%d, buf=[%s]\n", tok, tokbuf);
	}

	return 0;
}
