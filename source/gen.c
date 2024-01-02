#include "gen.h"
#include "limits.h"
#include "util.h"
#include "debug.h"
#include "parse.h"
#include "syntax.h"
#include "global.h"
#include "symtab.h"
#include "ir.h"

static void gen_pgm(pgm_node_t *node)
{
	block_node_t *b = node->bp;
	gen_pf_dec_list(b->pfdlp);

	// main function
	syment_t *entry = node->entry->symbol;
	emit1(ENT_OP, entry);
	gen_comp_stmt(b->csp);
	emit1(FIN_OP, entry);
}

static void gen_pf_dec_list(pf_dec_list_node_t *node)
{
	pf_dec_list_node_t *t;
	for (t = node; t; t = t->next) {
		switch (t->kind) {
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
	proc_dec_node_t *t;
	for (t = node; t; t = t->next) {
		block_node_t *b = t->pdp->bp;
		gen_pf_dec_list(b->pfdlp);

		emit1(ENT_OP, t->pdp->php->idp->symbol);
		gen_comp_stmt(b->csp);
		emit1(FIN_OP, t->pdp->php->idp->symbol);
	}
}

static void gen_fun_decf(fun_dec_node_t *node)
{
	fun_dec_node_t *t;
	for (t = node; t; t = t->next) {
		block_node_t *b = t->fdp->bp;

		gen_pf_dec_list(b->pfdlp);
		emit1(ENT_OP, t->fdp->fhp->idp->symbol);
		gen_comp_stmt(b->csp);
		emit1(FIN_OP, t->fdp->fhp->idp->symbol);
	}
}

static void gen_comp_stmt(comp_stmt_node_t *node)
{
	comp_stmt_node_t *t;
	for (t = node; t; t = t->next) {
		gen_stmt(t->sp);
	}
}

static void gen_stmt(stmt_node_t *node)
{
	switch (node->kind) {
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
	syment_t *r, *s, *d;
	d = node->idp->symbol;
	switch (node->kind) {
	case NORM_ASSGIN:
		r = gen_expr(node->rep);
		emit2(ASS_OP, d, r);
		break;
	case FUN_ASSGIN:
		r = gen_expr(node->rep);
		emit2(ASS_OP, d, r);
		break;
	case ARRAY_ASSGIN:
		s = gen_expr(node->lep);
		r = gen_expr(node->rep);
		emit3(ASA_OP, d, r, s);
		break;
	default:
		unlikely();
	}
}

static void gen_if_stmt(if_stmt_node_t *node)
{
	syment_t *ifthen, *ifdone;
	ifthen = symalloc(node->stab, "@ifthen", LABEL_OBJ, VOID_TYPE);
	ifdone = symalloc(node->stab, "@ifdone", LABEL_OBJ, VOID_TYPE);

	gen_cond(node->cp, ifthen);
	if (node->ep) {
		gen_stmt(node->ep);
	}
	emit1(JMP_OP, ifdone);
	emit1(LAB_OP, ifthen);
	gen_stmt(node->tp);
	emit1(LAB_OP, ifdone);
}

static void gen_repe_stmt(repe_stmt_node_t *node)
{
	syment_t *loopstart, *loopdone;
	loopstart = symalloc(node->stab, "@loopstart", LABEL_OBJ, VOID_TYPE);
	loopdone = symalloc(node->stab, "@loopdone", LABEL_OBJ, VOID_TYPE);

	emit1(LAB_OP, loopstart);
	gen_stmt(node->sp);
	gen_cond(node->cp, loopdone);
	emit1(JMP_OP, loopstart);
	emit1(LAB_OP, loopdone);
}

static void gen_for_stmt(for_stmt_node_t *node)
{
	syment_t *beg, *end;
	beg = gen_expr(node->lep);
	end = gen_expr(node->rep);

	syment_t *forstart, *fordone;
	forstart = symalloc(node->stab, "@forstart", LABEL_OBJ, VOID_TYPE);
	fordone = symalloc(node->stab, "@fordone", LABEL_OBJ, VOID_TYPE);

	syment_t *d;
	d = node->idp->symbol;
	emit2(ASS_OP, d, beg);
	emit1(LAB_OP, forstart);
	switch (node->kind) {
	case TO_FOR:
		emit3(GTT_OP, fordone, d, end);
		gen_stmt(node->sp);
		emit1(INC_OP, d);
		emit1(JMP_OP, forstart);
		emit1(LAB_OP, fordone);
		emit1(DEC_OP, d);
		break;
	case DOWNTO_FOR:
		emit3(LST_OP, fordone, d, end);
		gen_stmt(node->sp);
		emit1(DEC_OP, d);
		emit1(JMP_OP, forstart);
		emit1(LAB_OP, fordone);
		emit1(INC_OP, d);
		break;
	default:
		unlikely();
	}
}

static void gen_pcall_stmt(pcall_stmt_node_t *node)
{
	gen_arg_list(node->alp);
	emit2(CALL_OP, NULL, node->idp->symbol);
	arg_list_node_t *t;
	for (t = node->alp; t; t = t->next) {
		emit1(POP_OP, NULL);
	}
}

static void gen_read_stmt(read_stmt_node_t *node)
{
	read_stmt_node_t *t;
	syment_t *d = NULL;
	for (t = node; t; t = t->next) {
		d = t->idp->symbol;
		switch (d->type) {
		case CHAR_TYPE:
			emit1(RDC_OP, d);
			break;
		case INT_TYPE:
			emit1(RDI_OP, d);
			break;
		}
	}
}

static void gen_write_stmt(write_stmt_node_t *node)
{
	syment_t *d = NULL;
	switch (node->type) {
	case STR_WRITE:
		d = symalloc(node->stab, "@write/str", STR_OBJ, STR_TYPE);
		strcopy(d->str, node->sp);
		emit1(WRS_OP, d);
		break;
	case ID_WRITE:
		d = gen_expr(node->ep);
		switch (d->type) {
		case CHAR_TYPE:
			emit1(WRC_OP, d);
			break;
		case INT_TYPE:
			emit1(WRI_OP, d);
			break;
		default:
			unlikely();
		}
		break;
	case STRID_WRITE:
		d = symalloc(node->stab, "@write/str", STR_OBJ, STR_TYPE);
		strcopy(d->str, node->sp);
		emit1(WRS_OP, d);
		d = gen_expr(node->ep);
		switch (d->type) {
		case CHAR_TYPE:
			emit1(WRC_OP, d);
			break;
		case INT_TYPE:
			emit1(WRI_OP, d);
			break;
		default:
			unlikely();
		}
		break;
	default:
		unlikely();
	}
}

static syment_t *gen_expr(expr_node_t *node)
{
	expr_node_t *t;
	syment_t *d, *r, *e;
	d = r = e = NULL;
	for (t = node; t; t = t->next) {
		r = gen_term(t->tp);
		if (!d) {
			switch (t->kind) {
			case NEG_ADDOP:
				d = symalloc(node->stab, "@expr/neg", TMP_OBJ,
					     r->type);
				emit2(NEG_OP, d, r);
				break;
			case NOP_ADDOP:
				d = r;
				break;
			default:
				unlikely();
			}
			continue;
		}
		switch (t->kind) {
		case NOP_ADDOP:
		case ADD_ADDOP:
			e = d;
			d = symalloc(node->stab, "@expr/add", TMP_OBJ, e->type);
			emit3(ADD_OP, d, e, r);
			break;
		case MINUS_ADDOP:
		case NEG_ADDOP:
			e = d;
			d = symalloc(node->stab, "@expr/sub", TMP_OBJ, e->type);
			emit3(SUB_OP, d, e, r);
			break;
		default:
			unlikely();
		}
	}
	return d;
}

static syment_t *gen_term(term_node_t *node)
{
	term_node_t *t;
	syment_t *d, *r, *e;
	d = r = e = NULL;
	for (t = node; t; t = t->next) {
		r = gen_factor(t->fp);
		if (!d) {
			if (t->kind != NOP_MULTOP) {
				unlikely();
			}
			d = r;
			continue;
		}
		switch (t->kind) {
		case NOP_MULTOP:
		case MULT_MULTOP:
			e = d;
			d = symalloc(node->stab, "@term/mul", TMP_OBJ, e->type);
			emit3(MUL_OP, d, e, r);
			break;
		case DIV_MULTOP:
			e = d;
			d = symalloc(node->stab, "@term/div", TMP_OBJ, e->type);
			emit3(DIV_OP, d, e, r);
			break;
		default:
			unlikely();
		}
	}
	return d;
}

static syment_t *gen_factor(factor_node_t *node)
{
	syment_t *d, *r, *e;
	d = r = e = NULL;
	switch (node->kind) {
	case ID_FACTOR:
		d = node->idp->symbol;
		break;
	case ARRAY_FACTOR:
		r = node->idp->symbol;
		e = gen_expr(node->ep);
		d = symalloc(node->stab, "@factor/array", TMP_OBJ, r->type);
		emit3(LOAD_OP, d, r, e);
		break;
	case UNSIGN_FACTOR:
		d = symalloc(node->stab, "@factor/usi", NUM_OBJ, INT_TYPE);
		d->initval = node->value;
		break;
	case CHAR_FACTOR:
		d = symalloc(node->stab, "@factor/char", NUM_OBJ, CHAR_TYPE);
		d->initval = node->value;
		break;
	case EXPR_FACTOR:
		d = gen_expr(node->ep);
		break;
	case FUNCALL_FACTOR:
		d = gen_fcall_stmt(node->fcsp);
		break;
	default:
		unlikely();
	}
	return d;
}

static syment_t *gen_fcall_stmt(fcall_stmt_node_t *node)
{
	syment_t *d, *e;
	e = node->idp->symbol;
	d = symalloc(node->stab, "@fcall/ret", TMP_OBJ, e->type);
	gen_arg_list(node->alp);
	emit2(CALL_OP, d, e);
	arg_list_node_t *t;
	for (t = node->alp; t; t = t->next) {
		emit1(POP_OP, NULL);
	}
	return d;
}

static void gen_cond(cond_node_t *node, syment_t *label)
{
	syment_t *r, *s;
	r = gen_expr(node->lep);
	s = gen_expr(node->rep);
	switch (node->kind) {
	case EQU_RELA:
		emit3(EQU_OP, label, r, s);
		break;
	case NEQ_RELA:
		emit3(NEQ_OP, label, r, s);
		break;
	case GTT_RELA:
		emit3(GTT_OP, label, r, s);
		break;
	case GEQ_RELA:
		emit3(GEQ_OP, label, r, s);
		break;
	case LST_RELA:
		emit3(LST_OP, label, r, s);
		break;
	case LEQ_RELA:
		emit3(LEQ_OP, label, r, s);
		break;
	}
}

static void gen_arg_list(arg_list_node_t *node)
{
	if (!node) {
		return;
	}
	arg_list_node_t *t = node;

	// Push arguments in reverse order
	gen_arg_list(t->next);

	syment_t *d = NULL, *r = NULL;
	switch (t->refsym->cate) {
	case BYVAL_OBJ:
		d = gen_expr(t->ep);
		emit1(PUSH_OP, d);
		break;
	case BYREF_OBJ:
		d = t->argsym;
		switch (t->argsym->cate) {
		case VAR_OBJ:
			emit2(PADR_OP, d, NULL);
			break;
		case ARRAY_OBJ:
			r = gen_expr(t->idx);
			emit2(PADR_OP, d, r);
			break;
		default:
			unlikely();
		}
		break;
	default:
		unlikely();
	}
}

void genir()
{
	gen_pgm(pgm);
	chkerr("generate fail and exit.");
	phase = CODE_GEN;
}
