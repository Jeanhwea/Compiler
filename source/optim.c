#include "optim.h"
#include "debug.h"
#include "ir.h"
#include "limits.h"

mod_t mod;
int bbcnt = 0;

static fun_t *currfunc;
static inst_t *leader;

fun_t *funalloc(void)
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

bb_t *bballoc(void)
{
	bb_t *bb;
	NEWBASICBLOCK(bb);
	if (currfunc->bhead) {
		currfunc->btail->next = bb;
		currfunc->btail = bb;
	} else {
		currfunc->bhead = currfunc->btail = bb;
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
			currfunc = funalloc();
			leader = leader->next;
			break;
		case FIN_OP:
			if (currfunc->scope != leader->d->scope) {
				panic("ENTER_FINISH_NOT_MATCH");
			}
			currfunc = NULL;
			leader = leader->next;
			break;
		default:
			bballoc();
		}
	}
}
