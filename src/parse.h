/**
 * File: parse.h
 * Date: Nov 8, 2013
 * Author: Jeanhwea
 */
#ifndef PARSE_H

#define PARSE_H

/* declaretion of a bundle of struct pointer */
typedef struct _PgmS *PgmSP;
typedef struct _BlokS *BlokSP;
typedef struct _ConstDecS *ConstDecSP;
typedef struct _ConstDefS *ConstDefSP;
typedef struct _VarDecS *VarDecSP;
typedef struct _VarDefS *VarDefSP;
typedef struct _PFDecListS *PFDecListSP;
typedef struct _ProcDecS *ProcDecSP;
typedef struct _ProcS *ProcSP;
typedef struct _ProcHeadS *ProcHeadSP;
typedef struct _FunDecS *FunDecSP;
typedef struct _FunS *FunSP;
typedef struct _FunHeadS *FunHeadSP;
typedef struct _StmtS *StmtSP;
typedef struct _AssignstmtS *AssignstmtSP;
typedef struct _IfstmtS *IfstmtSP;
typedef struct _RepestmtS *RepestmtSP;
typedef struct _ForstmtS *ForstmtSP;
typedef struct _PcallstmtS *PcallstmtSP;
typedef struct _FcallstmtS *FcallstmtSP;
typedef struct _CompstmtS *CompstmtSP;
typedef struct _ReadstmtS *ReadstmtSP;
typedef struct _WritestmtS *WritestmtSP;
typedef struct _ExprS *ExprSP;
typedef struct _TermS *TermSP;
typedef struct _FactorS *FactorSP;
typedef struct _ConstS *ConstSP;
typedef struct _VarS *VarSP;
typedef struct _IdentS *IdentSP;
typedef struct _CondS *CondSP;
typedef struct _ParalistS *ParalistSP;
typedef struct _ParaS *ParaSP;
typedef struct _ArglistS *ArglistSP;

/* declaretion of a bundle of node type */
typedef enum { 
	Fun_PFDec_t , Proc_PFDec_t 
} PFDec_t;
typedef enum {
	Add_Addop_t, Minus_Addop_t 
} Addop_t;
typedef enum { 
	Nop_Multop_t, Mult_Multop_t, Div_Multop_t 
} Multop_t;
typedef enum { 
	Equ_Rela_t, Neq_Rela_t, Gtt_Rela_t, 
	Geq_Rela_t, Lst_Rela_t, Leq_Rela_t 
} Rela_t;
typedef enum { 
	Num_Const_t, Char_Const_t 
} Const_t;
typedef enum { 
	Int_Funret_t, Char_Funret_t 
} Funret_t;
typedef enum { 
	Int_Para_t, Char_Para_t, Array_Para_t 
} Para_t;
typedef enum { 
	Int_Var_t, Char_Var_t, IntArr_Var_t, 
	CharArr_Var_t 
} Var_t;
typedef enum { 
	ID_Ident_t, Proc_Ident_t, Fun_Ident_t, 
	Arr_Ident_t, IntPara_Ident_t, CharPara_Ident_t
} Ident_t;
typedef enum { 
	Assgin_Statement_t, IF_Statement_t, 
	Repeat_Statement_t, Pcall_Statement_t, 
	Comp_Statement_t, Read_Statement_t,
	Write_Statement_t, For_Statement_t, 
	Null_Statement_t 
} Statement_t;
typedef enum { 
	Norm_Assgin_t, Fun_Assgin_t, Array_Assgin_t 
} Assgin_t;
typedef enum { 
	To_For_t, Downto_For_t 
} For_t;
typedef enum { 
	Id_Factor_t, Array_Factor_t, Unsign_Factor_t,
	Expr_Factor_t, Funcall_Factor_t 
} Factor_t;
typedef enum { 
	StrId_Write_t, Str_Write_t, Id_Write_t 
} Write_t;

