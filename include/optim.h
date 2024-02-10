#ifndef _OPTIM_H_
#define _OPTIM_H_
#include "ir.h"
#include "limits.h"

typedef struct _basic_block_struct bb_t;

typedef struct _basic_block_struct {
	int bid; // block ID
	int ninst; // number of instructions
	inst_t *[MAXBBLOCK] insts; // instructions
	bb_t *[MAXBBLINK] bb_pre;
	bb_t *[MAXBBLINK] bb_post;
} bb_t;

#endif /* End of _OPTIM_H_ */
