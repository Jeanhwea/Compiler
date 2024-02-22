#ifndef _OPTIM_H_
#define _OPTIM_H_
#include "limits.h"
#include "ir.h"
#include "symtab.h"

// CFG: flow graph objects: Module, Function, BasicBlock
typedef struct _module_struct mod_t;
typedef struct _function_struct fun_t;
typedef struct _basic_block_struct bb_t;

// DAG: graph, nodes
typedef struct _dag_struct dag_t;
typedef struct _dag_node_struct dag_node_t;

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

	// next-use information
	bool liveness[MAXSYMENT];
	inst_t *nextuse[MAXSYMENT];

	// predecessors and successors
	bb_t *pred[MAXBBLINK];
	bb_t *succ[MAXBBLINK];
};

struct _dag_struct {
	int gid; // graph ID
	dag_node_t *nodes[MAXDAGNODES]; // vertices
	dag_node_t *leaves[MAXSYMENT]; // leaf lookup table
};

struct _dag_node_struct {
	int nid; // node ID

	// attributes for non-leaf nodes
	op_t *op; // the operator
	// attributes for leaf nodes
	syment_t *syment; // the symbol entry

	// common
	dag_node_t *left;
	dag_node_t *right;
};

// global module handler
extern mod_t mod;

// optimize function
void partition_basic_blocks(void);
void construct_flow_graph(void);

// optimize entry
void optim(void);
#endif /* End of _OPTIM_H_ */
