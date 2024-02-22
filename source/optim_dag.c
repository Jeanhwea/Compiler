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
static dag_node_t *create_dag_node(void)
{
	dag_node_t *node;
	INITMEM(dag_node_t, node);
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
static dag_node_t *find_leaf_node(dag_t *graph, syment_t *e)
{
	dag_node_t *leaf = graph->leaves[e->sid];

	// create one leaf node if not found
	if (!leaf) {
		leaf = create_dag_node();
		leaf->syment = e;
		graph->leaves[e->sid] = leaf;
	}

	return leaf;
}

static dag_node_t *find_nonleaf_node(dag_t *graph, syment_t *e)
{
	// TODO
}

// construct DAG for the basic block
static void construct_dag(bb_t *bb)
{
	dag_t *graph = create_dag();

	inst_t *x;
	int i;
	for (i = 0; i < bb->total; ++i) {
		x = bb->insts[i];
		dag_node_t *left, *right;
		switch (x->op) {
		case ADD_OP:
			left = find_leaf_node(graph, x->r);
			right = find_leaf_node(graph, x->s);
			break;
		}
	}
}
