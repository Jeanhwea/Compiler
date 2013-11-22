/**
 * File: code.c
 * Date: Nov 19, 2013
 * Author: Jeanhwea
 */
#include "global.h"
#include "parse.h"
#include "symtab.h"
#include "quad.h"
#include "code.h"

void StmtG(StmtSP t);
void AssignStmtG(AssignStmtSP t);
void IfStmtG(IfStmtSP t);
void RepeStmtG(RepeStmtSP t);
void ForStmtG(ForStmtSP t);
void PcallStmtG(PcallStmtSP t);
void ReadStmtG(ReadStmtSP t);
void WriteStmtG(WriteStmtSP t);
void CompStmtG(CompStmtSP t);
SymTabESP ExprG(ExprSP t);
SymTabESP TermG(TermSP t);
SymTabESP FactorG(FactorSP t);
SymTabESP FcallStmtG(FcallStmtSP t);
SymTabESP CondG(CondSP t);

void StmtG(StmtSP t)
{
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
		fprintf(errlist, "CODE BUG:43\n");
	}
}

void AssignStmtG(AssignStmtSP t)
{
	SymTabESP res;
	QuadSP q;
	switch (t->type) {
	case Norm_Assgin_t:
	case Fun_Assgin_t:
		res = sym_lookup(t->idp->name);
		if (res == NULL) {
			fprintf(errlist, "SYMNOFOUND:57\n");
			abort();
		}
		if (OBJ(Fun_Obj_t)) {
			NEWQUAD(q);
			q->op = SRET_op;
			q->r = NULL;
			q->s = ExprG(t->rep);
			q->d = NULL;
			emit(q);
		} else if (OBJ3(Var_Obj_t,Para_Val_Obj_t,Para_Ref_Obj_t)) {
			NEWQUAD(q);
			q->op = ASS_op;
			q->r = ExprG(t->rep);
			q->s = NULL;
			q->d = res;
			emit(q);
		} else{
			fprintf(errlist, "CODE BUG:70\n");
		}
		break;
	case Array_Assgin_t:
		res = sym_lookup(t->idp->name);
		if (OBJ(Array_Obj_t)) {
			NEWQUAD(q);
			q->op = AARR_op;
			q->r = ExprG(t->lep);
			q->s = ExprG(t->rep);
			q->d = res;
			emit(q);
		} else {
			fprintf(errlist, "CODE BUG:76\n");
		}
		break;
	default:
		fprintf(errlist, "CODE BUG:84\n");
	}
}
void IfStmtG(IfStmtSP t)
{
	QuadSP q, el, out;
	NEWQUAD(el);
	el->op = LABEL_op;
	el->r = NULL;
	el->s = NULL;
	el->d = sym_make_label();
	NEWQUAD(out);
	out->op = LABEL_op;
	out->r = NULL;
	out->s = NULL;
	out->d = sym_make_label();
	NEWQUAD(q);
	q->op = BRZ_op;
	q->r = CondG(t->cp);
	q->s = NULL;
	q->d = el->d;
	emit(q);
	StmtG(t->tp);
	NEWQUAD(q);
	q->op = JMP_op;
	q->r = NULL;
	q->s = NULL;
	q->d = out->d;
	emit(q);
	emit(el);
	if (t->ep != NULL) {
		StmtG(t->ep);
	}
	emit(out);
}

void RepeStmtG(RepeStmtSP t)
{
	QuadSP q, loop;
	NEWQUAD(loop);
	loop->op = LABEL_op;
	loop->r = NULL;
	loop->s = NULL;
	loop->d = sym_make_label();
	emit(loop);
	StmtG(t->sp);
	NEWQUAD(q);
	q->op = BNZ_op;
	q->r = CondG(t->cp);
	q->s = NULL;
	q->d = loop->d;
	emit(q);
}

void ForStmtG(ForStmtSP t)
{
	QuadSP q, start, out;
	SymTabESP res, le, re;
	NEWQUAD(start);
	start->op = LABEL_op;
	start->r = NULL;
	start->s = NULL;
	start->d = sym_make_label();
	NEWQUAD(out);
	out->op = LABEL_op;
	out->r = NULL;
	out->s = NULL;
	out->d = sym_make_label();
	le = ExprG(t->lep);
	re = ExprG(t->rep);
	res = sym_lookup(t->idp->name);
	if (res == NULL) {
		fprintf(errlist, "undifined symbol\n");
		abort();
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
		q->op = BGT_op;
		q->r = res;
		q->s = re;
		q->d = out->d;
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
		q->op = BLT_op;
		q->r = res;
		q->s = re;
		q->d = out->d;
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
		fprintf(errlist, "CODE BUG:161\n");
	}
	NEWQUAD(q);
	q->op = JMP_op;
	q->r = NULL;
	q->s = NULL;
	q->d = start->d;
	emit(q);
	emit(out);
}

