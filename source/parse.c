#include "common.h"
#include "debug.h"
#include "error.h"
#include "gen.h"
#include "global.h"
#include "parse.h"
#include "scan.h"
#include "util.h"
#include "lexical.h"
#include "syntax.h"
#include <stdio.h>

// AST
pgm_node_t *ast;
int nidcnt = 0;

// current token
static token_t currtok;
// hold previous token
static token_t prevtok;
static char prevtokbuf[MAXTOKENSIZE + 1];
static int prevlineno;

// match an expected token, and skip to next token
static void match(token_t expected)
{
	// check if token matched
	if (currtok != expected) {
		char buf[1024];
		sprintf(buf, "UNEXPECTED_TOKEN: LINE%d [%s]", lineno, tokbuf);
		panic(buf);
	}

	// store previous token
	strncpy(prevtokbuf, tokbuf, MAXTOKENSIZE);
	prevtok = currtok;
	prevlineno = toklineno;

	// read next token
	currtok = gettok();
}

/**
 * program ->
 *	block .
 */
static pgm_node_t *parse_pgm(void)
{
	pgm_node_t *t;
	NEWNODE(pgm_node_t, t);

	// setup entrypoint
	ident_node_t *entry;
	NEWNODE(ident_node_t, entry);
	entry->kind = INT_FUN_IDENT;
	entry->value = 0;
	entry->length = 0;
	entry->line = lineno;
	entry->name = MAINFUNC;
	t->entry = entry;

	t->bp = parse_block();
	match(SS_DOT);
	return t;
}

/**
 * block ->
 *	[constdec] [vardec] [pfdeclist] compstmt
 */
static block_node_t *parse_block(void)
{
	block_node_t *t;
	NEWNODE(block_node_t, t);

	if (CURRTOK_ANY(KW_CONST)) {
		t->cdp = parse_const_dec();
	}

	if (CURRTOK_ANY(KW_VAR)) {
		t->vdp = parse_var_dec();
	}

	if (CURRTOK_ANY2(KW_FUNCTION, KW_PROCEDURE)) {
		t->pfdlp = parse_pf_dec_list();
	}

	if (CURRTOK_ANY(KW_BEGIN)) {
		t->csp = parse_comp_stmt();
	}

	return t;
}

/**
 * constdec ->
 *	CONST constdef {, constdef};
 */
static const_dec_node_t *parse_const_dec(void)
{
	const_dec_node_t *t, *p, *q;
	NEWNODE(const_dec_node_t, t);

	match(KW_CONST);
	t->cdp = parse_const_def();

	for (p = t; CURRTOK_ANY(SS_COMMA); p = q) {
		match(SS_COMMA);
		NEWNODE(const_dec_node_t, q);
		p->next = q;
		q->cdp = parse_const_def();
	}
	match(SS_SEMI);

	return t;
}

/**
 * constdef ->
 *	ident = const
 */
static const_def_node_t *parse_const_def(void)
{
	const_def_node_t *t;
	NEWNODE(const_def_node_t, t);

	if (CURRTOK_ANY(MC_ID)) {
		t->idp = parse_ident(READCURR);
	}

	match(SS_EQU);

	if (CURRTOK_ANY4(SS_PLUS, SS_MINUS, MC_UNS, MC_CH)) {
		switch (currtok) {
		case SS_PLUS:
			match(SS_PLUS);
			t->idp->kind = INT_CONST_IDENT;
			t->idp->value = atoi(tokbuf);
			match(MC_UNS);
			break;
		case SS_MINUS:
			match(SS_MINUS);
			t->idp->kind = INT_CONST_IDENT;
			t->idp->value = -atoi(tokbuf);
			match(MC_UNS);
			break;
		case MC_UNS:
			t->idp->kind = INT_CONST_IDENT;
			t->idp->value = atoi(tokbuf);
			match(MC_UNS);
			break;
		case MC_CH:
			t->idp->kind = CHAR_CONST_IDENT;
			t->idp->value = (int)tokbuf[0];
			match(MC_CH);
			break;
		default:
			unlikely();
		}
	} else {
		unlikely();
	}

	return t;
}

/**
 * vardec ->
 *	VAR vardef; { vardef;}
 */
