#ifndef _OPTIM_H_
#define _OPTIM_H_
#include "limits.h"
#include "ir.h"

typedef struct _module_struct mod_t;
typedef struct _function_struct fun_t;
typedef struct _basic_block_struct bb_t;

struct _module_struct {
	fun_t *fhead;
	fun_t *ftail;
};

struct _function_struct {
	symtab_t *scope;
	bb_t *bhead;
	bb_t *btail;
	fun_t *next;
};

struct _basic_block_struct {
	// basic information
	int bid; // block ID
	int total; // total number of instructions
	inst_t *insts[MAXBBINST]; // instructions
	bb_t *next;

	// predecessors and successors
	bb_t *pred[MAXBBLINK];
	bb_t *succ[MAXBBLINK];
};

extern mod_t mod;
extern int bbcnt;

#define NEWFUNCTION(v) INITMEM(fun_t, v);

#define NEWBASICBLOCK(v)                                                       \
	do {                                                                   \
		INITMEM(bb_t, v);                                              \
		v->bid = ++bbcnt;                                              \
	} while (0)

void partition(void);
void construct(void);
#endif /* End of _OPTIM_H_ */
