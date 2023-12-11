#ifndef _PARSE_H_
#define _PARSE_H_
#include "global.h"
#include "scan.h"

////////////////////////////////////////////////////////////////////////////////
// Declaretion of a bundle of AST struct
typedef struct _pgm_struct pgm_s;
typedef struct _block_struct block_s;
typedef struct _const_dec_struct const_dec_s;
typedef struct _const_def_struct const_def_s;
typedef struct _var_dec_struct var_dec_s;
typedef struct _var_def_struct var_def_s;
typedef struct _pf_dec_list_struct pf_dec_list_s;
typedef struct _proc_dec_struct proc_dec_s;
typedef struct _proc_def_struct proc_def_s;
typedef struct _proc_head_struct proc_head_s;
typedef struct _fun_dec_struct fun_dec_s;
typedef struct _fun_def_struct fun_def_s;
typedef struct _fun_head_struct fun_head_s;
typedef struct _stmt_struct stmt_s;
typedef struct _assign_stmt_struct assign_stmt_s;
typedef struct _if_stmt_struct if_stmt_s;
typedef struct _repe_stmt_struct repe_stmt_s;
typedef struct _for_stmt_struct for_stmt_s;
typedef struct _pcall_stmt_struct pcall_stmt_s;
typedef struct _fcall_stmt_struct fcall_stmt_s;
typedef struct _comp_stmt_struct comp_stmt_s;
typedef struct _read_stmt_struct read_stmt_s;
typedef struct _write_stmt_struct write_stmt_s;
typedef struct _expr_struct expr_s;
typedef struct _term_struct term_s;
typedef struct _factor_struct factor_s;
typedef struct _cond_struct cond_s;
typedef struct _ident_struct ident_s;
typedef struct _para_list_struct para_list_s;
typedef struct _para_def_struct para_def_s;
typedef struct _arg_list_struct arg_list_s;

////////////////////////////////////////////////////////////////////////////////
// Initialize node struct, allocate memory
//     INITMEM(s: struct, v: variable, sturct pointer)
#define INITMEM(s, v)                                                          \
	do {                                                                   \
		v = (s *)malloc(sizeof(s));                                    \
		if (v == NULL) {                                               \
			panic("OUT_OF_MEMORY");                                \
		};                                                             \
		memset(v, 0, sizeof(s));                                       \
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
static pgm_s *parse_pgm(void);
static block_s *parse_block(void);
static const_dec_s *parse_const_dec(void);
static const_def_s *parse_const_def(void);
static var_dec_s *parse_var_dec(void);
static var_def_s *parse_var_def(void);
static pf_dec_list_s *parse_pf_dec_list(void);
static proc_dec_s *parse_proc_dec(void);
static proc_def_s *parse_proc_def(void);
static proc_head_s *parse_proc_head(void);
static fun_dec_s *parse_fun_dec(void);
static fun_def_s *parse_fun_def(void);
static fun_head_s *parse_fun_head(void);
static stmt_s *parse_stmt(void);
static assign_stmt_s *parse_assign_stmt(void);
static if_stmt_s *parse_if_stmt(void);
static repe_stmt_s *parse_repe_stmt(void);
static for_stmt_s *parse_for_stmt(void);
static pcall_stmt_s *parse_pcall_stmt(void);
static fcall_stmt_s *parse_fcall_stmt(void);
static comp_stmt_s *parse_comp_stmt(void);
static read_stmt_s *parse_read_stmt(void);
static write_stmt_s *parse_write_stmt(void);
static expr_s *parse_expr(void);
static term_s *parse_term(void);
static factor_s *parse_factor(void);
static cond_s *parse_cond(void);
static ident_s *parse_ident(idreadmode_t mode);
static para_list_s *parse_para_list(void);
static para_def_s *parse_para_def(void);
static arg_list_s *parse_arg_list(void);

////////////////////////////////////////////////////////////////////////////////
// Parse source file to AST
pgm_s *parse(void);
#endif /* End of _PARSE_H_ */
