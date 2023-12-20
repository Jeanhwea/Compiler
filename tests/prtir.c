#include "anlys.h"
#include "debug.h"
#include "global.h"
#include "tree.h"
#include "ir.h"
#include "symtab.h"
#include "util.h"
#include "syntax.h"
#include "gen.h"
#include <stdio.h>

char *opcode[32] = {
	[0] = "ADD",   [1] = "SUB",   [2] = "MUL",   [3] = "DIV",
	[4] = "INC",   [5] = "DEC",   [6] = "NEG",   [7] = "LOAD",
	[8] = "ASS",   [9] = "ASA",   [10] = "EQU",  [11] = "NEQ",
	[12] = "GTT",  [13] = "GEQ",  [14] = "LST",  [15] = "LEQ",
	[16] = "JMP",  [17] = "PUSH", [18] = "PADR", [19] = "POP",
	[20] = "CALL", [21] = "SRET", [22] = "ENT",  [23] = "FIN",
	[24] = "RDI",  [25] = "RDC",  [26] = "WRS",  [27] = "WRI",
	[28] = "WRC",  [29] = "LAB",
};

char *symcate[12] = {
	[0] = "NOP", [1] = "CONST", [2] = "VAR",   [3] = "PROC",
	[4] = "FUN", [5] = "ARRAY", [6] = "BYVAL", [7] = "BYREF",
	[8] = "TMP", [9] = "LABEL", [10] = "NUM",  [11] = "STR",
};

void fmtinst(inst_t *x)
{
	char buf[1024];
	sprintf(buf, "%03d: %s", x->xid, opcode[x->op]);
	if (x->r) {
		appendf(buf, "\tr=%s", x->r->label);
	}
	if (x->s) {
		appendf(buf, "\ts=%s", x->s->label);
	}
	if (x->d) {
		appendf(buf, "\td=%s", x->d->label);
	}
	msg("%s\n", buf);
}

void dumpent(syment_t *e)
{
	msg("label=%s type=%d cate=%s name=%s off=%d initval=%d arrlen=%d str=%s\n",
	    e->label, e->type, symcate[e->cate], e->name, e->off, e->initval,
	    e->arrlen, e->str);
}

int main(int argc, char *argv[])
{
	echo = 0;
	init(argc, argv);
	parse();
	analysis();
	genir();

	msg("\n");
	int i;
	for (i = 1; i <= symcnt; ++i) {
		syment_t *e = syments[i];
		dumpent(e);
	}

	msg("\n");
	inst_t *x;
	for (x = xhead; x; x = x->next) {
		fmtinst(x);
	}
	return 0;
}
