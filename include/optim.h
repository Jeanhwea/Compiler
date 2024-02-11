#ifndef _OPTIM_H_
#define _OPTIM_H_
#include "ir.h"
#include "limits.h"

typedef struct _basic_block_struct bb_t;

typedef struct _basic_block_struct {
	int bid; // block ID
	int total; // total number of instructions
	inst_t *insts[MAXBBINST]; // instructions
	bb_t *pre_bb_list[MAXBBLINK]; // BBs entering this BB
	bb_t *post_bb_list[MAXBBLINK]; // BBs exiting this BB
	bb_t *next;
} bb_t;

extern int bbcnt;
extern bb_t *bbhead;
extern bb_t *bbtail;

#define NEWBASICBLOCK(v)                                                       \
	do {                                                                   \
		INITMEM(bb_t, v);                                              \
		v->bid = ++bbcnt;                                              \
	} while (0)

void partition(void);
#endif /* End of _OPTIM_H_ */
