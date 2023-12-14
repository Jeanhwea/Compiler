#include "global.h"

int main(int argc, char *argv[])
{
	echo = FALSE;
	init(argc, argv);
	int counter = 0;

	token_t tok;
	while ((tok = gettok()) != ENDFILE) {
		msg("%03d: token=%d, buf=[%s]\n", ++counter, tok, tokbuf);
	}

	return 0;
}
