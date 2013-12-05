/**
 * File: parse.c
 * Date: Nov 9, 2013
 * Author: Jeanhwea
 */

#include "global.h"
#include "scan.h"
#include "parse.h"
#include "util.h"
#include "error.h"

static TokenType token; /* hold current token*/

/**
 * storedString and storedToken is to
 * dealing with joint FIRST set problem
 */
static char prevTokenString[MAXTOKENSIZE + 1];
static int preTokenLocation;
static TokenType prevToken;

static PgmSP PgmB(void);
static BlockSP BlockB(void);
static ConstDecSP ConstDecB(void);
static ConstDefSP ConstDefB(void);
static VarDecSP VarDecB(void);
static VarDefSP VarDefB(void);
static PFDecListSP PFDecListB(void);
static ProcDecSP ProcDecB(void);
static ProcDefSP ProcDefB(void);
static ProcHeadSP ProcHeadB(void);
static FunDecSP FunDecB(void);
static FunDefSP FunDefB(void);
static FunHeadSP FunHeadB(void);
static StmtSP StmtB(void);
static AssignStmtSP AssignStmtB(void);
static IfStmtSP IfStmtB(void);
static RepeStmtSP RepeStmtB(void);
static ForStmtSP ForStmtB(void);
static PcallStmtSP PcallStmtB(void);
static FcallStmtSP FcallStmtB(void);
static CompStmtSP CompStmtB(void);
static ReadStmtSP ReadStmtB(void);
static WriteStmtSP WriteStmtB(void);
static ExprSP ExprB(void);
static TermSP TermB(void);
static FactorSP FactorB(void);
static CondSP CondB(void);
static IdentSP IdentB(IDREADMODE mode);
static ParaListSP ParaListB(void);
static ParaDefSP ParaDefB(void);
static ArgListSP ArgListB(void);

static inline void getsym(void)
{
	/* store current token type and token string */
	strncpy(prevTokenString, tokenString, MAXTOKENSIZE);
	prevToken = token;
	preTokenLocation = tokenLocation;
	/* get next token */
	token = getToken();
}

static inline BOOL match(TokenType expected)
{
	if (TEST(expected)) {
		getsym();
		return TRUE;
	} else {
		fprintf(tiplist, "********************************\n");
		fprintf(tiplist, "missing match at line %d\n", lineno);
		printToken(expected, prevTokenString);
		fprintf(tiplist, "********************************\n");
		return FALSE;
	}
}

/**
 * program ->
 * 	block .
 */
PgmSP PgmB(void)
{
	PgmSP t;
	NEWNODE(PgmS, t);
	t->bp = BlockB();
	if (TEST(DOT)) {
		match(DOT);
	} else {
		--runlevel;
		syntaxError(MISSDOT, lineno, FALSE, NULL);
	}
	return t;
}

/**
 * block ->
 * 	[constdec] [vardec] [pfdeclist] compstmt
 */
BlockSP BlockB(void)
{
	BlockSP t;
	NEWNODE(BlockS, t);
	if (TEST(CONST)) {
		t->cdp = ConstDecB();
	} else t->cdp = NULL;

	if (TEST(VAR)) {
		t->vdp = VarDecB();
	} else t->vdp = NULL;
	
	if (TEST2(FUNCTION, PROCEDURE)) {
		t->pfdlp = PFDecListB();
	} else t->pfdlp = NULL;

	if (TEST(BEGIN)) {
		t->csp = CompStmtB();
	} else {
		--runlevel;
		syntaxError(MISSBODY, lineno, FALSE, NULL);
	}
	return t;
}

/**
 * constdec ->
 * 	CONST constdef {, constdef};
 */
ConstDecSP ConstDecB(void)
{
	ConstDecSP t, p, q;
	match(CONST);
	NEWNODE(ConstDecS, t);
	t->cdp = ConstDefB();
	t->next = NULL;
	for (p = t; TEST(COMMA); p = q) {
		match(COMMA);
		NEWNODE(ConstDecS, q);
		p->next = q;
		q->cdp = ConstDefB();
		q->next = NULL;
	}
	if (TEST(SEMI)) {
		match(SEMI);
	} else {
		--runlevel;
		syntaxError(MISSSEMI, lineno, FALSE, prevTokenString);
	}
	return t;
}

