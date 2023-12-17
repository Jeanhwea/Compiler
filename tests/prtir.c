#include "anlys.h"
#include "debug.h"
#include "global.h"
#include "ast.h"
#include "ir.h"
#include "symtab.h"
#include "util.h"
#include "syntax.h"
#include "gen.h"

int main(int argc, char *argv[])
{
	echo = 0;
	silent = 1;
	init(argc, argv);
	parse();
	analysis();
	generate();

	for (inst_t *x = ihead; x; x = x->next) {
		msg("%d\n", x->op);
	}
	return 0;
}
