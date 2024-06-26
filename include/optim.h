#ifndef _OPTIM_H_
#define _OPTIM_H_
#include "limits.h"
#include "ir.h"
#include "symtab.h"
#include "util.h"

// array number counter
#define NBITARR (MAXSETBITS / BITSIZE)

// get syment_t *e representation
#define REPR(e) (e->cate == TMP_OBJ ? e->label : e->name)

// bitset function
void sset(bits_t bits[], syment_t *e);
bool sget(bits_t bits[], syment_t *e);
void sdup(bits_t des[], bits_t src[]);
void sclr(bits_t *bits);
bool ssame(bits_t a[], bits_t b[]);
void sunion(bits_t *r, bits_t *a, bits_t *b);
void ssub(bits_t *r, bits_t *a, bits_t *b);

// helper
inst_t *dupinst(op_t op, syment_t *d, syment_t *r, syment_t *s);

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
	// current scope
	symtab_t *scope;

	// basic block list
	bb_t *bhead; // prev of bhead is ENTRY
	bb_t *btail; // next of btail is EXIT

	// store variables in LVA
	int total;		   // total variables
	syment_t *vars[MAXSYMENT]; // symbol entry
	int seqs[MAXSYMENT];	   // variable sequence

	fun_t *next;
};

struct _basic_block_struct {
	// basic information
	int bid;		  // block ID
	int total;		  // total number of instructions
	inst_t *insts[MAXBBINST]; // instructions
	fun_t *fun;		  // which fun_t belongs to
	bb_t *next;		  // next BB

	// links
	bb_t *pred[MAXBBLINK]; // predecessors
	bb_t *succ[MAXBBLINK]; // successors

	// DAG optimization
	dgraph_t *dag;		   // the DAG
	int inst2cnt;		   // insts2[MAXBBINST] counter
	inst_t *insts2[MAXBBINST]; // instructions after DAG optim

	// DFA: data flow analysis
	bits_t in[NBITARR];  // in set
	bits_t out[NBITARR]; // out set

	// LVA: live variable analysis
	bits_t use[NBITARR]; // use set
	bits_t def[NBITARR]; // def set

	int inst3cnt;		   // insts3[MAXBBINST] counter
	inst_t *insts3[MAXBBINST]; // instructions after DAG optim
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

// re-generated instruction counter
extern int xidcnt2;

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
