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
			recover(DUPSYM, "L%d: const %s already defined.",
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
				recover(DUPSYM,
					"L%d: variable %s already defined.",
					idp->line, idp->name);
				idp->symbol = e;
				continue;
			}
			syminit(p->idp);
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
		recover(DUPSYM, "L%d: procedure %s already defined.", idp->line,
			idp->name);
		idp->symbol = e;
	} else {
		syminit(idp);
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
		recover(DUPSYM, "L%d: function %s already defined.", idp->line,
			idp->name);
		idp->symbol = e;
	} else {
		syminit(t->idp);
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
			syminit(p->idp);
		}
	}
}

void anlys_comp_stmt(comp_stmt_node_t *node)
{
	for (comp_stmt_node_t *t = node; t != NULL; t = t->next) {
		nevernil(t->sp);
		// anlys_stmt(t->sp);
	}
}

// void anlys_stmt(stmt_node_t *t)
// {
//	switch (t->type) {
//	case ASSGIN_STMT:
//		anlys_assign_stmt(t->asp);
//		break;
//	case IF_STMT:
//		anlys_if_stmt(t->ifp);
//		break;
//	case REPEAT_STMT:
//		anlys_repe_stmt(t->rpp);
//		break;
//	case FOR_STMT:
//		anlys_for_stmt(t->frp);
//		break;
//	case PCALL_STMT:
//		anlys_pcall_stmt(t->pcp);
//		break;
//	case COMP_STMT:
//		anlys_comp_stmt(t->cpp);
//		break;
//	case READ_STMT:
//		anlys_read_stmt(t->rdp);
//		break;
//	case WRITE_STMT:
//		anlys_write_stmt(t->wtp);
//		break;
//	case NULL_STMT:
//		break;
//	default:
//		unlikely();
//	}
// }

// void anlys_assign_stmt(assign_stmt_node_t *t)
// {
//	syment_t *res;
//	inst_t *q;
//	if (t == NULL)
//		return;
//	switch (t->type) {
//	case Norm_Assgin_t:
//	case Fun_Assgin_t:
//		res = sym_lookup(t->idp->name);
//		if (res == NULL) {
//			--runlevel;
//			semanticError(NULLSYM, t->idp->line, FALSE,
//				      t->idp->name);
//			break;
//		}
//		if (OBJ(Fun_Obj_t)) {
//			NEWQUAD(q);
//			q->op = SRET_op;
//			q->r = anlys_expr(t->rep);
//			q->s = NULL;
//			q->d = res;
//			emit(q);
//		} else if (OBJ3(Var_Obj_t, Para_Val_Obj_t, Para_Ref_Obj_t)) {
//			NEWQUAD(q);
//			q->op = ASS_op;
//			q->r = anlys_expr(t->rep);
//			q->s = NULL;
//			q->d = res;
//			emit(q);
//		} else {
//			--runlevel;
//			semanticError(NOPVAR, t->idp->line, FALSE,
//				      t->idp->name);
//		}
//		break;
//	case Array_Assgin_t:
//		res = sym_lookup(t->idp->name);
//		if (res == NULL) {
//			--runlevel;
//			semanticError(NULLSYM, t->idp->line, FALSE,
//				      t->idp->name);
//			break;
//		}
//		if (OBJ(Array_Obj_t)) {
//			NEWQUAD(q);
//			q->op = AARR_op;
//			q->r = anlys_expr(t->rep);
//			q->s = anlys_expr(t->lep);
//			q->d = res;
//			emit(q);
//		} else {
//			--runlevel;
//			semanticError(NOPARRAY, t->idp->line, FALSE,
//				      t->idp->name);
//		}
//		break;
//	default:
//		fprintf(tiplist, "CODE BUG:84\n");
//		assert(0);
//	}
// }

