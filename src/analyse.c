/**
 * File: analyse.c
 * Date: Nov 12, 2013
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

static void PgmV(PgmSP t);
static void BlockV(BlockSP t);
static void ConstDecV(ConstDecSP t);
static void ConstDefV(ConstDefSP t);
static void VarDecV(VarDecSP t);
static void VarDefV(VarDefSP t);
static void PFDecListV(PFDecListSP t);
static void ProcDecV(ProcDecSP t);
static void ProcDefV(ProcDefSP t);
static void ProcHeadV(ProcHeadSP t);
static void FunDecV(FunDecSP t);
static void FunDefV(FunDefSP t);
static void FunHeadV(FunHeadSP t);
static void StmtV(StmtSP t);
static void AssignStmtV(AssignStmtSP t);
static void IfStmtV(IfStmtSP t);
static void RepeStmtV(RepeStmtSP t);
static void ForStmtV(ForStmtSP t);
static void PcallStmtV(PcallStmtSP t);
static void FcallStmtV(FcallStmtSP t);
static void CompStmtV(CompStmtSP t);
static void ReadStmtV(ReadStmtSP t);
static void WriteStmtV(WriteStmtSP t);
static void ExprV(ExprSP t);
static void TermV(TermSP t);
static void FactorV(FactorSP t);
static void CondV(CondSP t);
static void IdentV(IdentSP t);
static void ParaListV(ParaListSP t);
static void ParaDefV(ParaDefSP t);
static void ArgListV(ArgListSP t);

void PgmV(PgmSP t)
{
	headPr("Pgm");
	if (t != NULL) {
		BlockV(t->bp);
	}
	tailPr("Pgm");
}

void BlockV(BlockSP t)
{
	headPr("Block");
	if (t != NULL) {
		ConstDecV(t->cdp);
		VarDecV(t->vdp);
		PFDecListV(t->pfdlp);
		CompStmtV(t->csp);
	}
	tailPr("Block");
}

void ConstDecV(ConstDecSP t)
{
	headPr("ConstDec");
	for (; t != NULL; t = t->next) {
		ConstDefV(t->cdp);
	}
	tailPr("ConstDec");
}

void ConstDefV(ConstDefSP t)
{
	headPr("ConstDef");
	if (t != NULL) {
		IdentV(t->idp);
	}
	tailPr("ConstDef");
}

void VarDecV(VarDecSP t)
{
	headPr("VarDec");
	for (; t != NULL; t = t->next) {
		VarDefV(t->vdp);
	}
	tailPr("VarDec");
}

void VarDefV(VarDefSP t)
{
	headPr("VarDef");
	for (; t != NULL; t = t->next) {
		IdentV(t->idp);
	}
	tailPr("VarDef");
}

void PFDecListV(PFDecListSP t)
{
	headPr("PFDecList");
	for (; t != NULL; t = t->next) {
		switch (t->type) {
		case Proc_PFDec_t:			
			ProcDecV(t->pdp);
			break;
		case Fun_PFDec_t:
			FunDecV(t->fdp);
			break;
		default:
			fprintf(errlist, "ANALYSER BUG:104\n");
		}
	}
	tailPr("PFDecList");
}

void ProcDecV(ProcDecSP t)
{
	headPr("ProcDec");
	for (; t != NULL; t = t->next) {
		ProcDefV(t->pdp);
	}
	tailPr("ProcDec");
}

void ProcDefV(ProcDefSP t)
{
	headPr("ProcDef");
	if (t != NULL) {
		ProcHeadV(t->php);
		BlockV(t->bp);
	}
	tailPr("ProcDef");
}

void ProcHeadV(ProcHeadSP t)
{
	headPr("ProcHead");
	if (t != NULL) {
		IdentV(t->idp);
		ParaListV(t->plp);
	}
	tailPr("ProcHead");
}

void FunDecV(FunDecSP t)
{
	headPr("FunDec");
	for (; t != NULL; t = t->next) {
		FunDefV(t->fdp);
	}
	tailPr("FunDec");
}

void FunDefV(FunDefSP t)
{
	headPr("FunDef");
	if (t != NULL) {
		FunHeadV(t->fhp);
		BlockV(t->bp);
	}
	tailPr("FunDef");
}

void FunHeadV(FunHeadSP t)
{
	headPr("FunHead");
	if (t != NULL) {
		IdentV(t->idp);
		ParaListV(t->plp);
	}
	tailPr("FunHead");
}

void StmtV(StmtSP t)
{
	headPr("Stmt");
	if (t != NULL) {
		switch (t->type) {
		case Assgin_Stmt_t:
			AssignStmtV(t->asp);
			break;
		case IF_Stmt_t:
			IfStmtV(t->ifp);
			break;
		case Repeat_Stmt_t:
			RepeStmtV(t->rpp);
			break;
		case For_Stmt_t:
			ForStmtV(t->frp);
			break;
		case Pcall_Stmt_t:
			PcallStmtV(t->pcp);
			break;
		case Comp_Stmt_t:
			CompStmtV(t->cpp);
			break;
		case Read_Stmt_t:
			ReadStmtV(t->rdp);
			break;
		case Write_Stmt_t:
			WriteStmtV(t->wtp);
			break;
		case Null_Stmt_t:
			innerIdnlnPr(1,"Null_Stmt_t");
			break;
		default:
			fprintf(errlist, "ANALYSER BUG:192\n");
		}
	}
	tailPr("Stmt");
}

void AssignStmtV(AssignStmtSP t)
{
	headPr("AssignStmt");
	if (t != NULL) {
		switch (t->type) {
		case Norm_Assgin_t:
			innerIdnlnPr(2,"type=","Norm_Assgin_t");
			break;
		case Fun_Assgin_t:
			innerIdnlnPr(2,"type=","Fun_Assgin_t");
			break;
		case Array_Assgin_t:
			innerIdnlnPr(2,"type=","Array_Assgin_t");
			break;
		default:
			fprintf(errlist, "ANALYSER BUG:210\n");
		}
		IdentV(t->idp);
		innerIdnlnPr(1,"**left");
		ExprV(t->lep);
		innerIdnlnPr(1,"**right");
		ExprV(t->rep);
	}
	tailPr("AssignStmt");
}

void IfStmtV(IfStmtSP t)
{
	headPr("IfStmt");
	if (t != NULL) {
		CondV(t->cp);
		innerIdnlnPr(1,"**then");
		StmtV(t->tp);
		if (t->ep != NULL) {
			innerIdnlnPr(1,"**elsep");
			StmtV(t->ep);
		}
	}
	tailPr("IfStmt");
}

void RepeStmtV(RepeStmtSP t)
{
	headPr("RepeStmt");
	if (t != NULL) {
		innerIdnlnPr(1,"**repeat");
		StmtV(t->sp);
		innerIdnlnPr(1,"**until");
		CondV(t->cp);
	}
	tailPr("RepeStmt");
}

void ForStmtV(ForStmtSP t)
{
	headPr("ForStmt");
	if (t != NULL) {
		IdentV(t->idp);
		switch (t->type) {
		case To_For_t:
			innerIdnlnPr(2,"type=","To_For_t");
			break;
		case Downto_For_t:
			innerIdnlnPr(2,"type=","Downto_For_t");
			break;
		default:
			fprintf(errlist, "ANALYSER BUG:283\n");
		}
		innerIdnlnPr(1,"**start");
		ExprV(t->lep);
		innerIdnlnPr(1,"**end");
		ExprV(t->rep);
		innerIdnlnPr(1,"**do");
		StmtV(t->sp);
	}
	tailPr("ForStmt");
}

void PcallStmtV(PcallStmtSP t)
{
	headPr("PcallStmt");
	if (t != NULL) {
		IdentV(t->idp);
		ArgListV(t->alp);
	}
	tailPr("PcallStmt");
}

void FcallStmtV(FcallStmtSP t)
{
	headPr("FcallStmt");
	if (t != NULL) {
		IdentV(t->idp);
		ArgListV(t->alp);
	}
	tailPr("FcallStmt");
}

void CompStmtV(CompStmtSP t)
{
	headPr("CompStmt");
	for (; t != NULL; t = t->next) {
		StmtV(t->sp);
	}
	tailPr("CompStmt");
}

void ReadStmtV(ReadStmtSP t)
{
	headPr("ReadStmt");
	for (; t != NULL; t = t->next) {
		IdentV(t->idp);
	}
	tailPr("ReadStmt");
}

void WriteStmtV(WriteStmtSP t)
{
	headPr("WriteStmt");
	if (t != NULL) {
		switch (t->type) {
		case Id_Write_t:
			innerIdnlnPr(2,"type=","Id_Write_t");
			ExprV(t->ep);
			break;
		case Str_Write_t:
			innerIdnlnPr(2,"type=","Str_Write_t");
			innerIdnPr(1,"string=");
			innerlnPr(1,t->sp);
			break;
		case StrId_Write_t:
			innerIdnlnPr(2,"type=","StrId_Write_tid");
			innerIdnPr(1,"string=");
			innerlnPr(1,t->sp);
			ExprV(t->ep);
			break;
		default:
			fprintf(errlist, "ANALYSER BUG:353\n");
		}
	}
	tailPr("WriteStmt");
}

void ExprV(ExprSP t)
{
	headPr("Expr");
	for (; t != NULL; t = t->next) {
		switch (t->op) {
		case Nop_Addop_t:
			innerIdnlnPr(2,"op=","Nop_Addop_t");
			break;
		case Add_Addop_t:
			innerIdnlnPr(2,"op=","Add_Addop_t");
			break;
		case Neg_Addop_t:
			innerIdnlnPr(2,"op=","Neg_Addop_t");
			break;
		case Minus_Addop_t:
			innerIdnlnPr(2,"op=","Minus_Addop_t");
			break;
		default:
			fprintf(errlist, "ANALYSER BUG:369\n");
		}
		TermV(t->tp);
	}
	tailPr("Expr");
}

void TermV(TermSP t)
{
	headPr("Term");
	for (; t != NULL; t = t->next) {
		switch (t->op) {
		case Nop_Multop_t:
			innerIdnlnPr(2,"op=","Nop_Multop_t");
			break;
		case Mult_Multop_t:
			innerIdnlnPr(2,"op=","Mult_Multop_t");
			break;
		case Div_Multop_t:
			innerIdnlnPr(2,"op=","Div_Multop_t");
			break;
		default:
			fprintf(errlist, "ANALYSER BUG:391\n");
		}
		FactorV(t->fp);
	}
	tailPr("Term");
}

void FactorV(FactorSP t)
{
	headPr("Factor");
	if (t != NULL) {
		switch (t->type) {
		case Id_Factor_t:
			innerIdnlnPr(2,"type=","Id_Factor_t");
			IdentV(t->idp);
			break;
		case Array_Factor_t:
			innerIdnlnPr(2,"type=","Array_Factor_t");
			IdentV(t->idp);
			ExprV(t->ep);
			break;
		case Unsign_Factor_t:
			innerIdnlnPr(2,"type=","Unsign_Factor_t");
			innerIdnPr(1,"usi=");
			innerIntPr(t->usi);
			break;
		case Expr_Factor_t:
			innerIdnlnPr(2,"type=","Expr_Factor_t");
			ExprV(t->ep);
			break;
		case Funcall_Factor_t:
			innerIdnlnPr(2,"type=","Funcall_Factor_t");
			FcallStmtV(t->fcsp);
			break;
		default:
			fprintf(errlist, "ANALYSER BUG:430\n");
		}
	}
	tailPr("Factor");
}

void CondV(CondSP t)
{
	headPr("Cond");
	if (t != NULL) {
		switch (t->op) {
		case Equ_Rela_t:
			innerIdnlnPr(2,"op=","Equ_Rela_t");
			break;
		case Neq_Rela_t:
			innerIdnlnPr(2,"op=","Neq_Rela_t");
			break;
		case Gtt_Rela_t:
			innerIdnlnPr(2,"op=","Gtt_Rela_t");
			break;
		case Geq_Rela_t:
			innerIdnlnPr(2,"op=","Geq_Rela_t");
			break;
		case Lst_Rela_t:
			innerIdnlnPr(2,"op=","Lst_Rela_t");
			break;
		case Leq_Rela_t :
			innerIdnlnPr(2,"op=","Leq_Rela_t ");
			break;
		default:
			fprintf(errlist, "ANALYSER BUG:534\n");
		}
		innerIdnlnPr(1,"**left");
		ExprV(t->lep);
		innerIdnlnPr(1,"**right");
		ExprV(t->rep);
	}
	tailPr("Cond");
}

void IdentV(IdentSP t)
{
	headPr("Ident");
	if (t != NULL) {
		switch (t->type) {
		case Init_Ident_t:
			innerIdnlnPr(2,"type=","Init_Ident_t");
			innerIdnPr(1,"name=");
			innerlnPr(1,t->name);
			innerIdnPr(1,"val=");
			innerIntPr(t->val);
			innerIdnPr(1,"length=");
			innerIntPr(t->length);
			innerIdnPr(1,"line=");
			innerIntPr(t->line);
			break;
		case Proc_Ident_t:
			innerIdnlnPr(2,"type=","Proc_Ident_t");
			innerIdnPr(1,"name=");
			innerlnPr(1,t->name);
			innerIdnPr(1,"line=");
			innerIntPr(t->line);
			break;
		case Int_Fun_Ident_t:
			innerIdnlnPr(2,"type=","Int_Fun_Ident_t");
			innerIdnPr(1,"name=");
			innerlnPr(1,t->name);
			innerIdnPr(1,"line=");
			innerIntPr(t->line);
			break;
		case Char_Fun_Ident_t:
			innerIdnlnPr(2,"type=","Char_Fun_Ident_t");
			innerIdnPr(1,"name=");
			innerlnPr(1,t->name);
			innerIdnPr(1,"line=");
			innerIntPr(t->line);
			break;
		case Int_Const_Ident_t:
			innerIdnlnPr(2,"type=","Int_Const_Ident_t");
			innerIdnPr(1,"name=");
			innerlnPr(1,t->name);
			innerIdnPr(1,"val=");
			innerIntPr(t->val);
			innerIdnPr(1,"line=");
			innerIntPr(t->line);
			break;
		case Char_Const_Ident_t:
			innerIdnlnPr(2,"type=","Char_Const_Ident_t");
			innerIdnPr(1,"name=");
			innerlnPr(1,t->name);
			innerIdnPr(1,"val=");
			innerCharPr( (char) t->val);
			innerIdnPr(1,"line=");
			innerIntPr(t->line);
			break;
		case Int_Var_Ident_t:
			innerIdnlnPr(2,"type=","Int_Var_Ident_t");
			innerIdnPr(1,"name=");
			innerlnPr(1,t->name);
			innerIdnPr(1,"line=");
			innerIntPr(t->line);
			break;
		case Char_Var_Ident_t:
			innerIdnlnPr(2,"type=","Char_Var_Ident_t");
			innerIdnPr(1,"name=");
			innerlnPr(1,t->name);
			innerIdnPr(1,"line=");
			innerIntPr(t->line);
			break;
		case IntArr_Var_Ident_t:
			innerIdnlnPr(2,"type=","IntArr_Var_Ident_t");
			innerIdnPr(1,"name=");
			innerlnPr(1,t->name);
			innerIdnPr(1,"length=");
			innerIntPr(t->length);
			innerIdnPr(1,"line=");
			innerIntPr(t->line);
			break;
		case CharArr_Var_Ident_t:
			innerIdnlnPr(2,"type=","CharArr_Var_Ident_t");
			innerIdnPr(1,"name=");
			innerlnPr(1,t->name);
			innerIdnPr(1,"length=");
			innerIntPr(t->length);
			innerIdnPr(1,"line=");
			innerIntPr(t->line);
			break;
		case Int_Para_Val_Ident_t:
			innerIdnlnPr(2,"type=","Int_Para_Val_Ident_t");
			innerIdnPr(1,"name=");
			innerlnPr(1,t->name);
			innerIdnPr(1,"line=");
			innerIntPr(t->line);
			break;
		case Char_Para_Val_Ident_t:
			innerIdnlnPr(2,"type=","Char_Para_Val_Ident_t");
			innerIdnPr(1,"name=");
			innerlnPr(1,t->name);
			innerIdnPr(1,"line=");
			innerIntPr(t->line);
			break;
		case Int_Para_Ref_Ident_t:
			innerIdnlnPr(2,"type=","Int_Para_Ref_Ident_t");
			innerIdnPr(1,"name=");
			innerlnPr(1,t->name);
			innerIdnPr(1,"line=");
			innerIntPr(t->line);
			break;
		case Char_Para_Ref_Ident_t:
			innerIdnlnPr(2,"type=","Char_Para_Ref_Ident_t");
			innerIdnPr(1,"name=");
			innerlnPr(1,t->name);
			innerIdnPr(1,"line=");
			innerIntPr(t->line);
			break;
		default:
			fprintf(errlist, "ANALYSER BUG:503\n");
		}
	}
	tailPr("Ident");
}

void ParaListV(ParaListSP t)
{
	headPr("ParaList");
	for (; t != NULL; t = t->next) {
		ParaDefV(t->pdp);
	}
	tailPr("ParaList");
}

void ParaDefV(ParaDefSP t)
{
	headPr("ParaDef");
	for (; t != NULL; t = t->next) {
		IdentV(t->idp);
	}
	tailPr("ParaDef");
}

void ArgListV(ArgListSP t)
{
	headPr("ArgList");
	for (; t != NULL; t = t->next) {
		ExprV(t->ep);
	}
	tailPr("ArgList");
}

void analyse(PgmSP t)
{
	/*
	 *if (ShowAST)
	 *        fprintf(listing, "\nBegin AST ...\n");
	 */
	if (t != NULL)
		PgmV(t);
}
