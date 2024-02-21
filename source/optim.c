#include "optim.h"
#include "debug.h"
#include "ir.h"
#include "limits.h"

// module
mod_t mod;
// basic block counter
int bbcnt = 0;

// point to the current function scope
static fun_t *thefunc;
// leader of current basic block
static inst_t *leader;

static fun_t *functor(void)
{
	fun_t *fun;
	NEWFUNCTION(fun);

	if (mod.fhead) {
		mod.ftail->next = fun;
		mod.ftail = fun;
	} else {
		mod.fhead = mod.ftail = fun;
	}

	fun->scope = leader->d->scope;
	return fun;
}

static bb_t *bbctor(void)
{
	bb_t *bb;
	NEWBASICBLOCK(bb);
	if (thefunc->bhead) {
		thefunc->btail->next = bb;
		thefunc->btail = bb;
	} else {
		thefunc->bhead = thefunc->btail = bb;
	}

	for (inst_t *x = leader; x; x = x->next) {
		if (bb->total >= MAXBBINST) {
			panic("BASIC_BLOCK_INSTRUCTION_OVERFLOW");
		}
		bb->insts[bb->total++] = x;
		dbg("%03d: x=%d\n", x->xid, x->op);

		leader = x->next;
		if (!leader) {
			goto ok;
		}

		// Case I: Found next leader, which leader is in:
		//     1. conditional jump
		//     2. unconditional jump
		//     3. a label
		//     4. function enter/finish
		switch (leader->op) {
		case EQU_OP:
		case NEQ_OP:
		case GTT_OP:
		case GEQ_OP:
		case LST_OP:
		case LEQ_OP:
		case JMP_OP:
		case LAB_OP:
		case ENT_OP:
		case FIN_OP:
			goto ok;
		default:
			break;
		}

		// Case II: Current x is OK
		//     1. conditional jump
		//     2. unconditional jump
		switch (x->op) {
		case EQU_OP:
		case NEQ_OP:
		case GTT_OP:
		case GEQ_OP:
		case LST_OP:
		case LEQ_OP:
		case JMP_OP:
			goto ok;
		default:
			break;
		}
	}

ok:
	return bb;
}

// partition into basic blocks
void partition(void)
{
	leader = xhead;
	while (leader) {
		switch (leader->op) {
		case ENT_OP:
			thefunc = functor();
			leader = leader->next;
			break;
		case FIN_OP:
			if (thefunc->scope != leader->d->scope) {
				panic("ENTER_FINISH_NOT_MATCH");
			}
			thefunc = NULL;
			leader = leader->next;
			break;
		default:
			bbctor();
		}
	}
}

static void bblink(fun_t *f)
{
	bb_t *lab2bb[MAXSYMENT];
	bb_t *bb = NULL, *prev = NULL;

	// Step1: make lab2bb[...] map, create x->succ[0], x->pred[0] link
	for (bb = f->bhead; bb; bb = bb->next) {
		// make lab2bb[...] map
		inst_t *x = bb->insts[0];
		if (x->op == LAB_OP) {
			lab2bb[x->d->sid] = bb;
		}

		// create succ[0], pred[0] link
		if (!prev) {
			prev = bb;
			continue;
		}
		prev->succ[0] = bb;
		bb->pred[0] = prev;
		prev = bb;
	}

	bb_t *target = NULL;
	int i;

	// Step2: make jump label links
	for (bb = f->bhead; bb; bb = bb->next) {
		inst_t *x = bb->insts[bb->total - 1];
		switch (x->op) {
		case EQU_OP:
		case NEQ_OP:
		case GTT_OP:
		case GEQ_OP:
		case LST_OP:
		case LEQ_OP:
		case JMP_OP:
			// get target basic block
			target = lab2bb[x->d->sid];
			// link bb->succ[...]
			for (i = 0; i < MAXBBLINK; ++i) {
				if (!bb->succ[i]) {
					bb->succ[i] = target;
				}
				if (bb->succ[i] == target) {
					break;
				}
			}
			// link target->pred[...]
			for (i = 0; i < MAXBBLINK; ++i) {
				if (!target->pred[i]) {
					target->pred[i] = bb;
				}
				if (target->pred[i] == bb) {
					break;
				}
			}
			break;
		default:
			continue;
		}
	}
}

// construct the flow graph
void construct(void)
{
	fun_t *f;
	for (f = mod.fhead; f; f = f->next) {
		bblink(f);
	}
}
