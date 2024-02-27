#ifndef _OPTIM_H_
#define _OPTIM_H_
#include "limits.h"
#include "ir.h"
#include "symtab.h"
#include "util.h"

// CFG: flow graph objects: Module, Function, BasicBlock
typedef struct _module_struct mod_t;
typedef struct _function_struct fun_t;
typedef struct _basic_block_struct bb_t;

// DAG: graph, nodes
typedef struct _dag_graph_struct dgraph_t;
typedef struct _dag_node_struct dnode_t;
typedef struct _dag_node_var_struct dnvar_t;

// DFA: data flow analysis

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
	int bid;		  // block ID
	int total;		  // total number of instructions
	inst_t *insts[MAXBBINST]; // instructions
	bb_t *next;

	// links
	bb_t *pred[MAXBBLINK]; // predecessors
	bb_t *succ[MAXBBLINK]; // successors

	// DAG optimization
	dgraph_t *dag;		   // the DAG
	int inst2cnt;		   // insts2[MAXBBINST] counter
	inst_t *insts2[MAXBBINST]; // instructions after DAG optim

	// LVA: live variable analysis
	bits_t use[MAXSETNUM];	// use set
	bits_t def[MAXSETNUM];	// def set
	bits_t in[MAXSETNUM];	// new in set
	bits_t out[MAXSETNUM];	// new out set
	bits_t in0[MAXSETNUM];	// old in set
	bits_t out0[MAXSETNUM]; // old out set
};

struct _dag_graph_struct {
	int gid;		      // graph ID
	int nodecnt;		      // nodes counter
	dnode_t *nodes[MAXDAGNODES];  // vertices
	dnode_t *symmap[MAXDAGNODES]; // symbol map, mapping symbol to node
};

typedef enum dnode_cate_enum {
	OPERNODE = 0,
	SYMBOLNODE = 1,
} dnode_cate_t;

struct _dag_node_struct {
	// common
	int nid; // node ID
	dnode_cate_t cate;

	// attributes for operation node
	op_t op;      // operation
	dnode_t *lhs; // left hand side
	dnode_t *rhs; // right hand side

	// attributes for symbol node
	syment_t *syment;

	// control parameters
	dnvar_t *reflist; // reference to symbol entry
	bool generated;	  // if current node is generated
};

// store referenecd symbol variables in DAG node
struct _dag_node_var_struct {
	syment_t *sym;
	dnvar_t *next;
};

// global module handler
extern mod_t mod;

// Optimization
//
//   1. Flow Graph
void partition_basic_blocks(void);
void construct_flow_graph(void);
//   2. DAG Graph
void dag_optim(void);
//   3. Live Variables Analysis
void lva_optim(void);

// optimize entry
void optim(void);
#endif /* End of _OPTIM_H_ */
