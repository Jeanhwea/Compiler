#include "global.h"
#include "scan.h"

int main(int argc, char *argv[])
{
	echo = 0;
	silent = 1;
	init(argc, argv);
	int counter = 0;

	token_t tok;
	while ((tok = gettok()) != ENDFILE) {
		printf("%03d: token=%d, buf=[%s]\n", ++counter, tok, tokbuf);
	}

	return 0;
}
