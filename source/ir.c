#include "ir.h"

// instructions
inst_t *ihead;
inst_t *itail;

inst_t *emit()
{
	inst_t *t;
	NEWINST(t);

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
