/**
 * File: code.c
 * Date: Nov 19, 2013
 * Author: Jeanhwea
 */
#include "global.h"
#include "util.h"
#include "error.h"
#include "parse.h"
#include "symtab.h"
#include "analyse.h"
#include "nspace.h"
#include "quad.h"
#include "code.h"

static void PgmG(PgmSP t);
static void ConstDecfG(ConstDecSP t);
static void VarDecfG(VarDecSP t);
static void PFDecListG(PFDecListSP t);
static void ProcDecfG(ProcDecSP t);
static SymTabESP ProcHeadG(ProcHeadSP t);
static void FunDecfG(FunDecSP t);
static SymTabESP FunHeadG(FunHeadSP t);
static void StmtG(StmtSP t);
static void AssignStmtG(AssignStmtSP t);
static void IfStmtG(IfStmtSP t);
static void RepeStmtG(RepeStmtSP t);
static void ForStmtG(ForStmtSP t);
static void PcallStmtG(PcallStmtSP t);
static void ReadStmtG(ReadStmtSP t);
static void WriteStmtG(WriteStmtSP t);
static void CompStmtG(CompStmtSP t);
static SymTabESP ExprG(ExprSP t);
static SymTabESP TermG(TermSP t);
static SymTabESP FactorG(FactorSP t);
static SymTabESP FcallStmtG(FcallStmtSP t);
static void CondG(CondSP t, SymTabESP label);
static void ParaListG(ParaListSP t);
static void ArgListG(ArgListSP t, SymBucketSP info);

void PgmG(PgmSP t)
{
	SymTabSP st;
	QuadSP q;
	BlockSP b;
	if (t == NULL) {
		fprintf(tiplist, "CODE BUG:47\n");
		exit(1);
	}
	Ninit();
	st = newstab();
	push(st);
	b = t->bp;
	if (b == NULL) {
		fprintf(tiplist, "CODE BUG:52\n");
		exit(1);
	}
	ConstDecfG(b->cdp);
	VarDecfG(b->vdp);
	PFDecListG(b->pfdlp);
	NEWQUAD(q);
	q->op = ENTER_op;
	q->r = NULL;
	q->s = NULL;
	q->d = sym_make_main();
	emit(q);
	CompStmtG(b->csp);
	NEWQUAD(q);
	q->op = FIN_op;
	q->r = NULL;
	q->s = NULL;
	q->d = NULL;
	emit(q);
	st = pop();
	printTab(st);
	Npop();
	if (runlevel > 0)
		printAllQuad();
}

void ConstDecfG(ConstDecSP t)
{
	for (; t != NULL; t = t->next) {
		if (t->cdp != NULL && t->cdp->idp != NULL) {
			sym_insert_const(t->cdp->idp);
		} else {
			fprintf(tiplist, "CODE BUG:70\n");
			exit(1);
		}
	}
}

void VarDecfG(VarDecSP t)
{
	VarDefSP p;
	for (; t != NULL; t = t->next) {
		for (p = t->vdp; p != NULL; p = p->next) {
			if (p != NULL && p->idp != NULL) {
				sym_insert_var(p->idp);
			} else {
				fprintf(tiplist, "CODE BUG:81\n");
				exit(1);
			}
		}
	}
}

void PFDecListG(PFDecListSP t)
{
	for (; t != NULL; t = t->next) {
		switch (t->type) {
		case Proc_PFDec_t:			
			ProcDecfG(t->pdp);
			break;
		case Fun_PFDec_t:
			FunDecfG(t->fdp);
			break;
		default:
			fprintf(tiplist, "CODE BUG:104\n");
			exit(1);
		}
	}
}

void ProcDecfG(ProcDecSP t)
{
	QuadSP q;
	SymTabSP st;
	SymTabESP e;
	BlockSP b;
	for (; t != NULL; t = t->next) {
		if (t->pdp == NULL) {
			fprintf(tiplist, "CODE BUG:112\n");
			continue;
		}
		e = ProcHeadG(t->pdp->php);
		b = t->pdp->bp;
		if (b == NULL) {
			fprintf(tiplist, "CODE BUG:120\n");
			continue;
		}
		ConstDecfG(b->cdp);
		VarDecfG(b->vdp);
		PFDecListG(b->pfdlp);
		NEWQUAD(q);
		q->op = ENTER_op;
		q->r = NULL;
		q->s = NULL;
		q->d = e;
		emit(q);
		CompStmtG(b->csp);
		NEWQUAD(q);
		q->op = FIN_op;
		q->r = NULL;
		q->s = NULL;
		q->d = NULL;
		emit(q);
		st = pop();
		printTab(st);
		Npop();
	}
}

