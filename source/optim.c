#include "optim.h"

// define the global module
mod_t mod;

void optim(void)
{
	partition_basic_blocks();
	construct_flow_graph();
	dag_optim();
}
