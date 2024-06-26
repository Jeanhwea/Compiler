/**
 * File: elf.c
 * Date: Nov 23, 2013
 * Author: Jeanhwea
 */

#include "global.h"
#include "util.h"
#include "parse.h"
#include "symtab.h"
#include "quad.h"
#include "elf.h"
#include "reg.h"
#include "asm.h"

static void ADDA(SymTabESP r, SymTabESP s, SymTabESP d);
static void SUBA(SymTabESP r, SymTabESP s, SymTabESP d);
static void MULA(SymTabESP r, SymTabESP s, SymTabESP d);
static void DIVA(SymTabESP r, SymTabESP s, SymTabESP d);
static void INCA(SymTabESP r, SymTabESP s, SymTabESP d);
static void DECA(SymTabESP r, SymTabESP s, SymTabESP d);
static void NEGA(SymTabESP r, SymTabESP s, SymTabESP d);
static void LOADA(SymTabESP r, SymTabESP s, SymTabESP d);
static void ASSA(SymTabESP r, SymTabESP s, SymTabESP d);
static void AARRA(SymTabESP r, SymTabESP s, SymTabESP d);
static void EQUA(SymTabESP r, SymTabESP s, SymTabESP d);
static void NEQA(SymTabESP r, SymTabESP s, SymTabESP d);
static void GTTA(SymTabESP r, SymTabESP s, SymTabESP d);
static void GEQA(SymTabESP r, SymTabESP s, SymTabESP d);
static void LSTA(SymTabESP r, SymTabESP s, SymTabESP d);
static void LEQA(SymTabESP r, SymTabESP s, SymTabESP d);
static void JMPA(SymTabESP r, SymTabESP s, SymTabESP d);
static void PUSHA(SymTabESP r, SymTabESP s, SymTabESP d);
static void PUSHAA(SymTabESP r, SymTabESP s, SymTabESP d);
static void POPA(SymTabESP r, SymTabESP s, SymTabESP d);
static void CALLA(SymTabESP r, SymTabESP s, SymTabESP d);
static void SRETA(SymTabESP r, SymTabESP s, SymTabESP d);
static void ENTERA(SymTabESP r, SymTabESP s, SymTabESP d);
static void FINA(SymTabESP r, SymTabESP s, SymTabESP d);
static void READA(SymTabESP r, SymTabESP s, SymTabESP d);
static void READCA(SymTabESP r, SymTabESP s, SymTabESP d);
static void WRSA(SymTabESP r, SymTabESP s, SymTabESP d);
static void WRIA(SymTabESP r, SymTabESP s, SymTabESP d);
static void WRCA(SymTabESP r, SymTabESP s, SymTabESP d);
static void LABELA(SymTabESP r, SymTabESP s, SymTabESP d);

void ADDA(SymTabESP r, SymTabESP s, SymTabESP d)
{
	int reg1, reg2;
	reg1 = getReg();
	reg2 = getReg();
	switch (r->obj) {
	case Var_Obj_t:
	case Tmp_Obj_t:
	case Para_Val_Obj_t:
	case Para_Ref_Obj_t:
	case Num_Obj_t:
	case Const_Obj_t:
		// movRM_asm("ecx", r);
		movRM_asm(tmp_regs[reg1], r);
		break;
	default:
		fprintf(errlist, "ELF BUG:57\n");
	}
	switch (s->obj) {
	case Var_Obj_t:
	case Tmp_Obj_t:
	case Para_Val_Obj_t:
	case Para_Ref_Obj_t:
	case Num_Obj_t:
	case Const_Obj_t:
		// movRM_asm("edx", s);
		movRM_asm(tmp_regs[reg2], s);
		break;
	default:
		fprintf(errlist, "ELF BUG:67\n");
	}
	switch (d->obj) {
	case Var_Obj_t:
	case Tmp_Obj_t:
	case Para_Val_Obj_t:
	case Para_Ref_Obj_t:
		// addRR_asm("ecx", "edx");
		addRR_asm(tmp_regs[reg1], tmp_regs[reg2]);
		// movMR_asm(d, "ecx");
		movMR_asm(d, tmp_regs[reg1]);
		break;
	default:
		fprintf(errlist, "ELF BUG:75\n");
	}
	relReg(reg1);
	relReg(reg2);
}

