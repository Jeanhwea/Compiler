#ifndef _PARSE_H_
#define _PARSE_H_
#include "global.h"
#include "scan.h"

// Declaretion of a bundle of struct pointer
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

// initialize node struct, allocate memory
//     INITMEM(s:struct, v: variable, sturct pointer)
#define INITMEM(s, v)                                                          \
	do {                                                                   \
		v = (s##_p)malloc(sizeof(s));                                  \
		if (v == NULL) {                                               \
			panic("OUT_OF_MEMORY");                                \
		};                                                             \
		memset(v, 0, sizeof(s));                                       \
	} while (0)

// ID read mode
typedef int idreadmode_t;
#define READCURR 0
#define READPREV 1

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

// Define a bundle of parse function
static pgm_p parse_pgm(void);
static block_p parse_block(void);
static const_dec_p parse_const_dec(void);
static const_def_p parse_const_def(void);
static var_dec_p parse_var_dec(void);
static var_def_p parse_var_def(void);
static pf_dec_list_p parse_pf_dec_list(void);
static proc_dec_p parse_proc_dec(void);
static proc_def_p parse_proc_def(void);
static proc_head_p parse_proc_head(void);
static fun_dec_p parse_fun_dec(void);
static fun_def_p parse_fun_def(void);
static fun_head_p parse_fun_head(void);
static stmt_p parse_stmt(void);
static assign_stmt_p parse_assign_stmt(void);
static if_stmt_p parse_if_stmt(void);
static repe_stmt_p parse_repe_stmt(void);
static for_stmt_p parse_for_stmt(void);
static pcall_stmt_p parse_pcall_stmt(void);
static fcall_stmt_p parse_fcall_stmt(void);
static comp_stmt_p parse_comp_stmt(void);
static read_stmt_p parse_read_stmt(void);
static write_stmt_p parse_write_stmt(void);
static expr_p parse_expr(void);
static term_p parse_term(void);
static factor_p parse_factor(void);
static cond_p parse_cond(void);
static ident_p parse_ident(idreadmode_t mode);
static para_list_p parse_para_list(void);
static para_def_p parse_para_def(void);
static arg_list_p parse_arg_list(void);

// Parse source file to AST
pgm_p parse(void);
#endif /* End of _PARSE_H_ */