/**
 * constdef ->
 * 	ident = const 
 */
ConstDefSP ConstDefB(void)
{
	ConstDefSP t;
	NEWNODE(ConstDefS, t);
	if (TEST(ID)) {
		t->idp = IdentB(READCURR);
	} else t->idp = NULL;
	if (TEST(EQU)) {
		match(EQU);
	} else {
		--runlevel;
		syntaxError(MISSEQU, lineno, FALSE, prevTokenString);
	}
	if (TEST4(PLUS, MINUS, UNS, CH)) {
		switch (token) {
		case PLUS:
			match(PLUS);
			t->idp->type = Int_Const_Ident_t;
			if (TEST(UNS)) {
				t->idp->val = atoi(tokenString);
				match(UNS);
			} else {
				--runlevel;
				syntaxError(MISSUNS, lineno, FALSE, prevTokenString);
			}
			break;
		case MINUS:
			match(MINUS);
			t->idp->type = Int_Const_Ident_t;
			if (TEST(UNS)) {
				t->idp->val = - atoi(tokenString);
				match(UNS);
			} else {
				--runlevel;
				syntaxError(MISSUNS, lineno, FALSE, prevTokenString);
			}
			break;
		case UNS:
			t->idp->type = Int_Const_Ident_t;
			t->idp->val = atoi(tokenString);
			match(UNS);
			break;
		case CH:
			t->idp->type = Char_Const_Ident_t;
			t->idp->val = (int) tokenString[0];
			match(CH);
			break;
		default:
			--runlevel;
			syntaxError(UNEXPECT, lineno, TRUE, tokenString);
		}
	} else t->idp = NULL;
	return t;
}

/**
 * vardec ->
 * 	VAR vardef; { vardef;}
 */
VarDecSP VarDecB(void)
{
	VarDecSP t, p, q;
	NEWNODE(VarDecS, t);
	match(VAR);
	t->vdp = VarDefB();
	t->next = NULL;
	if (TEST(SEMI)) {
		match(SEMI);
	} else {
		--runlevel;
		syntaxError(MISSSEMI, lineno, FALSE, prevTokenString);
	}
	for (p = t; TEST(ID); p = q) {
		NEWNODE(VarDecS, q);
		p->next = q;
		q->vdp = VarDefB();
		q->next = NULL;
		if (TEST(SEMI)) {
			match(SEMI);
		} else {
			--runlevel;
			syntaxError(MISSSEMI, lineno, FALSE, prevTokenString);
		}
	}
	return t;
}

/**
 * vardef ->
 * 	ident {, ident} : type 
 */
VarDefSP VarDefB(void)
{
	VarDefSP t, p, q;
	int arraylength = 0;
	NEWNODE(VarDefS, t);
	t->idp = IdentB(READCURR);
	t->next = NULL;
	for (p = t; TEST(COMMA); p = q) {
		match(COMMA);
		NEWNODE(VarDefS, q);
		p->next = q;
		q->idp = IdentB(READCURR);
		q->next = NULL;
	}
	if (TEST(COLON)) {
		match(COLON);
	} else {
		--runlevel;
		syntaxError(MISSCOLON, lineno, FALSE, prevTokenString);
	}
	/* type write back */
	switch (token) {
	case INTEGER:
		match(INTEGER);
		for (p = t; p != NULL; p = p->next) 
			p->idp->type = Int_Var_Ident_t;
		break;
	case CHAR:
		match(CHAR);
		for (p = t; p != NULL; p = p->next) 
			p->idp->type = Char_Var_Ident_t;
		break;
	case ARRAY:
		match(ARRAY);
		if (TEST(LBRA)) {
			match(LBRA);
		} else {
			--runlevel;
			syntaxError(MISSLBRA, lineno, FALSE, prevTokenString);
		}
		if (TEST(UNS)) {
			arraylength = atoi(tokenString);
			match(UNS);
		} else {
			--runlevel;
			syntaxError(MISSUNS, lineno, FALSE, prevTokenString);
		}
		if (TEST(RBRA)) {
			match(RBRA);
		} else {
			--runlevel;
			syntaxError(MISSRBRA, lineno, FALSE, prevTokenString);
		}
		if (TEST(OF)) {
			match(OF);
		} else {
			--runlevel;
			syntaxError(MISSOF, lineno, FALSE, prevTokenString);
		}
		if (TEST(INTEGER)) {
			match(INTEGER);
			for (p = t; p != NULL; p = p->next) {
				p->idp->type = IntArr_Var_Ident_t;
				p->idp->length = arraylength;
			}
		} else if (TEST(CHAR)) {
			match(CHAR);
			for (p = t; p != NULL; p = p->next) {
				p->idp->type = CharArr_Var_Ident_t;
				p->idp->length = arraylength;
			}
		} else {
			--runlevel;
			syntaxError(UNEXPECT, lineno, TRUE, tokenString);
		}
		break;
	default:
		--runlevel;
		syntaxError(UNEXPECT, lineno, TRUE, tokenString);
		break;
	}
	return t;
}

