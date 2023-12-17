#include "ir.h"
#include "symtab.h"

// instructions
inst_t *ihead;
inst_t *itail;

// instruction count
int xcnt = 0;

static inst_t *emit()
{
	inst_t *t;
	NEWINST(t);
	t->xid = ++xcnt;

	if (itail == NULL) {
		t->prev = itail;
		ihead = itail = t;
	} else {
		t->prev = itail;
		itail->next = t;
		itail = t;
	}
	return t;
}

inst_t *emit0(op_t op)
{
	inst_t *x = emit();
	x->op = op;
	return x;
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
