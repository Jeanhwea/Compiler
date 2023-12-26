#include "anlys.h"
#include "asm.h"
#include "gen.h"
#include "global.h"
#include "post.h"
#include "scan.h"
#include "parse.h"

int main(int argc, char *argv[])
{
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

	post_clean();
	msg("done\n");
	return 0;
}
