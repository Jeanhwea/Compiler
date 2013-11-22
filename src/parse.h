/**
 * File: parse.h
 * Date: Nov 8, 2013
 * Author: Jeanhwea
 */
#ifndef PARSE_H

#define PARSE_H

/* declaretion of a bundle of struct pointer */
typedef struct _PgmS *PgmSP;
typedef struct _BlockS *BlockSP;
typedef struct _ConstDecS *ConstDecSP;
typedef struct _ConstDefS *ConstDefSP;
typedef struct _VarDecS *VarDecSP;
typedef struct _VarDefS *VarDefSP;
typedef struct _PFDecListS *PFDecListSP;
typedef struct _ProcDecS *ProcDecSP;
typedef struct _ProcDefS *ProcDefSP;
typedef struct _ProcHeadS *ProcHeadSP;
typedef struct _FunDecS *FunDecSP;
typedef struct _FunDefS *FunDefSP;
typedef struct _FunHeadS *FunHeadSP;
typedef struct _StmtS *StmtSP;
typedef struct _AssignStmtS *AssignStmtSP;
typedef struct _IfStmtS *IfStmtSP;
typedef struct _RepeStmtS *RepeStmtSP;
typedef struct _ForStmtS *ForStmtSP;
typedef struct _PcallStmtS *PcallStmtSP;
typedef struct _FcallStmtS *FcallStmtSP;
typedef struct _CompStmtS *CompStmtSP;
typedef struct _ReadStmtS *ReadStmtSP;
typedef struct _WriteStmtS *WriteStmtSP;
typedef struct _ExprS *ExprSP;
typedef struct _TermS *TermSP;
typedef struct _FactorS *FactorSP;
typedef struct _CondS *CondSP;
typedef struct _IdentS *IdentSP;
typedef struct _ParaListS *ParaListSP;
typedef struct _ParaDefS *ParaDefSP;
typedef struct _ArgListS *ArgListSP;

