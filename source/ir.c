#include "ir.h"
#include "symtab.h"

// instructions
inst_t *xhead;
inst_t *xtail;

// instruction count
int instcnt = 0;

static inst_t *emit()
{
	inst_t *t;
	NEWINST(t);
	t->xid = ++instcnt;

	if (xtail) {
		t->prev = xtail;
		xtail->next = t;
		xtail = t;
	} else {
		t->prev = xtail;
		xhead = xtail = t;
	}

	dbg("emit xid=%d\n", t->xid);
	return t;
}

inst_t *emit1(op_t op, syment_t *d)
{
	inst_t *x = emit();
	x->op = op;
	x->d = d;
	return x;
}

inst_t *emit2(op_t op, syment_t *r, syment_t *d)
{
	inst_t *x = emit();
	x->op = op;
	x->d = d;
	x->r = r;
	return x;
}

inst_t *emit3(op_t op, syment_t *r, syment_t *s, syment_t *d)
{
	inst_t *x = emit();
	x->op = op;
	x->d = d;
	x->r = r;
	x->s = s;
	return x;
}
