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
	int sid;
	for (sid = 0; sid < MAXSYMENT; ++sid) {
		syment_t *e = fun->vars[sid];
		if (!e) {
			continue;
		}
		fun->seqs[fun->total++] = sid;
		dbg("seq=%02d sid=%02d var=%s\n", fun->total, sid, REPR(e));
	}
}

void make_bitmap(fun_t *fun, bits_t bits[], char *bmap)
{
	int i;
	for (i = 0; i < fun->total; ++i) {
		bmap[i] = bget(bits, fun->seqs[i]) ? '1' : '0';
	}
	bmap[fun->total] = '\0';
}

void make_vector(fun_t *fun, bits_t bits[], char *vec)
{
	int i;
	for (i = 0; i < fun->total; ++i) {
		if (!bget(bits, fun->seqs[i])) {
			continue;
		}
		if (strlen(vec) > 0) {
			strncat(vec, ",", MAXSTRBUF - 1);
		}
		strncat(vec, REPR(syments[fun->seqs[i]]), MAXSTRBUF - 1);
	}
}

static void dump_use_def(fun_t *fun)
{
	int total = fun->total;
	int *seqs = fun->seqs;

	bb_t *bb;
	for (bb = fun->bhead; bb; bb = bb->next) {
		char bm_def[MAXSYMENT] = {}, bm_use[MAXSYMENT] = {};
		make_bitmap(fun, bb->def, bm_def);
		make_bitmap(fun, bb->use, bm_use);
		dbg("B%d def=%s use=%s\n", bb->bid, bm_def, bm_use);

		char vt_def[MAXSTRBUF] = {}, vt_use[MAXSTRBUF] = {};
		make_vector(fun, bb->def, vt_def);
		make_vector(fun, bb->use, vt_use);
		dbg("B%d def=[%s] use=[%s]\n", bb->bid, vt_def, vt_use);
	}
}

static void dump_in_out(fun_t *fun)
{
	int total = fun->total;
	int *seqs = fun->seqs;

	bb_t *bb;
	for (bb = fun->bhead; bb; bb = bb->next) {
		char bm_in[MAXSYMENT] = {}, bm_out[MAXSYMENT] = {};
		make_bitmap(fun, bb->in, bm_in);
		make_bitmap(fun, bb->out, bm_out);
		dbg("B%d in=%s out=%s\n", bb->bid, bm_in, bm_out);

		char vt_in[MAXSTRBUF] = {}, vt_out[MAXSTRBUF] = {};
		make_vector(fun, bb->in, vt_in);
		make_vector(fun, bb->out, vt_out);
		dbg("B%d in=[%s] out=[%s]\n", bb->bid, vt_in, vt_out);
	}
}

// Data Flow Analysis (Backward)
static void data_flow_anlys(fun_t *fun)
{
	bool changed = TRUE; // flag, loop if IN set is changed
	int epoch = 1;	     // which iteration round?

	while (changed) {
		dbg("epoch=%d\n", epoch);
		changed = FALSE;

		dump_in_out(fun);

		bb_t *bb;
		// update IN/OUT in current loop
		for (bb = fun->bhead; bb; bb = bb->next) {
			int i;
			// OUT[B] = Union_{S is B's successor}(IN[S])
			// sclr(bb->out);
			for (i = 0; i < MAXBBLINK; ++i) {
				bb_t *s = bb->succ[i];
				if (!s) {
					break;
				}
				sunion(bb->out, bb->out, s->in);
			}

			// save old IN sets
			bits_t old_in[NBITARR];
			sdup(old_in, bb->in);

			// IN[B] = use[B] union (OUT[B] - def[B])
			bits_t tmp[NBITARR];
			ssub(tmp, bb->out, bb->def);
			sunion(bb->in, bb->use, tmp);

			// check exit condition
			if (!ssame(bb->in, old_in)) {
				changed = TRUE;
			}
		}

		epoch++;
	}

	dbg("LVA DONE\n");
	dump_in_out(fun);
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
	data_flow_anlys(fun);
}

// Eliminate Dead Assign
static void elim_dead_assign(bb_t *bb)
{
	int i;
	for (i = 0; i < bb->total; ++i) {
		inst_t *curr = bb->insts[i];

		// check if eliminate current instruction
		syment_t *d = curr->d;
		if (curr->op != ASS_OP) {
			goto duplication;
		}
		if (d->cate != VAR_OBJ && d->cate != TMP_OBJ) {
			goto duplication;
		}
		if (!sget(bb->in, d) && !sget(bb->out, d)) {
			continue;
		}

	duplication:
		inst_t *copy = dupinst(curr->op, curr->d, curr->r, curr->s);
		if (bb->inst3cnt >= MAXBBINST) {
			panic("LVA_ELIM_DEAD_ASSIGN_OVERFLOW");
		}
		bb->insts3[bb->inst3cnt++] = copy;
	}
}

void lva_optim(void)
{
	fun_t *fun;
	for (fun = mod.fhead; fun; fun = fun->next) {
		dbg("LIVE VARIABLE ANALYSIS: fun=%s\n", fun->scope->nspace);
		live_var_anlys(fun);

		bb_t *bb;
		for (bb = fun->bhead; bb; bb = bb->next) {
			elim_dead_assign(bb);
		}
	}
}