void SUBA(SymTabESP r, SymTabESP s, SymTabESP d)
{
	int reg1, reg2;
	reg1 = getReg();
	reg2 = getReg();
	switch (r->obj) {
	case Var_Obj_t:
	case Tmp_Obj_t:
	case Para_Val_Obj_t:
	case Para_Ref_Obj_t:
	case Num_Obj_t:
	case Const_Obj_t:
		// movRM_asm("ecx", r);
		movRM_asm(tmp_regs[reg1], r);
		break;
	default:
		fprintf(errlist, "ELF BUG:89\n");
	}
	switch (s->obj) {
	case Var_Obj_t:
	case Tmp_Obj_t:
	case Para_Val_Obj_t:
	case Para_Ref_Obj_t:
	case Num_Obj_t:
	case Const_Obj_t:
		// movRM_asm("edx", s);
		movRM_asm(tmp_regs[reg2], s);
		break;
	default:
		fprintf(errlist, "ELF BUG:67\n");
	}
	switch (d->obj) {
	case Var_Obj_t:
	case Tmp_Obj_t:
	case Para_Val_Obj_t:
	case Para_Ref_Obj_t:
		// subRR_asm("ecx", "edx");
		subRR_asm(tmp_regs[reg1], tmp_regs[reg2]);
		// movMR_asm(d, "ecx");
		movMR_asm(d, tmp_regs[reg1]);
		break;
	default:
		fprintf(errlist, "ELF BUG:109\n");
	}
	relReg(reg1);
	relReg(reg2);
}

void MULA(SymTabESP r, SymTabESP s, SymTabESP d)
{
	int reg1, reg2;
	reg1 = getReg();
	reg2 = getReg();
	switch (r->obj) {
	case Var_Obj_t:
	case Tmp_Obj_t:
	case Para_Val_Obj_t:
	case Para_Ref_Obj_t:
	case Num_Obj_t:
	case Const_Obj_t:
		// movRM_asm("ecx", r);
		movRM_asm(tmp_regs[reg1], r);
		break;
	default:
		fprintf(errlist, "ELF BUG:128\n");
	}
	switch (s->obj) {
	case Var_Obj_t:
	case Tmp_Obj_t:
	case Para_Val_Obj_t:
	case Para_Ref_Obj_t:
	case Num_Obj_t:
	case Const_Obj_t:
		// movRM_asm("edx", s);
		movRM_asm(tmp_regs[reg2], s);
		break;
	default:
		fprintf(errlist, "ELF BUG:140\n");
	}
	switch (d->obj) {
	case Var_Obj_t:
	case Tmp_Obj_t:
	case Para_Val_Obj_t:
	case Para_Ref_Obj_t:
		// mulRR_asm("ecx", "edx");
		mulRR_asm(tmp_regs[reg1], tmp_regs[reg2]);
		// movMR_asm(d, "ecx");
		movMR_asm(d, tmp_regs[reg1]);
		break;
	default:
		fprintf(errlist, "ELF BUG:150\n");
	}
	relReg(reg1);
	relReg(reg2);
}

