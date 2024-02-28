#include "ir.h"
#include "symtab.h"

// OPCODE Table
char *opcode[32] = {
	[0] = "ADD",   [1] = "SUB",  [2] = "MUL",   [3] = "DIV",   [4] = "INC",
	[5] = "DEC",   [6] = "NEG",  [7] = "LOAD",  [8] = "ASS",   [9] = "ASA",
	[10] = "EQU",  [11] = "NEQ", [12] = "GTT",  [13] = "GEQ",  [14] = "LST",
	[15] = "LEQ",  [16] = "JMP", [17] = "PUSH", [18] = "PADR", [19] = "POP",
	[20] = "CALL", [21] = "ENT", [22] = "FIN",  [23] = "RDI",  [24] = "RDC",
	[25] = "WRS",  [26] = "WRI", [27] = "WRC",  [28] = "LAB",
};

// instructions
inst_t *xhead;
inst_t *xtail;

// instruction count
static int xidcnt = 0;

static inst_t *emit(op_t op)
{
	inst_t *t;
	NEWINST(t);
	t->xid = ++xidcnt;
	t->op = op;

	if (xtail) {
		t->prev = xtail;
		xtail->next = t;
		xtail = t;
	} else {
		t->prev = xtail;
		xhead = xtail = t;
	}

	dbg("emit xid=%d op=%d\n", t->xid, op);
	return t;
}

inst_t *emit1(op_t op, syment_t *d)
{
	inst_t *x = emit(op);
	x->d = d;
	return x;
}

inst_t *emit2(op_t op, syment_t *d, syment_t *r)
{
	inst_t *x = emit(op);
	x->d = d;
	x->r = r;
	return x;
}

inst_t *emit3(op_t op, syment_t *d, syment_t *r, syment_t *s)
{
	inst_t *x = emit(op);
	x->d = d;
	x->r = r;
	x->s = s;
	return x;
}
