#ifndef _OPTIM_H_
#define _OPTIM_H_
#include "limits.h"
#include "ir.h"

typedef struct _module_struct mod_t;
typedef struct _function_struct fun_t;
typedef struct _basic_block_struct bb_t;

typedef struct _module_struct {
	fun_t *fhead;
	fun_t *ftail;
} mod_t;

typedef struct _function_struct {
	symtab_t *scope;
	bb_t *bhead;
	bb_t *btail;
	fun_t *next;
} fun_t;

typedef struct _basic_block_struct {
	int bid; // block ID
	int total; // total number of instructions
	inst_t *insts[MAXBBINST]; // instructions
	bb_t *pred_bbs[MAXBBLINK]; // predecessors of basic blocks
	bb_t *succ_bbs[MAXBBLINK]; // successors of basic blocks
	bb_t *next;
} bb_t;

extern mod_t mod;
extern int bbcnt;

#define NEWFUNCTION(v) INITMEM(fun_t, v);

#define NEWBASICBLOCK(v)                                                       \
	do {                                                                   \
		INITMEM(bb_t, v);                                              \
		v->bid = ++bbcnt;                                              \
	} while (0)

void partition(void);
#endif /* End of _OPTIM_H_ */
