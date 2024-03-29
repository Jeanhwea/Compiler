#include "common.h"
#include "debug.h"
#include "ir.h"
#include "limits.h"
#include "optim.h"
#include "symtab.h"

// the DAG counter
static int graphcnt = 0;
// the DAG nodes counter
static int nodecnt = 0;

// check instructions in basic block is dagable
static bool check_dagable(bb_t *bb)
{
	inst_t *x;
	int i;
	for (i = 0; i < bb->total; ++i) {
		x = bb->insts[i];
		switch (x->op) {
		case ASA_OP:
		case PUSH_OP:
		case PADR_OP:
		case POP_OP:
		case CALL_OP:
		case RDI_OP:
		case RDC_OP:
		case WRS_OP:
		case WRI_OP:
		case WRC_OP:
			return FALSE;
		default:
			continue;
		}
	}
	return TRUE;
}

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

// lookup leaf node, for symbol
static dnode_t *find_leaf(dgraph_t *g, syment_t *e)
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

// lookup non leaf node, for opertion
static dnode_t *find_nonleaf(dgraph_t *g, op_t op, dnode_t *lhs, dnode_t *rhs)
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
static void construct_graph(bb_t *bb)
{
	dgraph_t *graph = create_dag_graph();

	int i;
	for (i = 0; i < bb->total; ++i) {
		dnode_t *lhs = NULL, *rhs = NULL, *out = NULL;
		inst_t *x = bb->insts[i];
		switch (x->op) {
		case ADD_OP:
		case SUB_OP:
		case MUL_OP:
		case DIV_OP:
		case LOAD_OP:
			lhs = find_leaf(graph, x->r);
			rhs = find_leaf(graph, x->s);
			out = find_nonleaf(graph, x->op, lhs, rhs);
			break;
		case INC_OP:
		case DEC_OP:
			lhs = find_leaf(graph, x->d);
			out = find_nonleaf(graph, x->op, lhs, rhs);
			break;
		case NEG_OP:
		case ASS_OP:
			lhs = find_leaf(graph, x->r);
			out = find_nonleaf(graph, x->op, lhs, rhs);
			break;
		case ASA_OP:
		case PUSH_OP:
		case PADR_OP:
		case POP_OP:
		case CALL_OP:
		case ENT_OP:
		case FIN_OP:
		case RDI_OP:
		case RDC_OP:
		case WRS_OP:
		case WRI_OP:
		case WRC_OP:
			panic("UNSUPPORT_INSTRUCTION");
			break;
		case EQU_OP:
		case NEQ_OP:
		case GTT_OP:
		case GEQ_OP:
		case LST_OP:
		case LEQ_OP:
		case JMP_OP:
		case LAB_OP:
		default:
			continue;
		}

		// update output symbol
		graph->symmap[x->d->sid] = out;
	}

	bb->dag = graph;
}

// build referred variables
static void build_referred_info(dgraph_t *g)
{
	dnode_t *v = NULL;
	syment_t *e = NULL;
	int i;
	for (i = 0; i < MAXDAGNODES; ++i) {
		v = g->symmap[i];
		if (!v) {
			continue;
		}
		e = syments[i];

		dnvar_t *p;
		INITMEM(dnvar_t, p);
		p->sym = e;

		// set symbol reference
		if (!v->syment) {
			v->syment = e;
		}

		// head-insert to reflist
		p->next = v->reflist;
		v->reflist = p;
	}
}

static void gen_curr_node(bb_t *bb, dnode_t *n)
{
	if (n->generated) {
		return;
	}

	// if is symbol/leaf node, skip
	if (n->cate == SYMBOLNODE) {
		return;
	}

	// now is OPERNODE
	if (n->lhs) {
		gen_curr_node(bb, n->lhs);
	}
	if (n->rhs) {
		gen_curr_node(bb, n->rhs);
	}

	// duplicate instruction
	syment_t *r = n->lhs ? n->lhs->syment : NULL;
	syment_t *s = n->rhs ? n->rhs->syment : NULL;
	inst_t *x = dupinst(n->op, n->syment, r, s);

	if (bb->inst2cnt >= MAXBBINST) {
		panic("DAG_REGEN_INSTRUCTION_OVERFLOW");
	}
	bb->insts2[bb->inst2cnt++] = x;
	n->generated = TRUE;
}

// re-generate instructions
static void regen_instructions(bb_t *bb)
{
	dgraph_t *g = bb->dag;
	dnode_t *n = NULL;
	int i;
	for (i = 0; i < g->nodecnt; ++i) {
		n = g->nodes[i];
		if (n->generated) {
			continue;
		}
		gen_curr_node(bb, n);
	}
}

void dag_optim(void)
{
	fun_t *fun;
	bb_t *bb;
	for (fun = mod.fhead; fun; fun = fun->next) {
		for (bb = fun->bhead; bb; bb = bb->next) {
			if (!check_dagable(bb)) {
				continue;
			}
			dbg("DAG OPTIMIZATION: bb=B%d\n", bb->bid);
			construct_graph(bb);
			build_referred_info(bb->dag);
			regen_instructions(bb);
		}
	}
}
