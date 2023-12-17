#include "anlys.h"
#include "debug.h"
#include "global.h"
#include "ast.h"
#include "ir.h"
#include "symtab.h"
#include "util.h"
#include "syntax.h"
#include "gen.h"
#include <stdio.h>

char *opcode[32] = {
	[0] = "ADD",   [1] = "SUB",    [2] = "MUL",    [3] = "DIV",
	[4] = "INC",   [5] = "DEC",    [6] = "NEG",    [7] = "LOAD",
	[8] = "ASS",   [9] = "ASA",    [10] = "EQU",   [11] = "NEQ",
	[12] = "GTT",  [13] = "GEQ",   [14] = "LST",   [15] = "LEQ",
	[16] = "JMP",  [17] = "PUSH",  [18] = "PUSHA", [19] = "POP",
	[20] = "CALL", [21] = "SRET",  [22] = "ENTER", [23] = "FIN",
	[24] = "RDI",  [25] = "RDC",   [26] = "WRS",   [27] = "WRI",
	[28] = "WRC",  [29] = "LABEL",
};

void fmtinst(inst_t *x)
{
	char buf[1024];
	sprintf(buf, "%s", opcode[x->op]);
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

int main(int argc, char *argv[])
{
	echo = 0;
	init(argc, argv);
	parse();
	analysis();
	generate();

	for (inst_t *x = ihead; x; x = x->next) {
		fmtinst(x);
	}
	return 0;
}
