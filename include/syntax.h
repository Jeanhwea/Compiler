#ifndef _SYNTAX_H_
#define _SYNTAX_H_
#include "parse.h"

/* program */
typedef struct _pgm_struct {
	block_s *bp;
} pgm_s;

/* block */
typedef struct _block_struct {
	const_dec_s *cdp;
	var_dec_s *vdp;
	pf_dec_list_s *pfdlp;
	comp_stmt_s *csp;
} block_s;
typedef struct _const_dec_struct {
	const_def_s *cdp;
	const_dec_s *next;
} const_dec_s;
typedef struct _const_def_struct {
	ident_s *idp;
} const_def_s;
typedef struct _var_dec_struct {
	var_def_s *vdp;
	var_dec_s *next;
} var_dec_s;
typedef struct _var_def_struct {
	ident_s *idp;
	var_def_s *next;
} var_def_s;

typedef enum _pf_dec_enum { FUN_PFDEC, PROC_PFDEC } pf_dec_t;
typedef struct _pf_dec_list_struct {
	pf_dec_t type;
	proc_dec_s *pdp;
	fun_dec_s *fdp;
	pf_dec_list_s *next;
} pf_dec_list_s;
typedef struct _proc_dec_struct {
	proc_def_s *pdp;
	proc_dec_s *next;
} proc_dec_s;
typedef struct _proc_def_struct {
	proc_head_s *php;
	block_s *bp;
} proc_def_s;
typedef struct _proc_head_struct {
	ident_s *idp;
	para_list_s *plp;
} proc_head_s;
typedef struct _fun_dec_struct {
	fun_def_s *fdp;
	fun_dec_s *next;
} fun_dec_s;
typedef struct _fun_def_struct {
	fun_head_s *fhp;
	block_s *bp;
} fun_def_s;
typedef struct _fun_head_struct {
	ident_s *idp;
	para_list_s *plp;
} fun_head_s;

/* statement */
typedef enum _stmt_enum {
	ASSGIN_STMT,
	IF_STMT,
	REPEAT_STMT,
	PCALL_STMT,
	COMP_STMT,
	READ_STMT,
	WRITE_STMT,
	FOR_STMT,
	NULL_STMT
} stmt_t;
typedef struct _stmt_struct {
	stmt_t type;
	assign_stmt_s *asp;
	if_stmt_s *ifp;
	repe_stmt_s *rpp;
	for_stmt_s *frp;
	pcall_stmt_s *pcp;
	comp_stmt_s *cpp;
	read_stmt_s *rdp;
	write_stmt_s *wtp;
} stmt_s;
typedef enum _assgin_enum { NORM_ASSGIN, FUN_ASSGIN, ARRAY_ASSGIN } assgin_t;
typedef struct _assign_stmt_struct {
	assgin_t type;
	ident_s *idp;
	expr_s *lep;
	expr_s *rep;
} assign_stmt_s;
typedef struct _if_stmt_struct {
	cond_s *cp;
	/* then */
	stmt_s *tp;
	/* else */
	stmt_s *ep;
} if_stmt_s;
typedef struct _repe_stmt_struct {
	stmt_s *sp;
	cond_s *cp;
} repe_stmt_s;
typedef enum _for_enum { TO_FOR, DOWNTO_FOR } for_t;
typedef struct _for_stmt_struct {
	for_t type;
	ident_s *idp;
	expr_s *lep;
	expr_s *rep;
	stmt_s *sp;
} for_stmt_s;
typedef struct _pcall_stmt_struct {
	ident_s *idp;
	arg_list_s *alp;
} pcall_stmt_s;
typedef struct _fcall_stmt_struct {
	ident_s *idp;
	arg_list_s *alp;
} fcall_stmt_s;
typedef struct _comp_stmt_struct {
	stmt_s *sp;
	comp_stmt_s *next;
} comp_stmt_s;
typedef struct _read_stmt_struct {
	ident_s *idp;
	read_stmt_s *next;
} read_stmt_s;
typedef enum _write_enum { STRID_WRITE, STR_WRITE, ID_WRITE } write_t;
typedef struct _write_stmt_struct {
	write_t type;
	/* string pointer */
	char *sp;
	expr_s *ep;
} write_stmt_s;

/* expression term factor condition */
typedef enum _addop_enum {
	NOP_ADDOP,
	ADD_ADDOP,
	NEG_ADDOP,
	MINUS_ADDOP
} addop_t;
typedef struct _expr_struct {
	addop_t op;
	term_s *tp;
	expr_s *next;
} expr_s;
typedef enum _multop_enum { NOP_MULTOP, MULT_MULTOP, DIV_MULTOP } multop_t;
typedef struct _term_struct {
	multop_t op;
	factor_s *fp;
	term_s *next;
} term_s;
typedef enum _factor_enum {
	ID_FACTOR,
	ARRAY_FACTOR,
	UNSIGN_FACTOR,
	EXPR_FACTOR,
	FUNCALL_FACTOR
} factor_t;
typedef struct _factor_struct {
	factor_t type;
	ident_s *idp;
	expr_s *ep;
	/* unsign int */
	int usi;
	fcall_stmt_s *fcsp;
} factor_s;
typedef enum _rela_enum {
	EQU_RELA,
	NEQ_RELA,
	GTT_RELA,
	GEQ_RELA,
	LST_RELA,
	LEQ_RELA
} rela_t;
typedef struct _cond_struct {
	expr_s *lep;
	rela_t op;
	expr_s *rep;
} cond_s;

/* ident parameter argument*/
typedef enum _ident_enum {
	/* normal identifier type */
	INIT_IDENT,
	PROC_IDENT,
	INT_FUN_IDENT,
	CHAR_FUN_IDENT,
	/* const identifier type */
	INT_CONST_IDENT,
	CHAR_CONST_IDENT,
	/* variable identifier type */
	INT_VAR_IDENT,
	CHAR_VAR_IDENT,
	INTARR_VAR_IDENT,
	CHARARR_VAR_IDENT,
	/* parameter identifier type */
	/* call by value */
	INT_PARA_VAL_IDENT,
	CHAR_PARA_VAL_IDENT,
	/* call by address */
	INT_PARA_REF_IDENT,
	CHAR_PARA_REF_IDENT
} ident_t;
typedef struct _ident_struct {
	ident_t type;
	char *name;
	int val;
	int length;
	int line;
} ident_s;
typedef struct _para_list_struct {
	para_def_s *pdp;
	para_list_s *next;
} para_list_s;
typedef struct _para_def_struct {
	ident_s *idp;
	para_def_s *next;
} para_def_s;
typedef struct _arg_list_struct {
	expr_s *ep;
	arg_list_s *next;
} arg_list_s;

#endif /* End of _SYNTAX_H_ */
