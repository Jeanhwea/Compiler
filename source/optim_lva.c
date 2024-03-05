#include "ir.h"
#include "limits.h"
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
	bb->fun->vars[e->sid] = e;

	// if e belongs to DEF, then skip set USE
	if (sget(bb->def, e)) {
		return;
	}

	sset(bb->use, e);

	dbg("SET USE: %s\n", REPR(e));
}

// set DEF in BB
void setdef(bb_t *bb, syment_t *e)
{
	if (!isvar(e)) {
		return;
	}
	bb->fun->vars[e->sid] = e;

	// if e belongs to USE, then skip set DEF
	if (sget(bb->use, e)) {
		return;
	}

	sset(bb->def, e);

	dbg("SET DEF: %s\n", REPR(e));
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

static void dump_vars(fun_t *fun)
{
	int sid, seq = 0;
	for (sid = 0; sid < MAXSYMENT; ++sid) {
		syment_t *e = fun->vars[sid];
		if (!e) {
			continue;
		}
		dbg("seq=%02d sid=%02d var=%s\n", ++seq, sid, REPR(e));
	}
}

static void dump_use_def(fun_t *fun)
{
	int seqs[MAXSYMENT], total = 0;
	int sid = 0;
	for (sid = 0; sid < MAXSYMENT; ++sid) {
		syment_t *e = fun->vars[sid];
		if (!e) {
			continue;
		}
		seqs[total++] = sid;
	}

	bb_t *bb;
	for (bb = fun->bhead; bb; bb = bb->next) {
		char bm_def[MAXSYMENT] = {};
		char bm_use[MAXSYMENT] = {};
		int i;
		for (i = 0; i < total; ++i) {
			bm_def[i] = bget(bb->def, seqs[i]) ? '1' : '0';
			bm_use[i] = bget(bb->use, seqs[i]) ? '1' : '0';
		}
		bm_def[total] = '\0';
		bm_use[total] = '\0';
		dbg("B%d def=%s use=%s\n", bb->bid, bm_def, bm_use);

		char buf_def[MAXSTRBUF] = {};
		for (i = 0; i < total; ++i) {
			if (!bget(bb->def, seqs[i])) {
				continue;
			}
			if (strlen(buf_def) > 0) {
				strncat(buf_def, ",", MAXSTRBUF);
			}
			strncat(buf_def, REPR(syments[seqs[i]]), MAXSTRBUF);
		}

		char buf_use[MAXSTRBUF] = {};
		for (i = 0; i < total; ++i) {
			if (!bget(bb->use, seqs[i])) {
				continue;
			}
			if (strlen(buf_use) > 0) {
				strncat(buf_use, ",", MAXSTRBUF);
			}
			strncat(buf_use, REPR(syments[seqs[i]]), MAXSTRBUF);
		}
		dbg("B%d def=[%s] use=[%s]\n", bb->bid, buf_def, buf_use);
	}
}

static void live_var_anlys(fun_t *fun)
{
	bb_t *bb;

	// init USE/DEF set
	for (bb = fun->bhead; bb; bb = bb->next) {
		calc_use_def(bb);
	}

	// dump variables
	dump_vars(fun);
	dump_use_def(fun);

	// Iterative Solver
	bool changed = TRUE; // loop flag
	int epoch = 1;
	while (changed) {
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
		changed = FALSE;
		for (bb = fun->bhead; bb; bb = bb->next) {
			if (!ssame(bb->in, bb->in0)) {
				changed = TRUE;
				break;
			}
			if (!ssame(bb->out, bb->out0)) {
				changed = TRUE;
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
