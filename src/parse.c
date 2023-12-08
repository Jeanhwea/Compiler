#include "common.h"
#include "debug.h"
#include "global.h"
#include "parse.h"
#include "util.h"
#include "lexical.h"
#include "syntax.h"

// current token
static token_t currtok;
// hold previous token
static token_t prevtok;
static char prevtokbuf[MAXTOKENSIZE + 1];
static int prevlineno;

// match an expected token, and skip to next token
static void match(token_t expected)
{
	// check token
	if (currtok != expected) {
		panic("UNEXPECTED_TOKEN");
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
static pgm_p parse_pgm(void)
{
	pgm_p t;
	INITMEM(pgm, t);

	t->bp = parse_block();
	match(SS_DOT);

	return t;
}

/**
 * block ->
 *	[constdec] [vardec] [pfdeclist] compstmt
 */
static block_p parse_block(void)
{
	block_p t;
	INITMEM(block, t);

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
static const_dec_p parse_const_dec(void)
{
	const_dec_p t, p, q;
	INITMEM(const_dec, t);

	match(KW_CONST);
	t->cdp = parse_const_def();

	for (p = t; CURRTOK_ANY(SS_COMMA); p = q) {
		match(SS_COMMA);
		INITMEM(const_dec, q);
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
static const_def_p parse_const_def(void)
{
	const_def_p t;
	INITMEM(const_def, t);

	if (CURRTOK_ANY(MC_ID)) {
		t->idp = parse_ident(READCURR);
	}

	match(SS_EQU);

	if (CURRTOK_ANY4(SS_PLUS, SS_MINUS, MC_UNS, MC_CH)) {
		switch (currtok) {
		case SS_PLUS:
			match(SS_PLUS);
			t->idp->type = INT_CONST_IDENT;
			t->idp->val = atoi(tokbuf);
			match(MC_UNS);
			break;
		case SS_MINUS:
			match(SS_MINUS);
			t->idp->type = INT_CONST_IDENT;
			t->idp->val = -atoi(tokbuf);
			match(MC_UNS);
			break;
		case MC_UNS:
			t->idp->type = INT_CONST_IDENT;
			t->idp->val = -atoi(tokbuf);
			match(MC_UNS);
			break;
		case MC_CH:
			t->idp->type = CHAR_CONST_IDENT;
			t->idp->val = (int)tokbuf[0];
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
static var_dec_p parse_var_dec(void)
{
	var_dec_p t, p, q;
	INITMEM(var_dec, t);

	match(KW_VAR);
	t->vdp = parse_var_def();
	match(SS_SEMI);

	for (p = t; CURRTOK_ANY(MC_ID); p = q) {
		INITMEM(var_dec, q);
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
static var_def_p parse_var_def(void)
{
	var_def_p t, p, q;
	INITMEM(var_def, t);

	int arrlen = 0;
	t->idp = parse_ident(READCURR);

	for (p = t; CURRTOK_ANY(SS_COMMA); p = q) {
		match(SS_COMMA);
		INITMEM(var_def, q);
		p->next = q;
		q->idp = parse_ident(READCURR);
	}

	match(SS_COLON);

	switch (currtok) {
	case KW_INTEGER:
		match(KW_INTEGER);
		for (p = t; p; p = p->next) {
			p->idp->type = INT_VAR_IDENT;
		}
		break;
	case KW_CHAR:
		match(KW_CHAR);
		for (p = t; p; p = p->next) {
			p->idp->type = INT_VAR_IDENT;
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
				p->idp->type = INTARR_VAR_IDENT;
				p->idp->length = arrlen;
			}
		} else if (CURRTOK_ANY(KW_CHAR)) {
			match(KW_CHAR);
			for (p = t; p; p = p->next) {
				p->idp->type = CHARARR_VAR_IDENT;
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
static pf_dec_list_p parse_pf_dec_list(void)
{
	pf_dec_list_p t, p, q;

	for (p = t = NULL; CURRTOK_ANY2(KW_FUNCTION, KW_PROCEDURE); p = q) {
		INITMEM(pf_dec_list, q);
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
static proc_dec_p parse_proc_dec(void)
{
	proc_dec_p t, p, q;
	INITMEM(proc_dec, t);

	t->pdp = parse_proc_def();
	match(SS_SEMI);

	for (p = t; CURRTOK_ANY(KW_PROCEDURE); p = q) {
		INITMEM(proc_dec, q);
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
static proc_def_p parse_proc_def(void)
{
	proc_def_p t;
	INITMEM(proc_def, t);
	t->php = parse_proc_head();
	t->bp = parse_block();
	return t;
}

/**
 * prochead ->
 *	PROCEDURE ident '(' [paralist] ')' ;
 */
static proc_head_p parse_proc_head(void)
{
	proc_head_p t;
	INITMEM(proc_head, t);

	match(KW_PROCEDURE);
	t->idp = parse_ident(READCURR);
	t->idp->type = PROC_IDENT;

	match(SS_LPAR);
	if (CURRTOK_ANY2(KW_VAR, MC_ID)) {
		t->plp = parse_para_list();
	} else {
		unlikely();
	}
	match(SS_RPAR);
	match(SS_SEMI);

	return t;
}

/**
 * fundec ->
 *	fundef {; fundef};
 */
static fun_dec_p parse_fun_dec(void)
{
	fun_dec_p t, p, q;
	INITMEM(fun_dec, t);

	t->fdp = parse_fun_def();
	match(SS_SEMI);

	for (p = t; CURRTOK_ANY(KW_FUNCTION); p = q) {
		INITMEM(fun_dec, q);
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
static fun_def_p parse_fun_def(void)
{
	fun_def_p t;
	INITMEM(fun_def, t);

	t->fhp = parse_fun_head();
	t->bp = parse_block();

	return t;
}

/**
 * funhead ->
 *	FUNCTION ident '(' [paralist] ')' : basictype ;
 */
static fun_head_p parse_fun_head(void)
{
	fun_head_p t;
	INITMEM(fun_head, t);

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
		t->idp->type = CHAR_FUN_IDENT;
		break;
	case KW_CHAR:
		match(KW_CHAR);
		t->idp->type = CHAR_FUN_IDENT;
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
static stmt_p parse_stmt(void)
{
	stmt_p t;
	INITMEM(stmt, t);

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
static assign_stmt_p parse_assign_stmt(void)
{
	assign_stmt_p t;
	INITMEM(assign_stmt, t);

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
static if_stmt_p parse_if_stmt(void)
{
	if_stmt_p t;
	INITMEM(if_stmt, t);

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
static repe_stmt_p parse_repe_stmt(void)
{
	repe_stmt_p t;
	INITMEM(repe_stmt, t);

	t->sp = parse_stmt();
	match(KW_UNTIL);
	t->cp = parse_cond();

	return t;
}

/**
 * forstmt ->
 *	FOR ident := expression ( TO | DOWNTO ) expression DO statement
 */
static for_stmt_p parse_for_stmt(void)
{
	for_stmt_p t;
	INITMEM(for_stmt, t);

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
static pcall_stmt_p parse_pcall_stmt(void)
{
	pcall_stmt_p t;
	INITMEM(pcall_stmt, t);

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
static fcall_stmt_p parse_fcall_stmt(void)
{
	fcall_stmt_p t;
	INITMEM(fcall_stmt, t);
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
static comp_stmt_p parse_comp_stmt(void)
{
	comp_stmt_p t, p, q;
	INITMEM(comp_stmt, t);
	match(KW_BEGIN);
	t->sp = parse_stmt();

	for (p = t; CURRTOK_ANY(SS_SEMI); p = q) {
		match(SS_SEMI);
		INITMEM(comp_stmt, q);
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
static read_stmt_p parse_read_stmt(void)
{
	read_stmt_p t, p, q;
	INITMEM(read_stmt, t);

	match(KW_READ);
	match(SS_LPAR);
	t->idp = parse_ident(READCURR);
	for (p = t; CURRTOK_ANY(SS_COMMA); p = q) {
		match(SS_COMMA);
		INITMEM(read_stmt, q);
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
static write_stmt_p parse_write_stmt(void)
{
	write_stmt_p t;
	INITMEM(write_stmt, t);

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
static expr_p parse_expr(void)
{
	expr_p t, p, q;
	INITMEM(expr, t);

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

	for (p = t; CURRTOK_ANY2(SS_PLUS, SS_MINUS); p = q) {
		INITMEM(expr, q);
		p->next = q;
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
static term_p parse_term(void)
{
	term_p t, p, q;
	INITMEM(term, t);

	t->op = NOP_MULTOP;
	t->fp = parse_factor();

	for (p = t; CURRTOK_ANY2(SS_STAR, SS_OVER); p = q) {
		INITMEM(term, q);
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
static factor_p parse_factor(void)
{
	factor_p t;
	INITMEM(factor, t);

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
static cond_p parse_cond(void)
{
	cond_p t;
	INITMEM(cond, t);

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
static ident_p parse_ident(idreadmode_t mode)
{
	ident_p t;
	INITMEM(ident, t);

	switch (mode) {
	case READCURR:
		t->type = INIT_IDENT;
		t->val = 0;
		t->length = 0;
		t->line = lineno;
		t->name = dupstr(tokbuf);
		match(MC_ID);
		break;
	case READPREV:
		t->type = INIT_IDENT;
		t->val = 0;
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
static para_list_p parse_para_list(void)
{
	para_list_p t, p, q;
	INITMEM(para_list, t);

	t->pdp = parse_para_def();
	for (p = t; CURRTOK_ANY(SS_SEMI); p = q) {
		match(SS_SEMI);
		INITMEM(para_list, q);
		p->next = q;
		q->pdp = parse_para_def();
	}

	return t;
}

/**
 * paradef ->
 *	[VAR] ident {, ident} : basictype
 */
static para_def_p parse_para_def(void)
{
	para_def_p t, p, q;
	INITMEM(para_def, t);

	// VAR mean call by reference
	bool byref = FALSE;
	if (CURRTOK_ANY(KW_VAR)) {
		byref = TRUE;
		match(KW_VAR);
	}

	t->idp = parse_ident(READCURR);

	for (p = t; CURRTOK_ANY(SS_COMMA); p = q) {
		match(SS_COMMA);
		INITMEM(para_def, q);
		p->next = q;
		q->idp = parse_ident(READCURR);
	}
	match(SS_COLON);

	switch (currtok) {
	case KW_INTEGER:
		match(KW_INTEGER);
		for (p = t; p; p = p->next) {
			p->idp->type =
				byref ? INT_PARA_REF_IDENT : INT_PARA_VAL_IDENT;
		}
		break;
	case KW_CHAR:
		match(KW_CHAR);
		for (p = t; p; p = p->next) {
			p->idp->type = byref ? CHAR_PARA_REF_IDENT :
					       CHAR_PARA_VAL_IDENT;
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
static arg_list_p parse_arg_list(void)
{
	arg_list_p t, p, q;
	INITMEM(arg_list, t);

	t->ep = parse_expr();

	for (p = t; CURRTOK_ANY(SS_COMMA); p = q) {
		match(SS_COMMA);
		INITMEM(arg_list, q);
		p->next = q;
		q->ep = parse_expr();
	}

	return t;
}

pgm_p parse(void)
{
	currtok = gettok();
	return parse_pgm();
}