// void anlys_if_stmt(if_stmt_node_t *t)
// {
//	inst_t *q, start, out;
//	syment_t *startlabel, outlabel;
//	if (t == NULL)
//		return;
//	startlabel = sym_make_label();
//	NEWQUAD(start);
//	start->op = LABEL_op;
//	start->r = NULL;
//	start->s = NULL;
//	start->d = startlabel;
//	outlabel = sym_make_label();
//	NEWQUAD(out);
//	out->op = LABEL_op;
//	out->r = NULL;
//	out->s = NULL;
//	out->d = outlabel;
//	anlys_cond(t->cp, startlabel);
//	if (t->ep != NULL) {
//		anlys_stmt(t->ep);
//	}
//	NEWQUAD(q);
//	q->op = JMP_op;
//	q->r = NULL;
//	q->s = NULL;
//	q->d = outlabel;
//	emit(q);
//	emit(start);
//	anlys_stmt(t->tp);
//	emit(out);
// }

// void anlys_repe_stmt(repe_stmt_node_t *t)
// {
//	inst_t *q, loop, out;
//	syment_t *looplabel, outlabel;
//	if (t == NULL)
//		return;
//	looplabel = sym_make_label();
//	NEWQUAD(loop);
//	loop->op = LABEL_op;
//	loop->r = NULL;
//	loop->s = NULL;
//	loop->d = looplabel;
//	outlabel = sym_make_label();
//	NEWQUAD(out);
//	out->op = LABEL_op;
//	out->r = NULL;
//	out->s = NULL;
//	out->d = outlabel;
//	emit(loop);
//	anlys_stmt(t->sp);
//	anlys_cond(t->cp, outlabel);
//	NEWQUAD(q);
//	q->op = JMP_op;
//	q->r = NULL;
//	q->s = NULL;
//	q->d = looplabel;
//	emit(q);
//	emit(out);
// }

// void anlys_for_stmt(for_stmt_node_t *t)
// {
//	inst_t *q, start, out;
//	syment_t *res, le, re, startlabel, outlabel;
//	if (t == NULL)
//		return;
//	startlabel = sym_make_label();
//	NEWQUAD(start);
//	start->op = LABEL_op;
//	start->r = NULL;
//	start->s = NULL;
//	start->d = startlabel;
//	outlabel = sym_make_label();
//	NEWQUAD(out);
//	out->op = LABEL_op;
//	out->r = NULL;
//	out->s = NULL;
//	out->d = outlabel;
//	le = anlys_expr(t->lep);
//	re = anlys_expr(t->rep);
//	res = sym_lookup(t->idp->name);
//	if (res == NULL) {
//		--runlevel;
//		semanticError(NULLSYM, t->idp->line, FALSE, t->idp->name);
//		return;
//	}
//	NEWQUAD(q);
//	q->op = ASS_op;
//	q->r = le;
//	q->s = NULL;
//	q->d = res;
//	emit(q);
//	emit(start);
//	switch (t->type) {
//	case To_For_t:
//		NEWQUAD(q);
//		q->op = GTT_op;
//		q->r = res;
//		q->s = re;
//		q->d = outlabel;
//		emit(q);
//		anlys_stmt(t->sp);
//		NEWQUAD(q);
//		q->op = INC_op;
//		q->r = NULL;
//		q->s = NULL;
//		q->d = res;
//		emit(q);
//		NEWQUAD(q);
//		q->op = JMP_op;
//		q->r = NULL;
//		q->s = NULL;
//		q->d = startlabel;
//		emit(q);
//		emit(out);
//		NEWQUAD(q);
//		q->op = DEC_op;
//		q->r = NULL;
//		q->s = NULL;
//		q->d = res;
//		emit(q);
//		break;
//	case Downto_For_t:
//		NEWQUAD(q);
//		q->op = LST_op;
//		q->r = res;
//		q->s = re;
//		q->d = outlabel;
//		emit(q);
//		anlys_stmt(t->sp);
//		NEWQUAD(q);
//		q->op = DEC_op;
//		q->r = NULL;
//		q->s = NULL;
//		q->d = res;
//		emit(q);
//		NEWQUAD(q);
//		q->op = JMP_op;
//		q->r = NULL;
//		q->s = NULL;
//		q->d = startlabel;
//		emit(q);
//		emit(out);
//		NEWQUAD(q);
//		q->op = INC_op;
//		q->r = NULL;
//		q->s = NULL;
//		q->d = res;
//		emit(q);
//		break;
//	default:
//		fprintf(tiplist, "CODE BUG:161\n");
//		assert(0);
//	}
// }

