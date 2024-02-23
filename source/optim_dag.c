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
static dag_t *create_dag_graph(void)
{
	dag_t *graph;
	INITMEM(dag_t, graph);
	graph->gid = ++graphcnt;
	return graph;
}

static dnode_t *find_sym_node(dag_t *g, syment_t *e)
{
	dnode_t *node = g->sbnodes[e->sid];

	// insert new one node if not found
	if (!node) {
		node = create_dag_node(SYMBOLNODE);
		node->syment = e;

		// add node to graph
		g->sbnodes[e->sid] = node;
	}

	return node;
}

static dnode_t *find_op_node(dag_t *g, op_t op, dnode_t *left, dnode_t *right)
{
	dnode_t *node;
	int i;
	for (i = 0; i < g->opcnt; ++i) {
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

	// insert new one if not found
	node = create_dag_node(OPERNODE);
	node->left = left;
	node->right = right;
	node->op = op;

	// add node to graph
	g->opnodes[g->opcnt++] = node;

	return node;
}

// construct DAG for the basic block
static void construct_dag(bb_t *bb)
{
	dag_t *graph = create_dag_graph();

	inst_t *x;
	int i;
	for (i = 0; i < bb->total; ++i) {
		x = bb->insts[i];
		dnode_t *left, *right, *root;
		switch (x->op) {
		case ADD_OP:
			left = find_sym_node(graph, x->r);
			right = find_sym_node(graph, x->s);
			root = find_op_node(graph, x->op, left, right);
			// TODO
			break;
		}
	}
}
