#include "anlys.h"
#include "gen.h"
#include "global.h"
#include "scan.h"
#include "parse.h"

int main(int argc, char *argv[])
{
	msg("compiler %s start, version %s\n", PL0C_NAME, PL0C_VERSION);

	// initial
	init(argc, argv);
	if (errnum > 0) {
		return errnum;
	}

	// lexical & syntax
	parse();

	// semantic
	analysis();

	// generation IR
	generate();

	msg("done\n");
	return 0;
}