static var_dec_node_t *parse_var_dec(void)
{
	var_dec_node_t *t, *p, *q;
	NEWNODE(var_dec_node_t, t);

	match(KW_VAR);
	t->vdp = parse_var_def();
	match(SS_SEMI);

	for (p = t; CURRTOK_ANY(MC_ID); p = q) {
		NEWNODE(var_dec_node_t, q);
		p->next = q;
		q->vdp = parse_var_def();
		match(SS_SEMI);
	}

	return t;
}

/**
 * vardef ->
 *	ident {, ident} : type
 */
static var_def_node_t *parse_var_def(void)
{
	var_def_node_t *t, *p, *q;
	NEWNODE(var_def_node_t, t);

	int arrlen = 0;
	t->idp = parse_ident(READCURR);

	for (p = t; CURRTOK_ANY(SS_COMMA); p = q) {
		match(SS_COMMA);
		NEWNODE(var_def_node_t, q);
		p->next = q;
		q->idp = parse_ident(READCURR);
	}

	match(SS_COLON);

	switch (currtok) {
	case KW_INTEGER:
		match(KW_INTEGER);
		for (p = t; p; p = p->next) {
			p->idp->kind = INT_VAR_IDENT;
		}
		break;
	case KW_CHAR:
		match(KW_CHAR);
		for (p = t; p; p = p->next) {
			p->idp->kind = CHAR_VAR_IDENT;
		}
		break;
	case KW_ARRAY: // array[10] of integer
		match(KW_ARRAY);
		match(SS_LBRA);
		if (CURRTOK_ANY(MC_UNS)) {
			arrlen = atoi(tokbuf);
			match(MC_UNS);
		} else {
			unlikely();
		}
		match(SS_RBRA);
		match(KW_OF);
		if (CURRTOK_ANY(KW_INTEGER)) {
			match(KW_INTEGER);
			for (p = t; p; p = p->next) {
				p->idp->kind = INT_ARRVAR_IDENT;
				p->idp->length = arrlen;
			}
		} else if (CURRTOK_ANY(KW_CHAR)) {
			match(KW_CHAR);
			for (p = t; p; p = p->next) {
				p->idp->kind = CHAR_ARRVAR_IDENT;
				p->idp->length = arrlen;
			}
		} else {
			unlikely();
		}
		break;
	default:
		unlikely();
	}

	return t;
}

/**
 * pfdeclist ->
 *	{ procdec | fundec }
 */
static pf_dec_list_node_t *parse_pf_dec_list(void)
{
	pf_dec_list_node_t *t, *p, *q;

	for (p = t = NULL; CURRTOK_ANY2(KW_FUNCTION, KW_PROCEDURE); p = q) {
		NEWNODE(pf_dec_list_node_t, q);
		if (p == NULL) {
			t = q;
		} else {
			p->next = q;
		}
		switch (currtok) {
		case KW_PROCEDURE:
			q->type = PROC_PFDEC;
			q->pdp = parse_proc_dec();
			break;
		case KW_FUNCTION:
			q->type = FUN_PFDEC;
			q->fdp = parse_fun_dec();
			break;
		default:
			unlikely();
		}
	}

	return t;
}

/**
 * procdec ->
 *	procdef {; procdef};
 */
static proc_dec_node_t *parse_proc_dec(void)
{
	proc_dec_node_t *t, *p, *q;
	NEWNODE(proc_dec_node_t, t);

	t->pdp = parse_proc_def();
	match(SS_SEMI);

	for (p = t; CURRTOK_ANY(KW_PROCEDURE); p = q) {
		NEWNODE(proc_dec_node_t, q);
		p->next = q;
		q->pdp = parse_proc_def();
		match(SS_SEMI);
	}

	return t;
}

/**
 * procdef ->
 *	prochead block
 */
static proc_def_node_t *parse_proc_def(void)
{
	proc_def_node_t *t;
	NEWNODE(proc_def_node_t, t);
	t->php = parse_proc_head();
	t->bp = parse_block();
	return t;
}

/**
 * prochead ->
 *	PROCEDURE ident '(' [paralist] ')' ;
 */
static proc_head_node_t *parse_proc_head(void)
{
	proc_head_node_t *t;
	NEWNODE(proc_head_node_t, t);

	match(KW_PROCEDURE);
	t->idp = parse_ident(READCURR);
	t->idp->kind = PROC_IDENT;

	match(SS_LPAR);
	if (CURRTOK_ANY2(KW_VAR, MC_ID)) {
		t->plp = parse_para_list();
	}
	match(SS_RPAR);
	match(SS_SEMI);

	return t;
}

