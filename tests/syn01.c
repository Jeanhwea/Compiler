#include "global.h"
#include "scan.h"
#include "parse.h"

int main(int argc, char *argv[])
{
	echo = TRUE;

	init(argc, argv);

	prog = parse();

	msg("prog=%p\n", prog);
	return 0;
}
