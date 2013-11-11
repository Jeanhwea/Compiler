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
static TokenType prevToken;

static PgmSP PgmB(void);
static BlokSP BlokB(void);
static ConstDecSP ConstDecB(void);
static ConstDefSP ConstDefB(void);
static VarDecSP VarDecB(void);
static VarDefSP VarDefB(void);
static PFDecListSP PFDecListB(void);
static ProcDecSP ProcDecB(void);
static ProcSP ProcB(void);
static ProcHeadSP ProcHeadB(void);
static FunDecSP FunDecB(void);
static FunSP FunB(void);
static FunHeadSP FunHeadB(void);
static StmtSP StmtB(void);
static AssignstmtSP AssignstmtB(void);
static IfstmtSP IfstmtB(void);
static RepestmtSP RepestmtB(void);
static ForstmtSP ForstmtB(void);
static PcallstmtSP PcallstmtB(void);
static FcallstmtSP FcallstmtB(void);
static CompstmtSP CompstmtB(void);
static ReadstmtSP ReadstmtB(void);
static WritestmtSP WritestmtB(void);
static ExprSP ExprB(void);
static TermSP TermB(void);
static FactorSP FactorB(void);
static ConstSP ConstB(void);
static VarSP VarB(void);
static IdentSP IdentB(IDREADMODE);
static CondSP CondB(void);
static ParalistSP ParalistB(void);
static ParaSP ParaB(void);
static ArglistSP ArglistB(void);

static inline void getsym(void)
{
	/* store current token type and token string */
	strncpy(prevTokenString, tokenString, MAXTOKENSIZE);
	prevToken = token;
	/* get next token */
	getToken();
}

static inline BOOL match(TokenType expected)
{
	if (TEST(expected)) {
		token = getsym();
		return TRUE;
	} else {
		return FALSE;
	}
}

/** the same as macro TEST 
 *  however, it dealing with more parameter
 */
static inline BOOL test(int n, ...)
{
	int i = 0;
	TokenType tokToTest;
	BOOL r = FALSE;
	va_list = vl;
	va_start(vl, n);
	do {
		tokToTest = va_arg(vl, TokenType);
		if (tokToTest == token) {
			r = TRUE;
			break;
		}
		++i;
	} while (i < n);
	va_end(vl);
	return r;
}
/**
 * program ->
 * 	block .
 */
PgmSP PgmB(void)
{
	PgmSP t;
	MALLOC(PgmS, t);
	t->blockp = Blok();
	if (!match(DOT)) {
		syntaxError(MISSDOT);
	}
	return t;
}

/**
 * block ->
 * 	[constdec] [vardec] [pfdeclist] compstmt
 */
BlokSP BlokB(void)
{
	BlokSP t;
	MALLOC(BlokS, t);
	if (TEST(CONST)) {
		t->constdecp = ConstDecB();
	} else t->constdecp = NULL;

	if (TEST(VAR)) {
		t->vardecp = VarDecB();
	} else t->vardecp = NULL;
	
	if (test(2, FUNCTION, PROCEDURE)) {
		t->pflistp = PFDecListB();
	} else t->pflistp = NULL;
	
	t->compstmtp = CompstmtB();
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
	MALLOC(ConstDecS, t);
	t->constdefp = ConstDefB();
	t->head = t;
	t->next = NULL;
	for (p = t; TEST(COMMA); p = q) {
		match(COMMA);
		MALLOC(ConstDecS, q);
		p->next = q;
		q->constdecp = ConstDefB();
		q->head = t;
		q->next = NULL;
	}
	match(SEMI);
	return t;
}

/**
 * constdef ->
 * 	ident = const 
 */
ConstDefSP ConstDefB(void)
{
	ConstDecSP t;
	MALLOC(ConstDecS, t);
	if (TEST(ID)) {
		t->identp = IdentB(READCURR);
	} else t->identp = NULL;
	match(EQU);
	if (TEST(CONST)) {
		t->constp = ConstB();
	} else t->constp = NULL;
	return t;
}

/**
 * vardec ->
 * 	VAR vardef; { vardef;}
 */