/**
 * fundec ->
 *	fundef {; fundef};
 */
static fun_dec_node_t *parse_fun_dec(void)
{
	fun_dec_node_t *t, *p, *q;
	NEWNODE(fun_dec_node_t, t);

	t->fdp = parse_fun_def();
	match(SS_SEMI);

	for (p = t; CURRTOK_ANY(KW_FUNCTION); p = q) {
		NEWNODE(fun_dec_node_t, q);
		p->next = q;
		q->fdp = parse_fun_def();
		match(SS_SEMI);
	}

	return t;
}

/**
 * fundef ->
 *	funhead block
 */
static fun_def_node_t *parse_fun_def(void)
{
	fun_def_node_t *t;
	NEWNODE(fun_def_node_t, t);

	t->fhp = parse_fun_head();
	t->bp = parse_block();

	return t;
}

/**
 * funhead ->
 *	FUNCTION ident '(' [paralist] ')' : basictype ;
 */
static fun_head_node_t *parse_fun_head(void)
{
	fun_head_node_t *t;
	NEWNODE(fun_head_node_t, t);

	match(KW_FUNCTION);
	t->idp = parse_ident(READCURR);
	match(SS_LPAR);
	if (CURRTOK_ANY2(KW_VAR, MC_ID)) {
		t->plp = parse_para_list();
	} else {
		unlikely();
	}
	match(SS_RPAR);
	match(SS_COLON);

	switch (currtok) {
	case KW_INTEGER:
		match(KW_INTEGER);
		t->idp->kind = CHAR_FUN_IDENT;
		break;
	case KW_CHAR:
		match(KW_CHAR);
		t->idp->kind = CHAR_FUN_IDENT;
		break;
	default:
		unlikely();
	}
	match(SS_SEMI);

	return t;
}

/**
 * statement ->
 *	assignstmt | ifstmt | repeatstmt | Pcallstmt | compstmt
 *		readstmt | writestmt | forstmt | nullstmt
 */
static stmt_node_t *parse_stmt(void)
{
	stmt_node_t *t;
	NEWNODE(stmt_node_t, t);

	switch (currtok) {
	case KW_IF:
		t->type = IF_STMT;
		t->ifp = parse_if_stmt();
		break;
	case KW_REPEAT:
		t->type = REPEAT_STMT;
		t->rpp = parse_repe_stmt();
		break;
	case KW_BEGIN:
		t->type = COMP_STMT;
		t->cpp = parse_comp_stmt();
		break;
	case KW_READ:
		t->type = READ_STMT;
		t->rdp = parse_read_stmt();
		break;
	case KW_WRITE:
		t->type = WRITE_STMT;
		t->wtp = parse_write_stmt();
		break;
	case KW_FOR:
		t->type = FOR_STMT;
		t->frp = parse_for_stmt();
		break;
	case MC_ID:
		match(MC_ID);
		if (CURRTOK_ANY(SS_LPAR)) {
			t->type = PCALL_STMT;
			t->pcp = parse_pcall_stmt();
		} else if (CURRTOK_ANY2(SS_ASGN, SS_LBRA)) {
			t->type = ASSGIN_STMT;
			t->asp = parse_assign_stmt();
		} else if (CURRTOK_ANY(SS_EQU)) {
			t->type = ASSGIN_STMT;
			t->asp = parse_assign_stmt();
			rescue(ERRTOK, "L%d: bad token, = may be :=", lineno);
		} else {
			unlikely();
		}
		break;
	default:
		t->type = NULL_STMT;
		break;
	}

	return t;
}

/**
 * remember in the statement build function
 * we have read the token from ident to := or '['
 *
 * assignstmt ->
 *	ident := expression | funident := expression
 *		| ident '[' expression ']' := expression
 */
static assign_stmt_node_t *parse_assign_stmt(void)
{
	assign_stmt_node_t *t;
	NEWNODE(assign_stmt_node_t, t);

	switch (currtok) {
	case SS_ASGN:
		t->type = NORM_ASSGIN;
		t->idp = parse_ident(READPREV);
		match(SS_ASGN);
		t->lep = NULL;
		t->rep = parse_expr();
		break;
	case SS_LBRA:
		t->type = ARRAY_ASSGIN;
		t->idp = parse_ident(READPREV);
		match(SS_LBRA);
		t->lep = parse_expr();
		match(SS_RBRA);
		match(SS_ASGN);
		t->rep = parse_expr();
		break;
	case SS_EQU: // bad case
		t->type = NORM_ASSGIN;
		t->idp = parse_ident(READPREV);
		match(SS_EQU);
		t->lep = NULL;
		t->rep = parse_expr();
		break;
	default:
		unlikely();
	}

	return t;
}

