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

static fun_t *funalloc(void)
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

static bb_t *bballoc(void)
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

void partition(void)
{
	leader = xhead;
	while (leader) {
		switch (leader->op) {
		case ENT_OP:
			thefunc = funalloc();
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
			bballoc();
		}
	}
}
