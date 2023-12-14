#ifndef _SEM_H_
#define _SEM_H_
#include "global.h"
#include "parse.h"
#include "symtab.h"

static void anlys_pgm(pgm_node_t t);
static void anlys_const_decf(const_dec_node_t t);
static void anlys_var_decf(var_dec_node_t t);
static void anlys_pf_dec_list(pf_dec_list_node_t t);
static void anlys_proc_decf(proc_dec_node_t t);
static syment_t *anlys_proc_head(proc_head_node_t t);
static void anlys_fun_decf(fun_dec_node_t t);
static syment_t *anlys_fun_head(fun_head_node_t t);
static void anlys_stmt(stmt_node_t t);
static void anlys_assign_stmt(assign_stmt_node_t t);
static void anlys_if_stmt(if_stmt_node_t t);
static void anlys_repe_stmt(repe_stmt_node_t t);
static void anlys_for_stmt(for_stmt_node_t t);
static void anlys_pcall_stmt(pcall_stmt_node_t t);
static void anlys_read_stmt(read_stmt_node_t t);
static void anlys_write_stmt(write_stmt_node_t t);
static void anlys_comp_stmt(comp_stmt_node_t t);
static syment_t *anlys_expr(expr_node_t t);
static syment_t *anlys_term(term_node_t t);
static syment_t *anlys_factor(factor_node_t t);
static syment_t *anlys_fcall_stmt(fcall_stmt_node_t t);
static void anlys_cond(cond_node_t t, syment_t *label);
static void anlys_para_list(para_list_node_t t);
static void anlys_arg_list(arg_list_node_t t, syment_t *pfste);

#endif /* End of _SEM_H_ */