SymTabESP ProcHeadG(ProcHeadSP t)
{
	SymTabSP st;
	SymTabESP e;
	if (t == NULL) return NULL;
	e = sym_insert_proc(t->idp, t->plp);
	if (e == NULL) {
		return NULL;
	}
	st = newstab();
	if (runlevel > 0)
		e->stp = st;
	push(st);
	ParaListG(t->plp);
	return e;
}

void FunDecfG(FunDecSP t)
{
	QuadSP q;
	SymTabSP st;
	SymTabESP e;
	BlockSP b;
	for (; t != NULL; t = t->next) {
		if (t->fdp == NULL) {
			fprintf(tiplist, "CODE BUG:168\n");
			continue;
		}
		e = FunHeadG(t->fdp->fhp);
		b = t->fdp->bp;
		if (b == NULL) {
			fprintf(tiplist, "CODE BUG:174\n");
			continue;
		}
		ConstDecfG(b->cdp);
		VarDecfG(b->vdp);
		PFDecListG(b->pfdlp);
		NEWQUAD(q);
		q->op = ENTER_op;
		q->r = NULL;
		q->s = NULL;
		q->d = e;
		emit(q);
		CompStmtG(b->csp);
		NEWQUAD(q);
		q->op = FIN_op;
		q->r = NULL;
		q->s = NULL;
		q->d = NULL;
		emit(q);
		st = pop();
		printTab(st);
		Npop();
	}
}

SymTabESP FunHeadG(FunHeadSP t)
{
	SymTabSP st;
	SymTabESP e;
	if (t == NULL) {
		return NULL;
	}
	e = sym_insert_fun(t->idp, t->plp);
	if (e == NULL) {
		return NULL;
	}
	st = newstab();
	if (runlevel > 0)
		e->stp = st;
	push(st);
	ParaListG(t->plp);
	return e;
}

void StmtG(StmtSP t)
{
	if (t == NULL) {
		return;
	}
	switch (t->type) {
	case Assgin_Stmt_t:
		AssignStmtG(t->asp);
		break;
	case IF_Stmt_t:
		IfStmtG(t->ifp);
		break;
	case Repeat_Stmt_t:
		RepeStmtG(t->rpp);
		break;
	case For_Stmt_t:
		ForStmtG(t->frp);
		break;
	case Pcall_Stmt_t:
		PcallStmtG(t->pcp);
		break;
	case Comp_Stmt_t:
		CompStmtG(t->cpp);
		break;
	case Read_Stmt_t:
		ReadStmtG(t->rdp);
		break;
	case Write_Stmt_t:
		WriteStmtG(t->wtp);
		break;
	case Null_Stmt_t:
		break;
	default:
		fprintf(tiplist, "CODE BUG:43\n");
		exit(1);
	}
}

void AssignStmtG(AssignStmtSP t)
{
	SymTabESP res;
	QuadSP q;
	if (t == NULL) return ;
	switch (t->type) {
	case Norm_Assgin_t:
	case Fun_Assgin_t:
		res = sym_lookup(t->idp->name);
		if (res == NULL) {
			--runlevel;
			semanticError(NULLSYM, t->idp->line, FALSE, t->idp->name);
			break;
		}
		if (OBJ(Fun_Obj_t)) {
			NEWQUAD(q);
			q->op = SRET_op;
			q->r = ExprG(t->rep);
			q->s = NULL;
			q->d = res;
			emit(q);
		} else if (OBJ3(Var_Obj_t,Para_Val_Obj_t,
			Para_Ref_Obj_t)) {
			NEWQUAD(q);
			q->op = ASS_op;
			q->r = ExprG(t->rep);
			q->s = NULL;
			q->d = res;
			emit(q);
		} else{
			--runlevel;
			semanticError(NOPVAR, t->idp->line, FALSE, t->idp->name);
		}
		break;
	case Array_Assgin_t:
		res = sym_lookup(t->idp->name);
		if (res == NULL) {
			--runlevel;
			semanticError(NULLSYM, t->idp->line, FALSE, t->idp->name);
			break;
		}
		if (OBJ(Array_Obj_t)) {
			NEWQUAD(q);
			q->op = AARR_op;
			q->r = ExprG(t->rep);
			q->s = ExprG(t->lep);
			q->d = res;
			emit(q);
		} else {
			--runlevel;
			semanticError(NOPARRAY, t->idp->line, FALSE, t->idp->name);
		}
		break;
	default:
		fprintf(tiplist, "CODE BUG:84\n");
		exit(1);
	}
}

