#include "global.h"
#include "parse.h"
#include "symtab.h"
#include "quad.h"
#include "elf.h"
#include "dag.h"
#include "util.h"
#include "bblock.h"
#include "live_variable.h"
// #define VARIABLE_LIMIT (16*8)
// extern SymTabESP all_variables[VARIABLE_LIMIT];
// extern int var_num;

// SymTabESP cur_scope = NULL;
BBListSP fun_block_head = NULL;
// BBListSP fun_block_tail = NULL;

// 0 <= index <= 127
void bit_set(int bm[], int index)
{
	bm[index >> 4] |= (1 << (index & 0xf));
}

void bit_clear(int bm[], int index)
{
	bm[index >> 4] &= ~(1 << (index & 0xf));
}

BOOL bit_test(int bm[], int index)
{
	return (bm[index >> 4] & (1 << (index & 0xf)) ) > 0 ? TRUE: FALSE;
}

void bit_clear_all(int bm[])
{
	int i;
	for (i = 0; i < 8; i++)
		bm[i] &= 0;
}

void bit_set_all(int bm[])
{
	int i;
	for (i = 0; i< 8; i++)
		bm[i] |= 0xffff;
}

BOOL bm_issame(int bm_srca[], int bm_srcb[])
{
	int i;
	for (i = 0; i < 8; i++)
		if(bm_srca[i] != bm_srcb[i])
			return FALSE;
	return TRUE;
}

void bm_copy(int bm_des[], int bm_src[])
{
	int i;
	for (i = 0; i < 8; i++)
		bm_des[i] = bm_src[i];
}

void bm_union(int bm_des[], int bm_srca[], int bm_srcb[])
{
	int i;
	for (i = 0; i < 8; i++)
		bm_des[i] = bm_srca[i] | bm_srcb[i];
}

void bm_sub(int bm_des[], int bm_srca[], int bm_srcb[])
{
	// bm_des = bm_srca - bm_srcb
	int i;
	for (i = 0; i < 8; i++)
		bm_des[i] = bm_srca[i] & ~bm_srcb[i];
}

void bm_set(int bm[], SymTabESP ste)
{
	bit_set(bm, find_var_pos(ste));
}

void bm_clear(int bm[], SymTabESP ste)
{
	bit_clear(bm, find_var_pos(ste));
}

BOOL bm_test(int bm[], SymTabESP ste)
{
	return bit_test(bm, find_var_pos(ste));
}

// see bblock.c 
// BBListSP bblst = NULL;
void cal_use_def(void)
{
	BBListSP bl;
	BBSP b;
	QuadSP q;
	for (bl = bblst; bl; bl = bl->next) {
		b = bl->bbp;
		// cur_scope = b->scope->d;
		bit_clear_all(b->use);
		bit_clear_all(b->def);
		bit_clear_all(b->in);
		bit_clear_all(b->out);
		bit_set_all(b->in_old);
		bit_set_all(b->out_old);
		for (q = b->qhead; q; q = q->next) {
			// printQuad(q);
			// printBitsmap(b->use);
			// printBitsmap(b->def);
			if (CON_BRANCE(q)) {
				// LST GRE ...
				if (LIVE_VARS(q->r) && !bm_test(b->def,q->r))
					bm_set(b->use, q->r);
				if (LIVE_VARS(q->s) && !bm_test(b->def,q->s))
					bm_set(b->use, q->s);
			} else if (BI_ARITH(q)) {
				// ADD SUB MUL DIV LOAD AARR
				if (LIVE_VARS(q->r) && !bm_test(b->def,q->r))
					bm_set(b->use, q->r);
				if (LIVE_VARS(q->s) && !bm_test(b->def,q->s))
					bm_set(b->use, q->s);
				if (LIVE_VARS(q->d) && !bm_test(b->use, q->d))
					bm_set(b->def, q->d);
			} else if (UNA_ARITH(q)) {
				// NEG ASS SRET
				if (LIVE_VARS(q->r) && !bm_test(b->def,q->r))
					bm_set(b->use, q->r);
				assert(!q->s);
				if (LIVE_VARS(q->d) && !bm_test(b->use, q->d))
					bm_set(b->def, q->d);
			} else if (UNARAY(q)) {
				// INC DEC
				if (LIVE_VARS(q->d) && !bm_test(b->def,q->d))
					bm_set(b->use, q->d);
			} else if (SIG_USE(q)) {
				// PUSH PUSHA WRI WEC
				if (q->s && LIVE_VARS(q->s) && !bm_test(b->def,q->s))
					bm_set(b->use, q->s);
				if (LIVE_VARS(q->d) && !bm_test(b->def,q->d))
					bm_set(b->use, q->d);
			} else if (READ(q)) {
				// READ READC
				if (LIVE_VARS(q->d) && !bm_test(b->use, q->d))
					bm_set(b->def, q->d);
			}
			// printBitsmap(b->use);
			// printBitsmap(b->def);
		}
	}
	// printf("tttttttttttttttttttttttttt\n");
}

BOOL exit_condition(void)
{
	// if TRUE, then exit
	BBListSP bl;
	for (   bl = fun_block_head; 
		bl->bbp->posts->bbp; 
		bl = bl->next) {
		if (!bm_issame(bl->bbp->in, bl->bbp->in_old) ||
			!bm_issame(bl->bbp->out, bl->bbp->out_old))
			return FALSE;
	}
	return TRUE;
}

void _do_dataflow(void)
{
	BBListSP bl, blt;
	BBSP b;
	int bm_tmp[8];
	do {
		for (   bl = fun_block_head; 
			bl->bbp->posts->bbp; 
			bl = bl->next) 
		{
			b = bl->bbp;
			bm_copy(b->in_old, b->in);
			bm_copy(b->out_old, b->out);
			bit_clear_all(b->out);
			for (blt = b->posts; blt; blt = blt->next) {
				bm_union(b->out, b->out, blt->bbp->in);
			}
			bm_sub(bm_tmp, b->out, b->def);
			bm_union(b->in, b->use, bm_tmp);

		// fprintf(code, "_do_dataflow in :");
		// printBitsmap(b->in);
		// fprintf(code, "_do_dataflow out:");
		// printBitsmap(b->out);
		}
	// printf("**********************************************\n");
	} while (!exit_condition());
	// printf("**********************************************\n");
}

void do_dataflow(void)
{
	BBListSP bl;
	for (bl = bblst; bl && !bl->bbp->pres->bbp; ) {
		fun_block_head = bl;
		// fun_block_tail = bl;
		_do_dataflow();
		// printf("********** void do_dataflow(void) ***********\n");
		for (bl = bl->next; bl && bl->bbp->pres->bbp ; bl = bl->next) 
			;
	}
}

void rm_useless_assign(void)
{
	BBListSP bl;
	BBSP b;
	QuadSP q;
	for (bl = bblst; bl; bl = bl->next) {
		b = bl->bbp;
		for (q = b->qhead; q; q = q->next) {
			if ( (q->op == ASS_op) && !bm_test(b->out, q->d)
			   && q->d->obj == Tmp_Obj_t) 
			{
				q->rm_flag = TRUE;
			}
		}
	}
}