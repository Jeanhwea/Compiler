/**
 * File: parse.h
 * Date: Nov 8, 2013
 * Author: Jeanhwea
 */
#ifndef PARSE_H

#define PARSE_H

/* declaretion of a bundle of struct pointer */
typedef struct PgmS *PgmSP;
typedef struct BlokS *BlokSP;
typedef struct ConstDecS *ConstDecSP;
typedef struct ConstDefS *ConstDefSP;
typedef struct VarDecS *VarDecSP;
typedef struct VarDefS *VarDefSP;
typedef struct PFDecListS *PFDecListSP;
typedef struct ProcDecS *ProcDecSP;
typedef struct ProcS *ProcSP;
typedef struct ProcHeadS *ProcHeadSP;
typedef struct FunDecS *FunDecSP;
typedef struct FunS *FunSP;
typedef struct FunHeadS *FunHeadSP;
typedef struct StmtS *StmtSP;
typedef struct AssignstmtS *AssignstmtSP;
typedef struct IfstmtS *IfstmtSP;
typedef struct RepestmtS *RepestmtSP;
typedef struct ForstmtS *ForstmtSP;
typedef struct PcallstmtS *PcallstmtSP;
typedef struct FcallstmtS *FcallstmtSP;
typedef struct CompstmtS *CompstmtSP;
typedef struct ReadstmtS *ReadstmtSP;
typedef struct WritestmtS *WritestmtSP;
typedef struct ExprS *ExprSP;
typedef struct TermS *TermSP;
typedef struct FactorS *FactorSP;
typedef struct ConstS *ConstSP;
typedef struct VarS *VarSP;
typedef struct IdentS *IdentSP;
typedef struct CondS *CondSP;
typedef struct ParalistS *ParalistSP;
typedef struct ParaS *ParaSP;
typedef struct ArglistS *ArglistSP;

/* declaretion of a bundle of node type */
typedef enum { Fun_PFDec_t , Proc_PFDec_t } PFDec_t;
typedef enum { Add_Addop_t, Minus_Addop_t } Addop_t;
typedef enum {Nop_Multop_t, Mult_Multop_t, Div_Multop_t } Multop_t;
typedef enum { Equ_Rela_t, Neq_Rela_t, Gtt_Rela_t, Geq_Rela_t,
		Lst_Rela_t, Leq_Rela_t 
	} Rela_t;
typedef enum { Num_Const_t, Char_Const_t } Const_t;
typedef enum { Int_Funret_t, Char_Funret_t } Funret_t;
typedef enum { Int_Para_t, Char_Para_t, Array_Para_t } Para_t;
typedef enum { Int_Var_t, Char_Var_t, IntArr_Var_t, CharArr_Var_t } Var_t;
typedef enum { ID_Ident_t, Proc_Ident_t, Fun_Ident_t, Arr_Ident_t,
		IntPara_Ident_t, CharPara_Ident_t
	} Ident_t;
typedef enum { Assgin_Statement_t, IF_Statement_t, Repeat_Statement_t,
		Pcall_Statement_t, Comp_Statement_t, Read_Statement_t,
		Write_Statement_t, For_Statement_t, Null_Statement_t 
	} Statement_t;
typedef enum { Norm_Assgin_t, Fun_Assgin_t, Array_Assgin_t } Assgin_t;
typedef enum { To_For_t, Downto_For_t } For_t;
typedef enum { Id_Factor_t, Array_Factor_t, Unsign_Factor_t,
		Expr_Factor_t, Funcall_Factor_t 
	} Factor_t;
typedef enum { StrId_Write_t, Str_Write_t, Id_Write_t } Write_t;

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
	ConstDecSP head;
	ConstDecSP next;
	ConstDefSP constdefp;
} ConstDecS;
typedef struct _ConstDefS {
	IdentSP identp;
	ConstSP constp;
} ConstDefS;
typedef struct _VarDecS {
	VarDecSP head;
	VarDecSP next;
	VarDefSP vardefp;
} VarDecS;
typedef struct _VarDefS {
	VarDefSP head;
	VarDefSP next;
	VarSP varp;
} VarDefS;
typedef struct _PFDecListS {
	PFDec_t type;
	PFDecListSP head;
	PFDecListSP next;
	/* ProcDecSP or FunDecSP */
	ProcDecSP pdecp; 
	FunDecSP fdecp; 
} PFDecListS;
typedef struct _ProcDecS {
	ProcDecSP head;
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
	FunDecSP head;
	FunDecSP next;
	FunSP funp;
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
	CompstmtSP head;
	CompstmtSP next;
	StmtSP curr;
} CompstmtS;
typedef struct _ReadstmtS {
	ReadstmtSP head;
	ReadstmtSP next;
	IdentSP identp;
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
	ExprSP head;
	ExprSP next;
} ExprS;
typedef struct _TermS {
	Multop_t op;
	FactorSP factorp;
	TermSP head;
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
	char *name;
} IdentS;
typedef struct _CondS {
	ExprSP lexprp;
	Rela_t op;
	ExprSP rexprp;
} CondS;
typedef struct _ParalistS {
	ParaListSP head;
	ParaListSP next;
	ParaSP parap;
} ParalistS;
typedef struct _ParaS {
	ParaSP head;
	ParaSP next;
	IdentSP identp;
} ParaS;
typedef struct _ArglistS {
	ArglistSP head;
	ArglistSP next;
	ExprSP argp;
} ArglistS;

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
#endif /* end of include guard: PARSE_H */

typedef IDREADMODE int;
#define READCURR 0
#define READPREV 1