void DIVA(SymTabESP r, SymTabESP s, SymTabESP d)
{
	int reg1, reg2;
	reg1 = getReg();
	reg2 = getReg();
	switch (r->obj) {
	case Var_Obj_t:
	case Tmp_Obj_t:
	case Para_Val_Obj_t:
	case Para_Ref_Obj_t:
	case Num_Obj_t:
	case Const_Obj_t:
		clsR_asm("edx");
		movRM_asm("eax", r);
		break;
	default:
		fprintf(errlist, "ELF BUG:167\n");
	}
	switch (s->obj) {
	case Var_Obj_t:
	case Tmp_Obj_t:
	case Para_Val_Obj_t:
	case Para_Ref_Obj_t:
	case Num_Obj_t:
	case Const_Obj_t:
		movRM_asm("ecx", s);
		break;
	default:
		fprintf(errlist, "ELF BUG:139\n");
	}
	switch (d->obj) {
	case Var_Obj_t:
	case Tmp_Obj_t:
	case Para_Val_Obj_t:
	case Para_Ref_Obj_t:
	/**
	 * idiv (r/imm32)
	 * edx:eax / (r/imm32)
	 *
	 * result:
	 * eax <- quotient
	 * edx <- remainder
	 *
	 */
		divR_asm("ecx");
		movMR_asm(d, "eax");
		break;
	default:
		fprintf(errlist, "ELF BUG:177\n");
	}
	relReg(reg1);
	relReg(reg2);
}

void INCA(SymTabESP r, SymTabESP s, SymTabESP d)
{
	int reg1 = getReg();
	// movRM_asm("ecx", d);
	// inc_asm("ecx");
	// movMR_asm(d, "ecx");
	movRM_asm(tmp_regs[reg1], d);
	inc_asm(tmp_regs[reg1]);
	movMR_asm(d, tmp_regs[reg1]);
	relReg(reg1);
}

void DECA(SymTabESP r, SymTabESP s, SymTabESP d)
{
	int reg1 = getReg();
	// movRM_asm("ecx", d);
	// dec_asm("ecx");
	// movMR_asm(d, "ecx");
	movRM_asm(tmp_regs[reg1], d);
	dec_asm(tmp_regs[reg1]);
	movMR_asm(d, tmp_regs[reg1]);
	relReg(reg1);
}

void NEGA(SymTabESP r, SymTabESP s, SymTabESP d)
{
	int reg1 = getReg();
	// movRM_asm("ecx", r);
	// neg_asm("ecx");
	// movMR_asm(d, "ecx");
	movRM_asm(tmp_regs[reg1], d);
	neg_asm(tmp_regs[reg1]);
	movMR_asm(d, tmp_regs[reg1]);
	relReg(reg1);
}

void LOADA(SymTabESP r, SymTabESP s, SymTabESP d)
{
	int reg1, reg2;
	reg1 = getReg();
	reg2 = getReg();
	switch (s->obj) {
	case Var_Obj_t:
	case Tmp_Obj_t:
	case Num_Obj_t:
	case Const_Obj_t:
	case Para_Val_Obj_t:
	case Para_Ref_Obj_t:
		// movRM_asm("eax", s);
		movRM_asm(tmp_regs[reg1], s);
		break;
	default:
		fprintf(errlist, "ELF BUG:199\n");
	}
	// movRA_asm(r, "eax", "ecx");
	movRA_asm(r, tmp_regs[reg1], tmp_regs[reg2]);
	switch (d->obj) {
	case Var_Obj_t:
	case Tmp_Obj_t:
		// movMR_asm(d, "ecx");
		movMR_asm(d, tmp_regs[reg2]);
		break;
	default:
		fprintf(errlist, "ELF BUG:139\n");
	}
	relReg(reg1);
	relReg(reg2);
}

void ASSA(SymTabESP r, SymTabESP s, SymTabESP d)
{
	int reg1 = getReg();
	switch (r->obj) {
	case Var_Obj_t:
	case Tmp_Obj_t:
	case Num_Obj_t:
	case Const_Obj_t:
	case Para_Val_Obj_t:
	case Para_Ref_Obj_t:
		// movRM_asm("ecx", r);
		movRM_asm(tmp_regs[reg1], r);
		break;
	default:
		fprintf(errlist, "ELF BUG:87\n");
	}
	switch (d->obj) {
	case Var_Obj_t:
	case Tmp_Obj_t:
	case Para_Val_Obj_t:
	case Para_Ref_Obj_t:
		// movMR_asm(d, "ecx");
		movMR_asm(d, tmp_regs[reg1]);
		break;
	default:
		fprintf(errlist, "ELF BUG:92\n");
	}
	relReg(reg1);
}