// void anlys_pcall_stmt(pcall_stmt_node_t *t)
// {
//	syment_t *res;
//	inst_t *q;
//	if (t == NULL)
//		return;
//	res = sym_lookup(t->idp->name);
//	if (res == NULL) {
//		--runlevel;
//		semanticError(NULLSYM, t->idp->line, FALSE, t->idp->name);
//		return;
//	}
//	if (OBJ(Proc_Obj_t)) {
//		anlys_arg_list(t->alp, res);
//		NEWQUAD(q);
//		q->op = CALL_op;
//		q->r = res;
//		q->s = NULL;
//		q->d = NULL;
//		emit(q);
//	} else {
//		--runlevel;
//		semanticError(NOPPROC, t->idp->line, FALSE, t->idp->name);
//	}
// }

// void anlys_read_stmt(read_stmt_node_t *t)
// {
//	syment_t *res;
//	inst_t *q;
//	for (; t != NULL; t = t->next) {
//		res = sym_lookup(t->idp->name);
//		if (res == NULL) {
//			--runlevel;
//			semanticError(NULLSYM, t->idp->line, FALSE,
//				      t->idp->name);
//			continue;
//		}
//		if (res->type == Char_Type_t) {
//			NEWQUAD(q);
//			q->op = READC_op;
//			q->r = NULL;
//			q->s = NULL;
//			q->d = res;
//			emit(q);
//		} else {
//			NEWQUAD(q);
//			q->op = READ_op;
//			q->r = NULL;
//			q->s = NULL;
//			q->d = res;
//			emit(q);
//		}
//	}
// }

// void anlys_write_stmt(write_stmt_node_t *t)
// {
//	inst_t *q;
//	syment_t *res;
//	factor_node_t *f;
//	if (t == NULL)
//		return;
//	switch (t->type) {
//	case Str_Write_t:
//		NEWQUAD(q);
//		q->op = WRS_op;
//		q->r = NULL;
//		q->s = NULL;
//		q->d = sym_make_string(t->sp);
//		emit(q);
//		break;
//	case Id_Write_t:
//		f = NULL;
//		if ((t->ep != NULL) && (t->ep->next == NULL) &&
//		    (t->ep->tp != NULL) && (t->ep->tp->next == NULL) &&
//		    (t->ep->tp->fp != NULL)) {
//			f = t->ep->tp->fp;
//		}
//		if (f != NULL &&
//		    (f->type == Id_Factor_t || f->type == Array_Factor_t)) {
//			res = sym_lookup(f->idp->name);
//			if (res == NULL) {
//				--runlevel;
//				semanticError(NULLSYM, f->idp->line, FALSE,
//					      f->idp->name);
//				break;
//			}
//			if (res->type == Char_Type_t) {
//				NEWQUAD(q);
//				q->op = WRC_op;
//				q->r = NULL;
//				q->s = NULL;
//				q->d = anlys_expr(t->ep);
//				emit(q);
//				break;
//			}
//		}
//		NEWQUAD(q);
//		q->op = WRI_op;
//		q->r = NULL;
//		q->s = NULL;
//		q->d = anlys_expr(t->ep);
//		emit(q);
//		break;
//	case StrId_Write_t:
//		NEWQUAD(q);
//		q->op = WRS_op;
//		q->r = NULL;
//		q->s = NULL;
//		q->d = sym_make_string(t->sp);
//		emit(q);
//		f = NULL;
//		if ((t->ep != NULL) && (t->ep->next == NULL) &&
//		    (t->ep->tp != NULL) && (t->ep->tp->next == NULL) &&
//		    (t->ep->tp->fp != NULL)) {
//			f = t->ep->tp->fp;
//		}
//		if (f != NULL &&
//		    (f->type == Id_Factor_t || f->type == Array_Factor_t)) {
//			res = sym_lookup(f->idp->name);
//			if (res == NULL) {
//				--runlevel;
//				semanticError(NULLSYM, f->idp->line, FALSE,
//					      f->idp->name);
//				break;
//			}
//			if (res->type == Char_Type_t) {
//				NEWQUAD(q);
//				q->op = WRC_op;
//				q->r = NULL;
//				q->s = NULL;
//				q->d = anlys_expr(t->ep);
//				emit(q);
//				break;
//			}
//		}
//		NEWQUAD(q);
//		q->op = WRI_op;
//		q->r = NULL;
//		q->s = NULL;
//		q->d = anlys_expr(t->ep);
//		emit(q);
//		break;
//	default:
//		fprintf(tiplist, "CODE BUG:290\n");
//		assert(0);
//	}
// }