/**
 * pfdeclist -> 
 * 	{ procdec | fundec }
 */
PFDecListSP PFDecListB(void)
{
	PFDecListSP t, p, q;
	NEWNODE(PFDecListS, t);
	t->pdp = NULL;
	t->fdp = NULL;
	switch (token) {
	case PROCEDURE:
		t->type = Proc_PFDec_t;
		t->pdp = ProcDecB();
		break;
	case FUNCTION:
		t->type = Fun_PFDec_t;
		t->fdp = FunDecB();
		break;
	default:
		--runlevel;
		syntaxError(UNEXPECT, lineno, TRUE, tokenString);
		break;
	}
	t->next = NULL;
	for (p = t; TEST2(FUNCTION, PROCEDURE); p = q) {
		NEWNODE(PFDecListS, q);
		p->next = q;
		q->pdp = NULL;
		q->fdp = NULL;
		switch (token) {
		case PROCEDURE:
			q->type = Proc_PFDec_t;
			q->pdp = ProcDecB();
			break;
		case FUNCTION:
			q->type = Fun_PFDec_t;
			q->fdp = FunDecB();
			break;
		default:
			--runlevel;
			syntaxError(UNEXPECT, lineno, TRUE, tokenString);
		}
		q->next = NULL;
	}
	return t;
}

/**
 * procdec ->
 * 	procdef {; procdef};
 */
ProcDecSP ProcDecB(void)
{
	ProcDecSP t, p, q;
	NEWNODE(ProcDecS, t);
	t->pdp = ProcDefB();
	t->next = NULL;
	if (TEST(SEMI)) {
		match(SEMI);
	} else {
		--runlevel;
		syntaxError(MISSSEMI, lineno, FALSE, prevTokenString);
	}
	for (p = t; TEST(PROCEDURE); p = q) {
		NEWNODE(ProcDecS, q);
		p->next = q;
		q->pdp = ProcDefB();
		q->next = NULL;
		if (TEST(SEMI)) {
			match(SEMI);
		} else {
			--runlevel;
			syntaxError(MISSSEMI, lineno, FALSE, prevTokenString);
		}
	}
	return t;
}

/**
 * procdef ->
 * 	prochead block
 */
ProcDefSP ProcDefB(void)
{
	ProcDefSP t;
	NEWNODE(ProcDefS, t);
	t->php = ProcHeadB();
	t->bp = BlockB();
	return t;
}

/** 
 * prochead ->
 * 	PROCEDURE ident '(' [paralist] ')' ;
 */
ProcHeadSP ProcHeadB(void)
{
	ProcHeadSP t;
	NEWNODE(ProcHeadS, t);
	match(PROCEDURE);
	t->idp = IdentB(READCURR);
	/* PROCEDURE identifier type write back */
	t->idp->type = Proc_Ident_t;
	if (TEST(LPAR)) {
		match(LPAR);
	} else {
		--runlevel;
		syntaxError(MISSLPAR, lineno, FALSE, prevTokenString);
	}
	if (TEST(VAR) || TEST(ID))
		t->plp = ParaListB();
	else t->plp = NULL;
	if (TEST(RPAR)) {
		match(RPAR);
	} else {
		--runlevel;
		syntaxError(MISSRPAR, lineno, FALSE, prevTokenString);
	}
	if (TEST(SEMI)) {
		match(SEMI);
	} else {
		--runlevel;
		syntaxError(MISSSEMI, lineno, FALSE, prevTokenString);
	}
	return t;
}