void AARRA(SymTabESP r, SymTabESP s, SymTabESP d)
{
	int reg1, reg2;
	reg1 = getReg();
	reg2 = getReg();
	switch (r->obj) {
	case Var_Obj_t:
	case Tmp_Obj_t:
	case Num_Obj_t:
	case Const_Obj_t:
	case Para_Val_Obj_t:
	case Para_Ref_Obj_t:
		// movRM_asm("ecx", r);
		movRM_asm(tmp_regs[reg1], r);
		break;
	default:
		fprintf(errlist, "ELF BUG:139\n");
	}
	switch (s->obj) {
	case Var_Obj_t:
	case Tmp_Obj_t:
	case Num_Obj_t:
	case Const_Obj_t:
	case Para_Val_Obj_t:
	case Para_Ref_Obj_t:
		// movRM_asm("eax", s);
		movRM_asm(tmp_regs[reg2], s);
		break;
	default:
		fprintf(errlist, "ELF BUG:149\n");
	}
	// movAR_asm(d, "eax", "ecx");
	movAR_asm(d, tmp_regs[reg2], tmp_regs[reg1]);
	relReg(reg1);
	relReg(reg2);
}

void EQUA(SymTabESP r, SymTabESP s, SymTabESP d)
{
	int reg1, reg2;
	reg1 = getReg();
	reg2 = getReg();
	switch (r->obj) {
	case Var_Obj_t:
	case Tmp_Obj_t:
	case Num_Obj_t:
	case Const_Obj_t:
	case Para_Val_Obj_t:
	case Para_Ref_Obj_t:
		// movRM_asm("eax", r);
		movRM_asm(tmp_regs[reg1], r);
		break;
	default:
		fprintf(errlist, "ELF BUG:228\n");
	}
	switch (s->obj) {
	case Var_Obj_t:
	case Tmp_Obj_t:
	case Num_Obj_t:
	case Const_Obj_t:
	case Para_Val_Obj_t:
	case Para_Ref_Obj_t:
		// movRM_asm("ecx", s);
		movRM_asm(tmp_regs[reg2],s);
		break;
	default:
		fprintf(errlist, "ELF BUG:238\n");
	}
	// cmpRR_asm("eax", "ecx");
	cmpRR_asm(tmp_regs[reg1], tmp_regs[reg2]);
	jz_asm(d);
	relReg(reg1);
	relReg(reg2);
}

void NEQA(SymTabESP r, SymTabESP s, SymTabESP d)
{
	int reg1, reg2;
	reg1 = getReg();
	reg2 = getReg();
	switch (r->obj) {
	case Var_Obj_t:
	case Tmp_Obj_t:
	case Num_Obj_t:
	case Const_Obj_t:
	case Para_Val_Obj_t:
	case Para_Ref_Obj_t:
		// movRM_asm("eax", r);
		movRM_asm(tmp_regs[reg1], r);
		break;
	default:
		fprintf(errlist, "ELF BUG:228\n");
	}
	switch (s->obj) {
	case Var_Obj_t:
	case Tmp_Obj_t:
	case Num_Obj_t:
	case Const_Obj_t:
	case Para_Val_Obj_t:
	case Para_Ref_Obj_t:
		// movRM_asm("ecx", s);
		movRM_asm(tmp_regs[reg2],s);
		break;
	default:
		fprintf(errlist, "ELF BUG:238\n");
	}
	// cmpRR_asm("eax", "ecx");
	cmpRR_asm(tmp_regs[reg1], tmp_regs[reg2]);
	jnz_asm(d);
	relReg(reg1);
	relReg(reg2);
}

