#include "x86.h"
#include "debug.h"
#include "ir.h"
#include "symtab.h"

// register table
reg_t regs[4] = {
	[0] = { "eax", 0 },
	[1] = { "ebx", 0 },
	[2] = { "ecx", 0 },
	[3] = { "edx", 0 },
};

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

void *putreg(reg_t *r)
{
	r->refcnt--;
}

// i386 assembly
void x86_mov_rm(reg_t *reg, syment_t *mem)
{
	switch (mem->cate) {
	case VAR_OBJ:
		printf("mov\t%s, [ebp - %d];\n", reg->name, OFFSET(mem));
		break;
	default:
		unlikely();
	}
}
