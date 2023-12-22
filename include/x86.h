#ifndef _X86_H_
#define _X86_H_
#include "symtab.h"

// register
typedef struct _reg_struct {
	char name[4];
	int refcnt;
} reg_t;

// Pointer register
#define REG_BP "ebp"
#define REG_SP "esp"
#define REG_DI "edi"
#define REG_SI "esi"
#define REG_RA "eax"
#define REG_RB "ebx"
#define REG_RC "ecx"
#define REG_RD "edx"
#define REG_CL "cl"
#define REG_DL "dl"
#define PTR_BI "[ebi]"
#define PTR_SI "[esi]"
#define BTP_SI "byte[esi]"
#define SYSCAL "0x80"

// General register operations
reg_t *allocreg();
reg_t *lockreg(char *name);
void freereg(reg_t *r);

#define ALIGN 4
#define OFFSET(e) (ALIGN * e->off)

// x86 instructions
#define MAXOPLEN 64
typedef struct _x86_inst_struct {
	bool islab; // if instruction is a label
	char op[MAXOPLEN]; // operator or label
	char fa[MAXOPLEN]; // operand field a
	char fb[MAXOPLEN]; // operand field b
	char et[MAXOPLEN]; // extra: comment, label etc.
} x86i_t;

#define MAXDATASEC 32
#define MAXTEXTSEC 1024
typedef struct _program_code_struct {
	int idata;
	x86i_t data[MAXDATASEC];
	int itext;
	x86i_t text[MAXTEXTSEC];
} progcode_t;

// dump all assemble codes
void progdump();

typedef enum _rwmemmode_enum {
	READ_MEM_VAL,
	READ_MEM_REF,
	SAVE_REG_VAL,
	SAVE_MEM_REF,
	LOAD_MEM_ADDR
} rwmode_t;

// asm instructions
void x86_init();
void x86_mov(reg_t *reg, syment_t *var);
void x86_mov2(syment_t *var, reg_t *reg);
void x86_mov3(reg_t *reg, syment_t *arr, reg_t *idx);
void x86_mov4(syment_t *arr, reg_t *idx, reg_t *reg);
void x86_mov5(reg_t *r1, reg_t *r2);
void x86_mov6(reg_t *reg, int num);
void x86_mov7(reg_t *reg, char *strconst);
void x86_lea(reg_t *reg, syment_t *var);
void x86_lea2(reg_t *reg, syment_t *arr, reg_t *idx);
void x86_add(reg_t *r1, reg_t *r2);
void x86_sub(reg_t *r1, reg_t *r2);
void x86_mul(reg_t *r1, reg_t *r2);
reg_t *x86_div(reg_t *r1, reg_t *eax, reg_t *edx);
void x86_neg(reg_t *r1);
void x86_inc(reg_t *r1);
void x86_dec(reg_t *r1);
void x86_xor(reg_t *r1, reg_t *r2);
void x86_cls(reg_t *r1);
void x86_pop(reg_t *reg);
void x86_push(reg_t *reg);
void x86_push2(syment_t *var);
void x86_enter(syment_t *func);
void x86_leave(syment_t *func);
void x86_call(syment_t *func);
void x86_ret();
reg_t *x86_syscall(char *func, reg_t *eax);
void x86_label(syment_t *lab);
void x86_jmp(syment_t *lab);
void x86_cmp(reg_t *r1, reg_t *r2);
void x86_jz(syment_t *lab);
void x86_jnz(syment_t *lab);
void x86_jg(syment_t *lab);
void x86_jng(syment_t *lab);
void x86_jl(syment_t *lab);
void x86_jnl(syment_t *lab);
void x86_alloc_string(char *name, char *initval);
#endif /* End of _X86_H_ */
