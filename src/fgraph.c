/**
 * File: fgraph.c
 * Date: Dec 10, 2013
 * Author: Jeanhwea
 */

#include "global.h"
#include "parse.h"
#include "symtab.h"
#include "quad.h"
#include "elf.h"
#include "dag.h"
#include "bblock.h"
#include "fgraph.h"

// point to basic block head
// BBListSP bblst = NULL; see bblock.c

BOOL dagable_bblock(BBSP b)
{
	QuadSP p;
	for (p = b->first; p != NULL; p = p->next) {
		if (!DAGABLE(p)) return FALSE;
		if (p == b->last) break;
	}
	return TRUE;
}

void make_fgraph(void)
{
	BBSP b;
	initLeader();
	elf_header();
	do {
		b = newBblock();
		addBblock(b);
		printBblock(b);
		if (dagable_bblock(b)) {
			make_dag_for_bblock(b);
		} else {
			copy_quad_for_bblock(b);
		}
		printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
		printAllQuads(b->qhead);
		elf_for_block(b);
	} while (!quad_end());
	// printAllBblock();
}
