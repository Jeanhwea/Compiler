#include "common.h"
#include "optim.h"

// the DAG nodes counter
static int nodecnt = 0;

static dag_node_t *create_dag_node(void)
{
	dag_node_t *node;
	INITMEM(dag_node_t, node);
	node->nid = ++nodecnt;
	return node;
}
