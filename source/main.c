#include "anlys.h"
#include "asm.h"
#include "gen.h"
#include "global.h"
#include "post.h"
#include "scan.h"
#include "parse.h"

int main(int argc, char *argv[])
{
	msg("compiler %s start, version %s\n", PL0C_NAME, PL0C_VERSION);

	// initial
	init(argc, argv);

	// lexical & syntax
	parse();

	// semantic
	analysis();

	// generate IR
	genir();

	// generate target code
	genasm();

	// post works
	post_nasm();
	post_link();

	msg("done\n");
	return 0;
}
