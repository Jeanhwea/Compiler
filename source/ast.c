#include "ast.h"
#include "debug.h"
#include "global.h"
#include "parse.h"
#include "syntax.h"

static node_t *initnode(char *name)
{
	node_t *d;
	INITMEM(node_t, d);
	d->name = name;
	return d;
}

static node_t *conv_pgm_node(pgm_node_t *t)
{
	node_t *d = initnode("PGM");
	d->childs[d->nchild++] = conv_block_node(t->bp);
	return d;
}

static node_t *conv_block_node(block_node_t *t)
{
	node_t *d = initnode("BLOCK");
	d->childs[d->nchild++] = conv_const_dec_node(t->cdp);
	d->childs[d->nchild++] = conv_var_dec_node(t->vdp);
	d->childs[d->nchild++] = conv_pf_dec_list_node(t->pfdlp);
	d->childs[d->nchild++] = conv_comp_stmt_node(t->csp);
	return d;
}

static node_t *conv_const_dec_node(const_dec_node_t *t)
{
	node_t *d = initnode("CONST_DEC");
	for (; t; t = t->next) {
		d->childs[d->nchild++] = conv_const_def_node(t->cdp);
	}
	return d;
}

static node_t *conv_const_def_node(const_def_node_t *t)
{
	node_t *d = initnode("CONST_DEF");
	d->idp = t->idp;
	return d;
}

static node_t *conv_var_dec_node(var_dec_node_t *t)
{
	node_t *d = initnode("VAR_DEC");
	for (; t; t = t->next) {
		d->childs[d->nchild++] = conv_var_def_node(t->vdp);
	}
	return d;
}

static node_t *conv_var_def_node(var_def_node_t *t)
{
	node_t *d = initnode("VAR_DEF");
	d->idp = t->idp;
	return d;
}

static node_t *conv_pf_dec_list_node(pf_dec_list_node_t *t)
{
	node_t *d = initnode("PF_DEC_LIST");
	for (; t; t = t->next) {
		switch (t->type) {
		case PROC_PFDEC:
			d->childs[d->nchild++] = conv_proc_dec_node(t->pdp);
			break;
		case FUN_PFDEC:
			d->childs[d->nchild++] = conv_fun_dec_node(t->fdp);
			break;
		default:
			unlikely();
		}
	}
	return d;
}

static node_t *conv_proc_dec_node(proc_dec_node_t *t)
{
	node_t *d = initnode("PROC_DEC");
	for (; t; t = t->next) {
		d->childs[d->nchild++] = conv_proc_def_node(t->pdp);
	}
	return d;
}

static node_t *conv_proc_def_node(proc_def_node_t *t)
{
	node_t *d = initnode("PROC_DEF");
	d->childs[d->nchild++] = conv_proc_head_node(t->php);
	d->childs[d->nchild++] = conv_block_node(t->bp);
	return d;
}

static node_t *conv_proc_head_node(proc_head_node_t *t)
{
	node_t *d = initnode("PROC_HEAD");
	d->idp = t->idp;
	d->childs[d->nchild++] = conv_para_list_node(t->plp);
	return d;
}

static node_t *conv_fun_dec_node(fun_dec_node_t *t)
{
	node_t *d = initnode("FUN_DEC");
	return d;
}

static node_t *conv_fun_def_node(fun_def_node_t *t)
{
	node_t *d = initnode("FUN_DEF");
	return d;
}

static node_t *conv_fun_head_node(fun_head_node_t *t)
{
	node_t *d = initnode("FUN_HEAD");
	return d;
}

static node_t *conv_stmt_node(stmt_node_t *t)
{
	node_t *d = initnode("STMT");
	return d;
}
static node_t *conv_assign_stmt_node(assign_stmt_node_t *t)
{
	node_t *d = initnode("ASSIGN_STMT");
	return d;
}
static node_t *conv_if_stmt_node(if_stmt_node_t *t)
{
	node_t *d = initnode("IF_STMT");
	return d;
}
static node_t *conv_repe_stmt_node(repe_stmt_node_t *t)
{
	node_t *d = initnode("REPE_STMT");
	return d;
}
static node_t *conv_for_stmt_node(for_stmt_node_t *t)
{
	node_t *d = initnode("FOR_STMT");
	return d;
}
static node_t *conv_pcall_stmt_node(pcall_stmt_node_t *t)
{
	node_t *d = initnode("PCALL_STMT");
	return d;
}
static node_t *conv_fcall_stmt_node(fcall_stmt_node_t *t)
{
	node_t *d = initnode("FCALL_STMT");
	return d;
}
static node_t *conv_comp_stmt_node(comp_stmt_node_t *t)
{
	node_t *d = initnode("COMP_STMT");
	return d;
}
static node_t *conv_read_stmt_node(read_stmt_node_t *t)
{
	node_t *d = initnode("READ_STMT");
	return d;
}
static node_t *conv_write_stmt_node(write_stmt_node_t *t)
{
	node_t *d = initnode("WRITE_STMT");
	return d;
}
static node_t *conv_expr_node(expr_node_t *t)
{
	node_t *d = initnode("EXPR");
	return d;
}
static node_t *conv_term_node(term_node_t *t)
{
	node_t *d = initnode("TERM");
	return d;
}
static node_t *conv_factor_node(factor_node_t *t)
{
	node_t *d = initnode("FACTOR");
	return d;
}
static node_t *conv_cond_node(cond_node_t *t)
{
	node_t *d = initnode("COND");
	return d;
}
static node_t *conv_ident_node(ident_node_t *t)
{
	node_t *d = initnode("IDENT");
	return d;
}
static node_t *conv_para_list_node(para_list_node_t *t)
{
	node_t *d = initnode("PARA_LIST");
	return d;
}
static node_t *conv_para_def_node(para_def_node_t *t)
{
	node_t *d = initnode("PARA_DEF");
	return d;
}
static node_t *conv_arg_list_node(arg_list_node_t *t)
{
	node_t *d = initnode("ARG_LIST");
	return d;
}

node_t *conv_ast()
{
	return conv_pgm_node(prog);
}