/**
 * fundec ->
 * 	fundef {; fundef};
 */
FunDecSP FunDecB(void)
{
	FunDecSP t, p, q;
	NEWNODE(FunDecS, t);
	t->fdp = FunDefB();
	t->next = NULL;
	if (TEST(SEMI)) {
		match(SEMI);
	} else {
		--runlevel;
		syntaxError(MISSSEMI, lineno, FALSE, prevTokenString);
	}
	for (p = t; TEST(FUNCTION); p = q) {
		NEWNODE(FunDecS, q);
		p->next =  q;
		q->fdp = FunDefB();
		q->next = NULL;
		if (TEST(SEMI)) {
			match(SEMI);
		} else {
			--runlevel;
			syntaxError(MISSSEMI, lineno, FALSE, prevTokenString);
		}
	}
	return t;
}

/**
 * fundef -> 
 * 	funhead block
 */
FunDefSP FunDefB(void)
{
	FunDefSP t;
	NEWNODE(FunDefS, t);
	t->fhp = FunHeadB();
	t->bp = BlockB();
	return t;
}

/**
 * funhead ->
 * 	FUNCTION ident '(' [paralist] ')' : basictype ;
 */
FunHeadSP FunHeadB(void)
{
	FunHeadSP t;
	NEWNODE(FunHeadS, t);
	match(FUNCTION);
	t->idp = IdentB(READCURR);
	if (TEST(LPAR)) {
		match(LPAR);
	} else {
		--runlevel;
		syntaxError(MISSLPAR, lineno, FALSE, prevTokenString);
	}
	if (TEST(VAR) || TEST(ID))
		t->plp = ParaListB();
	else t->plp = NULL;
	if (TEST(RPAR)) {
		match(RPAR);
	} else {
		--runlevel;
		syntaxError(MISSRPAR, lineno, FALSE, prevTokenString);
	}
	if (TEST(COLON)) {
		match(COLON);
	} else {
		--runlevel;
		syntaxError(MISSCOLON, lineno, FALSE, prevTokenString);
	}
	switch (token) {
	case INTEGER:
		match(INTEGER);
		t->idp->type = Int_Fun_Ident_t;
		break;
	case CHAR:
		match(CHAR);
		t->idp->type = Char_Fun_Ident_t;
		break;
	default:
		--runlevel;
		syntaxError(UNEXPECT, lineno, TRUE, tokenString);
		break;
	}
	if (TEST(SEMI)) {
		match(SEMI);
	} else {
		--runlevel;
		syntaxError(MISSSEMI, lineno, FALSE, prevTokenString);
	}
	return t;
}

/**
 * statement ->
 * 	assignstmt | ifstmt | repeatstmt | Pcallstmt | compstmt
 * 		readstmt | writestmt | forstmt | nullstmt
 */
StmtSP StmtB(void)
{
	StmtSP t;
	NEWNODE(StmtS, t);
	t->asp = NULL;
	t->ifp = NULL;
	t->rpp = NULL;
	t->frp = NULL;
	t->pcp = NULL;
	t->cpp = NULL;
	t->rdp = NULL;
	t->wtp = NULL;
	switch (token) {
	case IF:
		t->type = IF_Stmt_t;
		t->ifp = IfStmtB();
		break;
	case REPEAT:
		t->type = Repeat_Stmt_t;
		t->rpp = RepeStmtB();
		break;
	case BEGIN:
		t->type = Comp_Stmt_t;
		t->cpp = CompStmtB();
		break;
	case READ:
		t->type = Read_Stmt_t;
		t->rdp = ReadStmtB();
		break;
	case WRITE:
		t->type = Write_Stmt_t;
		t->wtp = WriteStmtB();
		break;
	case FOR:
		t->type = For_Stmt_t;
		t->frp = ForStmtB();
		break;
	case ID:
		getsym();
		if (TEST(LPAR)) {	
			t->type = Pcall_Stmt_t;
			t->pcp = PcallStmtB();
		} else if (TEST(ASSIGN) ||  TEST(LBRA)) {
			t->type = Assgin_Stmt_t;
			t->asp = AssignStmtB();
		} else {
			--runlevel;
			syntaxError(UNEXPECT, lineno, TRUE, tokenString);
		}
		break;
	default:
		t->type = Null_Stmt_t;
		break;
	}
	return t;
}