/* declaretion of a bundle of node type */
typedef enum { 
	Fun_PFDec_t , Proc_PFDec_t 
} PFDec_t;
typedef enum {
	Nop_Addop_t, Add_Addop_t, Neg_Addop_t,
	Minus_Addop_t 
} Addop_t;
typedef enum { 
	Nop_Multop_t, Mult_Multop_t, Div_Multop_t 
} Multop_t;
typedef enum { 
	Equ_Rela_t, Neq_Rela_t, Gtt_Rela_t, 
	Geq_Rela_t, Lst_Rela_t, Leq_Rela_t 
} Rela_t;
typedef enum { 
	/* normal identifier type */
	Init_Ident_t, Proc_Ident_t, Int_Fun_Ident_t, 
	Char_Fun_Ident_t,
	/* const identifier type */
	Int_Const_Ident_t, Char_Const_Ident_t,
	/* variable identifier type */
	Int_Var_Ident_t, Char_Var_Ident_t,
	IntArr_Var_Ident_t, CharArr_Var_Ident_t,
	/* parameter identifier type */
	/* call by value */
	Int_Para_Val_Ident_t, Char_Para_Val_Ident_t,
	/* call by address */
	Int_Para_Ref_Ident_t, Char_Para_Ref_Ident_t
} Ident_t;
typedef enum { 
	Assgin_Stmt_t, IF_Stmt_t, Repeat_Stmt_t,
	Pcall_Stmt_t, Comp_Stmt_t, Read_Stmt_t,
	Write_Stmt_t,  For_Stmt_t, 
	Null_Stmt_t 
} Stmt_t;
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
	BlockSP bp;
} PgmS;
/* block */
typedef struct _BlockS {
	ConstDecSP cdp;
	VarDecSP vdp;
	PFDecListSP pfdlp;
	CompStmtSP csp;
} BlockS;
typedef struct _ConstDecS {
	ConstDefSP cdp;
	ConstDecSP next;
} ConstDecS;
typedef struct _ConstDefS {
	IdentSP idp;
} ConstDefS;
typedef struct _VarDecS {
	VarDefSP vdp;
	VarDecSP next;
} VarDecS;
typedef struct _VarDefS {
	IdentSP idp;
	VarDefSP next;
} VarDefS;
typedef struct _PFDecListS {
	PFDec_t type;
	ProcDecSP pdp; 
	FunDecSP fdp; 
	PFDecListSP next;
} PFDecListS;
typedef struct _ProcDecS {
	ProcDefSP pdp;
	ProcDecSP next;
} ProcDecS;
typedef struct _ProcDefS {
	ProcHeadSP php;
	BlockSP bp;
} ProcDefS;
typedef struct _ProcHeadS {
	IdentSP idp;
	ParaListSP plp;
} ProcHeadS;
typedef struct _FunDecS {
	FunDefSP fdp;
	FunDecSP next;
} FunDecS;
typedef struct _FunDefS {
	FunHeadSP fhp;
	BlockSP bp;
} FunDefS;
typedef struct _FunHeadS {
	IdentSP idp;
	ParaListSP plp;
} FunHeadS;
/* statement */
typedef struct _StmtS {
	Stmt_t type;
	AssignStmtSP asp;
	IfStmtSP ifp;
	RepeStmtSP rpp;
	ForStmtSP frp;
	PcallStmtSP pcp;
	CompStmtSP cpp;
	ReadStmtSP rdp;
	WriteStmtSP wtp;
} StmtS;
typedef struct _AssignStmtS {
	Assgin_t type;
	IdentSP idp;
	ExprSP lep;
	ExprSP rep;
} AssignStmtS;
typedef struct _IfStmtS {
	CondSP cp;
	/* then */
	StmtSP tp;
	/* else */
	StmtSP ep;
} IfStmtS;
typedef struct _RepeStmtS {
	StmtSP sp;
	CondSP cp;
} RepeStmtS;
typedef struct _ForStmtS {
	For_t type;
	IdentSP idp;
	ExprSP lep;
	ExprSP rep;
	StmtSP sp;
} ForStmtS;
typedef struct _PcallStmtS {
	IdentSP idp;
	ArgListSP alp;
} PcallStmtS;
typedef struct _FcallStmtS {
	IdentSP idp;
	ArgListSP alp;
} FcallStmtS;
typedef struct _CompStmtS {
	StmtSP sp;
	CompStmtSP next;
} CompStmtS;
typedef struct _ReadStmtS {
	IdentSP idp;
	ReadStmtSP next;
} ReadStmtS;
typedef struct _WriteStmtS {
	Write_t type;
	/* string pointer */
	char *sp;
	ExprSP ep;
} WriteStmtS;
/* expression term factor condition */
typedef struct _ExprS {
	Addop_t op;
	TermSP tp;
	ExprSP next;
} ExprS;
typedef struct _TermS {
	Multop_t op;
	FactorSP fp;
	TermSP next;
} TermS;
typedef struct _FactorS {
	Factor_t type;
	IdentSP idp;
	ExprSP ep;
	/* unsign int */
	int usi;
	FcallStmtSP fcsp;
} FactorS;
typedef struct _CondS {
	ExprSP lep;
	Rela_t op;
	ExprSP rep;
} CondS;
/* ident parameter argument*/
typedef struct _IdentS {
	Ident_t type;
	char *name;
	int val;
	int length;
	int line;
} IdentS;
typedef struct _ParaListS {
	ParaDefSP pdp;
	ParaListSP next;
} ParaListS;
typedef struct _ParaDefS {
	IdentSP idp;
	ParaDefSP next;
} ParaDefS;
typedef struct _ArgListS {
	ExprSP ep;
	ArgListSP next;
} ArgListS;


typedef int IDREADMODE; 
#define READCURR 0
#define READPREV 1


/* some helpful macros */
/* s = struct name for a node, v = variable, a struct pointer */
#define NEWNODE(s, v) \
do{ \
	v = (s##P) malloc(sizeof(s));					\
	if (v == NULL){							\
		fprintf(errlist, "OUTOFMEM: at line %d\n", lineno);	\
	}								\
} while(0)

/* just test if current token match what we expect */
/* we won't get next token */
#define TEST(a) (token==(a))
#define TEST2(a,b) (token==(a)||token==(b))
#define TEST3(a,b,c) (token==(a)||token==(b)||token==(c))
#define TEST4(a,b,c,d) (token==(a)||token==(b)||token==(c)||token==(d))
#define TEST5(a,b,c,d,e) (token==(a)||token==(b)||token==(c)		\
		||token==(d)||token==(e))
#define TEST6(a,b,c,d,e,f) (token==(a)||token==(b)||token==(c) 		\
				||token==(d)||token==(e)||token==(f))

PgmSP parse(void);

#endif /* end of include guard: PARSE_H */
