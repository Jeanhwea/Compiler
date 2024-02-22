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
static dnode_t *create_dag_node(void)
{
	dnode_t *node;
	INITMEM(dnode_t, node);
	node->nid = ++nodecnt;
	return node;
}

// create DAG graph
static dag_t *create_dag(void)
{
	dag_t *graph;
	INITMEM(dag_t, graph);
	graph->gid = ++graphcnt;
	return graph;
}

// find leaf node in DAG, which is the symbol entry
static dnode_t *find_symbol_node(dag_t *g, syment_t *e)
{
	dnode_t *node = g->symnodes[e->sid];

	// create one leaf node if not found
	if (!node) {
		node = create_dag_node();
		node->syment = e;
		g->symnodes[e->sid] = node;
	}

	return node;
}

static dnode_t *find_op_node(dag_t *g, op_t op, dnode_t *left, dnode_t *right)
{
	dnode_t *node;
	int i;
	for (i = 0; i < g->nnode; ++i) {
		node = g->opnodes[i];
		if (node->left != left) {
			continue;
		}
		if (node->right != right) {
			continue;
		}
		if (node->op != op) {
			continue;
		}
		return node;
	}

	node = create_dag_node();
	node->left = left;
	node->right = right;
	node->op = op;
	return node;
}

// construct DAG for the basic block
static void construct_dag(bb_t *bb)
{
	dag_t *graph = create_dag();

	inst_t *x;
	int i;
	for (i = 0; i < bb->total; ++i) {
		x = bb->insts[i];
		dnode_t *left, *right, *root;
		switch (x->op) {
		case ADD_OP:
			left = find_symbol_node(graph, x->r);
			right = find_symbol_node(graph, x->s);
			root = find_op_node(graph, x->op, left, right);
			// TODO
			break;
		}
	}
}
