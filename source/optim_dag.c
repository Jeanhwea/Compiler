#include "common.h"
#include "optim.h"

static int dagndcnt = 0;

static dag_node_t *create_dag_node(void)
{
	dag_node_t *node;
	INITMEM(dag_node_t, node);
	node->nid = ++dagndcnt;
	return node;
}
