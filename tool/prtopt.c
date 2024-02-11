#include "global.h"
#include "anlys.h"
#include "debug.h"
#include "conv.h"
#include "ir.h"
#include "limits.h"
#include "optim.h"
#include "symtab.h"
#include "util.h"
#include "syntax.h"
#include "gen.h"

char *opcode[32] = {
	[0] = "ADD",   [1] = "SUB",  [2] = "MUL",   [3] = "DIV",   [4] = "INC",
	[5] = "DEC",   [6] = "NEG",  [7] = "LOAD",  [8] = "ASS",   [9] = "ASA",
	[10] = "EQU",  [11] = "NEQ", [12] = "GTT",  [13] = "GEQ",  [14] = "LST",
	[15] = "LEQ",  [16] = "JMP", [17] = "PUSH", [18] = "PADR", [19] = "POP",
	[20] = "CALL", [21] = "ENT", [22] = "FIN",  [23] = "RDI",  [24] = "RDC",
	[25] = "WRS",  [26] = "WRI", [27] = "WRC",  [28] = "LAB",
};

char *symcate[12] = {
	[0] = "NOP", [1] = "CONST", [2] = "VAR",   [3] = "PROC",
	[4] = "FUN", [5] = "ARRAY", [6] = "BYVAL", [7] = "BYREF",
	[8] = "TMP", [9] = "LABEL", [10] = "NUM",  [11] = "STR",
};

void fmtinst2(inst_t *x)
{
	char buf[MAXSTRBUF];
	sprintf(buf, "  #%03d: %s", x->xid, opcode[x->op]);
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

	partition();

	fun_t *fun;
	for (fun = mod.fhead; fun; fun = fun->next) {
		msg("func(nspace=%s)\n", fun->scope->nspace);
		bb_t *bb;
		for (bb = fun->bhead; bb; bb = bb->next) {
			msg(" block(bid=%d)\n", bb->bid);
			int i;
			for (i = 0; i < bb->total; i++) {
				fmtinst2(bb->insts[i]);
			}
		}
	}
	msg("\n");

	return 0;
}
