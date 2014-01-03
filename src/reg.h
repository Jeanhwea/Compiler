/**
 * File: reg.h
 * Date: Nov 23, 2013
 * Author: Jeanhwea
 */
#ifndef REG_H

#define REG_H

#define COUNT_VARS(ste) (\
(ste->obj==Var_Obj_t)||(ste->obj==Tmp_Obj_t)||\
(ste->obj==Para_Val_Obj_t)||(ste->obj==Para_Ref_Obj_t)\
)

void do_use_count(void);
#endif /* end of include guard: REG_H */
