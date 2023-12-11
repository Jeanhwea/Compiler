#include "global.h"
#include "scan.h"

int main(int argc, char *argv[])
{
	echo = TRUE;
	init(argc, argv);

	while (gettok() != ENDFILE)
		;

	return 0;
}
