#include "error.h"
#include "anlys.h"
#include "global.h"
#include "debug.h"
#include "util.h"
#include "syntax.h"
#include "parse.h"
#include "symtab.h"

void anlys_pgm(pgm_node_t *node)
{
	scope_entry("main");

	block_node_t *b = node->bp;
	anlys_const_decf(b->cdp);
	anlys_var_decf(b->vdp);
	anlys_pf_dec_list(b->pfdlp);
	anlys_comp_stmt(b->csp);

	scope_exit();
}

void anlys_const_decf(const_dec_node_t *node)
{
	for (const_dec_node_t *t = node; t; t = t->next) {
		nevernil(t->cdp);
		nevernil(t->cdp->idp);
		ident_node_t *idp = t->cdp->idp;
		syment_t *e = symget(idp->name);
		if (e) {
			rescue(DUPSYM, "L%d: const %s already defined.",
			       idp->line, idp->name);
			idp->symbol = e;
			continue;
		}
		idp->symbol = syminit(idp);
	}
}

void anlys_var_decf(var_dec_node_t *node)
{
	for (var_dec_node_t *t = node; t; t = t->next) {
		for (var_def_node_t *p = t->vdp; p; p = p->next) {
			nevernil(p->idp);
			ident_node_t *idp = p->idp;
			syment_t *e = symget(idp->name);
			if (e) {
				rescue(DUPSYM,
				       "L%d: variable %s already defined.",
				       idp->line, idp->name);
				idp->symbol = e;
				continue;
			}
			idp->symbol = syminit(idp);
		}
	}
}

void anlys_pf_dec_list(pf_dec_list_node_t *node)
{
	for (pf_dec_list_node_t *t = node; t; t = t->next) {
		switch (t->type) {
		case PROC_PFDEC:
			anlys_proc_decf(t->pdp);
			break;
		case FUN_PFDEC:
			anlys_fun_decf(t->fdp);
			break;
		default:
			unlikely();
		}
	}
}

void anlys_proc_decf(proc_dec_node_t *node)
{
	for (proc_dec_node_t *t = node; t; t = t->next) {
		nevernil(t->pdp);
		nevernil(t->pdp->php);
		anlys_proc_head(t->pdp->php);

		nevernil(t->pdp->bp);
		block_node_t *b = t->pdp->bp;

		anlys_const_decf(b->cdp);
		anlys_var_decf(b->vdp);
		anlys_pf_dec_list(b->pfdlp);
		anlys_comp_stmt(b->csp);

		scope_exit();
	}
}

void anlys_proc_head(proc_head_node_t *node)
{
	proc_head_node_t *t = node;

	nevernil(t->idp);
	ident_node_t *idp = t->idp;
	syment_t *e = symget(idp->name);
	if (e) {
		rescue(DUPSYM, "L%d: procedure %s already defined.", idp->line,
		       idp->name);
		idp->symbol = e;
	} else {
		idp->symbol = syminit(idp);
	}

	scope_entry(idp->name);

	nevernil(t->plp);
	anlys_para_list(t->plp);
}

void anlys_fun_decf(fun_dec_node_t *node)
{
	for (fun_dec_node_t *t = node; t; t = t->next) {
		nevernil(t->fdp);
		nevernil(t->fdp->fhp);
		anlys_fun_head(t->fdp->fhp);

		nevernil(t->fdp->bp);
		block_node_t *b = t->fdp->bp;

		anlys_const_decf(b->cdp);
		anlys_var_decf(b->vdp);
		anlys_pf_dec_list(b->pfdlp);
		anlys_comp_stmt(b->csp);

		scope_exit();
	}
}

void anlys_fun_head(fun_head_node_t *node)
{
	fun_head_node_t *t = node;

	nevernil(t->idp);
	ident_node_t *idp = t->idp;
	syment_t *e = symget(idp->name);
	if (e) {
		rescue(DUPSYM, "L%d: function %s already defined.", idp->line,
		       idp->name);
		idp->symbol = e;
	} else {
		idp->symbol = syminit(idp);
	}

	scope_entry(idp->name);

	nevernil(t->plp);
	anlys_para_list(t->plp);
}

void anlys_para_list(para_list_node_t *node)
{
	for (para_list_node_t *t = node; t; t = t->next) {
		for (para_def_node_t *p = t->pdp; p; p = p->next) {
			nevernil(p->idp);
			ident_node_t *idp = p->idp;
			syment_t *e = symget(idp->name);
			if (e) {
				rescue(DUPSYM,
				       "L%d: parameter %s already defined.",
				       idp->line, idp->name);
				idp->symbol = e;
				continue;
			}
			idp->symbol = syminit(idp);
		}
	}
}

void anlys_comp_stmt(comp_stmt_node_t *node)
{
	for (comp_stmt_node_t *t = node; t != NULL; t = t->next) {
		nevernil(t->sp);
		anlys_stmt(t->sp);
	}
}

void anlys_stmt(stmt_node_t *node)
{
	switch (node->type) {
	case ASSGIN_STMT:
		anlys_assign_stmt(node->asp);
		break;
	case IF_STMT:
		anlys_if_stmt(node->ifp);
		break;
	case REPEAT_STMT:
		anlys_repe_stmt(node->rpp);
		break;
	case FOR_STMT:
		anlys_for_stmt(node->frp);
		break;
	case PCALL_STMT:
		anlys_pcall_stmt(node->pcp);
		break;
	case COMP_STMT:
		anlys_comp_stmt(node->cpp);
		break;
	case READ_STMT:
		anlys_read_stmt(node->rdp);
		break;
	case WRITE_STMT:
		anlys_write_stmt(node->wtp);
		break;
	case NULL_STMT:
		break;
	default:
		unlikely();
	}
}

