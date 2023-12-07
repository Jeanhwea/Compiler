#include "parse.h"
#include "debug.h"
#include "lexical.h"
#include "scan.h"
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
	if (currtok != expected) {
		panic("UNEXPECTED_TOKEN");
	}
	strncpy(prevtokbuf, tokbuf, MAXTOKENSIZE);
	prevtok = currtok;
	prevlineno = toklineno;
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
	} else if (CURRTOK_ANY(KW_VAR)) {
		t->vdp = parse_var_dec();
	} else if (CURRTOK_ANY2(KW_FUNCTION, KW_PROCEDURE)) {
		t->pfdlp = parse_pf_dec_list();
	} else if (CURRTOK_ANY(KW_BEGIN)) {
		t->csp = parse_comp_stmt();
	} else {
		unlikely();
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

static var_dec_p parse_var_dec(void)
{
	var_dec_p t;
	INITMEM(var_dec, t);
	return t;
}
static var_def_p parse_var_def(void)
{
	var_def_p t;
	INITMEM(var_def, t);
	return t;
}
static pf_dec_list_p parse_pf_dec_list(void)
{
	pf_dec_list_p t;
	INITMEM(pf_dec_list, t);
	return t;
}
static proc_dec_p parse_proc_dec(void)
{
	proc_dec_p t;
	INITMEM(proc_dec, t);
	return t;
}
static proc_def_p parse_proc_def(void)
{
	proc_def_p t;
	INITMEM(proc_def, t);
	return t;
}
static proc_head_p parse_proc_head(void)
{
	proc_head_p t;
	INITMEM(proc_head, t);
	return t;
}
static fun_dec_p parse_fun_dec(void)
{
	fun_dec_p t;
	INITMEM(fun_dec, t);
	return t;
}
static fun_def_p parse_fun_def(void)
{
	fun_def_p t;
	INITMEM(fun_def, t);
	return t;
}
static fun_head_p parse_fun_head(void)
{
	fun_head_p t;
	INITMEM(fun_head, t);
	return t;
}
static stmt_p parse_stmt(void)
{
	stmt_p t;
	INITMEM(stmt, t);
	return t;
}
static assign_stmt_p parse_assign_stmt(void)
{
	assign_stmt_p t;
	INITMEM(assign_stmt, t);
	return t;
}
static if_stmt_p parse_if_stmt(void)
{
	if_stmt_p t;
	INITMEM(if_stmt, t);
	return t;
}
static repe_stmt_p parse_repe_stmt(void)
{
	repe_stmt_p t;
	INITMEM(repe_stmt, t);
	return t;
}
static for_stmt_p parse_for_stmt(void)
{
	for_stmt_p t;
	INITMEM(for_stmt, t);
	return t;
}
static pcall_stmt_p parse_pcall_stmt(void)
{
	pcall_stmt_p t;
	INITMEM(pcall_stmt, t);
	return t;
}
static fcall_stmt_p parse_fcall_stmt(void)
{
	fcall_stmt_p t;
	INITMEM(fcall_stmt, t);
	return t;
}
static comp_stmt_p parse_comp_stmt(void)
{
	comp_stmt_p t;
	INITMEM(comp_stmt, t);
	return t;
}
static read_stmt_p parse_read_stmt(void)
{
	read_stmt_p t;
	INITMEM(read_stmt, t);
	return t;
}
static write_stmt_p parse_write_stmt(void)
{
	write_stmt_p t;
	INITMEM(write_stmt, t);
	return t;
}
static expr_p parse_expr(void)
{
	expr_p t;
	INITMEM(expr, t);
	return t;
}
static term_p parse_term(void)
{
	term_p t;
	INITMEM(term, t);
	return t;
}
static factor_p parse_factor(void)
{
	factor_p t;
	INITMEM(factor, t);
	return t;
}
static cond_p parse_cond(void)
{
	cond_p t;
	INITMEM(cond, t);
	return t;
}
static ident_p parse_ident(idreadmode_t mode)
{
	ident_p t;
	INITMEM(ident, t);
	return t;
}
static para_list_p parse_para_list(void)
{
	para_list_p t;
	INITMEM(para_list, t);
	return t;
}
static para_def_p parse_para_def(void)
{
	para_def_p t;
	INITMEM(para_def, t);
	return t;
}
static arg_list_p parse_arg_list(void)
{
	arg_list_p t;
	INITMEM(arg_list, t);
	return t;
}
