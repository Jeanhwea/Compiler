#include "optim.h"

// partition into basic blocks
void partition(void)
{
	partition_basic_blocks();
}

// construct the flow graph
void construct(void)
{
	construct_flow_graph();
}