// syment_t *anlys_expr(expr_node_t *t)
// {
//	syment_t *r, d;
//	inst_t *q;
//	if (t == NULL) {
//		fprintf(tiplist, "CODE BUG:14\n");
//		return NULL;
//	}
//	switch (t->op) {
//	case Nop_Addop_t:
//	case Add_Addop_t:
//	case Minus_Addop_t:
//		d = anlys_term(t->tp);
//		break;
//	case Neg_Addop_t:
//		NEWQUAD(q);
//		q->op = NEG_op;
//		q->r = anlys_term(t->tp);
//		q->s = NULL;
//		d = sym_insert_tmp(q->r->type);
//		q->d = d;
//		emit(q);
//		break;
//	default:
//		fprintf(tiplist, "SYMTAB BUG:27\n");
//		assert(0);
//	}
//	for (r = d; t->next != NULL; t = t->next) {
//		switch (t->next->op) {
//		case Add_Addop_t:
//			NEWQUAD(q);
//			q->op = ADD_op;
//			q->r = r;
//			q->s = anlys_term(t->next->tp);
//			if (q->r->type == Char_Type_t &&
//			    q->s->type == Char_Type_t) {
//				d = sym_insert_tmp(Char_Type_t);
//			} else {
//				d = sym_insert_tmp(Int_Type_t);
//			}
//			q->d = d;
//			emit(q);
//			break;
//		case Minus_Addop_t:
//			NEWQUAD(q);
//			q->op = SUB_op;
//			q->r = r;
//			q->s = anlys_term(t->next->tp);
//			if (q->r->type == Char_Type_t &&
//			    q->s->type == Char_Type_t) {
//				d = sym_insert_tmp(Char_Type_t);
//			} else {
//				d = sym_insert_tmp(Int_Type_t);
//			}
//			q->d = d;
//			emit(q);
//			break;
//		default:
//			fprintf(tiplist, "SYMTAB BUG:49\n");
//			assert(0);
//		}
//		r = d;
//	}
//	return d;
// }

// syment_t *anlys_term(term_node_t *t)
// {
//	syment_t *r, d;
//	inst_t *q;
//	if (t == NULL) {
//		fprintf(tiplist, "CODE BUG:54\n");
//		return NULL;
//	}
//	switch (t->op) {
//	case Nop_Multop_t:
//		d = anlys_factor(t->fp);
//		break;
//	default:
//		fprintf(tiplist, "SYMTAB BUG:67\n");
//		assert(0);
//	}
//	for (r = d; t->next != NULL; t = t->next) {
//		switch (t->next->op) {
//		case Mult_Multop_t:
//			NEWQUAD(q);
//			q->op = MUL_op;
//			q->r = r;
//			q->s = anlys_factor(t->next->fp);
//			if (q->r->type == Char_Type_t &&
//			    q->s->type == Char_Type_t) {
//				d = sym_insert_tmp(Char_Type_t);
//			} else {
//				d = sym_insert_tmp(Int_Type_t);
//			}
//			q->d = d;
//			emit(q);
//			break;
//		case Div_Multop_t:
//			NEWQUAD(q);
//			q->op = DIV_op;
//			q->r = r;
//			q->s = anlys_factor(t->next->fp);
//			if (q->r->type == Char_Type_t &&
//			    q->s->type == Char_Type_t) {
//				d = sym_insert_tmp(Char_Type_t);
//			} else {
//				d = sym_insert_tmp(Int_Type_t);
//			}
//			q->d = d;
//			emit(q);
//			break;
//		default:
//			fprintf(tiplist, "SYMTAB BUG:89\n");
//			assert(0);
//		}
//		r = d;
//	}
//	return d;
// }

