#include "global.h"
#include "anlys.h"
#include "debug.h"
#include "conv.h"
#include "ir.h"
#include "limits.h"
#include "symtab.h"
#include "util.h"
#include "syntax.h"
#include "gen.h"

char *symcate[12] = {
	[0] = "NOP", [1] = "CONST", [2] = "VAR",   [3] = "PROC",
	[4] = "FUN", [5] = "ARRAY", [6] = "BYVAL", [7] = "BYREF",
	[8] = "TMP", [9] = "LABEL", [10] = "NUM",  [11] = "STR",
};

void fmtinst(inst_t *x)
{
	char buf[MAXSTRBUF];
	sprintf(buf, "#%03d: %s", x->xid, opcode[x->op]);
	if (x->d) {
		appendf(buf, "\td=%s", x->d->label);
	}
	if (x->r) {
		appendf(buf, "\tr=%s", x->r->label);
	}
	if (x->s) {
		appendf(buf, "\ts=%s", x->s->label);
	}
	msg("%s\n", buf);
}

void dumpent(syment_t *e)
{
	msg("label=%s type=%d cate=%s name=%s off=%d stab=%d depth=%d initval=%d arrlen=%d str=%s\n",
	    e->label, e->type, symcate[e->cate], e->name, e->off, e->stab->tid,
	    e->stab->depth, e->initval, e->arrlen, e->str);
}

int main(int argc, char *argv[])
{
	echo = 0;
	init(argc, argv);
	parse();
	analysis();
	genir();
	msg("\n");

	msg("DUMP SYMBOLS:\n");
	int i;
	for (i = 1; i <= sidcnt; ++i) {
		syment_t *e = syments[i];
		dumpent(e);
	}
	msg("\n");

	msg("DUMP INTERMEDIATE REPRESENTATION:\n");
	inst_t *x;
	for (x = xhead; x; x = x->next) {
		fmtinst(x);
	}
	msg("\n");

	return 0;
}