/**
 * ifstmt ->
 *	IF condition THEN statement |
 *		IF condition THEN statement ELSE statement
 */
static if_stmt_node_t *parse_if_stmt(void)
{
	if_stmt_node_t *t;
	NEWNODE(if_stmt_node_t, t);

	match(KW_IF);
	t->cp = parse_cond();

	match(KW_THEN);
	t->tp = parse_stmt();

	if (CURRTOK_ANY(KW_ELSE)) {
		match(KW_ELSE);
		t->ep = parse_stmt();
	}

	return t;
}

/**
 * repeatstmt ->
 *	REPEAT statement UNTIL condition
 */
static repe_stmt_node_t *parse_repe_stmt(void)
{
	repe_stmt_node_t *t;
	NEWNODE(repe_stmt_node_t, t);

	t->sp = parse_stmt();
	match(KW_UNTIL);
	t->cp = parse_cond();

	return t;
}

/**
 * forstmt ->
 *	FOR ident := expression ( TO | DOWNTO ) expression DO statement
 */
static for_stmt_node_t *parse_for_stmt(void)
{
	for_stmt_node_t *t;
	NEWNODE(for_stmt_node_t, t);

	match(KW_FOR);
	t->idp = parse_ident(READCURR);
	match(SS_ASGN);

	t->lep = parse_expr();

	switch (currtok) {
	case KW_TO:
		match(KW_TO);
		t->type = TO_FOR;
		break;
	case KW_DOWNTO:
		match(KW_DOWNTO);
		t->type = DOWNTO_FOR;
		break;
	default:
		unlikely();
	}

	t->rep = parse_expr();
	match(KW_DO);
	t->sp = parse_stmt();

	return t;
}

/**
 * remember in the statement build function
 * we have read the token from ident to (
 *
 * pcallstmt ->
 *	ident '(' [arglist] ')'
 */
static pcall_stmt_node_t *parse_pcall_stmt(void)
{
	pcall_stmt_node_t *t;
	NEWNODE(pcall_stmt_node_t, t);

	t->idp = parse_ident(READPREV);
	match(SS_LPAR);

	if (CURRTOK_ANY5(MC_ID, SS_PLUS, SS_MINUS, MC_UNS, SS_LPAR)) {
		t->alp = parse_arg_list();
	}
	match(SS_RPAR);

	return t;
}

/**
 * remember in the factor build function
 * we have read the token from ident to (
 *
 * fcallstmt ->
 *	ident '(' [arglist] ')'
 */
static fcall_stmt_node_t *parse_fcall_stmt(void)
{
	fcall_stmt_node_t *t;
	NEWNODE(fcall_stmt_node_t, t);
	t->idp = parse_ident(READPREV);
	match(SS_LPAR);

	if (CURRTOK_ANY5(MC_ID, SS_PLUS, SS_MINUS, MC_UNS, SS_LPAR)) {
		t->alp = parse_arg_list();
	}
	match(SS_RPAR);

	return t;
}

/**
 * compstmt ->
 *	BEGIN statement {; statement} END
 */
static comp_stmt_node_t *parse_comp_stmt(void)
{
	comp_stmt_node_t *t, *p, *q;
	NEWNODE(comp_stmt_node_t, t);
	match(KW_BEGIN);
	t->sp = parse_stmt();

	for (p = t; CURRTOK_ANY(SS_SEMI); p = q) {
		match(SS_SEMI);
		NEWNODE(comp_stmt_node_t, q);
		p->next = q;
		q->sp = parse_stmt();
	}

	match(KW_END);

	return t;
}

/**
 * readstmt ->
 *	READ '(' ident {, ident} ')'
 */
