/**
 * File: reg.c
 * Date: Nov 23, 2013
 * Author: Jeanhwea
 */
#include "global.h"
#include "parse.h"
#include "symtab.h"
#include "quad.h"
#include "elf.h"
#include "dag.h"
#include "util.h"
#include "bblock.h"
#include "reg.h"

// #define VARIABLE_LIMIT (16*8)
// extern SymTabESP all_variables[VARIABLE_LIMIT];
// extern int var_num;
// see bblock.c
// BBListSP bblst = NULL;

int isUse[3] =
{
	FALSE,
	FALSE,
	FALSE
};

char *tmp_regs[3] =
{
	"eax",
	"ecx",
	"edx"
};

BBListSP fun_head = NULL;

int use_count[VARIABLE_LIMIT] = {0};

SymTabESP global_reg[VARIABLE_LIMIT] = {NULL};


int getReg(void)
{
	int i;
	for (i = 0; i < 3; ++i) {
		if (!isUse[i]) {
			isUse[i] = TRUE;
			return i;
		}
	}
	assert(0);
	return -1;
}

void relReg(int reg_num)
{
	isUse[reg_num] = FALSE;
}

void increaseCount(SymTabESP ste)
{
	use_count[find_var_pos(ste)]++;
}

void clear_all_count(void)
{
	int i;
	for (i = 0; i < VARIABLE_LIMIT; ++i) {
		use_count[i] = 0;
	}
}

int find_max_count(void)
{
	// return max use count index
	int i, max_i;
	for (max_i = 0, i = 1; i < VARIABLE_LIMIT; ++i) {
		if(use_count[i] > use_count[max_i]) {
			max_i = i;
		}
	}
	return max_i;
}

void _do_use_count(void)
{
	BBListSP bl;
	BBSP b;
	QuadSP q;
	int mi;
	clear_all_count();
	for (bl = fun_head; bl->bbp->posts->bbp; bl = bl->next) {
		b = bl->bbp;
		for (q = b->qhead; q; q = q->next) {
			if (q->r && COUNT_VARS(q->r))
				increaseCount(q->r);
			if (q->s && COUNT_VARS(q->s))
				increaseCount(q->s);
			if (q->d && COUNT_VARS(q->d))
				increaseCount(q->d);
		}
	}
	mi = find_max_count();
	if (strcmp(b->scope->d->label, "main"))
		global_reg[find_var_pos(b->scope->d)] = all_variables[mi];
}

void do_use_count(void)
{
	BBListSP bl;
	for (bl = bblst; bl && !bl->bbp->pres->bbp; ) {
		fun_head = bl;
		// fun_block_tail = bl;
		_do_use_count();
		// printf("********** void do_dataflow(void) ***********\n");
		for (bl = bl->next; bl && bl->bbp->pres->bbp ; bl = bl->next)
			;
	}
}
