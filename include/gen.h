#ifndef _GEN_H_
#define _GEN_H_
#include "parse.h"
#include "symtab.h"

static void gen_pgm(pgm_node_t *node);
static void gen_pf_dec_list(pf_dec_list_node_t *node);
static void gen_proc_decf(proc_dec_node_t *node);
static void gen_fun_decf(fun_dec_node_t *node);
static void gen_comp_stmt(comp_stmt_node_t *node);
static void gen_stmt(stmt_node_t *node);
static void gen_assign_stmt(assign_stmt_node_t *node);
static void gen_if_stmt(if_stmt_node_t *node);
static void gen_repe_stmt(repe_stmt_node_t *node);
static void gen_for_stmt(for_stmt_node_t *node);
static void gen_pcall_stmt(pcall_stmt_node_t *node);
static void gen_read_stmt(read_stmt_node_t *node);
static void gen_write_stmt(write_stmt_node_t *node);
static syment_t *gen_expr(expr_node_t *node);
static syment_t *gen_term(term_node_t *node);
static syment_t *gen_factor(factor_node_t *node);
static syment_t *gen_fcall_stmt(fcall_stmt_node_t *node);
static void gen_cond(cond_node_t *node, syment_t *dest);
static void gen_arg_list(arg_list_node_t *node);

void genir();
#endif /* End of _GEN_H_ */