void GTTA(SymTabESP r, SymTabESP s, SymTabESP d)
{
	int reg1, reg2;
	reg1 = getReg();
	reg2 = getReg();
	switch (r->obj) {
	case Var_Obj_t:
	case Tmp_Obj_t:
	case Num_Obj_t:
	case Const_Obj_t:
	case Para_Val_Obj_t:
	case Para_Ref_Obj_t:
		// movRM_asm("eax", r);
		movRM_asm(tmp_regs[reg1], r);
		break;
	default:
		fprintf(errlist, "ELF BUG:228\n");
	}
	switch (s->obj) {
	case Var_Obj_t:
	case Tmp_Obj_t:
	case Num_Obj_t:
	case Const_Obj_t:
	case Para_Val_Obj_t:
	case Para_Ref_Obj_t:
		// movRM_asm("ecx", s);
		movRM_asm(tmp_regs[reg2],s);
		break;
	default:
		fprintf(errlist, "ELF BUG:238\n");
	}
	// cmpRR_asm("eax", "ecx");
	cmpRR_asm(tmp_regs[reg1], tmp_regs[reg2]);
	jg_asm(d);
	relReg(reg1);
	relReg(reg2);
}

void GEQA(SymTabESP r, SymTabESP s, SymTabESP d)
{
	int reg1, reg2;
	reg1 = getReg();
	reg2 = getReg();
	switch (r->obj) {
	case Var_Obj_t:
	case Tmp_Obj_t:
	case Num_Obj_t:
	case Const_Obj_t:
	case Para_Val_Obj_t:
	case Para_Ref_Obj_t:
		// movRM_asm("eax", r);
		movRM_asm(tmp_regs[reg1], r);
		break;
	default:
		fprintf(errlist, "ELF BUG:228\n");
	}
	switch (s->obj) {
	case Var_Obj_t:
	case Tmp_Obj_t:
	case Num_Obj_t:
	case Const_Obj_t:
	case Para_Val_Obj_t:
	case Para_Ref_Obj_t:
		// movRM_asm("ecx", s);
		movRM_asm(tmp_regs[reg2],s);
		break;
	default:
		fprintf(errlist, "ELF BUG:238\n");
	}
	// cmpRR_asm("eax", "ecx");
	cmpRR_asm(tmp_regs[reg1], tmp_regs[reg2]);
	jnl_asm(d);
	relReg(reg1);
	relReg(reg2);
}

void LSTA(SymTabESP r, SymTabESP s, SymTabESP d)
{
	int reg1, reg2;
	reg1 = getReg();
	reg2 = getReg();
	switch (r->obj) {
	case Var_Obj_t:
	case Tmp_Obj_t:
	case Num_Obj_t:
	case Const_Obj_t:
	case Para_Val_Obj_t:
	case Para_Ref_Obj_t:
		// movRM_asm("eax", r);
		movRM_asm(tmp_regs[reg1], r);
		break;
	default:
		fprintf(errlist, "ELF BUG:228\n");
	}
	switch (s->obj) {
	case Var_Obj_t:
	case Tmp_Obj_t:
	case Num_Obj_t:
	case Const_Obj_t:
	case Para_Val_Obj_t:
	case Para_Ref_Obj_t:
		// movRM_asm("ecx", s);
		movRM_asm(tmp_regs[reg2],s);
		break;
	default:
		fprintf(errlist, "ELF BUG:238\n");
	}
	// cmpRR_asm("eax", "ecx");
	cmpRR_asm(tmp_regs[reg1], tmp_regs[reg2]);
	jl_asm(d);
	relReg(reg1);
	relReg(reg2);
}

void LEQA(SymTabESP r, SymTabESP s, SymTabESP d)
{
	int reg1, reg2;
	reg1 = getReg();
	reg2 = getReg();
	switch (r->obj) {
	case Var_Obj_t:
	case Tmp_Obj_t:
	case Num_Obj_t:
	case Const_Obj_t:
	case Para_Val_Obj_t:
	case Para_Ref_Obj_t:
		// movRM_asm("eax", r);
		movRM_asm(tmp_regs[reg1], r);
		break;
	default:
		fprintf(errlist, "ELF BUG:228\n");
	}
	switch (s->obj) {
	case Var_Obj_t:
	case Tmp_Obj_t:
	case Num_Obj_t:
	case Const_Obj_t:
	case Para_Val_Obj_t:
	case Para_Ref_Obj_t:
		// movRM_asm("ecx", s);
		movRM_asm(tmp_regs[reg2],s);
		break;
	default:
		fprintf(errlist, "ELF BUG:238\n");
	}
	// cmpRR_asm("eax", "ecx");
	cmpRR_asm(tmp_regs[reg1], tmp_regs[reg2]);
	jng_asm(d);
	relReg(reg1);
	relReg(reg2);
}

