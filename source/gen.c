#include "gen.h"
#include "syntax.h"
#include "global.h"
#include "symtab.h"

static void gen_pgm(pgm_node_t *node)
{
	scope_entry("main");

	nevernil(node->bp);
	block_node_t *b = node->bp;
	gen_const_decf(b->cdp);
	gen_var_decf(b->vdp);
	gen_pf_dec_list(b->pfdlp);
	gen_comp_stmt(b->csp);

	scope_exit();
}

static void gen_const_decf(const_dec_node_t *node)
{
	for (const_dec_node_t *t = node; t; t = t->next) {
		nevernil(t->cdp);
		nevernil(t->cdp->idp);
		ident_node_t *idp = t->cdp->idp;
		syment_t *e = symget(idp->name);
		if (e) {
			rescue(DUPSYM, "L%d: const %s already declared.",
			       idp->line, idp->name);
		} else {
			e = syminit(idp);
		}
		idp->symbol = e;
	}
}

static void gen_var_decf(var_dec_node_t *node)
{
	for (var_dec_node_t *t = node; t; t = t->next) {
		for (var_def_node_t *p = t->vdp; p; p = p->next) {
			nevernil(p->idp);
			ident_node_t *idp = p->idp;
			syment_t *e = symget(idp->name);
			if (e) {
				rescue(DUPSYM,
				       "L%d: variable %s already declared.",
				       idp->line, idp->name);
			} else {
				e = syminit(idp);
			}
			idp->symbol = e;
		}
	}
}

static void gen_pf_dec_list(pf_dec_list_node_t *node)
{
	for (pf_dec_list_node_t *t = node; t; t = t->next) {
		switch (t->type) {
		case PROC_PFDEC:
			gen_proc_decf(t->pdp);
			break;
		case FUN_PFDEC:
			gen_fun_decf(t->fdp);
			break;
		default:
			unlikely();
		}
	}
}

static void gen_proc_decf(proc_dec_node_t *node)
{
	for (proc_dec_node_t *t = node; t; t = t->next) {
		nevernil(t->pdp);
		nevernil(t->pdp->php);
		gen_proc_head(t->pdp->php);

		nevernil(t->pdp->bp);
		block_node_t *b = t->pdp->bp;

		gen_const_decf(b->cdp);
		gen_var_decf(b->vdp);
		gen_pf_dec_list(b->pfdlp);
		gen_comp_stmt(b->csp);

		scope_exit();
	}
}

static void gen_proc_head(proc_head_node_t *node)
{
	proc_head_node_t *t = node;

	nevernil(t->idp);
	ident_node_t *idp = t->idp;
	syment_t *e = symget(idp->name);
	if (e) {
		rescue(DUPSYM, "L%d: procedure %s already declared.", idp->line,
		       idp->name);
	} else {
		e = syminit(idp);
	}
	idp->symbol = e;

	scope_entry(idp->name);

	nevernil(t->plp);
	gen_para_list(idp->symbol, t->plp);
}

static void gen_fun_decf(fun_dec_node_t *node)
{
	for (fun_dec_node_t *t = node; t; t = t->next) {
		nevernil(t->fdp);
		nevernil(t->fdp->fhp);
		gen_fun_head(t->fdp->fhp);

		nevernil(t->fdp->bp);
		block_node_t *b = t->fdp->bp;

		gen_const_decf(b->cdp);
		gen_var_decf(b->vdp);
		gen_pf_dec_list(b->pfdlp);
		gen_comp_stmt(b->csp);

		scope_exit();
	}
}

static void gen_fun_head(fun_head_node_t *node)
{
	fun_head_node_t *t = node;

	nevernil(t->idp);
	ident_node_t *idp = t->idp;
	syment_t *e = symget(idp->name);
	if (e) {
		rescue(DUPSYM, "L%d: function %s already declared.", idp->line,
		       idp->name);
	} else {
		e = syminit(idp);
	}
	idp->symbol = e;

	scope_entry(idp->name);

	nevernil(t->plp);
	gen_para_list(idp->symbol, t->plp);
}

