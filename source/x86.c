#include "x86.h"
#include "debug.h"
#include "ir.h"
#include "symtab.h"
#include "util.h"
#include <stdio.h>

////////////////////////////////////////////////////////////////////////////////
// register table
reg_t regs[4] = {
	[0] = { "eax", 0 },
	[1] = { "ebx", 0 },
	[2] = { "ecx", 0 },
	[3] = { "edx", 0 },
};

// acquire a register
reg_t *getreg()
{
	for (int i = 0; i < sizeof(regs) / sizeof(reg_t); ++i) {
		reg_t *r = &regs[i];
		if (r->refcnt == 0) {
			r->refcnt++;
			return r;
		}
	}

	panic("NO_REGISTER_LEFT");
	return 0;
}

// free a register
void putreg(reg_t *r)
{
	r->refcnt--;
}

////////////////////////////////////////////////////////////////////////////////
// i386 instructions
char *addr(syment_t *e)
{
	char buf[16];
	sprintf(buf, "[%s-%d]", BP, ALIGN * e->off);
	return dupstr(buf);
}

void x86_enter(syment_t *e)
{
	printf("; enter\n");
}

void x86_mov(reg_t *reg, syment_t *var)
{
	switch (var->cate) {
	case VAR_OBJ:
		printf("mov\t%s, %s\n", reg->name, addr(var));
		break;
	default:
		unlikely();
	}
}

void x86_mov2(syment_t *var, reg_t *reg)
{
	switch (var->cate) {
	case VAR_OBJ:
		printf("mov\t%s, %s\n", addr(var), reg->name);
		break;
	default:
		unlikely();
	}
}

void x86_mov3(reg_t *reg, syment_t *arr, reg_t *off)
{
	switch (arr->cate) {
	case ARRAY_OBJ:
		printf("lea\t%s, %s\n", DI, addr(arr));
		printf("imul\t%s, %d\n", off->name, ALIGN);
		printf("sub\t%s, %s\n", DI, off->name);
		printf("mov\t%s, [%s]\n", reg->name, DI);
		break;
	default:
		unlikely();
	}
}

void x86_mov4(syment_t *arr, reg_t *off, reg_t *reg)
{
	switch (arr->cate) {
	case ARRAY_OBJ:
		printf("lea\t%s, %s\n", DI, addr(arr));
		printf("imul\t%s, %d\n", off->name, ALIGN);
		printf("sub\t%s, %s\n", DI, off->name);
		printf("mov\t[%s], %s\n", DI, reg->name);
		break;
	default:
		unlikely();
	}
}

void x86_mov5(reg_t *r1, reg_t *r2)
{
	printf("mov\t%s, %s\n", r1->name, r2->name);
}

void x86_mov6(reg_t *reg, int num)
{
	printf("mov\t%s, %d\n", reg->name, num);
}

void x86_lea(reg_t *reg, syment_t *var)
{
	switch (var->cate) {
	case VAR_OBJ:
		printf("lea\t%s, %s\n", reg->name, addr(var));
		break;
	default:
		unlikely();
	}
}

void x86_lea2(reg_t *reg, syment_t *arr, reg_t *off)
{
	switch (arr->cate) {
	case VAR_OBJ:
		printf("lea\t%s, %s\n", reg->name, addr(arr));
		printf("imul\t%s, %d\n", off->name, ALIGN);
		printf("sub\t%s, %s\n", reg->name, off->name);
		break;
	default:
		unlikely();
	}
}

void x86_add(reg_t *r1, reg_t *r2)
{
	printf("add\t%s, %s\n", r1->name, r2->name);
}

void x86_sub(reg_t *r1, reg_t *r2)
{
	printf("sub\t%s, %s\n", r1->name, r2->name);
}

void x86_mul(reg_t *r1, reg_t *r2)
{
	printf("imul\t%s, %s\n", r1->name, r2->name);
}

void x86_div(reg_t *r1)
{
	printf("idiv\t%s\n", r1->name);
}

void x86_inc(reg_t *r1)
{
	printf("inc\t%s\n", r1->name);
}

void x86_dec(reg_t *r1)
{
	printf("dec\t%s\n", r1->name);
}

void x86_pop(reg_t *reg)
{
	printf("pop\t%s\n", reg->name);
}

void x86_push(reg_t *reg)
{
	printf("push\t%s\n", reg->name);
}

void x86_push2(syment_t *var)
{
	printf("push\t%s\n", var->label);
}

void x86_call(syment_t *func)
{
	printf("call\t%s\n", func->label);
	int off = ALIGN * (func->stab->varoff + func->stab->tmpoff);
	printf("add\tesp, %d\n", off);
}

void x86_ret()
{
	printf("ret\n");
}

void x86_label(syment_t *lab)
{
	printf("%s:\n", lab->label);
}

void x86_jmp(syment_t *lab)
{
	printf("jmp\t%s\n", lab->label);
}

void x86_cmp(reg_t *r1, reg_t *r2)
{
	printf("cmp\t%s, %s\n", r1->name, r2->name);
}

void x86_jz(syment_t *lab)
{
	printf("jz\t%s\n", lab->label);
}

void x86_jnz(syment_t *lab)
{
	printf("jnz\t%s\n", lab->label);
}

void x86_jg(syment_t *lab)
{
	printf("jg\t%s\n", lab->label);
}

void x86_jng(syment_t *lab)
{
	printf("jng\t%s\n", lab->label);
}

void x86_jl(syment_t *lab)
{
	printf("jl\t%s\n", lab->label);
}

void x86_jnl(syment_t *lab)
{
	printf("jnl\t%s\n", lab->label);
}

void x86_sret(syment_t *reg)
{
	printf("mov\t[%s-%d], %s\n", BP, ALIGN, reg->name);
}