void IfStmtG(IfStmtSP t)
{
	QuadSP q, start, out;
	SymTabESP startlabel, outlabel;
	if (t == NULL) return ;
	startlabel = sym_make_label();
	NEWQUAD(start);
	start->op = LABEL_op;
	start->r = NULL;
	start->s = NULL;
	start->d = startlabel;
	outlabel = sym_make_label();
	NEWQUAD(out);
	out->op = LABEL_op;
	out->r = NULL;
	out->s = NULL;
	out->d = outlabel;
	CondG(t->cp, startlabel);
	if (t->ep != NULL) {
		StmtG(t->ep);
	}
	NEWQUAD(q);
	q->op = JMP_op;
	q->r = NULL;
	q->s = NULL;
	q->d = outlabel;
	emit(q);
	emit(start);
	StmtG(t->tp);
	emit(out);
}

void RepeStmtG(RepeStmtSP t)
{
	QuadSP q, loop, out;
	SymTabESP looplabel, outlabel;
	if (t == NULL) return ;
	looplabel = sym_make_label();
	NEWQUAD(loop);
	loop->op = LABEL_op;
	loop->r = NULL;
	loop->s = NULL;
	loop->d = looplabel;
	outlabel = sym_make_label();
	NEWQUAD(out);
	out->op = LABEL_op;
	out->r = NULL;
	out->s = NULL;
	out->d = outlabel;
	emit(loop);
	StmtG(t->sp);
	CondG(t->cp, outlabel);
	NEWQUAD(q);
	q->op = JMP_op;
	q->r = NULL;
	q->s = NULL;
	q->d = looplabel;
	emit(q);
	emit(out);
}

void ForStmtG(ForStmtSP t)
{
	QuadSP q, start, out;
	SymTabESP res, le, re, startlabel, outlabel;
	if (t == NULL) return ;
	startlabel = sym_make_label();
	NEWQUAD(start);
	start->op = LABEL_op;
	start->r = NULL;
	start->s = NULL;
	start->d = startlabel;
	outlabel = sym_make_label();
	NEWQUAD(out);
	out->op = LABEL_op;
	out->r = NULL;
	out->s = NULL;
	out->d = outlabel;
	le = ExprG(t->lep);
	re = ExprG(t->rep);
	res = sym_lookup(t->idp->name);
	if (res == NULL) {
		--runlevel;
		semanticError(NULLSYM, t->idp->line, FALSE, t->idp->name);
		return;
	}
	NEWQUAD(q);
	q->op = ASS_op;
	q->r = le;
	q->s = NULL;
	q->d = res;
	emit(q);
	emit(start);
	switch (t->type) {
	case To_For_t:
		NEWQUAD(q);
		q->op = GTT_op;
		q->r = res;
		q->s = re;
		q->d = outlabel;
		emit(q);
		StmtG(t->sp);
		NEWQUAD(q);
		q->op = INC_op;
		q->r = NULL;
		q->s = NULL;
		q->d = res;
		emit(q);
		break;
	case Downto_For_t:
		NEWQUAD(q);
		q->op = LST_op;
		q->r = res;
		q->s = re;
		q->d = outlabel;
		emit(q);
		StmtG(t->sp);
		NEWQUAD(q);
		q->op = DEC_op;
		q->r = NULL;
		q->s = NULL;
		q->d = res;
		emit(q);
		break;
	default:
		fprintf(tiplist, "CODE BUG:161\n");
		exit(1);
	}
	NEWQUAD(q);
	q->op = JMP_op;
	q->r = NULL;
	q->s = NULL;
	q->d = startlabel;
	emit(q);
	emit(out);
}

void PcallStmtG(PcallStmtSP t)
{
	SymTabESP res;
	QuadSP q;
	if (t == NULL) return ;
	res = sym_lookup(t->idp->name);
	if (res == NULL) {
		--runlevel;
		semanticError(NULLSYM, t->idp->line, FALSE, t->idp->name);
		return;
	}
	if (OBJ(Proc_Obj_t)) {
		ArgListG(t->alp, res->stp->headinfo);
		NEWQUAD(q);
		q->op = CALL_op;
		q->r = res;
		q->s = NULL;
		q->d = NULL;
		emit(q);
	} else {
		--runlevel;
		semanticError(NOPPROC, t->idp->line, FALSE, t->idp->name);
	}
}

