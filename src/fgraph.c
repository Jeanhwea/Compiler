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
#include "live_variable.h"
#include "reg.h"

// point to basic block head
// BBListSP bblst = NULL; see bblock.c

BOOL dagable_bblock(BBSP b)
{// helper
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
		// printBblock(b);
		if (dagable_bblock(b)) {
			make_dag_for_bblock(b);
		} else {
			copy_quad_for_bblock(b);
		}
		printAllQuads(b->qhead);
		// elf_for_block(b);
	} while (!quad_end());
	link_bblock();
	// printAllBblock();
}

void dataflow(void)
{
	BBListSP bl;
	cal_use_def();
	// printf("1111111111111111111111111111111111111111111\n");
	// printAllBblock();
	do_dataflow();
	_printAllBblock();
	rm_useless_assign();
	_printAllBblock();
	for (bl = bblst; bl; bl = bl->next) 
		elf_for_block(bl->bbp);
}

void global_reg_alocate(void)
{
	do_use_count();
}