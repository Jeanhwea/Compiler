/**
 * File: analyse.c
 * Date: Nov 12, 2013
 * Author: Jeanhwea
 */

#include "global.h"
#include "analyse.h"
#include "parse.h"
#include "util.h"
#include "scan.h"
#include "error.h"

static void PgmV(PgmSP);
static void BlokV(BlokSP);
static void ConstDecV(ConstDecSP);
static void ConstDefV(ConstDefSP);
static void VarDecV(VarDecSP);
static void VarDefV(VarDefSP);
static void PFDecListV(PFDecListSP);
static void ProcDecV(ProcDecSP);
static void ProcV(ProcSP);
static void ProcHeadV(ProcHeadSP);
static void FunDecV(FunDecSP);
static void FunV(FunSP);
static void FunHeadV(FunHeadSP);
static void StmtV(StmtSP);
static void AssignstmtV(AssignstmtSP);
static void IfstmtV(IfstmtSP);
static void RepestmtV(RepestmtSP);
static void ForstmtV(ForstmtSP);
static void PcallstmtV(PcallstmtSP);
static void FcallstmtV(FcallstmtSP);
static void CompstmtV(CompstmtSP);
static void ReadstmtV(ReadstmtSP);
static void WritestmtV(WritestmtSP);
static void ExprV(ExprSP);
static void TermV(TermSP);
static void FactorV(FactorSP);
static void ConstV(ConstSP);
static void VarV(VarSP);
static void IdentV(IdentSP);
static void CondV(CondSP);
static void ParalistV(ParalistSP);
static void ParaV(ParaSP);
static void ArglistV(ArglistSP);

