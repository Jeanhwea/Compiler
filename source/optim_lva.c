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

// test if symbol e is a variable
bool isvar(syment_t *e)
{
	switch (e->cate) {
	case VAR_OBJ:
	case TMP_OBJ:
	case BYVAL_OBJ:
	case BYREF_OBJ:
		return TRUE;
	default:
		return FALSE;
	}
}

// set USE in BB
void setuse(bb_t *bb, syment_t *e)
{
	if (!isvar(e)) {
		return;
	}
	if (bmget(bb->def, e)) {
		return;
	}

	bmset(bb->use, e);
}

// set DEF in BB
void setdef(bb_t *bb, syment_t *e)
{
	if (!isvar(e)) {
		return;
	}
	if (bmget(bb->use, e)) {
		return;
	}

	bmset(bb->def, e);
}

void live_var_anlys(bb_t *bb)
{
	// init
	bclrall(bb->use, MAXSETNUM);
	bclrall(bb->def, MAXSETNUM);
	bclrall(bb->in, MAXSETNUM);
	bclrall(bb->out, MAXSETNUM);

	int i;
	for (i = 0; i < bb->total; ++i) {
		inst_t *x = bb->insts[i];
		switch (x->op) {
		case ADD_OP:
		case SUB_OP:
		case MUL_OP:
		case DIV_OP:
		case LOAD_OP:
		case ASA_OP:
			setuse(bb, x->r);
			setuse(bb, x->s);
			setdef(bb, x->d);
			break;
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
