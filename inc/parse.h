#ifndef _PARSE_H_
#define _PARSE_H_
#include "global.h"
#include "syntax.h"
#include "scan.h"

// hold current token
static token_t token;

// ID read mode
typedef int idreadmode_t;
#define READCURR 0
#define READPREV 1

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

#endif /* End of _PARSE_H_ */