void ReadStmtG(ReadStmtSP t)
{
	SymTabESP res;
	QuadSP q;
	for (; t != NULL; t = t->next) {
		res = sym_lookup(t->idp->name);
		if (res == NULL) {
			--runlevel;
			semanticError(NULLSYM, t->idp->line, FALSE, t->idp->name);
			continue;
		}
		if (res->type == Char_Type_t) {
			NEWQUAD(q);
			q->op = READC_op;
			q->r = NULL;
			q->s = NULL;
			q->d = res;
			emit(q);
		} else {
			NEWQUAD(q);
			q->op = READ_op;
			q->r = NULL;
			q->s = NULL;
			q->d = res;
			emit(q);
		}
	}
}

void WriteStmtG(WriteStmtSP t)
{
	QuadSP q;
	SymTabESP res;
	FactorSP f;
	if (t == NULL) return ;
	switch (t->type) {
	case Str_Write_t:
		NEWQUAD(q);
		q->op = WRS_op;
		q->r = NULL;
		q->s = NULL;
		q->d = sym_make_string(t->sp);
		emit(q);
		break;
	case Id_Write_t:
		f = NULL;
		if ((t->ep != NULL) && (t->ep->next == NULL) &&
		    (t->ep->tp != NULL) && (t->ep->tp->next == NULL)
			&& (t->ep->tp->fp !=NULL)) {
			f = t->ep->tp->fp;
		}
		if (f != NULL && (f->type == Id_Factor_t ||
			f->type == Array_Factor_t)) {
			res = sym_lookup(f->idp->name);
			if (res == NULL) {
				--runlevel;
				semanticError(NULLSYM, f->idp->line,
						FALSE, f->idp->name);
				break;
			}
			if (res->type == Char_Type_t) {
				NEWQUAD(q);
				q->op = WRC_op;
				q->r = NULL;
				q->s = NULL;
				q->d = ExprG(t->ep);
				emit(q);
				break;
			} 
		}
		NEWQUAD(q);
		q->op = WRI_op;
		q->r = NULL;
		q->s = NULL;
		q->d = ExprG(t->ep);
		emit(q);
		break;
	case StrId_Write_t:
		NEWQUAD(q);
		q->op = WRS_op;
		q->r = NULL;
		q->s = NULL;
		q->d = sym_make_string(t->sp);
		emit(q);
		f = NULL;
		if ((t->ep != NULL) && (t->ep->next == NULL) &&
		    (t->ep->tp != NULL) && (t->ep->tp->next == NULL)
			&& (t->ep->tp->fp !=NULL)) {
			f = t->ep->tp->fp;
		}
		if (f != NULL && (f->type == Id_Factor_t ||
			f->type == Array_Factor_t)) {
			res = sym_lookup(f->idp->name);
			if (res == NULL) {
				--runlevel;
				semanticError(NULLSYM, f->idp->line,
						FALSE, f->idp->name);
				break;
			}
			if (res->type == Char_Type_t) {
				NEWQUAD(q);
				q->op = WRC_op;
				q->r = NULL;
				q->s = NULL;
				q->d = ExprG(t->ep);
				emit(q);
				break;
			} 
		}
		NEWQUAD(q);
		q->op = WRI_op;
		q->r = NULL;
		q->s = NULL;
		q->d = ExprG(t->ep);
		emit(q);
		break;
	default:
		fprintf(tiplist, "CODE BUG:290\n");
		exit(1);
	}
}

void CompStmtG(CompStmtSP t)
{
	for (; t != NULL; t = t->next) {
		StmtG(t->sp);
	}
}

SymTabESP ExprG(ExprSP t)
{
	SymTabESP r, d;
	QuadSP q;
	if (t == NULL) {
		fprintf(tiplist, "CODE BUG:14\n");
		return NULL;
	}
	switch (t->op) {
	case Nop_Addop_t:
	case Add_Addop_t:
	case Minus_Addop_t:
		d = TermG(t->tp);
		break;
	case Neg_Addop_t:
		d = sym_insert_tmp();
		NEWQUAD(q);
		q->op = NEG_op;
		q->r = TermG(t->tp);
		q->s = NULL;
		q->d = d;
		emit(q);
		break;
	default:
		fprintf(tiplist, "SYMTAB BUG:27\n");
		exit(1);
	}
	for (r = d; t->next != NULL; t = t->next) {
		switch (t->next->op) {
		case Add_Addop_t:
			d = sym_insert_tmp();
			NEWQUAD(q);
			q->op = ADD_op;
			q->r = r;
			q->s = TermG(t->next->tp);
			q->d = d;
			emit(q);
			break;
		case Minus_Addop_t:
			d = sym_insert_tmp();
			NEWQUAD(q);
			q->op = SUB_op;
			q->r = r;
			q->s = TermG(t->next->tp);
			q->d = d;
			emit(q);
			break;
		default:
			fprintf(tiplist, "SYMTAB BUG:49\n");
			exit(1);
		}
		r = d;
	}
	return d;
}