void anlys_assign_stmt(assign_stmt_node_t *node)
{
	syment_t *e;
	switch (node->type) {
	case NORM_ASSGIN:
	case FUN_ASSGIN:
	case ARRAY_ASSGIN:
		ident_node_t *idp = node->idp;
		e = symfind(idp->name);
		if (!e) {
			giveup(BADSYM, "L%d: symbol %s not found.", idp->line,
			       idp->name);
		}
		idp->symbol = e;
	default:
		unlikely();
	}
}

void anlys_if_stmt(if_stmt_node_t *node)
{
	anlys_cond(node->cp);
	if (node->ep) {
		anlys_stmt(node->ep);
	}
	anlys_stmt(node->tp);
}

void anlys_repe_stmt(repe_stmt_node_t *node)
{
	anlys_stmt(node->sp);
	anlys_cond(node->cp);
}

void anlys_for_stmt(for_stmt_node_t *t)
{
	anlys_expr(t->lep);
	anlys_expr(t->rep);

	ident_node_t *idp = t->idp;
	syment_t *e = symfind(idp->name);
	if (!e) {
		giveup(BADSYM, "L%d: symbol %s not found.", idp->line,
		       idp->name);
	}
	idp->symbol = e;

	switch (t->type) {
	case TO_FOR:
	case DOWNTO_FOR:
		anlys_stmt(t->sp);
		break;
	default:
		unlikely();
	}
}

void anlys_pcall_stmt(pcall_stmt_node_t *t)
{
	ident_node_t *idp = t->idp;
	syment_t *e = symfind(idp->name);
	if (!e) {
		giveup(BADSYM, "L%d: symbol %s not found.", idp->line,
		       idp->name);
	}
	if (e->cate != PROC_OBJ) {
		giveup(BADSYM, "L%d: procedure %s not found.", idp->line,
		       idp->name);
	}
	idp->symbol = e;

	anlys_arg_list(t->alp);
}

void anlys_read_stmt(read_stmt_node_t *node)
{
	for (read_stmt_node_t *t = node; t; t = t->next) {
		nevernil(t->idp);
		ident_node_t *idp = t->idp;
		syment_t *e = symfind(idp->name);
		if (!e) {
			giveup(BADSYM, "L%d: symbol %s not found.", idp->line,
			       idp->name);
		}
		idp->symbol = e;
	}
}

void anlys_write_stmt(write_stmt_node_t *t)
{
	switch (t->type) {
	case STR_WRITE:
		break;
	case ID_WRITE:
	case STRID_WRITE:
		anlys_expr(t->ep);
		break;
	default:
		unlikely();
	}
}

void anlys_expr(expr_node_t *node)
{
	for (expr_node_t *t = node; t; t = t->next) {
		nevernil(t->tp);
		anlys_term(t->tp);
	}
}

void anlys_term(term_node_t *node)
{
	for (term_node_t *t = node; t; t = t->next) {
		nevernil(t->fp);
		anlys_factor(t->fp);
	}
}

void anlys_factor(factor_node_t *t)
{
	ident_node_t *idp;
	syment_t *e;
	switch (t->type) {
	case ID_FACTOR:
		nevernil(t->idp);
		idp = t->idp;
		e = symfind(idp->name);
		if (!e) {
			giveup(BADSYM, "L%d: symbol %s not found.", idp->line,
			       idp->name);
		}
		// TODO OBJ5(Const_Obj_t, Var_Obj_t, Para_Val_Obj_t, Para_Ref_Obj_t, Tmp_Obj_t)) {
		idp->symbol = e;
		break;
	case ARRAY_FACTOR:
		nevernil(t->idp);
		idp = t->idp;
		e = symfind(idp->name);
		if (!e) {
			giveup(BADSYM, "L%d: symbol %s not found.", idp->line,
			       idp->name);
		}
		if (e->cate != ARRAY_OBJ) {
			giveup(ERTYPE, "L%d: symbol %s type is not array.",
			       idp->line, idp->name);
		}
		idp->symbol = e;
		break;
	case UNSIGN_FACTOR:
		break;
	case EXPR_FACTOR:
		nevernil(t->ep);
		anlys_expr(t->ep);
		break;
	case FUNCALL_FACTOR:
		nevernil(t->fcsp);
		anlys_fcall_stmt(t->fcsp);
		break;
	default:
		unlikely();
	}
}

void anlys_fcall_stmt(fcall_stmt_node_t *t)
{
	nevernil(t->idp);
	ident_node_t *idp = t->idp;
	syment_t *e = symfind(idp->name);
	if (!e) {
		giveup(BADSYM, "L%d: function %s not found.", idp->line,
		       idp->name);
	}
	if (e->cate != FUN_OBJ) {
		giveup(ERTYPE, "L%d: symbol %s type is not function.",
		       idp->line, idp->name);
	}
	idp->symbol = e;

	nevernil(t->alp);
	anlys_arg_list(t->alp);
}

void anlys_cond(cond_node_t *t)
{
	nevernil(t->lep);
	anlys_expr(t->lep);
	nevernil(t->rep);
	anlys_expr(t->rep);
}

void anlys_arg_list(arg_list_node_t *node)
{
	// TODO
}