void JMPA(SymTabESP r, SymTabESP s, SymTabESP d)
{
	jmp_asm(d);
}

void PUSHA(SymTabESP r, SymTabESP s, SymTabESP d)
{
	switch (d->obj) {
	case Var_Obj_t:
	case Tmp_Obj_t:
	case Num_Obj_t:
	case Const_Obj_t:
	case Para_Val_Obj_t:
	case Para_Ref_Obj_t:
		movRM_asm("ecx", d);
		pushR_asm("ecx");
		break;
	default:
		fprintf(errlist, "ELF BUG:184\n");
	}
}

void PUSHAA(SymTabESP r, SymTabESP s, SymTabESP d)
{
	switch (d->obj) {
	case Var_Obj_t:
	case Tmp_Obj_t:
	case Para_Val_Obj_t:
	case Para_Ref_Obj_t:
		leaRM_asm("ecx", d);
		pushR_asm("ecx");
		break;
	case Array_Obj_t:
		movRM_asm("edx", s);
		leaRA_asm("ecx", "edx", d);
		pushR_asm("ecx");
		break;
	default:
		fprintf(errlist, "ELF BUG:184\n");
	}
}

void POPA(SymTabESP r, SymTabESP s, SymTabESP d)
{
	fprintf(asmlist, "TODO\n");
}

void CALLA(SymTabESP r, SymTabESP s, SymTabESP d)
{
	if (d == NULL) {
		call_asm(r);
	} else {
		call_asm(r);
		movMR_asm(d, "eax");
	}
}

void SRETA(SymTabESP r, SymTabESP s, SymTabESP d)
{
	int reg = getReg();
	// movRM_asm("ecx", r);
	// retval_asm("ecx");
	movRM_asm(tmp_regs[reg], r);
	retval_asm(tmp_regs[reg]);
	relReg(reg);
}

void ENTERA(SymTabESP r, SymTabESP s, SymTabESP d)
{
	if (d == NULL) {
		fprintf(errlist, "ELF BUG:97\n");
		assert(0);
	}
	if (d->stp == NULL) {
		fprintf(errlist, "ELF BUG:104\n");
		assert(0);
	}
	label_asm(d);
	pushR_asm("ebp");
	movRR_asm("ebp", "esp");
	enter(d);
	/* saved general register */
	pushR_asm("ebx");
	pushR_asm("esi");
	pushR_asm("edi");
}

void FINA(SymTabESP r, SymTabESP s, SymTabESP d)
{
	/* restore saved register */
	popR_asm("edi");
	popR_asm("esi");
	popR_asm("ebx");
	movRR_asm("eax", "[ebp - 4]");
	movRR_asm("esp", "ebp");
	popR_asm("ebp");
	ret_asm();
	setString_asm();
}

void READA(SymTabESP r, SymTabESP s, SymTabESP d)
{
	fprintf(asmlist, "\tcall\tscan_int\n");
	movMR_asm(d, "eax");
}

void READCA(SymTabESP r, SymTabESP s, SymTabESP d)
{
	fprintf(asmlist, "\tcall\tscan_char\n");
	movMR_asm(d, "eax");
}

void WRSA(SymTabESP r, SymTabESP s, SymTabESP d)
{
	char *loc;
	loc = allocs_asm(d);
	movRR_asm("eax", loc);
	fprintf(asmlist, "\tcall\tprint_string\n");
}