static read_stmt_node_t *parse_read_stmt(void)
{
	read_stmt_node_t *t, *p, *q;
	NEWNODE(read_stmt_node_t, t);

	match(KW_READ);
	match(SS_LPAR);
	t->idp = parse_ident(READCURR);
	for (p = t; CURRTOK_ANY(SS_COMMA); p = q) {
		match(SS_COMMA);
		NEWNODE(read_stmt_node_t, q);
		p->next = q;
		q->idp = parse_ident(READCURR);
	}
	match(SS_RPAR);

	return t;
}

/**
 * writestmt ->
 *	WRITE '(' string, expression ')' | WRITE '(' string ')' |
 *		WRITE '(' expression ')'
 */
static write_stmt_node_t *parse_write_stmt(void)
{
	write_stmt_node_t *t;
	NEWNODE(write_stmt_node_t, t);

	match(KW_WRITE);
	match(SS_LPAR);
	if (CURRTOK_ANY(MC_STR)) {
		t->type = STR_WRITE;
		t->sp = dupstr(tokbuf);
		match(MC_STR);
	} else if (CURRTOK_ANY5(MC_ID, SS_PLUS, SS_MINUS, MC_UNS, SS_LPAR)) {
		t->type = ID_WRITE;
		t->ep = parse_expr();
	} else {
		unlikely();
	}
	if (CURRTOK_ANY(SS_COMMA) && t->type == STR_WRITE) {
		match(SS_COMMA);
		t->type = STRID_WRITE;
		t->ep = parse_expr();
	}
	match(SS_RPAR);

	return t;
}

/**
 * expression ->
 *	[+|-] term { addop term }
 */
static expr_node_t *parse_expr(void)
{
	expr_node_t *t, *p, *q;
	NEWNODE(expr_node_t, t);

	// left-most part
	switch (currtok) {
	case SS_PLUS:
		match(SS_PLUS);
		t->op = ADD_ADDOP;
		t->tp = parse_term();
		break;
	case SS_MINUS:
		match(SS_MINUS);
		t->op = NEG_ADDOP;
		t->tp = parse_term();
		break;
	case MC_ID:
	case MC_UNS:
	case SS_LPAR:
		t->op = NOP_ADDOP;
		t->tp = parse_term();
		break;
	default:
		unlikely();
	}

	// reminder part
	for (p = t; CURRTOK_ANY2(SS_PLUS, SS_MINUS); p = q) {
		NEWNODE(expr_node_t, q);
		p->next = q;
		switch (currtok) {
		case SS_PLUS:
			match(SS_PLUS);
			q->op = ADD_ADDOP;
			q->tp = parse_term();
			break;
		case SS_MINUS:
			match(SS_MINUS);
			q->op = NEG_ADDOP;
			q->tp = parse_term();
			break;
		default:
			unlikely();
		}
	}

	return t;
}

/**
 * term ->
 *	factor { multop factor}
 */
static term_node_t *parse_term(void)
{
	term_node_t *t, *p, *q;
	NEWNODE(term_node_t, t);

	t->op = NOP_MULTOP;
	t->fp = parse_factor();

	for (p = t; CURRTOK_ANY2(SS_STAR, SS_OVER); p = q) {
		NEWNODE(term_node_t, q);
		p->next = q;
		switch (currtok) {
		case SS_STAR:
			match(SS_STAR);
			q->op = MULT_MULTOP;
			q->fp = parse_factor();
			break;
		case SS_OVER:
			match(SS_OVER);
			q->op = DIV_MULTOP;
			q->fp = parse_factor();
			break;
		default:
			unlikely();
		}
	}

	return t;
}

/**
 * factor ->
 *	ident | ident '[' expression ']' | unsign
 *		| '(' expression ')' | fcallstmt
 */
static factor_node_t *parse_factor(void)
{
	factor_node_t *t;
	NEWNODE(factor_node_t, t);

	switch (currtok) {
	case MC_UNS:
		t->type = UNSIGN_FACTOR;
		t->usi = atoi(tokbuf);
		match(MC_UNS);
		break;
	case SS_LPAR:
		match(SS_LPAR);
		t->type = EXPR_FACTOR;
		t->ep = parse_expr();
		match(SS_RPAR);
		break;
	case MC_ID:
		match(MC_ID);
		if (CURRTOK_ANY(SS_LBRA)) {
			t->type = ARRAY_FACTOR;
			t->idp = parse_ident(READPREV);
			match(SS_LBRA);
			t->ep = parse_expr();
			match(SS_RBRA);
		} else if (CURRTOK_ANY(SS_LPAR)) {
			t->type = FUNCALL_FACTOR;
			t->fcsp = parse_fcall_stmt();
		} else {
			t->type = ID_FACTOR;
			t->idp = parse_ident(READPREV);
		}
		break;
	default:
		unlikely();
	}

	return t;
}

