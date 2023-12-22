#include "global.h"
#include "scan.h"

int main(int argc, char *argv[])
{
	echo = 0;
	silent = 1;
	init(argc, argv);

	token_t tok;
	int seq = 0;
	char *indent = "              ";
	while ((tok = gettok()) != ENDFILE) {
		int i;
		for (i = 0; i < 60; ++i) {
			printf("-");
		}
		printf("\n");
		printf("#%03d LINE%03d: %s", ++seq, lineno, linebuf);

		int toksize = strlen(tokbuf);
		int start = colmno - toksize;
		printf("%s", indent);
		for (i = 0; i < bufsize; ++i) {
			if (i < start) {
				printf(" ");
			} else if (i < start + toksize) {
				printf("^");
			} else {
				break;
			}
		}
		printf("\n");

		printf("%s", indent);
		for (i = 0; i < start + toksize; ++i) {
			printf(" ");
		}
		printf("`-- ");
		printf("token=%d, buf=[%s]\n", tok, tokbuf);
	}

	return 0;
}