// syment_t *anlys_factor(factor_node_t *t)
// {
//	syment_t *res, d;
//	inst_t *q;
//	if (t == NULL) {
//		fprintf(tiplist, "CODE BUG:546\n");
//		return NULL;
//	}
//	d = NULL;
//	switch (t->type) {
//	case Id_Factor_t:
//		res = sym_lookup(t->idp->name);
//		if (res == NULL) {
//			--runlevel;
//			semanticError(NULLSYM, t->idp->line, FALSE,
//				      t->idp->name);
//			break;
//		}
//		if (OBJ5(Const_Obj_t, Var_Obj_t, Para_Val_Obj_t, Para_Ref_Obj_t,
//			 Tmp_Obj_t)) {
//			d = res;
//		} else {
//			--runlevel;
//			syntaxError(NOPVAR, t->idp->line, FALSE, t->idp->name);
//		}
//		break;
//	case Array_Factor_t:
//		res = sym_lookup(t->idp->name);
//		if (res == NULL) {
//			--runlevel;
//			semanticError(NULLSYM, t->idp->line, FALSE,
//				      t->idp->name);
//			break;
//		}
//		if (OBJ(Array_Obj_t)) {
//			NEWQUAD(q);
//			q->op = LOAD_op;
//			q->r = res;
//			q->s = anlys_expr(t->ep);
//			d = sym_insert_tmp(q->s->type);
//			q->d = d;
//			emit(q);
//		} else {
//			--runlevel;
//			syntaxError(NOPARRAY, t->idp->line, FALSE,
//				    t->idp->name);
//		}
//		break;
//	case Unsign_Factor_t:
//		d = sym_make_usi(t->usi);
//		break;
//	case Expr_Factor_t:
//		d = anlys_expr(t->ep);
//		break;
//	case Funcall_Factor_t:
//		anlys_d = fcall_stmt(t->fcsp);
//		break;
//	default:
//		fprintf(tiplist, "CODE BUG:129\n");
//		assert(0);
//	}
//	return d;
// }

// symentanlys__t *fcall_stmt(fcall_stmt_node_t *t)
// {
//	syment_t *res, d;
//	inst_t *q;
//	if (t == NULL) {
//		fprintf(tiplist, "CODE BUG:601\n");
//		return NULL;
//	}
//	res = sym_lookup(t->idp->name);
//	if (res == NULL) {
//		--runlevel;
//		semanticError(NULLSYM, t->idp->line, FALSE, t->idp->name);
//		return NULL;
//	}
//	if (OBJ(Fun_Obj_t)) {
//		anlys_arg_list(t->alp, res);
//		NEWQUAD(q);
//		q->op = CALL_op;
//		q->r = res;
//		q->s = NULL;
//		d = sym_insert_tmp(res->type);
//		q->d = d;
//		emit(q);
//	} else {
//		--runlevel;
//		semanticError(NOPFUN, t->idp->line, FALSE, t->idp->name);
//	}
//	return d;
// }

// void anlys_cond(cond_node_t *t, syment_t *label)
// {
//	inst_t *q;
//	if (t == NULL) {
//		fprintf(tiplist, "CODE BUG:629\n");
//		return;
//	}
//	switch (t->op) {
//	case Equ_Rela_t:
//		NEWQUAD(q);
//		q->op = EQU_op;
//		q->r = anlys_expr(t->lep);
//		q->s = anlys_expr(t->rep);
//		q->d = label;
//		emit(q);
//		break;
//	case Neq_Rela_t:
//		NEWQUAD(q);
//		q->op = NEQ_op;
//		q->r = anlys_expr(t->lep);
//		q->s = anlys_expr(t->rep);
//		q->d = label;
//		emit(q);
//		break;
//	case Gtt_Rela_t:
//		NEWQUAD(q);
//		q->op = GTT_op;
//		q->r = anlys_expr(t->lep);
//		q->s = anlys_expr(t->rep);
//		q->d = label;
//		emit(q);
//		break;
//	case Geq_Rela_t:
//		NEWQUAD(q);
//		q->op = GEQ_op;
//		q->r = anlys_expr(t->lep);
//		q->s = anlys_expr(t->rep);
//q->d = label;
//		emit(q);
//		break;
//	case Lst_Rela_t:
//		NEWQUAD(q);
//		q->op = LST_op;
//		q->r = anlys_expr(t->lep);
//		q->s = anlys_expr(t->rep);
//		q->d = label;
//		emit(q);
//		break;
//	case Leq_Rela_t:
//		NEWQUAD(q);
//		q->op = LEQ_op;
//		q->r = anlys_expr(t->lep);
//		q->s = anlys_expr(t->rep);
//		q->d = label;
//		emit(q);
//		break;
//	default:
//		fprintf(tiplist, "CODE BUG:194\n");
//		assert(0);
//	}
// }

