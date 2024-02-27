#include "ir.h"
#include "optim.h"
#include "symtab.h"
#include "util.h"

static void sset(bits_t bits[], syment_t *e)
{
	bset(bits, e->sid);
}

static bool sget(bits_t bits[], syment_t *e)
{
	return bget(bits, e->sid);
}

static void sdup(bits_t des[], bits_t src[])
{
	bdup(des, src, NBITARR);
}

static void sclr(bits_t *bits)
{
	bclrall(bits, NBITARR);
}

static void sunion(bits_t *r, bits_t *a, bits_t *b)
{
	bunion(r, a, b, NBITARR);
}

static void ssub(bits_t *r, bits_t *a, bits_t *b)
{
	bsub(r, a, b, NBITARR);
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
	for (bb = fun->bhead; bb; bb = bb->next) {
		calc_use_def(bb);
	}

	// iteration algorithm
	for (bb = fun->bhead; bb; bb = bb->next) {
		sdup(bb->in0, bb->in);
		sdup(bb->out0, bb->out);
		sclr(bb->out);

		int i;
		for (i = 0; i < MAXBBLINK && bb->succ[i]; ++i) {
			bb_t *s = bb->succ[i];
			sunion(bb->out, bb->out, s->in);
		}
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