void PcallStmtG(PcallStmtSP t)
{
}

void ReadStmtG(ReadStmtSP t)
{
	SymTabESP res;
	QuadSP q;
	for (; t != NULL; t = t->next) {
		res = sym_lookup(t->idp->name);
		if (res == NULL) {
			fprintf(errlist, "undifined symbol\n");
			abort();
		}
		NEWQUAD(q);
		q->op = READ_op;
		q->r = NULL;
		q->s = NULL;
		q->d = res;
		emit(q);
	}
}

void WriteStmtG(WriteStmtSP t)
{
	QuadSP q;
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
		NEWQUAD(q);
		q->op = WRI_op;
		q->r = NULL;
		q->s = NULL;
		q->d = ExprG(t->ep);
		emit(q);
		break;
	default:
		fprintf(errlist, "CODE BUG:290\n");
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
		fprintf(errlist, "CODE BUG:14\n");
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
		fprintf(errlist, "SYMTAB BUG:27\n");
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
			fprintf(errlist, "SYMTAB BUG:49\n");
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
		fprintf(errlist, "CODE BUG:54\n");
		return NULL;
	}
	switch (t->op) {
	case Nop_Multop_t:
		d = FactorG(t->fp);
		break;
	default:
		fprintf(errlist, "SYMTAB BUG:67\n");
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
			fprintf(errlist, "SYMTAB BUG:89\n");
		}
		r = d;
	}
	return d;
}

SymTabESP FactorG(FactorSP t)
{
	SymTabESP res, d;
	QuadSP q;
	d = NULL;
	switch (t->type) {
	case Id_Factor_t:
		res = sym_lookup(t->idp->name);
		if (res == NULL) {
			fprintf(errlist, "SYMNOFOUND:138\n");
			abort();
		}
		if (OBJ5(Const_Obj_t,Var_Obj_t,Para_Val_Obj_t,Para_Ref_Obj_t,Tmp_Obj_t)) {
			d = res;
		} else {
			fprintf(errlist, "undifined variable\n");
		}
		break;
	case Array_Factor_t:
		res = sym_lookup(t->idp->name);
		if (res == NULL) {
			fprintf(errlist, "SYMNOFOUND:138\n");
			abort();
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
			fprintf(errlist, "undifined array\n");
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
		fprintf(errlist, "CODE BUG:129\n");
	}
	return d;
}

SymTabESP FcallStmtG(FcallStmtSP t)
{
	SymTabESP res, d;
	QuadSP q;
	res = sym_lookup(t->idp->name);
	if (res == NULL) {
		fprintf(errlist, "SYMNOFOUND:138\n");
		abort();
	}
	if (OBJ(Fun_Obj_t)) {
		d = sym_insert_tmp();
		NEWQUAD(q);
		q->op = CALL_op;
		q->r = res;
		q->s = NULL;
		q->d = d;
		emit(q);
	} else {
		fprintf(errlist, "undifined function\n");
	}
	return d;
}

SymTabESP CondG(CondSP t)
{
	SymTabESP d;
	QuadSP q;
	d = NULL;
	switch (t->op) {
	case Equ_Rela_t:
		d = sym_insert_tmp();
		NEWQUAD(q);
		q->op = EQU_op;
		q->r = ExprG(t->lep);
		q->s = ExprG(t->rep);
		q->d = d;
		emit(q);
		break;
	case Neq_Rela_t:
		d = sym_insert_tmp();
		NEWQUAD(q);
		q->op = NEQ_op;
		q->r = ExprG(t->lep);
		q->s = ExprG(t->rep);
		q->d = d;
		emit(q);
		break;
	case Gtt_Rela_t:
		d = sym_insert_tmp();
		NEWQUAD(q);
		q->op = GTT_op;
		q->r = ExprG(t->lep);
		q->s = ExprG(t->rep);
		q->d = d;
		emit(q);
		break;
	case Geq_Rela_t:
		d = sym_insert_tmp();
		NEWQUAD(q);
		q->op = GEQ_op;
		q->r = ExprG(t->lep);
		q->s = ExprG(t->rep);
		q->d = d;
		emit(q);
		break;
	case Lst_Rela_t:
		d = sym_insert_tmp();
		NEWQUAD(q);
		q->op = LST_op;
		q->r = ExprG(t->lep);
		q->s = ExprG(t->rep);
		q->d = d;
		emit(q);
		break;
	case Leq_Rela_t:
		d = sym_insert_tmp();
		NEWQUAD(q);
		q->op = LEQ_op;
		q->r = ExprG(t->lep);
		q->s = ExprG(t->rep);
		q->d = d;
		emit(q);
		break;
	default:
		fprintf(errlist, "CODE BUG:194\n");
	}
	return d;
}
