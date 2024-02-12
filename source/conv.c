#include "conv.h"
#include "debug.h"
#include "ir.h"
#include "limits.h"
#include "util.h"
#include "global.h"
#include "parse.h"
#include "syntax.h"

static int nextseq = 0;

static node_t *initnode(int nid, char *name)
{
	node_t *d;
	INITMEM(node_t, d);
	d->seq = ++nextseq;
	d->nid = nid;
	strcopy(d->name, name);
	return d;
}

static void addchild(node_t *parent, node_t *child, char *ref)
{
	if (!child) {
		return;
	}

	if (parent->nchild + 1 >= MAXNODECHILD) {
		panic("TOO_MANY_NODE_CHILD");
	}

	strcopy(parent->chdptrs[parent->nchild], ref);
	parent->childs[parent->nchild] = child;
	parent->nchild++;
}

node_t *conv_pgm_node(pgm_node_t *t)
{
	if (!t) {
		return NULL;
	}
	node_t *d = initnode(t->nid, "PGM");
	addchild(d, conv_ident_node(t->entry), "entry");
	addchild(d, conv_block_node(t->bp), "bp");
	return d;
}

node_t *conv_block_node(block_node_t *t)
{
	if (!t) {
		return NULL;
	}
	node_t *d = initnode(t->nid, "BLOCK");
	addchild(d, conv_const_dec_node(t->cdp), "cdp");
	addchild(d, conv_var_dec_node(t->vdp), "vdp");
	addchild(d, conv_pf_dec_list_node(t->pfdlp), "pfdlp");
	addchild(d, conv_comp_stmt_node(t->csp), "csp");
	return d;
}

node_t *conv_const_dec_node(const_dec_node_t *t)
{
	if (!t) {
		return NULL;
	}
	node_t *d = initnode(t->nid, "CONST_DEC");
	for (; t; t = t->next) {
		addchild(d, conv_const_def_node(t->cdp), "cdp");
	}
	return d;
}

node_t *conv_const_def_node(const_def_node_t *t)
{
	if (!t) {
		return NULL;
	}
	node_t *d = initnode(t->nid, "CONST_DEF");
	addchild(d, conv_ident_node(t->idp), "idp");
	return d;
}

node_t *conv_var_dec_node(var_dec_node_t *t)
{
	if (!t) {
		return NULL;
	}
	node_t *d = initnode(t->nid, "VAR_DEC");
	for (; t; t = t->next) {
		addchild(d, conv_var_def_node(t->vdp), "vdp");
	}
	return d;
}

node_t *conv_var_def_node(var_def_node_t *t)
{
	if (!t) {
		return NULL;
	}
	node_t *d = initnode(t->nid, "VAR_DEF");
	for (; t; t = t->next) {
		addchild(d, conv_ident_node(t->idp), "idp");
	}
	return d;
}

node_t *conv_pf_dec_list_node(pf_dec_list_node_t *t)
{
	if (!t) {
		return NULL;
	}
	node_t *d = initnode(t->nid, "PF_DEC_LIST");
	for (; t; t = t->next) {
		switch (t->kind) {
		case PROC_PFDEC:
			addchild(d, conv_proc_dec_node(t->pdp), "pdp");
			break;
		case FUN_PFDEC:
			addchild(d, conv_fun_dec_node(t->fdp), "fdp");
			break;
		default:
			unlikely();
		}
	}
	return d;
}

node_t *conv_proc_dec_node(proc_dec_node_t *t)
{
	if (!t) {
		return NULL;
	}
	node_t *d = initnode(t->nid, "PROC_DEC");
	for (; t; t = t->next) {
		addchild(d, conv_proc_def_node(t->pdp), "pdp");
	}
	return d;
}

node_t *conv_proc_def_node(proc_def_node_t *t)
{
	if (!t) {
		return NULL;
	}
	node_t *d = initnode(t->nid, "PROC_DEF");
	addchild(d, conv_proc_head_node(t->php), "php");
	addchild(d, conv_block_node(t->bp), "bp");
	return d;
}

node_t *conv_proc_head_node(proc_head_node_t *t)
{
	if (!t) {
		return NULL;
	}
	node_t *d = initnode(t->nid, "PROC_HEAD");
	addchild(d, conv_ident_node(t->idp), "idp");
	addchild(d, conv_para_list_node(t->plp), "plp");
	return d;
}

node_t *conv_fun_dec_node(fun_dec_node_t *t)
{
	if (!t) {
		return NULL;
	}
	node_t *d = initnode(t->nid, "FUN_DEC");
	for (; t; t = t->next) {
		addchild(d, conv_fun_def_node(t->fdp), "fdp");
	}
	return d;
}

node_t *conv_fun_def_node(fun_def_node_t *t)
{
	if (!t) {
		return NULL;
	}
	node_t *d = initnode(t->nid, "FUN_DEF");
	addchild(d, conv_fun_head_node(t->fhp), "fhp");
	addchild(d, conv_block_node(t->bp), "bp");
	return d;
}

