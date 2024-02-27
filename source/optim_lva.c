#include "optim.h"
#include "symtab.h"
#include "util.h"

void bmset(bits_t bits[], syment_t *e)
{
	bset(bits, e->sid);
}

bool bmget(bits_t bits[], syment_t *e)
{
	return bget(bits, e->sid);
}

void live_var_anlys(bb_t *bb)
{
	bclrall(bb->use, MAXSETNUM);
	bclrall(bb->def, MAXSETNUM);
	bclrall(bb->in, MAXSETNUM);
	bclrall(bb->out, MAXSETNUM);

	inst_t *x;
	int i;
	for (i = 0; i < bb->total; ++i) {
		x = bb->insts[i];
		switch (x->op) {
		case ADD_OP:
		case SUB_OP:
		case MUL_OP:
		case DIV_OP:
		case LOAD_OP:
		default:
			continue;
		}
	}
}

void lva_optim(void)
{
	fun_t *fun;
	bb_t *bb;
	for (fun = mod.fhead; fun; fun = fun->next) {
		for (bb = fun->bhead; bb; bb = bb->next) {
			dbg("LIVE VARIABLE ANALYSIS: bb=B%d\n", bb->bid);
			live_var_anlys(bb);
		}
	}
}
