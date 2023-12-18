#ifndef _X86_H_
#define _X86_H_
#include "symtab.h"

// register
typedef struct _reg_struct {
	char name[4];
	int refcnt;
} reg_t;

// Pointer register
#define BP "ebp"
#define DI "ebi"

// General register operations
reg_t *ralloc();
reg_t *rlock(char *name);
void rfree(reg_t *r);

#define ALIGN 4
#define OFFSET(e) (ALIGN * e->off)

// asm instructions
void x86_enter(syment_t *e);
void x86_mov(reg_t *reg, syment_t *var);
void x86_mov2(syment_t *var, reg_t *reg);
void x86_mov3(reg_t *reg, syment_t *arr, reg_t *off);
void x86_mov4(syment_t *arr, reg_t *off, reg_t *reg);
void x86_mov5(reg_t *r1, reg_t *r2);
void x86_mov6(reg_t *reg, int num);
void x86_lea(reg_t *reg, syment_t *var);
void x86_lea2(reg_t *reg, syment_t *arr, reg_t *off);
void x86_add(reg_t *r1, reg_t *r2);
void x86_sub(reg_t *r1, reg_t *r2);
void x86_mul(reg_t *r1, reg_t *r2);
void x86_div(reg_t *r1);
void x86_neg(reg_t *r1);
void x86_inc(reg_t *r1);
void x86_dec(reg_t *r1);
void x86_pop(reg_t *reg);
void x86_push(reg_t *reg);
void x86_push2(syment_t *var);
void x86_call(syment_t *func);
void x86_ret();
void x86_label(syment_t *lab);
void x86_jmp(syment_t *lab);
void x86_cmp(reg_t *r1, reg_t *r2);
void x86_jz(syment_t *lab);
void x86_jnz(syment_t *lab);
void x86_jg(syment_t *lab);
void x86_jng(syment_t *lab);
void x86_jl(syment_t *lab);
void x86_jnl(syment_t *lab);
void x86_sret(syment_t *reg);
#endif /* End of _X86_H_ */