/**
 * remember in the statement build function 
 * we have read the token from ident to := or '['
 *
 * assignstmt ->
 * 	ident := expression | funident := expression
 * 		| ident '[' expression ']' := expression
 */
AssignStmtSP AssignStmtB(void)
{
	AssignStmtSP t;
	NEWNODE(AssignStmtS, t);
	switch (token) {
	case ASSIGN:
		/* ident or funident */
		t->type = Norm_Assgin_t;
		t->idp = IdentB(READPREV);
		match(ASSIGN);
		t->lep = NULL;
		t->rep = ExprB();
		break;
	case LBRA:
		t->type = Array_Assgin_t;
		t->idp = IdentB(READPREV);
		match(LBRA);
		t->lep = ExprB();
		if (TEST(RBRA)) {
			match(RBRA);
		} else {
			--runlevel;
			syntaxError(MISSRBRA, lineno, FALSE, prevTokenString);
		}
		if (TEST(ASSIGN)) {
			match(ASSIGN);
		} else {
			--runlevel;
			syntaxError(MISSASS, lineno, FALSE, prevTokenString);
		}
		t->rep = ExprB();
		break;
	default:
		--runlevel;
		syntaxError(UNEXPECT, lineno, TRUE, tokenString);
		break;
	}
	return t;
}

/**
 * ifstmt ->
 * 	IF condition THEN statement |
 * 		IF condition THEN statement ELSE statement
 */
IfStmtSP IfStmtB(void)
{
	IfStmtSP t;
	NEWNODE(IfStmtS, t);
	match(IF);
	t->cp = CondB();
	if (TEST(THEN)) {
		match(THEN);
	} else {
		--runlevel;
		syntaxError(MISSTHEN, lineno, FALSE, prevTokenString);
	}
	t->tp = StmtB();
	if (TEST(ELSE)) {
		match(ELSE);
		t->ep = StmtB();
	} else t->ep = NULL;
	return t;
}

/**
 * repeatstmt ->
 * 	REPEAT statement UNTIL condition
 */
RepeStmtSP RepeStmtB(void)
{
	RepeStmtSP t;
	NEWNODE(RepeStmtS, t);
	match(REPEAT);
	t->sp = StmtB();
	if (TEST(UNTIL)) {
		match(UNTIL);
	} else {
		--runlevel;
		syntaxError(MISSUNTIL, lineno, FALSE, prevTokenString);
	}
	t->cp = CondB();
	return t;
}

/**
 * forstmt ->
 * 	FOR ident := expression ( TO | DOWNTO ) expression DO statement
 */
ForStmtSP ForStmtB(void)
{
	ForStmtSP t;
	NEWNODE(ForStmtS, t);
	match(FOR);
	t->idp = IdentB(READCURR);
	if (TEST(ASSIGN)) {
		match(ASSIGN);
	} else {
		--runlevel;
		syntaxError(MISSUNS, lineno, FALSE, prevTokenString);
	}
	t->lep = ExprB();
	if (TEST(TO)) {
		match(TO);
		t->type = To_For_t;
	} else if (TEST(DOWNTO)) {
		match(DOWNTO);
		t->type = Downto_For_t;
	} else {
		--runlevel;
		syntaxError(MISSTODOWN, lineno, FALSE, prevTokenString);
	}
	t->rep = ExprB();
	if (TEST(DO)) {
		match(DO);
	} else {
		--runlevel;
		syntaxError(MISSDO, lineno, FALSE, prevTokenString);
	}
	t->sp = StmtB();
	return t;
}

/**
 * remember in the statement build function 
 * we have read the token from ident to (
 *
 * pcallstmt ->
 * 	ident '(' [arglist] ')'
 */
