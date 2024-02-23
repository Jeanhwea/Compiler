#include "common.h"
#include "ir.h"
#include "limits.h"
#include "optim.h"
#include "symtab.h"

// the DAG counter
static int graphcnt = 0;
// the DAG nodes counter
static int nodecnt = 0;

// create DAG node
static dnode_t *create_dag_node(dnode_cate_t cate)
{
	dnode_t *node;
	INITMEM(dnode_t, node);
	node->nid = ++nodecnt;
	node->cate = cate;
	return node;
}

// create DAG graph
static dgraph_t *create_dag_graph(void)
{
	dgraph_t *graph;
	INITMEM(dgraph_t, graph);
	graph->gid = ++graphcnt;
	return graph;
}

static dnode_t *find_sym_node(dgraph_t *g, syment_t *e)
{
	dnode_t *node = g->leaf[e->sid];

	// insert new one node if not found
	if (!node) {
		node = create_dag_node(SYMBOLNODE);
		node->syment = e;

		// add node to graph
		g->leaf[e->sid] = node;
	}

	return node;
}

static dnode_t *find_op_node(dgraph_t *g, op_t op, dnode_t *lhs, dnode_t *rhs)
{
	dnode_t *node;
	int i;
	for (i = 0; i < g->opcnt; ++i) {
		node = g->nonleaf[i];
		if (node->lhs != lhs) {
			continue;
		}
		if (node->rhs != rhs) {
			continue;
		}
		if (node->op != op) {
			continue;
		}
		return node;
	}

	// insert new one if not found
	node = create_dag_node(OPERNODE);
	node->lhs = lhs;
	node->rhs = rhs;
	node->op = op;

	// add node to graph
	g->nonleaf[g->opcnt++] = node;

	return node;
}

// construct DAG for the basic block
static void construct_dag(bb_t *bb)
{
	dgraph_t *graph = create_dag_graph();

	inst_t *x;
	int i;
	for (i = 0; i < bb->total; ++i) {
		x = bb->insts[i];
		dnode_t *lhs, *rhs, *out;
		switch (x->op) {
		case ADD_OP:
		case SUB_OP:
		case MUL_OP:
		case DIV_OP:
			lhs = find_sym_node(graph, x->r);
			rhs = find_sym_node(graph, x->s);
			out = find_op_node(graph, x->op, lhs, rhs);
			break;
		}
	}

	bb->dag = graph;
}

void dag(void)
{
	fun_t *f;
	bb_t *bb;
	for (f = mod.fhead; f; f = f->next) {
		for (bb = f->bhead; bb; bb = bb->next) {
			construct_dag(bb);
		}
	}
}