// void anlys_arg_list(arg_list_node_t *t, syment_t *pfste)
// {
//	syment_t *d, res;
//	sym_bucket_node_t *b;
//	factor_node_t *f;
//	inst_t *q;
//	int parapos = 1;
//	for (b = pfste->stp->headinfo; t != NULL && b != NULL;
//	     t = t->next, b = b->next, ++parapos) {
//		switch (b->ep->obj) {
//		case Para_Val_Obj_t:
//			d = anlys_expr(t->ep);
//			NEWQUAD(q);
//			q->op = PUSH_op;
//			q->r = NULL;
//			q->s = NULL;
//			if (d != NULL && d->type != b->ep->type) {
//				fprintf(errlist,
//					"warning:%d: type miss match at %dth position while using -> %s\n",
//					pfste->lineno, parapos, pfste->name);
//			}
//			q->d = d;
//			emit(q);
//			break;
//		case Para_Ref_Obj_t:
//			f = NULL;
//			if ((t->ep != NULL) && (t->ep->next == NULL) &&
//			    (t->ep->tp != NULL) && (t->ep->tp->next == NULL) &&
//			    (t->ep->tp->fp != NULL)) {
//				f = t->ep->tp->fp;
//			} else {
//				fprintf(tiplist, "CODE BUG:831\n");
//				assert(0);
//			}
//			switch (f->type) {
//			case Id_Factor_t:
//				res = sym_lookup(f->idp->name);
//				if (res == NULL) {
//					--runlevel;
//					semanticError(NULLSYM, f->idp->line,
//						      FALSE, f->idp->name);
//					break;
//				}
//				if (OBJ3(Var_Obj_t, Para_Val_Obj_t,
//					 Para_Ref_Obj_t)) {
//					d = res;
//				} else {
//					--runlevel;
//					semanticError(ERRREF, f->idp->line,
//						      FALSE, f->idp->name);
//					break;
//				}
//				NEWQUAD(q);
//				q->op = PUSHA_op;
//				q->r = NULL;
//				q->s = NULL;
//				if (d != NULL && d->type != b->ep->type) {
//					fprintf(errlist,
//						"warning:%d: type miss match at %dth position while using -> %s\n",
//						pfste->lineno, parapos,
//						pfste->name);
//				}
//				q->d = d;
//				emit(q);
//				break;
//			case Array_Factor_t:
//				res = sym_lookup(f->idp->name);
//				if (res == NULL) {
//					--runlevel;
//					semanticError(NULLSYM, f->idp->line,
//						      FALSE, f->idp->name);
//					break;
//				}
//				if (OBJ(Array_Obj_t)) {
//					d = res;
//				} else {
//					--runlevel;
//					semanticError(ERRREF, f->idp->line,
//						      FALSE, f->idp->name);
//					break;
//				}
//				NEWQUAD(q);
//				q->op = PUSHA_op;
//				q->r = NULL;
//				q->s = anlys_expr(f->ep);
//				if (d != NULL && d->type != b->ep->type) {
//					fprintf(errlist,
//						"warning:%d: type miss match at %dth position while using -> %s\n",
//						pfste->lineno, parapos,
//						pfste->name);
//				}
//				q->d = d;
//				emit(q);
//				break;
//			default:
//				fprintf(errlist,
//					"semanticError:%d: Uncompact pass by reference type %s\n",
//					pfste->lineno, pfste->name);
//				assert(0);
//			}
//			break;
//		default:
//			fprintf(tiplist, "CODE BUG:833\n");
//			assert(0);
//		}
//	}
//	if ((runlevel > 0) && (b != NULL || t != NULL)) {
//		--runlevel;
//		semanticError(ARGERROR, pfste->lineno, FALSE, pfste->name);
//	}
// }