PcallStmtSP PcallStmtB(void)
{
	PcallStmtSP t;
	NEWNODE(PcallStmtS, t);
	t->idp = IdentB(READPREV);
	if (TEST(LPAR)) {
		match(LPAR);
	} else {
		--runlevel;
		syntaxError(MISSLPAR, lineno, FALSE, prevTokenString);
	}
	if (TEST5(ID, PLUS, MINUS, UNS, LPAR)) {
		t->alp = ArgListB();
	} else t->alp = NULL;
	if (TEST(RPAR)) {
		match(RPAR);
	} else {
		--runlevel;
		syntaxError(MISSRPAR, lineno, FALSE, prevTokenString);
	}
	return t;
}

/**
 * remember in the factor build function 
 * we have read the token from ident to (
 *
 * fcallstmt ->
 * 	ident '(' [arglist] ')'
 */
FcallStmtSP FcallStmtB(void)
{
	FcallStmtSP t;
	NEWNODE(FcallStmtS, t);
	t->idp = IdentB(READPREV);
	if (TEST(LPAR)) {
		match(LPAR);
	} else {
		--runlevel;
		syntaxError(MISSLPAR, lineno, FALSE, prevTokenString);
	}
	if (TEST5(ID, PLUS, MINUS, UNS, LPAR)) {
		t->alp = ArgListB();
	} else t->alp = NULL;
	if (TEST(RPAR)) {
		match(RPAR);
	} else {
		--runlevel;
		syntaxError(MISSRPAR, lineno, FALSE, prevTokenString);
	}
	return t;
}

/**
 * compstmt ->
 * 	BEGIN statement {; statement} END 
 */
CompStmtSP CompStmtB(void)
{
	CompStmtSP t, p, q;
	NEWNODE(CompStmtS, t);
	match(BEGIN);
	t->sp = StmtB();
	t->next = NULL;
	for (p = t; TEST(SEMI) ; p = q) {
		match(SEMI);
		NEWNODE(CompStmtS, q);
		p->next = q;
		q->sp = StmtB();
		q->next = NULL;
	}
	if (TEST(END)) {
		match(END);
	} else {
		--runlevel;
		syntaxError(MISSEND, lineno, FALSE, prevTokenString);
	}
	return t;
}

/**
 * readstmt ->
 * 	READ '(' ident {, ident} ')'
 */
ReadStmtSP ReadStmtB(void)
{
	ReadStmtSP t, p, q;
	NEWNODE(ReadStmtS, t);
	match(READ);
	if (TEST(LPAR)) {
		match(LPAR);
	} else {
		--runlevel;
		syntaxError(MISSLPAR, lineno, FALSE, prevTokenString);
	}
	t->idp = IdentB(READCURR);
	t->next = NULL;
	for (p = t; TEST(COMMA); p = q) {
		match(COMMA);
		NEWNODE(ReadStmtS, q);
		p->next = q;
		q->idp = IdentB(READCURR);
		q->next = NULL;
	}
	if (TEST(RPAR)) {
		match(RPAR);
	} else {
		--runlevel;
		syntaxError(MISSRPAR, lineno, FALSE, prevTokenString);
	}
	return t;
}

/**
 * writestmt ->
 * 	WRITE '(' string, expression ')' | WRITE '(' string ')' |
 * 		WRITE '(' expression ')'
 */
WriteStmtSP WriteStmtB(void)
{
	WriteStmtSP t;
	NEWNODE(WriteStmtS, t);
	match(WRITE);
	if (TEST(LPAR)) {
		match(LPAR);
	} else {
		--runlevel;
		syntaxError(MISSLPAR, lineno, FALSE, prevTokenString);
	}
	t->sp = NULL;
	t->ep = NULL;
	if (TEST(STRING)) {
		t->type = Str_Write_t;
		t->sp = copyString(tokenString);
		match(STRING);
	} else if (TEST5(ID, PLUS, MINUS, UNS, LPAR)) {
		t->type = Id_Write_t;
		t->ep = ExprB();
	} else {
		--runlevel;
		syntaxError(UNEXPECT, lineno, TRUE, tokenString);
	}
	if (TEST(COMMA) && t->type == Str_Write_t) {
		match(COMMA);
		t->type = StrId_Write_t;
		t->ep = ExprB();
	}
	if (TEST(RPAR)) {
		match(RPAR);
	} else {
		--runlevel;
		syntaxError(MISSRPAR, lineno, FALSE, prevTokenString);
	}
	return t;
}