void WRIA(SymTabESP r, SymTabESP s, SymTabESP d)
{
	movRM_asm("eax", d);
	if (d->type == Char_Type_t)
		fprintf(asmlist, "\tcall\tprint_char\n");
	else
		fprintf(asmlist, "\tcall\tprint_int\n");
}

void WRCA(SymTabESP r, SymTabESP s, SymTabESP d)
{
	movRM_asm("eax", d);
	fprintf(asmlist, "\tcall\tprint_char\n");
}

void LABELA(SymTabESP r, SymTabESP s, SymTabESP d)
{
	label_asm(d);
}

void cgen(QuadSP t)
{
	if (t == NULL) {
		fprintf(errlist, "ELF BUG:314\n");
		return ;
	}
	if (t->rm_flag) return ;
	switch (t->op) {
	case ADD_op:
		ADDA(t->r, t->s, t->d);
		break;
	case SUB_op:
		SUBA(t->r, t->s, t->d);
		break;
	case MUL_op:
		MULA(t->r, t->s, t->d);
		break;
	case DIV_op:
		DIVA(t->r, t->s, t->d);
		break;
	case INC_op:
		INCA(t->r, t->s, t->d);
		break;
	case DEC_op:
		DECA(t->r, t->s, t->d);
		break;
	case NEG_op:
		NEGA(t->r, t->s, t->d);
		break;
	case LOAD_op:
		LOADA(t->r, t->s, t->d);
		break;
	case ASS_op:
		ASSA(t->r, t->s, t->d);
		break;
	case AARR_op:
		AARRA(t->r, t->s, t->d);
		break;
	case EQU_op:
		EQUA(t->r, t->s, t->d);
		break;
	case NEQ_op:
		NEQA(t->r, t->s, t->d);
		break;
	case GTT_op:
		GTTA(t->r, t->s, t->d);
		break;
	case GEQ_op:
		GEQA(t->r, t->s, t->d);
		break;
	case LST_op:
		LSTA(t->r, t->s, t->d);
		break;
	case LEQ_op:
		LEQA(t->r, t->s, t->d);
		break;
	case JMP_op:
		JMPA(t->r, t->s, t->d);
		break;
	case PUSH_op:
		PUSHA(t->r, t->s, t->d);
		break;
	case PUSHA_op:
		PUSHAA(t->r, t->s, t->d);
		break;
	case POP_op:
		POPA(t->r, t->s, t->d);
		break;
	case CALL_op:
		CALLA(t->r, t->s, t->d);
		break;
	case SRET_op:
		SRETA(t->r, t->s, t->d);
		break;
	case ENTER_op:
		ENTERA(t->r, t->s, t->d);
		break;
	case FIN_op:
		FINA(t->r, t->s, t->d);
		break;
	case READ_op:
		READA(t->r, t->s, t->d);
		break;
	case READC_op:
		READCA(t->r, t->s, t->d);
		break;
	case WRS_op:
		WRSA(t->r, t->s, t->d);
		break;
	case WRI_op:
		WRIA(t->r, t->s, t->d);
		break;
	case WRC_op:
		WRCA(t->r, t->s, t->d);
		break;
	case LABEL_op:
		LABELA(t->r, t->s, t->d);
		break;
	default:
		fprintf(errlist, "ELF BUG:420\n");
	}
}

void elf(void)
{
	QuadSP q;
	fprintf(asmlist, "; ELF32 on Ubuntu 12.04 \n");
	fprintf(asmlist, "; NASM version 2.09.10 \n");
	fprintf(asmlist, "; GCC version 4.6.3 \n");
	ioasm();
	//fprintf(asmlist, "%%include \"asm/io.asm\"\n");
	for (q = qhead; q != NULL; q = q->next) {
		cgen(q);
	}
}

void elf_header(void)
{
	fprintf(asmlist, "; ELF32 on Ubuntu 12.04 \n");
	fprintf(asmlist, "; NASM version 2.09.10 \n");
	fprintf(asmlist, "; GCC version 4.6.3 \n");
	ioasm();
}