static void gen_para_list(syment_t *sign, para_list_node_t *node)
{
	for (para_list_node_t *t = node; t; t = t->next) {
		for (para_def_node_t *p = t->pdp; p; p = p->next) {
			nevernil(p->idp);
			ident_node_t *idp = p->idp;
			syment_t *e = symget(idp->name);
			if (e) {
				rescue(DUPSYM,
				       "L%d: parameter %s already declared.",
				       idp->line, idp->name);
			} else {
				e = syminit(idp);
			}
			idp->symbol = e;

			param_t *param;
			NEWPARAM(param);
			param->symbol = e;

			if (!sign->ptail) {
				sign->ptail = param;
				sign->phead = param;
			} else {
				sign->ptail->next = param;
				sign->ptail = param;
			}
		}
	}
}

static void gen_comp_stmt(comp_stmt_node_t *node)
{
	for (comp_stmt_node_t *t = node; t != NULL; t = t->next) {
		nevernil(t->sp);
		gen_stmt(t->sp);
	}
}

static void gen_stmt(stmt_node_t *node)
{
	switch (node->type) {
	case ASSGIN_STMT:
		gen_assign_stmt(node->asp);
		break;
	case IF_STMT:
		gen_if_stmt(node->ifp);
		break;
	case REPEAT_STMT:
		gen_repe_stmt(node->rpp);
		break;
	case FOR_STMT:
		gen_for_stmt(node->frp);
		break;
	case PCALL_STMT:
		gen_pcall_stmt(node->pcp);
		break;
	case COMP_STMT:
		gen_comp_stmt(node->cpp);
		break;
	case READ_STMT:
		gen_read_stmt(node->rdp);
		break;
	case WRITE_STMT:
		gen_write_stmt(node->wtp);
		break;
	case NULL_STMT:
		break;
	default:
		unlikely();
	}
}

static void gen_assign_stmt(assign_stmt_node_t *node)
{
	syment_t *e;
	ident_node_t *idp = node->idp;
	e = symfind(idp->name);
	if (!e) {
		giveup(BADSYM, "L%d: symbol %s not found.", idp->line,
		       idp->name);
	}
	idp->symbol = e;
	switch (node->type) {
	case NORM_ASSGIN:
	case FUN_ASSGIN:
		gen_expr(node->rep);
		break;
	case ARRAY_ASSGIN:
		gen_expr(node->lep);
		gen_expr(node->rep);
		break;
	default:
		unlikely();
	}
}

static void gen_if_stmt(if_stmt_node_t *node)
{
	gen_cond(node->cp);
	if (node->ep) {
		gen_stmt(node->ep);
	}
	gen_stmt(node->tp);
}

static void gen_repe_stmt(repe_stmt_node_t *node)
{
	gen_stmt(node->sp);
	gen_cond(node->cp);
}

static void gen_for_stmt(for_stmt_node_t *node)
{
	gen_expr(node->lep);
	gen_expr(node->rep);

	ident_node_t *idp = node->idp;
	syment_t *e = symfind(idp->name);
	if (!e) {
		giveup(BADSYM, "L%d: symbol %s not found.", idp->line,
		       idp->name);
	}
	idp->symbol = e;

	switch (node->type) {
	case TO_FOR:
	case DOWNTO_FOR:
		gen_stmt(node->sp);
		break;
	default:
		unlikely();
	}
}

static void gen_pcall_stmt(pcall_stmt_node_t *node)
{
	ident_node_t *idp = node->idp;
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

	gen_arg_list(e, node->alp);
}

static void gen_read_stmt(read_stmt_node_t *node)
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

static void gen_write_stmt(write_stmt_node_t *node)
{
	switch (node->type) {
	case STR_WRITE:
		break;
	case ID_WRITE:
	case STRID_WRITE:
		gen_expr(node->ep);
		break;
	default:
		unlikely();
	}
}