/**
 * condition ->
 *	expression relop expression
 */
static cond_node_t *parse_cond(void)
{
	cond_node_t *t;
	NEWNODE(cond_node_t, t);

	t->lep = parse_expr();
	switch (currtok) {
	case SS_EQU:
		match(SS_EQU);
		t->op = EQU_RELA;
		break;
	case SS_LST:
		match(SS_LST);
		t->op = LST_RELA;
		break;
	case SS_LEQ:
		match(SS_LEQ);
		t->op = LEQ_RELA;
		break;
	case SS_GTT:
		match(SS_GTT);
		t->op = GTT_RELA;
		break;
	case SS_GEQ:
		match(SS_GEQ);
		t->op = GEQ_RELA;
		break;
	case SS_NEQ:
		match(SS_NEQ);
		t->op = NEQ_RELA;
		break;
	default:
		unlikely();
	}
	t->rep = parse_expr();

	return t;
}

/**
 * construct a identifier
 */
static ident_node_t *parse_ident(idreadmode_t mode)
{
	ident_node_t *t;
	NEWNODE(ident_node_t, t);

	switch (mode) {
	case READCURR:
		t->kind = INIT_IDENT;
		t->value = 0;
		t->length = 0;
		t->line = lineno;
		t->name = dupstr(tokbuf);
		match(MC_ID);
		break;
	case READPREV:
		t->kind = INIT_IDENT;
		t->value = 0;
		t->length = 0;
		t->line = prevlineno;
		t->name = dupstr(prevtokbuf);
		break;
	default:
		unlikely();
	}
	return t;
}

/**
 * paralist ->
 *	paradef {; paradef }
 */
static para_list_node_t *parse_para_list(void)
{
	para_list_node_t *t, *p, *q;
	NEWNODE(para_list_node_t, t);

	t->pdp = parse_para_def();
	for (p = t; CURRTOK_ANY(SS_SEMI); p = q) {
		match(SS_SEMI);
		NEWNODE(para_list_node_t, q);
		p->next = q;
		q->pdp = parse_para_def();
	}

	return t;
}

/**
 * paradef ->
 *	[VAR] ident {, ident} : basictype
 */
static para_def_node_t *parse_para_def(void)
{
	para_def_node_t *t, *p, *q;
	NEWNODE(para_def_node_t, t);

	// VAR mean call by reference
	bool byref = FALSE;
	if (CURRTOK_ANY(KW_VAR)) {
		byref = TRUE;
		match(KW_VAR);
	}

	t->idp = parse_ident(READCURR);

	for (p = t; CURRTOK_ANY(SS_COMMA); p = q) {
		match(SS_COMMA);
		NEWNODE(para_def_node_t, q);
		p->next = q;
		q->idp = parse_ident(READCURR);
	}
	match(SS_COLON);

	switch (currtok) {
	case KW_INTEGER:
		match(KW_INTEGER);
		for (p = t; p; p = p->next) {
			p->idp->kind =
				byref ? INT_BYADR_IDENT : INT_BYVAL_IDENT;
		}
		break;
	case KW_CHAR:
		match(KW_CHAR);
		for (p = t; p; p = p->next) {
			p->idp->kind =
				byref ? CHAR_BYADR_IDENT : CHAR_BYVAL_IDENT;
		}
		break;
	default:
		unlikely();
	}

	return t;
}

/**
 * arglist ->
 *	argument {, argument}
 *
 * argument ->
 *	expression
 */
static arg_list_node_t *parse_arg_list(void)
{
	arg_list_node_t *t, *p, *q;
	NEWNODE(arg_list_node_t, t);

	t->ep = parse_expr();

	for (p = t; CURRTOK_ANY(SS_COMMA); p = q) {
		match(SS_COMMA);
		NEWNODE(arg_list_node_t, q);
		p->next = q;
		q->ep = parse_expr();
	}

	return t;
}

pgm_node_t *parse(void)
{
	currtok = gettok();
	ast = parse_pgm();
	chkerr("parse fail and exit.");
	phase = SEMANTIC;
	fclose(source);
	return ast;
}