node_t *conv_fun_head_node(fun_head_node_t *t)
{
	if (!t) {
		return NULL;
	}
	node_t *d = initnode(t->nid, "FUN_HEAD");
	addchild(d, conv_ident_node(t->idp), "idp");
	addchild(d, conv_para_list_node(t->plp), "plp");
	return d;
}

node_t *conv_stmt_node(stmt_node_t *t)
{
	if (!t) {
		return NULL;
	}
	node_t *d = initnode(t->nid, "STMT");
	if (!t) {
		strcpy(d->name, "NULLSTMT");
		return d;
	}

	d->kind = t->kind;
	switch (t->kind) {
	case ASSGIN_STMT:
		addchild(d, conv_assign_stmt_node(t->asp), "asp");
		break;
	case IF_STMT:
		addchild(d, conv_if_stmt_node(t->ifp), "ifp");
		break;
	case REPEAT_STMT:
		addchild(d, conv_repe_stmt_node(t->rpp), "rpp");
		break;
	case PCALL_STMT:
		addchild(d, conv_pcall_stmt_node(t->pcp), "pcp");
		break;
	case COMP_STMT:
		addchild(d, conv_comp_stmt_node(t->cpp), "cpp");
		break;
	case READ_STMT:
		addchild(d, conv_read_stmt_node(t->rdp), "rdp");
		break;
	case WRITE_STMT:
		addchild(d, conv_write_stmt_node(t->wtp), "wtp");
		break;
	case FOR_STMT:
		addchild(d, conv_for_stmt_node(t->frp), "frp");
		break;
	case NULL_STMT:
		break;
	default:
		unlikely();
	}
	return d;
}

node_t *conv_assign_stmt_node(assign_stmt_node_t *t)
{
	if (!t) {
		return NULL;
	}
	node_t *d = initnode(t->nid, "ASSIGN_STMT");
	d->kind = t->kind;
	switch (t->kind) {
	case NORM_ASSGIN:
		addchild(d, conv_ident_node(t->idp), "idp");
		addchild(d, conv_expr_node(t->lep), "lep");
		addchild(d, conv_expr_node(t->rep), "rep");
		break;
	case ARRAY_ASSGIN:
		addchild(d, conv_ident_node(t->idp), "idp");
		addchild(d, conv_expr_node(t->lep), "lep");
		addchild(d, conv_expr_node(t->rep), "rep");
		break;
	case FUN_ASSGIN:
		unlikely();
		break;
	default:
		unlikely();
	}
	return d;
}

node_t *conv_if_stmt_node(if_stmt_node_t *t)
{
	if (!t) {
		return NULL;
	}
	node_t *d = initnode(t->nid, "IF_STMT");
	addchild(d, conv_cond_node(t->cp), "cp");
	addchild(d, conv_stmt_node(t->tp), "tp");
	addchild(d, conv_stmt_node(t->ep), "ep");
	return d;
}

node_t *conv_repe_stmt_node(repe_stmt_node_t *t)
{
	if (!t) {
		return NULL;
	}
	node_t *d = initnode(t->nid, "REPE_STMT");
	addchild(d, conv_cond_node(t->cp), "cp");
	addchild(d, conv_stmt_node(t->sp), "sp");
	return d;
}

node_t *conv_for_stmt_node(for_stmt_node_t *t)
{
	if (!t) {
		return NULL;
	}
	node_t *d = initnode(t->nid, "FOR_STMT");
	addchild(d, conv_ident_node(t->idp), "idp");
	addchild(d, conv_expr_node(t->lep), "lep");
	addchild(d, conv_expr_node(t->rep), "rep");
	addchild(d, conv_stmt_node(t->sp), "sp");
	return d;
}

node_t *conv_pcall_stmt_node(pcall_stmt_node_t *t)
{
	if (!t) {
		return NULL;
	}
	node_t *d = initnode(t->nid, "PCALL_STMT");
	addchild(d, conv_ident_node(t->idp), "idp");
	addchild(d, conv_arg_list_node(t->alp), "alp");
	return d;
}

node_t *conv_fcall_stmt_node(fcall_stmt_node_t *t)
{
	if (!t) {
		return NULL;
	}
	node_t *d = initnode(t->nid, "FCALL_STMT");
	addchild(d, conv_ident_node(t->idp), "idp");
	addchild(d, conv_arg_list_node(t->alp), "alp");
	return d;
}

node_t *conv_comp_stmt_node(comp_stmt_node_t *t)
{
	if (!t) {
		return NULL;
	}
	node_t *d = initnode(t->nid, "COMP_STMT");
	for (; t; t = t->next) {
		addchild(d, conv_stmt_node(t->sp), "sp");
	}
	return d;
}

node_t *conv_read_stmt_node(read_stmt_node_t *t)
{
	if (!t) {
		return NULL;
	}
	node_t *d = initnode(t->nid, "READ_STMT");
	for (; t; t = t->next) {
		addchild(d, conv_ident_node(t->idp), "idp");
	}
}

