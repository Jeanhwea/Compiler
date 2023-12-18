#include "x86.h"
#include "debug.h"
#include "ir.h"
#include "symtab.h"

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
}

// free a register
void *putreg(reg_t *r)
{
	r->refcnt--;
}

////////////////////////////////////////////////////////////////////////////////
// i386 instructions
void x86_enter(syment_t *e)
{
	printf("; enter\n");
}

void x86_mov(reg_t *reg, syment_t *var)
{
	switch (var->cate) {
	case VAR_OBJ:
		printf("mov\t%s, [ebp-%d]\n", reg->name, OFFSET(var));
		break;
	default:
		unlikely();
	}
}

void x86_mov2(syment_t *var, reg_t *reg)
{
	switch (var->cate) {
	case VAR_OBJ:
		printf("mov\t[ebp-%d], %s\n", OFFSET(var), reg->name);
		break;
	default:
		unlikely();
	}
}

void x86_mov3(reg_t *reg, syment_t *arr, reg_t *off)
{
	switch (arr->cate) {
	case ARRAY_OBJ:
		printf("lea\tedi, [ebp-%d]\n", OFFSET(arr));
		printf("imul\t%s, %d\n", off->name, ALIGN);
		printf("sub\tedi, %s\n", off->name);
		printf("mov\t%s, [edi]\n", reg->name);
		break;
	default:
		unlikely();
	}
}

void x86_mov4(syment_t *arr, reg_t *off, reg_t *reg)
{
	switch (arr->cate) {
	case ARRAY_OBJ:
		printf("lea\tedi, [ebp-%d]\n", OFFSET(arr));
		printf("imul\t%s, %d\n", off->name, ALIGN);
		printf("sub\tedi, %s\n", off->name);
		printf("mov\t[edi], %s\n", reg->name);
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
		printf("lea\t%s, [ebp-%d]\n", reg->name, OFFSET(var));
		break;
	default:
		unlikely();
	}
}

void x86_lea2(reg_t *reg, syment_t *arr, reg_t *off)
{
	switch (arr->cate) {
	case VAR_OBJ:
		printf("lea\t%s, [ebp-%d]\n", reg->name, OFFSET(arr));
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