SymTabESP TermG(TermSP t)
{
	SymTabESP r, d;
	QuadSP q;
	if (t == NULL) {
		fprintf(tiplist, "CODE BUG:54\n");
		return NULL;
	}
	switch (t->op) {
	case Nop_Multop_t:
		d = FactorG(t->fp);
		break;
	default:
		fprintf(tiplist, "SYMTAB BUG:67\n");
		exit(1);
	}
	for (r = d; t->next != NULL; t = t->next) {
		switch (t->next->op) {
		case Mult_Multop_t:
			d = sym_insert_tmp();
			NEWQUAD(q);
			q->op = MUL_op;
			q->r = r;
			q->s = FactorG(t->next->fp);
			q->d = d;
			emit(q);
			break;
		case Div_Multop_t:
			d = sym_insert_tmp();
			NEWQUAD(q);
			q->op = DIV_op;
			q->r = r;
			q->s = FactorG(t->next->fp);
			q->d = d;
			emit(q);
			break;
		default:
			fprintf(tiplist, "SYMTAB BUG:89\n");
			exit(1);
		}
		r = d;
	}
	return d;
}

SymTabESP FactorG(FactorSP t)
{
	SymTabESP res, d;
	QuadSP q;
	if (t == NULL) {
		fprintf(tiplist, "CODE BUG:546\n");
		return NULL;
	}
	d = NULL;
	switch (t->type) {
	case Id_Factor_t:
		res = sym_lookup(t->idp->name);
		if (res == NULL) {
			--runlevel;
			semanticError(NULLSYM, t->idp->line, FALSE, t->idp->name);
			break;
		}
		if (OBJ5(Const_Obj_t,Var_Obj_t,
			Para_Val_Obj_t, Para_Ref_Obj_t,Tmp_Obj_t)) {
			d = res;
		} else {
			--runlevel;
			syntaxError(NOPVAR, t->idp->line, FALSE, t->idp->name);
		}
		break;
	case Array_Factor_t:
		res = sym_lookup(t->idp->name);
		if (res == NULL) {
			--runlevel;
			semanticError(NULLSYM, t->idp->line, FALSE, t->idp->name);
			break;
		}
		if (OBJ(Array_Obj_t)) {
			d = sym_insert_tmp();
			NEWQUAD(q);
			q->op = LOAD_op;
			q->r = res;
			q->s = ExprG(t->ep);
			q->d = d;
			emit(q);
		} else {
			--runlevel;
			syntaxError(NOPARRAY, t->idp->line, FALSE, t->idp->name);
		}
		break;
	case Unsign_Factor_t:
		d = sym_make_usi(t->usi);
		break;
	case Expr_Factor_t:
		d = ExprG(t->ep);
		break;
	case Funcall_Factor_t:
		d = FcallStmtG(t->fcsp);
		break;
	default:
		fprintf(tiplist, "CODE BUG:129\n");
		exit(1);
	}
	return d;
}

SymTabESP FcallStmtG(FcallStmtSP t)
{
	SymTabESP res, d;
	QuadSP q;
	if (t == NULL) {
		fprintf(tiplist, "CODE BUG:601\n");
		return NULL;
	}
	res = sym_lookup(t->idp->name);
	if (res == NULL) {
		--runlevel;
		semanticError(NULLSYM, t->idp->line, FALSE, t->idp->name);
		return NULL;
	}
	if (OBJ(Fun_Obj_t)) {
		ArgListG(t->alp, res->stp->headinfo);
		d = sym_insert_tmp();
		NEWQUAD(q);
		q->op = CALL_op;
		q->r = res;
		q->s = NULL;
		q->d = d;
		emit(q);
	} else {
		--runlevel;
		semanticError(NOPFUN, t->idp->line, FALSE, t->idp->name);
	}
	return d;
}

