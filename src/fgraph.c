/**
 * File: fgraph.c
 * Date: Dec 10, 2013
 * Author: Jeanhwea
 */

#include "global.h"
#include "parse.h"
#include "symtab.h"
#include "quad.h"
#include "dag.h"
#include "bblock.h"
#include "fgraph.h"

// point to basic block head
// BBListSP bblst = NULL; see bblock.c

BOOL dagable(BBSP b)
{
	QuadSP p;
	for (p = b->first; p != NULL; p = p->next) {
		if (!DAGABLE(p)) return FALSE;
		if (p == b->first) break;
	}
	return TRUE;
}

void make_fgraph(void)
{
	BBSP b;
	initLeader();
	do {
		b = newBblock();
		addBblock(b);
		printBblock(b);
		if (dagable(b)) {
			make_dag_for_bblock(b);
		} else {
			copy_quad_for_bblock(b);
		}
	} while (!quad_end());
	// printAllBblock();
}