void PgmV(PgmSP t)
{
	printHead("Pgm");
	BlokV(t->blockp);
	printTail("Pgm");
}
void BlokV(BlokSP t)
{
	printHead("Blok");
	ConstDecV(t->constdecp);
	VarDecV(t->vardecp);
	PFDecListV(t->pflistp);
	CompstmtV(t->compstmtp);
	printTail("Blok");
}
void ConstDecV(ConstDecSP t)
{
	printHead("ConstDec");
	for (; t != NULL; t = t->next) {
		ConstDefV(t->constdefp);
	}
	printTail("ConstDec");
}
void ConstDefV(ConstDefSP t)
{
	printHead("ConstDef");
	IdentV(t->identp);
	ConstV(t->constp);
	printTail("ConstDef");
}
void VarDecV(VarDecSP t)
{
	printHead("VarDec");
	for (; t != NULL; t = t->next) {
		VarDefV(t->vardefp);
	}
	printTail("VarDec");
}
void VarDefV(VarDefSP t)
{
	printHead("VarDef");
	for (; t != NULL; t = t->next) {
		VarV(t->varp);
	}
	printTail("VarDef");
}
void PFDecListV(PFDecListSP t)
{
	printHead("PFDecList");
	for (; t != NULL; t = t->next) {
		switch (t->type) {
		case Proc_PFDec_t:			
			ProcDecV(t->pdecp);
			break;
		case Fun_PFDec_t:
			FunDecV(t->fdecp);
			break;
		default:
			fprintf(errlist, "BUG:104\n");
		}
	}
	printTail("PFDecList");
}
void ProcDecV(ProcDecSP t)
{
	printHead("ProcDec");
	for (; t != NULL; t = t->next) {
		ProcV(t->procp);
	}
	printTail("ProcDec");
}
void ProcV(ProcSP t)
{
	printHead("Proc");
	ProcHeadV(t->procheadp);
	BlokV(t->blockp);
	printTail("Proc");
}
void ProcHeadV(ProcHeadSP t)
{
	printHead("ProcHead");
	IdentV(t->identp);
	ParalistV(t->paralistp);
	printTail("ProcHead");
}
void FunDecV(FunDecSP t)
{
	printHead("FunDec");
	for (; t != NULL; t = t->next) {
		FunV(t->funp);
	}
	printTail("FunDec");
}
void FunV(FunSP t)
{
	printHead("Fun");
	FunHeadV(t->funheadp);
	BlokV(t->blockp);
	printTail("Fun");
}
void FunHeadV(FunHeadSP t)
{
	printHead("FunHead");
	IdentV(t->identp);
	ParalistV(t->paralistp);
	switch (t->rettype) {
	case Int_Funret_t:
		printInner(2,"rettype=","Int_Funret_t");
		break;
	case Char_Funret_t:
		printInner(2,"rettype=","Char_Funret_t");
		break;
	default:
		fprintf(errlist, "BUG:159\n");
	}
	printTail("FunHead");
}
void StmtV(StmtSP t)
{
	printHead("Stmt");
	switch (t->type) {
	case Assgin_Statement_t:
		AssignstmtV(t->assignp);
		break;
	case IF_Statement_t:
		IfstmtV(t->ifp);
		break;
	case Repeat_Statement_t:
		RepestmtV(t->repep);
		break;
	case For_Statement_t:
		ForstmtV(t->forp);
		break;
	case Pcall_Statement_t:
		PcallstmtV(t->pcallp);
		break;
	case Comp_Statement_t:
		CompstmtV(t->compp);
		break;
	case Read_Statement_t:
		ReadstmtV(t->readp);
		break;
	case Write_Statement_t:
		WritestmtV(t->writep);
		break;
	case Null_Statement_t:
		printInner(1,"Null_Statement_t");
		break;
	default:
		fprintf(errlist, "BUG:192\n");
	}
	printTail("Stmt");
}
void AssignstmtV(AssignstmtSP t)
{
	printHead("Assignstmt");
	switch (t->type) {
	case Norm_Assgin_t:
		printInner(2,"assigntype=","Norm_Assgin_t");
		break;
	case Fun_Assgin_t:
		printInner(2,"assigntype=","Fun_Assgin_t");
		break;
	case Array_Assgin_t:
		printInner(2,"assigntype=","Array_Assgin_t");
		break;
	default:
		fprintf(errlist, "BUG:210\n");
	}
	IdentV(t->idp);
	ExprV(t->lexprp);
	ExprV(t->rexprp);
	printTail("Assignstmt");
}
void IfstmtV(IfstmtSP t)
{
	printHead("Ifstmt");
	CondV(t->condp);
	printInner(1,"thenp");
	StmtV(t->thenp);
	if (t->elsep != NULL) {
		printInner(1,"elsep");
		StmtV(t->elsep);
	}
	printTail("Ifstmt");
}
void RepestmtV(RepestmtSP t)
{
	printHead("Repestmt");
	printInner(1,"stmtp");
	StmtV(t->stmtp);
	printInner(1,"condp");
	CondV(t->condp);
	printTail("Repestmt");
}
void ForstmtV(ForstmtSP t)
{
	printHead("Forstmt");
	switch (t->type) {
	case To_For_t:
		printInner(2,"type=","To_For_t");
		break;
	case Downto_For_t:
		printInner(2,"type=","Downto_For_t");
		break;
	default:
		fprintf(errlist, "BUG:283\n");
	}
	printInner(1,"identp");
	IdentV(t->identp);
	printInner(1,"lowp");
	ExprV(t->lowp);
	printInner(1,"highp");
	ExprV(t->highp);
	printInner(1,"stmtp");
	StmtV(t->stmtp);
	printTail("Forstmt");
}
void PcallstmtV(PcallstmtSP t)
{
	printHead("Pcallstmt");
	IdentV(t->identp);
	ArglistV(t->arglistp);
	printTail("Pcallstmt");
}
void FcallstmtV(FcallstmtSP t)
{
	printHead("Fcallstmt");
	IdentV(t->identp);
	ArglistV(t->arglistp);
	printTail("Fcallstmt");
}
void CompstmtV(CompstmtSP t)
{
	printHead("Compstmt");
	for (; t != NULL; t = t->next) {
		StmtV(t->curr);
	}
	printTail("Compstmt");
}
void ReadstmtV(ReadstmtSP t)
{
	printHead("Readstmt");
	for (; t != NULL; t = t->next) {
		IdentV(t->identp);
	}
	printTail("Readstmt");
}
void WritestmtV(WritestmtSP t)
{
	printHead("Writestmt");
	switch (t->type) {
	case Id_Write_t:
		printInner(2,"type","Id_Write_t");
		printInner(1,"exprp");
		ExprV(t->exprp);
		break;
	case Str_Write_t:
		printInner(2,"type","Str_Write_t");
		printInner(1,"stringp");
		printInner(1,t->stringp);
		break;
	case StrId_Write_t:
		printInner(2,"type","StrId_Write_tid");
		printInner(1,"exprp");
		ExprV(t->exprp);
		printInner(1,"stringp");
		printInner(1,t->stringp);
		break;
	default:
		fprintf(errlist, "BUG:353\n");
	}
	printTail("Writestmt");
}
void ExprV(ExprSP t)
{
	printHead("Expr");
	for (; t != NULL; t = t->next) {
		switch (t->op) {
		case Add_Addop_t:
			printInner(2,"type=","Add_Addop_t");
			break;
		case Minus_Addop_t:
			printInner(2,"type=","Minus_Addop_t");
			break;
		default:
			fprintf(errlist, "BUG:369\n");
		}
		TermV(t->termp);
	}
	printTail("Expr");
}
void TermV(TermSP t)
{
	printHead("Term");
	for (; t != NULL; t = t->next) {
		switch (t->op) {
		case Nop_Multop_t:
			printInner(2,"op=","Nop_Multop_t");
			break;
		case Mult_Multop_t:
			printInner(2,"op=","Mult_Multop_t");
			break;
		case Div_Multop_t:
			printInner(2,"op=","Div_Multop_t");
			break;
		default:
			fprintf(errlist, "BUG:391\n");
		}
		FactorV(t->factorp);
	}
	printTail("Term");
}
void FactorV(FactorSP t)
{
	printHead("Factor");
	switch (t->type) {
	case Id_Factor_t:
		printInner(2,"type=","Id_Factor_t");
		printInner(1,"identp");
		IdentV(t->identp);
		break;
	case Array_Factor_t:
		printInner(2,"type=","Array_Factor_t");
		printInner(1,"identp");
		IdentV(t->identp);
		printInner(1,"exprp");
		ExprV(t->exprp);
		break;
	case Unsign_Factor_t:
		printInner(2,"type=","Unsign_Factor_t");
		printInner(1,"unsignint");
		printInnerInt(t->unsignint);
		break;
	case Expr_Factor_t:
		printInner(2,"type=","Expr_Factor_t");
		printInner(1,"exprp");
		ExprV(t->exprp);
		break;
	case Funcall_Factor_t:
		printInner(2,"type=","Funcall_Factor_t");
		printInner(1,"fcallstmtp");
		FcallstmtV(t->fcallstmtp);
		break;
	default:
		fprintf(errlist, "BUG:430\n");
	}
	printTail("Factor");
}
void ConstV(ConstSP t)
{
	printHead("Const");
	switch (t->type) {
	case Num_Const_t:
		printInner(2,"type=","Num_Const_t");
		break;
	case Char_Const_t:
		printInner(2,"type=","Char_Const_t");
		break;
	default:
		fprintf(errlist, "BUG:445\n");
	}
	printInner(1,"value");
	printInnerInt(t->value);
	printTail("Const");
}
void VarV(VarSP t)
{
	printHead("Var");
	switch (t->type) {
	case Int_Var_t:
		printInner(2,"type=","Int_Var_t");
		break;
	case Char_Var_t:
		printInner(2,"type=","Char_Var_t");
		break;
	case IntArr_Var_t:
		printInner(2,"type=","IntArr_Var_t");
		printInner(1,"length");
		printInnerInt(t->length);
		break;
	case CharArr_Var_t:
		printInner(2,"type=","CharArr_Var_t");
		printInner(1,"length");
		printInnerInt(t->length);
		break;
	default:
		fprintf(errlist, "BUG:472\n");
	}
	printInner(1,"identp");
	IdentV(t->identp);
	printTail("Var");
}
void IdentV(IdentSP t)
{
	printHead("Ident");
	switch (t->type) {
	case ID_Ident_t:
		printInner(2,"type=","ID_Ident_t");
		break;
	case Proc_Ident_t:
		printInner(2,"type=","Proc_Ident_t");
		break;
	case Fun_Ident_t:
		printInner(2,"type=","Fun_Ident_t");
		break;
	case Arr_Ident_t:
		printInner(2,"type=","Arr_Ident_t");
		break;
	case IntPara_Ident_t:
		printInner(2,"type=","IntPara_Ident_t");
		break;
	case CharPara_Ident_t:
		printInner(2,"type=","CharPara_Ident_t");
		break;
	default:
		fprintf(errlist, "BUG:503\n");
	}
	printInner(1,"line");
	printInnerInt(t->line);
	printInner(1,"name");
	printInner(1,t->name);
	printTail("Ident");
}
void CondV(CondSP t)
{
	printHead("Cond");
	switch (t->op) {
	case Equ_Rela_t:
		printInner(2,"type=","Equ_Rela_t");
		break;
	case Neq_Rela_t:
		printInner(2,"type=","Neq_Rela_t");
		break;
	case Gtt_Rela_t:
		printInner(2,"type=","Gtt_Rela_t");
		break;
	case Geq_Rela_t:
		printInner(2,"type=","Geq_Rela_t");
		break;
	case Lst_Rela_t:
		printInner(2,"type=","Lst_Rela_t");
		break;
	case Leq_Rela_t :
		printInner(2,"type=","Leq_Rela_t ");
		break;
	default:
		fprintf(errlist, "BUG:534\n");
	}
	printInner(1,"lexprp");
	ExprV(t->lexprp);
	printInner(1,"rexprp");
	ExprV(t->rexprp);
	printTail("Cond");
}
void ParalistV(ParalistSP t)
{
	printHead("Paralist");
	for (; t != NULL; t = t->next) {
		ParaV(t->parap);
	}
	printTail("Paralist");
}
void ParaV(ParaSP t)
{
	printHead("Para");
	for (; t != NULL; t = t->next) {
		IdentV(t->identp);
	}
	printTail("Para");
}
void ArglistV(ArglistSP t)
{
	printHead("Arglist");
	for (; t != NULL; t = t->next) {
		ExprV(t->argp);
	}
	printTail("Arglist");
}

void analyse(PgmSP t)
{
	PgmV(t);
}
