#include "optim.h"

void optim(void)
{
	partition_basic_blocks();
	construct_flow_graph();
}
