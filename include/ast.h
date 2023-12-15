#ifndef _AST_H_
#define _AST_H_
#include "global.h"
#include "parse.h"

#define MAXCHILD 32
typedef struct _tree_node node_t;
typedef struct _tree_node {
	int id;
	char *name;
	int total;
	char *refs[MAXCHILD];
	node_t *childs[MAXCHILD];
	ident_node_t *idp;
	int type;
	char *extra;
} node_t;

static node_t *conv_pgm_node(pgm_node_t *t);
static node_t *conv_block_node(block_node_t *t);
static node_t *conv_const_dec_node(const_dec_node_t *t);
static node_t *conv_const_def_node(const_def_node_t *t);
static node_t *conv_var_dec_node(var_dec_node_t *t);
static node_t *conv_var_def_node(var_def_node_t *t);
static node_t *conv_pf_dec_list_node(pf_dec_list_node_t *t);
static node_t *conv_proc_dec_node(proc_dec_node_t *t);
static node_t *conv_proc_def_node(proc_def_node_t *t);
static node_t *conv_proc_head_node(proc_head_node_t *t);
static node_t *conv_fun_dec_node(fun_dec_node_t *t);
static node_t *conv_fun_def_node(fun_def_node_t *t);
static node_t *conv_fun_head_node(fun_head_node_t *t);
static node_t *conv_stmt_node(stmt_node_t *t);
static node_t *conv_assign_stmt_node(assign_stmt_node_t *t);
static node_t *conv_if_stmt_node(if_stmt_node_t *t);
static node_t *conv_repe_stmt_node(repe_stmt_node_t *t);
static node_t *conv_for_stmt_node(for_stmt_node_t *t);
static node_t *conv_pcall_stmt_node(pcall_stmt_node_t *t);
static node_t *conv_fcall_stmt_node(fcall_stmt_node_t *t);
static node_t *conv_comp_stmt_node(comp_stmt_node_t *t);
static node_t *conv_read_stmt_node(read_stmt_node_t *t);
static node_t *conv_write_stmt_node(write_stmt_node_t *t);
static node_t *conv_expr_node(expr_node_t *t);
static node_t *conv_term_node(term_node_t *t);
static node_t *conv_factor_node(factor_node_t *t);
static node_t *conv_cond_node(cond_node_t *t);
static node_t *conv_ident_node(ident_node_t *t);
static node_t *conv_para_list_node(para_list_node_t *t);
static node_t *conv_para_def_node(para_def_node_t *t);
static node_t *conv_arg_list_node(arg_list_node_t *t);

node_t *conv_ast();
#endif /* End of _AST_H_ */
