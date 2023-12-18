#include "x86.h"
#include "ir.h"

void asm_add_op(inst_t *x)
{
	reg_t *a = getreg();
	reg_t *b = getreg();
}

void *assemble()
{
	for (inst_t *x = xhead; x; x = x->next) {
		switch (x->op) {
		case ADD_OP:
			asm_add_op(x);
			break;
		default:
			unlikely();
		}
	}
}