node_t *conv_write_stmt_node(write_stmt_node_t *t)
{
	if (!t) {
		return NULL;
	}

	node_t *d = initnode(t->nid, "WRITE_STMT");
	char buf[MAXSTRBUF];
	d->kind = t->type;
	switch (t->type) {
	case STR_WRITE:
		sprintf(buf, "\\\"%s\\\"", t->sp);
		strcopy(d->extra, buf);
		break;
	case ID_WRITE:
		addchild(d, conv_expr_node(t->ep), "ep");
		break;
	case STRID_WRITE:
		sprintf(buf, "\\\"%s\\\"", t->sp);
		strcopy(d->extra, buf);
		addchild(d, conv_expr_node(t->ep), "ep");
		break;
	default:
		unlikely();
	}

	return d;
}

node_t *conv_expr_node(expr_node_t *t)
{
	if (!t) {
		return NULL;
	}
	node_t *d = initnode(t->nid, "EXPR");
	for (; t; t = t->next) {
		switch (t->kind) {
		case ADD_ADDOP:
			strcpy(d->extra, "+");
			break;
		case MINUS_ADDOP:
		case NEG_ADDOP:
			strcpy(d->extra, "-");
			break;
		}
		addchild(d, conv_term_node(t->tp), "tp");
	}
	return d;
}

node_t *conv_term_node(term_node_t *t)
{
	if (!t) {
		return NULL;
	}
	node_t *d = initnode(t->nid, "TERM");
	for (; t; t = t->next) {
		switch (t->kind) {
		case MULT_MULTOP:
			strcpy(d->extra, "*");
			break;
		case DIV_MULTOP:
			strcpy(d->extra, "/");
			break;
		}
		addchild(d, conv_factor_node(t->fp), "fp");
	}
	return d;
}

node_t *conv_factor_node(factor_node_t *t)
{
	if (!t) {
		return NULL;
	}

	node_t *d = initnode(t->nid, "FACTOR");
	char buf[MAXSTRBUF];
	d->kind = t->kind;
	switch (t->kind) {
	case ID_FACTOR:
		addchild(d, conv_ident_node(t->idp), "idp");
		break;
	case ARRAY_FACTOR:
		addchild(d, conv_ident_node(t->idp), "idp");
		addchild(d, conv_expr_node(t->ep), "ep");
		break;
	case UNSIGN_FACTOR:
		sprintf(buf, "%d", t->value);
		strcopy(d->extra, buf);
		break;
	case CHAR_FACTOR:
		sprintf(buf, "'%c'", t->value);
		strcopy(d->extra, buf);
		break;
	case EXPR_FACTOR:
		addchild(d, conv_expr_node(t->ep), "ep");
		break;
	case FUNCALL_FACTOR:
		addchild(d, conv_fcall_stmt_node(t->fcsp), "fcsp");
		break;
	}
	return d;
}

node_t *conv_cond_node(cond_node_t *t)
{
	if (!t) {
		return NULL;
	}
	node_t *d = initnode(t->nid, "COND");
	d->kind = t->kind;
	switch (t->kind) {
	case EQU_RELA:
		strcpy(d->extra, "=");
		break;
	case NEQ_RELA:
		strcpy(d->extra, "<>");
		break;
	case GTT_RELA:
		strcpy(d->extra, ">");
		break;
	case GEQ_RELA:
		strcpy(d->extra, ">=");
		break;
	case LST_RELA:
		strcpy(d->extra, "<");
		break;
	case LEQ_RELA:
		strcpy(d->extra, "<=");
		break;
	}
	addchild(d, conv_expr_node(t->lep), "lep");
	addchild(d, conv_expr_node(t->rep), "rep");
	return d;
}

node_t *conv_ident_node(ident_node_t *t)
{
	if (!t) {
		return NULL;
	}
	node_t *d = initnode(t->nid, "IDENT");
	d->idp = t;
	return d;
}

node_t *conv_para_list_node(para_list_node_t *t)
{
	if (!t) {
		return NULL;
	}
	node_t *d = initnode(t->nid, "PARA_LIST");
	for (; t; t = t->next) {
		addchild(d, conv_para_def_node(t->pdp), "pdp");
	}
	return d;
}

node_t *conv_para_def_node(para_def_node_t *t)
{
	if (!t) {
		return NULL;
	}
	node_t *d = initnode(t->nid, "PARA_DEF");
	for (; t; t = t->next) {
		addchild(d, conv_ident_node(t->idp), "idp");
	}
	return d;
}

node_t *conv_arg_list_node(arg_list_node_t *t)
{
	if (!t) {
		return NULL;
	}
	node_t *d = initnode(t->nid, "ARG_LIST");
	for (; t; t = t->next) {
		addchild(d, conv_expr_node(t->ep), "ep");
	}
	return d;
}
