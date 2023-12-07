#ifndef _SYNTAX_H_
#define _SYNTAX_H_

////////////////////////////////////////////////////////////////////////////////
// declaretion of a bundle of struct pointer
////////////////////////////////////////////////////////////////////////////////
typedef struct _pgm_struct *pgm_p;
typedef struct _block_struct *block_p;
typedef struct _const_dec_struct *const_dec_p;
typedef struct _const_def_struct *const_def_p;
typedef struct _var_dec_struct *var_dec_p;
typedef struct _var_def_struct *var_def_p;
typedef struct _pf_dec_list_struct *pf_dec_list_p;
typedef struct _proc_dec_struct *proc_dec_p;
typedef struct _proc_def_struct *proc_def_p;
typedef struct _proc_head_struct *proc_head_p;
typedef struct _fun_dec_struct *fun_dec_p;
typedef struct _fun_def_struct *fun_def_p;
typedef struct _fun_head_struct *fun_head_p;
typedef struct _stmt_struct *stmt_p;
typedef struct _assign_stmt_struct *assign_stmt_p;
typedef struct _if_stmt_struct *if_stmt_p;
typedef struct _repe_stmt_struct *repe_stmt_p;
typedef struct _for_stmt_struct *for_stmt_p;
typedef struct _pcall_stmt_struct *pcall_stmt_p;
typedef struct _fcall_stmt_struct *fcall_stmt_p;
typedef struct _comp_stmt_struct *comp_stmt_p;
typedef struct _read_stmt_struct *read_stmt_p;
typedef struct _write_stmt_struct *write_stmt_p;
typedef struct _expr_struct *expr_p;
typedef struct _term_struct *term_p;
typedef struct _factor_struct *factor_p;
typedef struct _cond_struct *cond_p;
typedef struct _ident_struct *ident_p;
typedef struct _para_list_struct *para_list_p;
typedef struct _para_def_struct *para_def_p;
typedef struct _arg_list_struct *arg_list_p;

////////////////////////////////////////////////////////////////////////////////
// declaretion of a bundle of node type
////////////////////////////////////////////////////////////////////////////////
/* program */
struct _pgm_struct {
	block_p bp;
} pgm;

/* block */
struct _block_struct {
	const_dec_p cdp;
	var_dec_p vdp;
	pf_dec_list_p pfdlp;
	comp_stmt_p csp;
} block;
struct _const_dec_struct {
	const_def_p cdp;
	const_dec_p next;
} const_dec;
struct _const_def_struct {
	ident_p idp;
} const_def;
struct _var_dec_struct {
	var_def_p vdp;
	var_dec_p next;
} var_dec;
struct _var_def_struct {
	ident_p idp;
	var_def_p next;
} var_def;

typedef enum _pf_dec_enum { FUN_PFDEC, PROC_PFDEC } pf_dec_t;
struct _pf_dec_list_struct {
	pf_dec_t type;
	proc_dec_p pdp;
	fun_dec_p fdp;
	pf_dec_list_p next;
} pf_dec_list;
struct _proc_dec_struct {
	proc_def_p pdp;
	proc_dec_p next;
} proc_dec;
struct _proc_def_struct {
	proc_head_p php;
	block_p bp;
} proc_def;
struct _proc_head_struct {
	ident_p idp;
	para_list_p plp;
} proc_head;
struct _fun_dec_struct {
	fun_def_p fdp;
	fun_dec_p next;
} fun_dec;
struct _fun_def_struct {
	fun_head_p fhp;
	block_p bp;
} fun_def;
struct _fun_head_struct {
	ident_p idp;
	para_list_p plp;
} fun_head;

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
struct _stmt_struct {
	stmt_t type;
	assign_stmt_p asp;
	if_stmt_p ifp;
	repe_stmt_p rpp;
	for_stmt_p frp;
	pcall_stmt_p pcp;
	comp_stmt_p cpp;
	read_stmt_p rdp;
	write_stmt_p wtp;
} stmt;
typedef enum _assgin_enum { NORM_ASSGIN, FUN_ASSGIN, ARRAY_ASSGIN } assgin_t;
struct _assign_stmt_struct {
	assgin_t type;
	ident_p idp;
	expr_p lep;
	expr_p rep;
} assign_stmt;
struct _if_stmt_struct {
	cond_p cp;
	/* then */
	stmt_p tp;
	/* else */
	stmt_p ep;
} if_stmt;
struct _repe_stmt_struct {
	stmt_p sp;
	cond_p cp;
} repe_stmt;
typedef enum _for_enum { TO_FOR, DOWNTO_FOR } for_t;
struct _for_stmt_struct {
	for_t type;
	ident_p idp;
	expr_p lep;
	expr_p rep;
	stmt_p sp;
} for_stmt;
struct _pcall_stmt_struct {
	ident_p idp;
	arg_list_p alp;
} pcall_stmt;
struct _fcall_stmt_struct {
	ident_p idp;
	arg_list_p alp;
} fcall_stmt;
struct _comp_stmt_struct {
	stmt_p sp;
	comp_stmt_p next;
} comp_stmt;
struct _read_stmt_struct {
	ident_p idp;
	read_stmt_p next;
} read_stmt;
typedef enum _write_enum { STRID_WRITE, STR_WRITE, ID_WRITE } write_t;
struct _write_stmt_struct {
	write_t type;
	/* string pointer */
	char *sp;
	expr_p ep;
} write_stmt;

/* expression term factor condition */
typedef enum _addop_enum {
	NOP_ADDOP,
	ADD_ADDOP,
	NEG_ADDOP,
	MINUS_ADDOP
} addop_t;
struct _expr_struct {
	addop_t op;
	term_p tp;
	expr_p next;
} expr;
typedef enum _multop_enum { NOP_MULTOP, MULT_MULTOP, DIV_MULTOP } multop_t;
struct _term_struct {
	multop_t op;
	factor_p fp;
	term_p next;
} term;
typedef enum _factor_enum {
	ID_FACTOR,
	ARRAY_FACTOR,
	UNSIGN_FACTOR,
	EXPR_FACTOR,
	FUNCALL_FACTOR
} factor_t;
struct _factor_struct {
	factor_t type;
	ident_p idp;
	expr_p ep;
	/* unsign int */
	int usi;
	fcall_stmt_p fcsp;
} factor;
typedef enum _rela_enum {
	EQU_RELA,
	NEQ_RELA,
	GTT_RELA,
	GEQ_RELA,
	LST_RELA,
	LEQ_RELA
} rela_t;
struct _cond_struct {
	expr_p lep;
	rela_t op;
	expr_p rep;
} cond;

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
struct _ident_struct {
	ident_t type;
	char *name;
	int val;
	int length;
	int line;
} ident;
struct _para_list_struct {
	para_def_p pdp;
	para_list_p next;
} para_list;
struct _para_def_struct {
	ident_p idp;
	para_def_p next;
} para_def;
struct _arg_list_struct {
	expr_p ep;
	arg_list_p next;
} arg_list;

#endif /* End of _SYNTAX_H_ */