/* declaretion of a bundle of struct */
/* Program */
typedef struct _PgmS {
	BlokSP blockp;
} PgmS;
/* block */
typedef struct _BlokS {
	ConstDecSP constdecp;
	VarDecSP vardecp;
	PFDecListSP pflistp;
	CompstmtSP compstmtp;
} BlokS;
typedef struct _ConstDecS {
	ConstDecSP next;
	ConstDefSP constdefp;
} ConstDecS;
typedef struct _ConstDefS {
	IdentSP identp;
	ConstSP constp;
} ConstDefS;
typedef struct _VarDecS {
	VarDecSP next;
	VarDefSP vardefp;
} VarDecS;
typedef struct _VarDefS {
	VarDefSP next;
	VarSP varp;
} VarDefS;
typedef struct _PFDecListS {
	PFDec_t type;
	PFDecListSP next;
	/* ProcDecSP or FunDecSP */
	ProcDecSP pdecp; 
	FunDecSP fdecp; 
} PFDecListS;
typedef struct _ProcDecS {
	ProcDecSP next;
	ProcSP procp;
} ProcDecS;
typedef struct _ProcS {
	ProcHeadSP procheadp;
	BlokSP blockp;
} ProcS;
typedef struct _ProcHeadS {
	IdentSP identp;
	ParalistSP paralistp;
} ProcHeadS;
typedef struct _FunDecS {
	FunSP funp;
	FunDecSP next;
} FunDecS;
typedef struct _FunS {
	FunHeadSP funheadp;
	BlokSP blockp;
} FunS;
typedef struct _FunHeadS {
	IdentSP identp;
	ParalistSP paralistp;
	Funret_t rettype;
} FunHeadS;
/* statement */
typedef struct _StmtS {
	Statement_t type;
	AssignstmtSP assignp;
	IfstmtSP ifp;
	RepestmtSP repep;
	ForstmtSP forp;
	PcallstmtSP pcallp;
	CompstmtSP compp;
	ReadstmtSP readp;
	WritestmtSP writep;
} StmtS;
typedef struct _AssignstmtS {
	Assgin_t type;
	IdentSP idp;
	ExprSP lexprp;
	ExprSP rexprp;
} AssignstmtS;
typedef struct _IfstmtS {
	CondSP condp;
	StmtSP thenp;
	StmtSP elsep;
} IfstmtS;
typedef struct _RepestmtS {
	StmtSP stmtp;
	CondSP condp;
} RepestmtS;
typedef struct _ForstmtS {
	For_t type;
	IdentSP identp;
	ExprSP lowp;
	ExprSP highp;
	StmtSP stmtp;
} ForstmtS;
typedef struct _PcallstmtS {
	IdentSP identp;
	ArglistSP arglistp;
} PcallstmtS;
typedef struct _FcallstmtS {
	IdentSP identp;
	ArglistSP arglistp;
} FcallstmtS;
typedef struct _CompstmtS {
	StmtSP curr;
	CompstmtSP next;
} CompstmtS;
typedef struct _ReadstmtS {
	IdentSP identp;
	ReadstmtSP next;
} ReadstmtS;
typedef struct _WritestmtS {
	Write_t type;
	char *stringp;
	ExprSP exprp;
} WritestmtS;
/* expression term factor*/
typedef struct _ExprS {
	Addop_t op;
	TermSP termp;
	ExprSP next;
} ExprS;
typedef struct _TermS {
	Multop_t op;
	FactorSP factorp;
	TermSP next;
} TermS;
typedef struct _FactorS {
	Factor_t type;
	IdentSP identp;
	ExprSP exprp;
	int unsignint;
	FcallstmtSP fcallstmtp;
} FactorS;
/* ident condition arguments*/
typedef struct _ConstS {
	Const_t type;
	/* int or char */
	int value;
} ConstS;
typedef struct _VarS {
	IdentSP identp;
	/* length for array */
	int length;
	Var_t type;
} VarS;
typedef struct _IdentS {
	Ident_t type;
	int line;
	char *name;
} IdentS;
typedef struct _CondS {
	ExprSP lexprp;
	Rela_t op;
	ExprSP rexprp;
} CondS;
typedef struct _ParalistS {
	ParaSP parap;
	ParalistSP next;
} ParalistS;
typedef struct _ParaS {
	ParaSP next;
	IdentSP identp;
} ParaS;
typedef struct _ArglistS {
	ExprSP argp;
	ArglistSP next;
} ArglistS;


typedef int IDREADMODE; 
#define READCURR 0
#define READPREV 1

/* some helpful macros */
/* s = struct name, v = variable, a struct pointer */
#define MALLOC(s, v) \
do{ \
	v = (s##P) malloc(sizeof(s));                                    \
	if (v == NULL){                                                  \
		fprintf(errlist, "out of memory at line %d\n", lineno);  \
	}                                                                \
} while(0)
/* just test if current token match what we expect */
/* we won't get next token */
#define TEST(expect) (token==(expect))

PgmSP parse(void);
#endif /* end of include guard: PARSE_H */
