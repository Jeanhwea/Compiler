#include "ir.h"
#include "symtab.h"

// instructions
inst_t *xhead;
inst_t *xtail;

// instruction count
int xidcnt = 0;

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
