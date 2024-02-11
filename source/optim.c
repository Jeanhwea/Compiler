#include "optim.h"
#include "debug.h"
#include "ir.h"
#include "limits.h"

int bbcnt = 0;
bb_t *bbhead = NULL;
bb_t *bbtail = NULL;

inst_t *leader;

bb_t *bballoc(void)
{
	bb_t *bb;
	NEWBASICBLOCK(bb);
	if (bbhead) {
		bbtail->next = bb;
		bbtail = bb;
	} else {
		bbhead = bbtail = bb;
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

		switch (x->op) {
		case EQU_OP:
		case NEQ_OP:
		case GTT_OP:
		case GEQ_OP:
		case LST_OP:
		case LEQ_OP:
		case JMP_OP:
		case ENT_OP:
		case FIN_OP:
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
		bballoc();
	}
}
