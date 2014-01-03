#ifndef LIVE_VARIABLE_H

#define LIVE_VARIABLE_H

#define CON_BRANCE(v) (\
(v->op==EQU_op)||(v->op==NEQ_op)||(v->op==GTT_op)\
||(v->op==GEQ_op)||(v->op==LST_op)||(v->op==LEQ_op)\
)
#define BI_ARITH(v) (\
(v->op==ADD_op)||(v->op==SUB_op)||(v->op==MUL_op)\
||(v->op==DIV_op)||(v->op==LOAD_op)||(v->op==AARR_op)\
)
#define UNA_ARITH(v) (\
(v->op==NEG_op)||(v->op==ASS_op)||(v->op==SRET_op)\
)
#define UNARAY(v) (\
(v->op==INC_op)||(v->op==DEC_op)\
)
#define SIG_USE(v) (\
(v->op==PUSH_op)||(v->op==PUSHA_op)\
||(v->op==WRI_op)||(v->op==WRC_op)\
)
#define READ(v) (\
(v->op==READ_op)||(v->op==READC_op)\
)

#define LIVE_VARS(ste) (\
(ste->obj==Var_Obj_t)||(ste->obj==Tmp_Obj_t)||\
(ste->obj==Para_Val_Obj_t)||(ste->obj==Para_Ref_Obj_t)\
)

void cal_use_def(void);
void do_dataflow(void);

#endif /* end of include guard: LIVE_VARIABLE_H */