VarDecSP VarDecB(void)
{
	VarDecSP t, p, q;
	match(VAR);
	MALLOC(VarDecS, t);
	t->vardefp = VarDefB();
	t->head = t;
	t->next = NULL;
	match(SEMI);
	for (p = t; TEST(ID); p = q) {
		MALLOC(VarDecS, q);
		p->next = q;
		q->vardefp = VarDefB();
		q->head = t;
		q->next = NULL;
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
	MALLOC(VarDefS, t);
	t->varp = VarB();
	t->head = t;
	t->next = NULL;
	for (p = t; TEST(COMMA); p = q) {
		match(COMMA);
		MALLOC(VarDefS, q);
		p->next = q;
		q->varp = VarB();
		q->head = t;
		q->next = NULL;
	}
	match(COLON);
	/* do type check and type write back */
	switch (token) {
	case INTEGER:
		match(INTEGER);
		break;
	case CHAR:
		match(CHAR);
		for (p = t; p != NULL; p = p->next) 
			p->varp->type = Char_Var_t;
		break;
	case ARRAY:
		match(ARRAY);
		match(LBRA);
		arraylength = atoi(tokenString);
		match(RBRA);
		match(OF);
		switch (token) {
		case INTEGER: 
			match(INTEGER);
			for (p = t; p != NULL; p = p->next) {
				p->varp->type = IntArr_Var_t;
				p->varp->length = arraylength;
			}
			break;
		case CHAR: 
			match(CHAR);
			for (p = t; p != NULL; p = p->next) {
				p->varp->type = CharArr_Var_t;
				p->varp->length = arraylength;
			}
			break;
		default:
		}
		break;
	default:
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
	MALLOC(PFDecListS, t);
	switch (token) {
	case PROCEDURE:
		t->type = Proc_PFDec_t;
		t->pdecp = ProcDecB();
		t->fdecp = NULL;
		break;
	case FUNCTION:
		t->type = Fun_PFDec_t;
		t->pdecp = NULL;
		t->fdecp = FunDecB();
		break;
	default:
	}
	t->head = t;
	t->next = NULL;
	for (p = t; test(2, FUNCTION, PROCEDURE); p = q) {
		MALLOC(PFDecListS, q);
		p->next = q;
		switch (token) {
		case PROCEDURE:
			q->type = Proc_PFDec_t;
			q->pdecp = ProcDecB();
			q->fdecp = NULL;
			break;
		case FUNCTION:
			q->type = Fun_PFDec_t;
			q->pdecp = NULL;
			q->fdecp = FunDecB();
			break;
		default:
		}
		q->head = t;
		q->next = NULL;
	}
	return t;
}

/**
 * procdec ->
 * 	proc {; proc};
 */
ProcDecSP ProcDecB(void)
{
	ProcDecSP t, p, q;
	MALLOC(ProcDecS, t);
	t->procp = ProcB();
	t->head = t;
	t->next = NULL;
	match(SEMI);
	for (p = t; TEST(PROCEDURE); p = q) {
		MALLOC(ProcDecS, q);
		p->next = q;
		q->procp = ProcB();
		q->head = t;
		q->next = NULL;
		match(SEMI);
	}
	return t;
}

/**
 * proc ->
 * 	prochead block
 */
ProcSP ProcB(void)
{
	ProcSP t;
	MALLOC(ProcS, t);
	t->procheadp = ProcHeadB();
	t->blockp = BlokB();
	return t;
}

/** 
 * prochead ->
 * 	PROCEDURE ident '(' [paralist] ')' ;
 */
ProcHeadSP ProcHeadB(void)
{
	ProcHeadSP t;
	match(PROCEDURE);
	t->identp = IdentB(READCURR);
	match(LPAR);
	if (test(2, VAR, ID))
		t->paralistp = ParalistB();
	else t->paralistp = NULL;
	match(RPAR);
	match(SEMI);
	return t;
}

/**
 * fundec ->
 * 	fun {; fun};
 */
FunDecSP FunDecB(void)
{
	FunDecSP t;
	MALLOC(FunDecS, t);
	t->funp = FunB();
	t->head = t;
	t->next = NULL;
	match(SEMI);
	for (p = t; TEST(FUNCTION); p = q) {
		MALLOC(FunDecS, q);
		p->next =  q;
		q->funp = FunB();
		q->head = t;
		q->next = NULL;
		match(SEMI);
	}
	return t;
}

/**
 * fun -> 
 * 	funhead block
 */
FunSP FunB(void)
{
	FunSP t;
	MALLOC(FunS, t);
	t->funheadp = FunHeadB();
	t->blockp = BlokB();
	return t;
}

/**
 * funhead ->
 * 	FUNCTION ident '(' [paralist] ')' : basictype ;
 */
FunHeadSP FunHeadB(void)
{
	FunHeadSP t;
	MALLOC(FunHeadS, t);
	match(FUNCTION);
	t->identp = IdentB(READCURR);
	match(LPAR);
	if (test(2, VAR, ID))
		t->paralistp = ParalistB();
	else t->paralistp = NULL;
	match(RPAR);
	match(COLON);
	switch (token) {
	case INTEGER:
		match(INTEGER);
		t->rettype = Int_Funret_t;
		break;
	case CHAR:
		match(CHAR);
		t->rettype = Char_Funret_t;
		break;
	default:
	}
	match(SEMI);
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
	MALLOC(StmtS, t);
	t->assignp = NULL;
	t->ifp = NULL;
	t->repep = NULL;
	t->forp = NULL;
	t->pcallp = NULL;
	t->compp = NULL;
	t->readp = NULL;
	t->writep = NULL;
	switch (token) {
	case IF:
		t->type = IF_Statement_t;
		t->ifp = IfstmtB();
		break;
	case REPEAT:
		t->type = Repeat_Statement_t;
		t->repep = RepestmtB();
		break;
	case BEGIN:
		t->type = Comp_Statement_t;
		t->compp = CompstmtB();
		break;
	case READ:
		t->type = Read_Statement_t;
		t->readp = ReadstmtB();
		break;
	case WRITE:
		t->type = Write_Statement_t;
		t->writep = WritestmtB();
		break;
	case FOR:
		t->type = For_Statement_t;
		t->forp = ForstmtB();
		break;
	case ID:
		getsym();
		if (TEST(LPAR)) {	
			t->type = Pcall_Statement_t;
			t->pcallp = PcallstmtB();
		} else if (test(2, ASSIGN, LBRA)) {
			t->type = Assgin_Statement_t;
			t->assignp = AssignstmtB();
		} else {

		}
		break;
	default:
		t->type = Null_Statement_t;
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
AssignstmtSP AssignstmtB(void)
{
	AssignstmtSP t;
	MALLOC(AssignstmtS, t);
	switch (token) {
	case ASSIGN:
		t->type = Norm_Assgin_t;
		t->idp = IdentB(READPREV);
		match(ASSIGN);
		t->lexprp = NULL;
		t->rexprp = ExprB();
		break;
	case LBRA:
		t->type = Array_Assgin_t;
		t->idp = IdentB(READPREV);
		match(LBRA);
		t->lexprp = ExprB();
		match(RBRA);
		match(ASSIGN);
		t->rexprp = ExprB();
		break;
	default:
	}
	return t;
}

/**
 * ifstmt ->
 * 	IF condition THEN statement |
 * 		IF condition THEN statement ELSE statement
 */
IfstmtSP IfstmtB(void)
{
	IfstmtSP t;
	MALLOC(IfstmtS, t);
	match(IF);
	t->condp = CondB();
	match(THEN);
	t->thenp = StmtB();
	if (TEST(ELSE)) {
		t->elsep = StmtB();
	} else t->elsep = NULL;
	return t;
}

/**
 * repeatstmt ->
 * 	REPEAT statement UNTIL condition
 */
RepestmtSP RepestmtB(void)
{
	RepestmtSP t;
	MALLOC(RepestmtS, t);
	match(REPEAT);
	t->stmtp = StmtB();
	match(UNTIL);
	t->condp = CondB();
	return t;
}

/**
 * forstmt ->
 * 	FOR ident := expression ( TO | DOWNTO ) expression DO statement
 */
ForstmtSP ForstmtB(void)
{
	ForstmtSP t;
	MALLOC(ForstmtS, t);
	match(FOR);
	t->identp = IdentB(READCURR);
	match(ASSIGN);
	t->lowp = ExprB();
	if (TEST(TO)) {
		match(TO);
		t->type = To_For_t;
	} else if (TEST(DOWNTO)) {
		match(DOWNTO);
		t->type = Downto_For_t;
	} else {

	}
	t->highp = ExprB();
	match(DO);
	t->stmtp = StmtB();
	return t;
}

/**
 * remember in the statement build function 
 * we have read the token from ident to (
 *
 * pcallstmt ->
 * 	ident '(' [arglist] ')'
 */
PcallstmtSP PcallstmtB(void)
{
	PcallstmtSP t;
	MALLOC(PcallstmtS, t);
	t->identp = IdentB(READPREV);
	match(LPAR);
	if (test(5, ID, PLUS, MINUS, UNS, LPAR)) {
		t->arglistp = ArglistB();
	} else t->arglistp = NULL;
	match(RPAR);
	return t;
}

/**
 * remember in the factor build function 
 * we have read the token from ident to (
 *
 * fcallstmt ->
 * 	ident '(' [arglist] ')'
 */
FcallstmtSP FcallstmtB(void)
{
	FcallstmtSP t;
	MALLOC(FcallstmtS, t);
	t->identp = IdentB(READPREV);
	match(LPAR);
	if (test(5, ID, PLUS, MINUS, UNS, LPAR)) {
		t->arglistp = ArglistB();
	} else t->arglistp = NULL;
	match(RPAR);
	return t;
}

/**
 * compstmt ->
 * 	BEGIN statement {; statement} END 
 */
CompstmtSP CompstmtB(void)
{
	CompstmtSP t, p, q;
	MALLOC(CompstmtS, t);
	match(BEGIN);
	t->curr = StmtB();
	t->head = t;
	t->next = NULL;
	for (p = t; TEST(SEMI) ; p = q) {
		match(SEMI);
		MALLOC(CompstmtS, q);
		p->next = q;
		q->curr = StmtB();
		q->head = t;
		q->next = NULL;
	}
	match(END);
	return t;
}

/**
 * readstmt ->
 * 	READ '(' ident {, ident} ')'
 */
ReadstmtSP ReadstmtB(void)
{
	ReadstmtSP t, p, q;
	MALLOC(ReadstmtS, t);
	match(READ);
	match(LPAR);
	t->identp = IdentB(READCURR);
	t->head = t;
	t->next = NULL;
	for (p = t; TEST(COMMA); p = q) {
		match(COMMA);
		MALLOC(ReadstmtS, q);
		p->next = q;
		q->identp = IdentB(READCURR);
		q->head = t;
		q->next = NULL;
	}
	match(RPAR);
	return t;
}

/**
 * writestmt ->
 * 	WRITE '(' string, expression ')' | WRITE '(' string ')' |
 * 		WRITE '(' expression ')'
 */
WritestmtSP WritestmtB(void)
{
	WritestmtSP t;
	MALLOC(WritestmtS, t);
	match(WRITE);
	match(LPAR);
	t->stringp = NULL;
	t->exprp = NULL;
	if (TEST(STRING)) {
		t->type = Str_Write_t;
		copyString(t->stringp, tokenString);
	} else if (test(5, ID, PLUS, MINUS, UNS, LPAR)) {
		t->type = Id_Write_t;
		t->exprp = ExprB();
	} else {
	
	}
	if (TEST(COMMA) && t->type == Str_Write_t) {
		match(COMMA);
		t->type = StrId_Write_t;
		t->exprp = ExprB();
	}
	match(RPAR);
	return t;
}

/**
 * expression ->
 * 	[+|-] term { addop term }
 */
ExprSP ExprB(void)
{
	ExprSP t, p, q;
	MALLOC(ExprS, t);
	switch (token) {
	case PLUS:
		match(PLUS);
		t->op = Add_Addop_t;
		t->termp = TermB();
		break;
	case MINUS:
		match(MINUS);
		t->op = Minus_Addop_t;
		t->termp = TermB();
		break;
	default:
		q->op = Add_Addop_t;
		t->termp = NULL;
	}
	t->head =  t;
	t->next = NULL;
	for (p = t; test(2, PLUS, MINUS); p = q) {
		MALLOC(ExprS, q);
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
			q->op = Add_Addop_t;
			q->termp = NULL;
		}
		q->termp = TermB();
		q->head =  t;
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
	MALLOC(TermS, t);
	t->op = Nop_Multop_t;
	t->factorp = FactorB();
	t->head = t;
	t->next = NULL;
	for (p = t; test(2, STAR, OVER); p = q) {
		MALLOC(TermS, t);
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
		}
		q->factorp = FactorB();
		q->head = t;
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
	MALLOC(FactorS, t);
	t->identp = NULL;
	t->exprp = NULL;
	t->unsignint = 0;
	t->fcallstmtp = NULL;
	switch (token) {
	case UNS:
		t->type = Unsign_Factor_t;
		t->unsignint = atoi(tokenString);
		match(UNS);
		break;
	case LPAR:
		match(LPAR);
		t->type = Expr_Factor_t;
		t->exprp = ExprB();
		break;
	case ID:
		getsym();
		if (TEST(LBRA)) {
			t->type = Array_Factor_t;
			t->identp = IdentB(READPREV);
			match(LBRA);
			t->exprp = ExprB();
			match(RBRA);
		} else if (TEST(LPAR)) {
			t->type = Funcall_Factor_t;
			t->fcallstmtp = FcallstmtB();
		} else {
			t->type = Id_Factor_t;
			t->identp = IdentB(READPREV);
		}
		break;
	default:
	}
	return t;
}

/**
 * const ->
 * 	[+|-] unsign | character
 */
ConstSP ConstB(void)
{
	ConstSP t;
	if (test(2, PLUS, MINUS)) {
		switch (token) {
		case PLUS:
			match(PLUS);
			t->type = Num_Const_t;
			t->value = atoi(tokenString);
			break;
		case MINUS:
			match(MINUS);
			t->type = Num_Const_t;
			t->value = - atoi(tokenString);
			break;
		default:
		}
		match(UNS);
	} else if (TEST(UNS)) {
		t->type = Num_Const_t;
		t->value = atoi(tokenString);
		match(UNS);
	} else if (TEST(CH)) {
		t->type = Char_Const_t;
		t->value = (int) tokenString[1];
		match(CH);
	} else {
	
	}
	return t;
}

/**
 * construct a var
 */
VarSP VarB(void)
{
	VarSP t;
	MALLOC(VarS, t);
	t->type = Int_Var_t;
	t->length = 0;
	t->identp = IdentB(READCURR);
	return t;
}

/**
 * construct a identifier
 */
IdentSP IdentB(IDREADMODE mode)
{
	IdentSP	t;
	MALLOC(IdentS, t);
	t->type = ID_Ident_t;
	switch (mode) {
	case READCURR:
		copyString(t->name, tokenString);
		break;
	case READPREV:
		copyString(t->name, prevTokenString);
		break;
	default:
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
	MALLOC(CondS, t);
	t->lexprp = ExprB();
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
	}
	t->rexprp = ExprB();
	return t;
}

/**
 * paralist ->
 * 	para {; para }
 */
ParalistSP ParalistB(void)
{
	ParalistSP t, p, q;
	MALLOC(ParalistS, t);
	if (TEST(VAR)) 
		match(VAR);
	t->parap = ParaB();
	t->head = t;
	t->next = NULL;
	for (p = t; TEST(SEMI) ; p = q) {
		match(SEMI);
		MALLOC(ParalistS, q);
		p->next = q;
		q->parap = ParaB();
		q->head = t;
		q->next = NULL;
	}
	return t;
}

/** 
 * para ->
 * 	ident {, ident} : basictype
 */
ParaSP ParaB(void)
{
	ParaSP t, p, q;
	MALLOC(ParaS, t);
	t->identp = IdentB(READCURR);
	t->head = t;
	t->next = NULL;
	for (p = t; TEST(COMMA); p = q) {
		match(COMMA);
		MALLOC(ParaS, q);
		p->next = q;
		q->identp = IdentB(READCURR);
		q->head = t;
		q->next = NULL;
	}
	match(COLON);
	/* type write back */
	switch (token) {
	case INTEGER:
		match(INTEGER);
		for (p = t; p != NULL; p = p->next)
			p->identp->type = IntPara_Ident_t;
		break;
	case CHAR:
		match(CHAR);
		for (p = t; p != NULL; p = p->next)
			p->identp->type = CharPara_Ident_t;
		break;
	default:
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
ArglistSP ArglistB(void)
{
	ArglistSP t, p, q;
	MALLOC(ArglistS, t);
	t->argp = ExprB();
	t->head = t;
	t->next = NULL;
	for (p = t; TEST(COMMA); p = q) {
		match(COMMA);
		MALLOC(ArglistS, q);
		p->next = q;
		q->argp = ExprB();
		q->head = t;
		q->next = NULL;
	}
	return t;
}