/**
 * expression ->
 * 	[+|-] term { addop term }
 */
ExprSP ExprB(void)
{
	ExprSP t, p, q;
	NEWNODE(ExprS, t);
	switch (token) {
	case PLUS:
		match(PLUS);
		t->op = Add_Addop_t;
		t->tp = TermB();
		break;
	case MINUS:
		match(MINUS);
		t->op = Neg_Addop_t;
		t->tp = TermB();
		break;
	case ID:
	case UNS:
	case LPAR:
		t->op = Nop_Addop_t;
		t->tp = TermB();
		break;
	default:
		t->op = Nop_Addop_t;
		t->tp = NULL;
		--runlevel;
		syntaxError(UNEXPECT, lineno, TRUE, tokenString);
		break;
	}
	t->next = NULL;
	for (p = t; TEST2(PLUS, MINUS); p = q) {
		NEWNODE(ExprS, q);
		p->next = q;
		switch (token) {
		case PLUS:
			match(PLUS);
			q->op = Add_Addop_t;
			break;
		case MINUS:
			match(MINUS);
			q->op = Minus_Addop_t;
			break;
		default:
			--runlevel;
			syntaxError(UNEXPECT, lineno, TRUE, tokenString);
			break;
		}
		q->tp = TermB();
		q->next = NULL;
	}
	return t;
}

/**
 * term ->
 * 	factor { multop factor}
 */
TermSP TermB(void)
{
	TermSP t, p, q;
	NEWNODE(TermS, t);
	t->op = Nop_Multop_t;
	t->fp = FactorB();
	t->next = NULL;
	for (p = t; TEST2(STAR, OVER); p = q) {
		NEWNODE(TermS, q);
		p->next = q;
		switch (token) {
		case STAR:
			match(STAR);
			q->op = Mult_Multop_t;
			break;
		case OVER:
			match(OVER);
			q->op = Div_Multop_t;
			break;
		default:
			--runlevel;
			syntaxError(UNEXPECT, lineno, TRUE, tokenString);
			break;
		}
		q->fp = FactorB();
		q->next = NULL;
	}
	return t;
}

/**
 * factor ->
 * 	ident | ident '[' expression ']' | unsign 
 * 		| '(' expression ')' | fcallstmt
 */
FactorSP FactorB(void)
{
	FactorSP t;
	NEWNODE(FactorS, t);
	t->idp = NULL;
	t->ep = NULL;
	t->usi = 0;
	t->fcsp = NULL;
	switch (token) {
	case UNS:
		t->type = Unsign_Factor_t;
		t->usi = atoi(tokenString);
		match(UNS);
		break;
	case LPAR:
		match(LPAR);
		t->type = Expr_Factor_t;
		t->ep = ExprB();
		match(RPAR);
		break;
	case ID:
		getsym();
		if (TEST(LBRA)) {
			t->type = Array_Factor_t;
			t->idp = IdentB(READPREV);
			match(LBRA);
			t->ep = ExprB();
			match(RBRA);
		} else if (TEST(LPAR)) {
			t->type = Funcall_Factor_t;
			t->fcsp = FcallStmtB();
		} else {
			t->type = Id_Factor_t;
			t->idp = IdentB(READPREV);
		}
		break;
	default:
		--runlevel;
		syntaxError(UNEXPECT, lineno, TRUE, tokenString);
		break;
	}
	return t;
}

/**
 * condition ->
 * 	expression relop expression
 */
