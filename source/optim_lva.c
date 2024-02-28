#include "ir.h"
#include "optim.h"
#include "symtab.h"
#include "util.h"

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

	// if e belongs to DEF, then skip set USE
	if (sget(bb->def, e)) {
		return;
	}

	sset(bb->use, e);

	dbg("SET USE: %s\n", e->cate == TMP_OBJ ? e->label : e->name);
}

// set DEF in BB
void setdef(bb_t *bb, syment_t *e)
{
	if (!isvar(e)) {
		return;
	}

	// if e belongs to USE, then skip set DEF
	if (sget(bb->use, e)) {
		return;
	}

	sset(bb->def, e);

	dbg("SET DEF: %s\n", e->cate == TMP_OBJ ? e->label : e->name);
}

static void calc_use_def(bb_t *bb)
{
	dbg("LVA USE/DEF: bb=B%d\n", bb->bid);

	// init
	sclr(bb->use);
	sclr(bb->def);
	sclr(bb->in);
	sclr(bb->out);

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
		case INC_OP:
		case DEC_OP:
			setuse(bb, x->d);
			break;
		case NEG_OP:
		case ASS_OP:
			setuse(bb, x->r);
			setdef(bb, x->d);
			break;
		case EQU_OP:
		case NEQ_OP:
		case GTT_OP:
		case GEQ_OP:
		case LST_OP:
		case LEQ_OP:
			setuse(bb, x->r);
			setuse(bb, x->s);
			break;
		case JMP_OP:
		case CALL_OP:
		case ENT_OP:
		case FIN_OP:
		case LAB_OP:
			continue;
		case PUSH_OP:
		case PADR_OP:
		case POP_OP:
		case RDI_OP:
		case RDC_OP:
			setuse(bb, x->d);
			if (x->r) {
				setuse(bb, x->r);
			}
			break;
		case WRS_OP:
		case WRI_OP:
		case WRC_OP:
			setdef(bb, x->d);
			break;
		default:
			panic("UNKNOWN_INSTRUCTION_OP");
		}
	}
}

static void live_var_anlys(fun_t *fun)
{
	bb_t *bb;

	// init USE/DEF set
	for (bb = fun->bhead; bb; bb = bb->next) {
		calc_use_def(bb);
	}

	// Iterative Solver
	bool loop = TRUE; // loop flag
	int epoch = 1;
	while (loop) {
		dbg("epoch=%d\n", epoch);

		// update IN/OUT in current loop
		for (bb = fun->bhead; bb; bb = bb->next) {
			// save old IN/OUT sets
			sdup(bb->in0, bb->in);
			sdup(bb->out0, bb->out);

			// set OUT[B] = empty set
			sclr(bb->out);

			// OUT[B] = Union_{b0 is B's successor}(IN[b0])
			int i;
			for (i = 0; i < MAXBBLINK; ++i) {
				bb_t *s = bb->succ[i];
				if (!s) {
					break;
				}
				sunion(bb->out, bb->out, s->in);
			}

			// IN[B] = use[B] union (OUT[B] - def[B])
			bits_t tmp[NBITARR];
			ssub(tmp, bb->out, bb->def);
			sunion(bb->in, bb->use, tmp);
		}

		// check exit condition
		loop = FALSE;
		for (bb = fun->bhead; bb; bb = bb->next) {
			if (!ssame(bb->in, bb->in0)) {
				loop = TRUE;
				break;
			}
			if (!ssame(bb->out, bb->out0)) {
				loop = TRUE;
				break;
			}
		}
		epoch++;
	}
}

void lva_optim(void)
{
	fun_t *fun;
	for (fun = mod.fhead; fun; fun = fun->next) {
		dbg("LIVE VARIABLE ANALYSIS: fun=%s\n", fun->scope->nspace);
		live_var_anlys(fun);
	}
}