void CondG(CondSP t, SymTabESP label)
{
	QuadSP q;
	if (t == NULL) {
		fprintf(tiplist, "CODE BUG:629\n");
		return ;
	}
	switch (t->op) {
	case Equ_Rela_t:
		NEWQUAD(q);
		q->op = EQU_op;
		q->r = ExprG(t->lep);
		q->s = ExprG(t->rep);
		q->d = label;
		emit(q);
		break;
	case Neq_Rela_t:
		NEWQUAD(q);
		q->op = NEQ_op;
		q->r = ExprG(t->lep);
		q->s = ExprG(t->rep);
		q->d = label;
		emit(q);
		break;
	case Gtt_Rela_t:
		NEWQUAD(q);
		q->op = GTT_op;
		q->r = ExprG(t->lep);
		q->s = ExprG(t->rep);
		q->d = label;
		emit(q);
		break;
	case Geq_Rela_t:
		NEWQUAD(q);
		q->op = GEQ_op;
		q->r = ExprG(t->lep);
		q->s = ExprG(t->rep);
		q->d = label;
		emit(q);
		break;
	case Lst_Rela_t:
		NEWQUAD(q);
		q->op = LST_op;
		q->r = ExprG(t->lep);
		q->s = ExprG(t->rep);
		q->d = label;
		emit(q);
		break;
	case Leq_Rela_t:
		NEWQUAD(q);
		q->op = LEQ_op;
		q->r = ExprG(t->lep);
		q->s = ExprG(t->rep);
		q->d = label;
		emit(q);
		break;
	default:
		fprintf(tiplist, "CODE BUG:194\n");
		exit(1);
	}
}

void ParaListG(ParaListSP t)
{
	ParaDefSP p;
	for (; t != NULL; t = t->next) {
		for (p = t->pdp; p != NULL; p = p->next) {
			if (p != NULL) {
				sym_insert_para(p->idp);
			} else {
				fprintf(tiplist, "CODE BUG:682\n");
				exit(1);
			}
		}
	}
}

void ArgListG(ArgListSP t, SymBucketSP info)
{
	SymTabESP d, res;
	SymBucketSP b;
	FactorSP f;
	QuadSP q;
	for (b = info; t != NULL && b != NULL; t = t->next, b = b->next) {
		switch (b->ep->obj) {
		case Para_Val_Obj_t:
			d = ExprG(t->ep);
			NEWQUAD(q);
			q->op = PUSH_op;
			q->r = NULL;
			q->s = NULL;
			q->d = d;
			emit(q);
			break;
		case Para_Ref_Obj_t:
			f = NULL;
			if ((t->ep != NULL) && (t->ep->next == NULL) &&
			    (t->ep->tp != NULL) && (t->ep->tp->next == NULL)
				&& (t->ep->tp->fp !=NULL)) {
				f = t->ep->tp->fp;
			} else {
				fprintf(tiplist, "CODE BUG:831\n");
				exit(1);
			}
			switch (f->type) {
			case Id_Factor_t:
				res = sym_lookup(f->idp->name);
				if (res == NULL) {
					--runlevel;
					semanticError(NULLSYM, f->idp->line, 
						FALSE, f->idp->name);
					break;
				}
				if (OBJ3(Var_Obj_t, Para_Val_Obj_t,
					Para_Ref_Obj_t)) {
					d = res;
				} else {
					--runlevel;
					semanticError(ERRREF, f->idp->line,
						FALSE, f->idp->name);
					break;
				}
				NEWQUAD(q);
				q->op = PUSHA_op;
				q->r = NULL;
				q->s = NULL;
				q->d = d;
				emit(q);
				break;
			case Array_Factor_t:
				res = sym_lookup(f->idp->name);
				if (res == NULL) {
					--runlevel;
					semanticError(NULLSYM, f->idp->line, 
						FALSE, f->idp->name);
					break;
				}
				if (OBJ(Array_Obj_t)) {
					d = res;
				} else {
					--runlevel;
					semanticError(ERRREF, f->idp->line,
						FALSE, f->idp->name);
					break;
				}
				NEWQUAD(q);
				q->op = PUSHA_op;
				q->r = NULL;
				q->s = ExprG(f->ep);
				q->d = d;
				emit(q);
				break;
			default:
				fprintf(tiplist, "CODE BUG:880\n");
				exit(1);
			}
			break;
		default:
			fprintf(tiplist, "CODE BUG:833\n");
			exit(1);
		}
	}
	if (b != NULL || t != NULL) {
		--runlevel;
		semanticError(ARGERROR, -1, FALSE, NULL);
	}
}

void coder(PgmSP t)
{
	--runlevel;
	if (t != NULL)
		PgmG(t);
}
