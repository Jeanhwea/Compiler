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
static dnode_t *create_dag_node(dgraph_t *g, dnode_cate_t cate)
{
	dnode_t *node;
	INITMEM(dnode_t, node);

	// init common attrs
	node->nid = ++nodecnt;
	node->cate = cate;

	// add node to graph
	g->nodes[g->nodecnt++] = node;
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
	dnode_t *node = g->symmap[e->sid];

	// insert new one node if not found
	if (!node) {
		node = create_dag_node(g, SYMBOLNODE);
		node->syment = e;

		// add to symmap
		g->symmap[e->sid] = node;
	}

	return node;
}

static dnode_t *find_op_node(dgraph_t *g, op_t op, dnode_t *lhs, dnode_t *rhs)
{
	dnode_t *node;
	int i;
	for (i = 0; i < g->nodecnt; ++i) {
		node = g->nodes[i];
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
	node = create_dag_node(g, OPERNODE);
	node->lhs = lhs;
	node->rhs = rhs;
	node->op = op;

	return node;
}

// construct DAG for the basic block
static void construct_dag(bb_t *bb)
{
	dgraph_t *graph = create_dag_graph();

	inst_t *x;
	int i;
	for (i = 0; i < bb->total; ++i) {
		dnode_t *lhs = NULL, *rhs = NULL, *out = NULL;

		x = bb->insts[i];
		switch (x->op) {
		case ADD_OP:
		case SUB_OP:
		case MUL_OP:
		case DIV_OP:
			// calculate: lhs, rhs and output
			lhs = find_sym_node(graph, x->r);
			rhs = find_sym_node(graph, x->s);
			out = find_op_node(graph, x->op, lhs, rhs);
			break;
		case INC_OP:
		case DEC_OP:
		case NEG_OP:
		case ASS_OP:
			lhs = find_sym_node(graph, x->r);
			out = find_op_node(graph, x->op, lhs, rhs);
			break;
		case LAB_OP:
		default:
			goto NEXTINST;
		}

		// update output symbol
		graph->symmap[x->d->sid] = out;

	NEXTINST:
	}

	bb->dag = graph;
}

void make_basic_block_dag(void)
{
	fun_t *f;
	bb_t *bb;
	for (f = mod.fhead; f; f = f->next) {
		for (bb = f->bhead; bb; bb = bb->next) {
			construct_dag(bb);
		}
	}
}