CondSP CondB(void)
{
	CondSP t;
	NEWNODE(CondS, t);
	t->lep = ExprB();
	switch (token) {
	case EQU:
		match(EQU);
		t->op = Equ_Rela_t;
		break;
	case LST:
		match(LST);
		t->op = Lst_Rela_t;
		break;
	case LEQ:
		match(LEQ);
		t->op = Leq_Rela_t;
		break;
	case GTT:
		match(GTT);
		t->op = Gtt_Rela_t;
		break;
	case GEQ:
		match(GEQ);
		t->op = Geq_Rela_t;
		break;
	case NEQ:
		match(NEQ);
		t->op = Neq_Rela_t;
		break;
	default:
		--runlevel;
		syntaxError(UNEXPECT, lineno, TRUE, tokenString);
		break;
	}
	t->rep = ExprB();
	return t;
}

/**
 * construct a identifier
 */
IdentSP IdentB(IDREADMODE mode)
{
	IdentSP	t;
	NEWNODE(IdentS, t);
	switch (mode) {
	case READCURR:
		t->type = Init_Ident_t;
		t->val = 0;
		t->length = 0;
		t->line = lineno;
		t->name = copyString(tokenString);
		if (TEST(ID)) {
			match(ID);
		} else {
			--runlevel;
			syntaxError(MISSID, lineno, FALSE, prevTokenString);
		}
		break;
	case READPREV:
		t->type = Init_Ident_t;
		t->val = 0;
		t->length = 0;
		t->line = preTokenLocation;
		t->name = copyString(prevTokenString);
		break;
	default:
		t->name = NULL;
		--runlevel;
		syntaxError(UNEXPECT, lineno, TRUE, tokenString);
		break;
	}
	return t;
}

/**
 * paralist ->
 * 	paradef {; paradef }
 */
ParaListSP ParaListB(void)
{
	ParaListSP t, p, q;
	NEWNODE(ParaListS, t);
	t->pdp = ParaDefB();
	t->next = NULL;
	for (p = t; TEST(SEMI) ; p = q) {
		match(SEMI);
		NEWNODE(ParaListS, q);
		p->next = q;
		q->pdp = ParaDefB();
		q->next = NULL;
	}
	return t;
}

/** 
 * paradef ->
 * 	[VAR] ident {, ident} : basictype
 */
ParaDefSP ParaDefB(void)
{
	ParaDefSP t, p, q;
	BOOL flag; // if TRUE, then call by value
	NEWNODE(ParaDefS, t);
	if (TEST(VAR)) {
		match(VAR);
		flag = FALSE;
	} else flag = TRUE;
	t->idp = IdentB(READCURR);
	t->next = NULL;
	for (p = t; TEST(COMMA); p = q) {
		match(COMMA);
		NEWNODE(ParaDefS, q);
		p->next = q;
		q->idp = IdentB(READCURR);
		q->next = NULL;
	}
	if (TEST(COLON)) {
		match(COLON);
	} else {
		--runlevel;
		syntaxError(MISSCOLON, lineno, FALSE, prevTokenString);
	}
	/* parameter identifier type write back */
	switch (token) {
	case INTEGER:
		match(INTEGER);
		if (flag) {
			for (p = t; p != NULL; p = p->next)
				p->idp->type = Int_Para_Val_Ident_t;
		} else {
			for (p = t; p != NULL; p = p->next)
				p->idp->type = Int_Para_Ref_Ident_t;
		}
		break;
	case CHAR:
		match(CHAR);
		if (flag) {
			for (p = t; p != NULL; p = p->next)
				p->idp->type = Char_Para_Val_Ident_t;
		} else {
			for (p = t; p != NULL; p = p->next)
				p->idp->type = Char_Para_Ref_Ident_t;
		}
		break;
	default:
		--runlevel;
		syntaxError(UNEXPECT, lineno, TRUE, tokenString);
		break;
	}
	return t;
}

/**
 * arglist ->
 * 	argument {, argument}
 *
 * argument -> 
 * 	expression
 */
ArgListSP ArgListB(void)
{
	ArgListSP t, p, q;
	NEWNODE(ArgListS, t);
	t->ep = ExprB();
	t->next = NULL;
	for (p = t; TEST(COMMA); p = q) {
		match(COMMA);
		NEWNODE(ArgListS, q);
		p->next = q;
		q->ep = ExprB();
		q->next = NULL;
	}
	return t;
}


PgmSP parse(void)
{
	token = getToken();
	--runlevel;
	return PgmB();
}
