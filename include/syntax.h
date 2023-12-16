#ifndef _SYNTAX_H_
#define _SYNTAX_H_
#include "parse.h"
#include "symtab.h"

/* program */
typedef struct _pgm_node {
	block_node_t *bp;
} pgm_node_t;

/* block */
typedef struct _block_node {
	const_dec_node_t *cdp;
	var_dec_node_t *vdp;
	pf_dec_list_node_t *pfdlp;
	comp_stmt_node_t *csp;
} block_node_t;
typedef struct _const_dec_node {
	const_def_node_t *cdp;
	const_dec_node_t *next;
} const_dec_node_t;
typedef struct _const_def_node {
	ident_node_t *idp;
} const_def_node_t;
typedef struct _var_dec_node {
	var_def_node_t *vdp;
	var_dec_node_t *next;
} var_dec_node_t;
typedef struct _var_def_node {
	ident_node_t *idp;
	var_def_node_t *next;
} var_def_node_t;

typedef enum _pf_dec_enum { FUN_PFDEC, PROC_PFDEC } pf_dec_t;
typedef struct _pf_dec_list_node {
	pf_dec_t type;
	proc_dec_node_t *pdp;
	fun_dec_node_t *fdp;
	pf_dec_list_node_t *next;
} pf_dec_list_node_t;
typedef struct _proc_dec_node {
	proc_def_node_t *pdp;
	proc_dec_node_t *next;
} proc_dec_node_t;
typedef struct _proc_def_node {
	proc_head_node_t *php;
	block_node_t *bp;
} proc_def_node_t;
typedef struct _proc_head_node {
	ident_node_t *idp;
	para_list_node_t *plp;
} proc_head_node_t;
typedef struct _fun_dec_node {
	fun_def_node_t *fdp;
	fun_dec_node_t *next;
} fun_dec_node_t;
typedef struct _fun_def_node {
	fun_head_node_t *fhp;
	block_node_t *bp;
} fun_def_node_t;
typedef struct _fun_head_node {
	ident_node_t *idp;
	para_list_node_t *plp;
} fun_head_node_t;

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
typedef struct _stmt_node {
	stmt_t type;
	assign_stmt_node_t *asp;
	if_stmt_node_t *ifp;
	repe_stmt_node_t *rpp;
	for_stmt_node_t *frp;
	pcall_stmt_node_t *pcp;
	comp_stmt_node_t *cpp;
	read_stmt_node_t *rdp;
	write_stmt_node_t *wtp;
} stmt_node_t;
typedef enum _assgin_enum { NORM_ASSGIN, FUN_ASSGIN, ARRAY_ASSGIN } assgin_t;
typedef struct _assign_stmt_node {
	assgin_t type;
	ident_node_t *idp;
	expr_node_t *lep;
	expr_node_t *rep;
} assign_stmt_node_t;
typedef struct _if_stmt_node {
	cond_node_t *cp;
	/* then */
	stmt_node_t *tp;
	/* else */
	stmt_node_t *ep;
} if_stmt_node_t;
typedef struct _repe_stmt_node {
	stmt_node_t *sp;
	cond_node_t *cp;
} repe_stmt_node_t;
typedef enum _for_enum { TO_FOR, DOWNTO_FOR } for_t;
typedef struct _for_stmt_node {
	for_t type;
	ident_node_t *idp;
	expr_node_t *lep;
	expr_node_t *rep;
	stmt_node_t *sp;
} for_stmt_node_t;
typedef struct _pcall_stmt_node {
	ident_node_t *idp;
	arg_list_node_t *alp;
} pcall_stmt_node_t;
typedef struct _fcall_stmt_node {
	ident_node_t *idp;
	arg_list_node_t *alp;
} fcall_stmt_node_t;
typedef struct _comp_stmt_node {
	stmt_node_t *sp;
	comp_stmt_node_t *next;
} comp_stmt_node_t;
typedef struct _read_stmt_node {
	ident_node_t *idp;
	read_stmt_node_t *next;
} read_stmt_node_t;
typedef enum _write_enum { STRID_WRITE, STR_WRITE, ID_WRITE } write_t;
typedef struct _write_stmt_node {
	write_t type;
	/* string pointer */
	char *sp;
	expr_node_t *ep;
} write_stmt_node_t;

/* expression term factor condition */
typedef enum _addop_enum {
	NOP_ADDOP,
	NEG_ADDOP,
	ADD_ADDOP,
	MINUS_ADDOP
} addop_t;
typedef struct _expr_node {
	addop_t op;
	term_node_t *tp;
	expr_node_t *next;
} expr_node_t;
typedef enum _multop_enum { NOP_MULTOP, MULT_MULTOP, DIV_MULTOP } multop_t;
typedef struct _term_node {
	multop_t op;
	factor_node_t *fp;
	term_node_t *next;
} term_node_t;
typedef enum _factor_enum {
	ID_FACTOR,
	ARRAY_FACTOR,
	UNSIGN_FACTOR,
	EXPR_FACTOR,
	FUNCALL_FACTOR
} factor_t;
typedef struct _factor_node {
	factor_t type;
	ident_node_t *idp;
	expr_node_t *ep;
	int usi; // store unsign int value
	fcall_stmt_node_t *fcsp;
} factor_node_t;
typedef enum _rela_enum {
	EQU_RELA,
	NEQ_RELA,
	GTT_RELA,
	GEQ_RELA,
	LST_RELA,
	LEQ_RELA
} rela_t;
typedef struct _cond_node {
	expr_node_t *lep;
	rela_t op;
	expr_node_t *rep;
} cond_node_t;

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
	INT_ARRVAR_IDENT,
	CHAR_ARRVAR_IDENT,
	/* parameter identifier type */
	/* call by value */
	INT_PARA_VAL_IDENT,
	CHAR_PARA_VAL_IDENT,
	/* call by address */
	INT_PARA_REF_IDENT,
	CHAR_PARA_REF_IDENT
} ident_t;
typedef struct _ident_node {
	ident_t kind;
	char *name;
	int value;
	int length;
	int line;
	syment_t *symbol;
} ident_node_t;
typedef struct _para_list_node {
	para_def_node_t *pdp;
	para_list_node_t *next;
} para_list_node_t;
typedef struct _para_def_node {
	ident_node_t *idp;
	para_def_node_t *next;
} para_def_node_t;
typedef struct _arg_list_node {
	expr_node_t *ep;
	arg_list_node_t *next;
	// link to referenced variable or array
	syment_t *symbol;
	syment_t *refsym;
} arg_list_node_t;

#endif /* End of _SYNTAX_H_ */
