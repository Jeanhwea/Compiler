#include "optim.h"

// define the global module
mod_t mod;

void optim(void)
{
	// make flow graph
	partition_basic_blocks();
	construct_flow_graph();

	// DAG optimization
	dag_optim();

	// Live Variables Analysis
	lva_optim();
}