static void gen_expr(expr_node_t *node)
{
	for (expr_node_t *t = node; t; t = t->next) {
		nevernil(t->tp);
		gen_term(t->tp);
	}
}

static void gen_term(term_node_t *node)
{
	for (term_node_t *t = node; t; t = t->next) {
		nevernil(t->fp);
		gen_factor(t->fp);
	}
}

static void gen_factor(factor_node_t *node)
{
	ident_node_t *idp;
	syment_t *e;
	switch (node->type) {
	case ID_FACTOR:
		nevernil(node->idp);
		idp = node->idp;
		e = symfind(idp->name);
		if (!e) {
			giveup(BADSYM, "L%d: symbol %s not found.", idp->line,
			       idp->name);
		}
		// TODO OBJ5(Const_Obj_t, Var_Obj_t, Para_Val_Obj_t, Para_Ref_Obj_t, Tmp_Obj_t)) {
		idp->symbol = e;
		break;
	case ARRAY_FACTOR:
		nevernil(node->idp);
		idp = node->idp;
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
		nevernil(node->ep);
		gen_expr(node->ep);
		break;
	case FUNCALL_FACTOR:
		nevernil(node->fcsp);
		gen_fcall_stmt(node->fcsp);
		break;
	default:
		unlikely();
	}
}

static void gen_fcall_stmt(fcall_stmt_node_t *node)
{
	nevernil(node->idp);
	ident_node_t *idp = node->idp;
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

	nevernil(node->alp);
	gen_arg_list(e, node->alp);
}

static void gen_cond(cond_node_t *node)
{
	nevernil(node->lep);
	gen_expr(node->lep);
	nevernil(node->rep);
	gen_expr(node->rep);
}

static void gen_arg_list(syment_t *sign, arg_list_node_t *node)
{
	arg_list_node_t *t = node;
	param_t *p = sign->phead;
	int pos = 0;
	for (; t && p; t = t->next, p = p->next) {
		pos++;
		syment_t *e = p->symbol;
		switch (e->cate) {
		case BYVAL_OBJ:
			nevernil(t->ep);
			gen_expr(t->ep);
			break;
		case BYREF_OBJ: // var, arr[exp]
			if (!t->ep || t->ep->op != NOP_ADDOP) {
				goto referr;
			}
			expr_node_t *ep = t->ep;
			if (!ep->tp || ep->tp->op != NOP_MULTOP) {
				goto referr;
			}
			term_node_t *tp = ep->tp;
			if (!tp->fp) {
				goto referr;
			}

			factor_node_t *fp = tp->fp;
			ident_node_t *idp;
			if (fp->type != ID_FACTOR || fp->type != ARRAY_FACTOR) {
				idp = fp->idp;
				goto refok;
			}
		referr:
			giveup(BADREF,
			       "L%d: %s call arguments has bad reference, pos = %d.",
			       sign->lineno, sign->name, pos);
			continue;
		refok:
			syment_t *e = symfind(idp->name);
			if (!e) {
				giveup(BADSYM, "L%d: symbol %s not found.",
				       idp->line, idp->name);
			}
			if (fp->type == ID_FACTOR && e->cate != VAR_OBJ) {
				giveup(OBJREF,
				       "L%d: argument %s call by reference is not variable object, pos = %d.",
				       idp->line, idp->name, pos);
			}
			if (fp->type == ARRAY_FACTOR && e->cate != ARRAY_OBJ) {
				giveup(OBJREF,
				       "L%d: argument %s call by reference is not array object, pos = %d.",
				       idp->line, idp->name, pos);
			}
			idp->symbol = e;
			break;
		default:
			unlikely();
		}
	}

	if (t || p) {
		giveup(BADLEN,
		       "L%d: %s call arguments and parameters length not equal.",
		       sign->lineno, sign->name);
	}
}

void codegen()
{
	gen_pgm(prog);
}
