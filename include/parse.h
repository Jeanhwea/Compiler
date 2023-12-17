#ifndef _PARSE_H_
#define _PARSE_H_
#include "global.h"
#include "scan.h"

////////////////////////////////////////////////////////////////////////////////
// Declaretion of a bundle of tree node for AST
typedef struct _pgm_node pgm_node_t;
typedef struct _block_node block_node_t;
typedef struct _const_dec_node const_dec_node_t;
typedef struct _const_def_node const_def_node_t;
typedef struct _var_dec_node var_dec_node_t;
typedef struct _var_def_node var_def_node_t;
typedef struct _pf_dec_list_node pf_dec_list_node_t;
typedef struct _proc_dec_node proc_dec_node_t;
typedef struct _proc_def_node proc_def_node_t;
typedef struct _proc_head_node proc_head_node_t;
typedef struct _fun_dec_node fun_dec_node_t;
typedef struct _fun_def_node fun_def_node_t;
typedef struct _fun_head_node fun_head_node_t;
typedef struct _stmt_node stmt_node_t;
typedef struct _assign_stmt_node assign_stmt_node_t;
typedef struct _if_stmt_node if_stmt_node_t;
typedef struct _repe_stmt_node repe_stmt_node_t;
typedef struct _for_stmt_node for_stmt_node_t;
typedef struct _pcall_stmt_node pcall_stmt_node_t;
typedef struct _fcall_stmt_node fcall_stmt_node_t;
typedef struct _comp_stmt_node comp_stmt_node_t;
typedef struct _read_stmt_node read_stmt_node_t;
typedef struct _write_stmt_node write_stmt_node_t;
typedef struct _expr_node expr_node_t;
typedef struct _term_node term_node_t;
typedef struct _factor_node factor_node_t;
typedef struct _cond_node cond_node_t;
typedef struct _ident_node ident_node_t;
typedef struct _para_list_node para_list_node_t;
typedef struct _para_def_node para_def_node_t;
typedef struct _arg_list_node arg_list_node_t;

extern int nidcnt;

// Create New Node
#define NEWNODE(s, v)                                                          \
	do {                                                                   \
		INITMEM(s, v);                                                 \
		v->nid = ++nidcnt;                                             \
	} while (0)

// use like:
//   if (CURRTOK_ANY(a, b, c, ...)) { ... }
#define CURRTOK_ANY(a) (currtok == (a))
#define CURRTOK_ANY2(a, b) (currtok == (a) || currtok == (b))
#define CURRTOK_ANY3(a, b, c)                                                  \
	(currtok == (a) || currtok == (b) || currtok == (c))
#define CURRTOK_ANY4(a, b, c, d)                                               \
	(currtok == (a) || currtok == (b) || currtok == (c) || currtok == (d))
#define CURRTOK_ANY5(a, b, c, d, e)                                            \
	(currtok == (a) || currtok == (b) || currtok == (c) ||                 \
	 currtok == (d) || currtok == (e))
#define CURRTOK_ANY6(a, b, c, d, e, f)                                         \
	(currtok == (a) || currtok == (b) || currtok == (c) ||                 \
	 currtok == (d) || currtok == (e) || currtok == (f))

////////////////////////////////////////////////////////////////////////////////
// ID read mode, for parse_ident()
typedef enum _idreadmode_enum { READCURR, READPREV } idreadmode_t;

// Define a bundle of parse function
static pgm_node_t *parse_pgm(void);
static block_node_t *parse_block(void);
static const_dec_node_t *parse_const_dec(void);
static const_def_node_t *parse_const_def(void);
static var_dec_node_t *parse_var_dec(void);
static var_def_node_t *parse_var_def(void);
static pf_dec_list_node_t *parse_pf_dec_list(void);
static proc_dec_node_t *parse_proc_dec(void);
static proc_def_node_t *parse_proc_def(void);
static proc_head_node_t *parse_proc_head(void);
static fun_dec_node_t *parse_fun_dec(void);
static fun_def_node_t *parse_fun_def(void);
static fun_head_node_t *parse_fun_head(void);
static stmt_node_t *parse_stmt(void);
static assign_stmt_node_t *parse_assign_stmt(void);
static if_stmt_node_t *parse_if_stmt(void);
static repe_stmt_node_t *parse_repe_stmt(void);
static for_stmt_node_t *parse_for_stmt(void);
static pcall_stmt_node_t *parse_pcall_stmt(void);
static fcall_stmt_node_t *parse_fcall_stmt(void);
static comp_stmt_node_t *parse_comp_stmt(void);
static read_stmt_node_t *parse_read_stmt(void);
static write_stmt_node_t *parse_write_stmt(void);
static expr_node_t *parse_expr(void);
static term_node_t *parse_term(void);
static factor_node_t *parse_factor(void);
static cond_node_t *parse_cond(void);
static ident_node_t *parse_ident(idreadmode_t mode);
static para_list_node_t *parse_para_list(void);
static para_def_node_t *parse_para_def(void);
static arg_list_node_t *parse_arg_list(void);

////////////////////////////////////////////////////////////////////////////////
// Parse source file to AST
pgm_node_t *parse(void);
#endif /* End of _PARSE_H_ */
