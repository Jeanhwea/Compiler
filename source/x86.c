#include "x86.h"
#include "asm.h"
#include "common.h"
#include "debug.h"
#include "ir.h"
#include "symtab.h"
#include "util.h"
#include <stdio.h>
#include <string.h>

////////////////////////////////////////////////////////////////////////////////
// register table
reg_t regs[4] = {
	[0] = { "eax", 0 },
	[1] = { "ebx", 0 },
	[2] = { "ecx", 0 },
	[3] = { "edx", 0 },
};

// Alloc a register
reg_t *allocreg()
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

// Lock specific register
reg_t *lockreg(char *name)
{
	for (int i = 0; i < sizeof(regs) / sizeof(reg_t); ++i) {
		reg_t *r = &regs[i];
		if (!strcmp(r->name, name) && r->refcnt == 0) {
			r->refcnt++;
			return r;
		}
	}

	panic("NO_REGISTER_LEFT");
	return 0;
}

// Free a register
void freereg(reg_t *r)
{
	r->refcnt--;
}

progcode_t prog;

////////////////////////////////////////////////////////////////////////////////
// i386 instructions
static char addrbuf[16];
static char *addr(syment_t *e)
{
	sprintf(addrbuf, "[%s-%d]", EBPREG, ALIGN * e->off);
	return addrbuf;
}

static char numbuf[16];
static char *tostr(int num)
{
	sprintf(numbuf, "%d", num);
	return numbuf;
}

static char srdbuf[16];
static char *sround(char *label)
{
	sprintf(srdbuf, "[%s]", label);
	return srdbuf;
}

// send label
void addlabel(char *label)
{
	x86i_t *i = &prog.text[prog.itext++];
	i->islab = TRUE;
	strncpy(i->op, label, MAXOPLEN);
}

// send data
void adddata3(char *name, char *initval)
{
	x86i_t *d = &prog.data[prog.idata++];
	d->islab = FALSE;
	strncpy(d->op, name, MAXOPLEN);
	strncpy(d->fa, initval, MAXOPLEN);
}

// send text/code
void addcode4(char *op, char *fa, char *fb, char *extra)
{
	x86i_t *i = &prog.text[prog.itext++];
	i->islab = FALSE;
	strncpy(i->op, op, MAXOPLEN);
	strncpy(i->fa, fa, MAXOPLEN);
	strncpy(i->fb, fb, MAXOPLEN);
	strncpy(i->et, extra, MAXOPLEN);
}

void addcode3(char *op, char *fa, char *fb)
{
	addcode4(op, fa, fb, "");
}

void addcode2(char *op, char *fa)
{
	addcode4(op, fa, "", "");
}

void addcode1(char *op)
{
	addcode4(op, "", "", "");
}

void progdump()
{
	msg("section .text\n");
	for (int k = 0; k < prog.itext; ++k) {
		x86i_t *i = &prog.text[k];
		if (i->islab) {
			msg("%s:\n", i->op);
			continue;
		}
		if (strlen(i->et)) {
			msg("\t%s\t%s, %s\t; %s\n", i->op, i->fa, i->fb, i->et);
		} else if (strlen(i->fb)) {
			msg("\t%s\t%s, %s\n", i->op, i->fa, i->fb);
		} else if (strlen(i->fa)) {
			msg("\t%s\t%s\n", i->op, i->fa);
		} else if (strlen(i->op)) {
			msg("\t%s\n", i->op);
		} else {
			unlikely();
		}
	}

	if (!prog.idata)
		return;

	msg("section .data\n");
	for (int k = 0; k < prog.idata; ++k) {
		x86i_t *d = &prog.data[k];
		msg("\t%s db '%s', 0\n", d->op, d->fa);
	}
}

void x86_iolib_exit()
{
	addlabel(LIBEXIT);
	addcode3("mov", "eax", "1"); // syscall number
	addcode3("xor", "ebx", "ebx"); // return value
	addcode2("int", "0x80");
}

void x86_iolib_wrtchar()
{
	adddata3("_chrbuf", "x");

	addlabel(LIBWCHR);
	addcode3("mov", "eax", "4");
	addcode3("mov", "ebx", "1");
	addcode3("mov", "ecx", "_chrbuf");
	addcode3("mov", "edx", "1");
	addcode2("int", "0x80");
	addcode1("ret");
}

void x86_iolib_wrtint()
{
	adddata3("_intbuf", "????????????????");

	addlabel(LIBWINT);
	addcode3("xor", "edi", "edi"); // negtive flag
	addcode3("cmp", "eax", "0");
	addcode2("jnl", "_notneg");
	addcode2("inc", "edi");
	addcode2("neg", "eax");
	addlabel("_notneg");
	addcode3("mov", "ebx", "10"); // number base
	addcode3("xor", "ecx", "ecx"); // number string length
	addcode3("mov", "esi", "_intbuf+15"); // number string pointer
	addlabel("_loopdigit");
	addcode3("xor", "edx", "edx");
	addcode2("div", "ebx");
	addcode3("add", "edx", "'0'");
	addcode3("mov", "[esi]", "dl");
	addcode2("dec", "esi");
	addcode2("inc", "ecx");
	addcode3("test", "eax", "eax");
	addcode2("jnz", "_loopdigit");
	addcode3("test", "edi", "edi");
	addcode2("jnz", "_negsign");
	addcode2("inc", "esi");
	addcode2("jmp", "_wrtint");
	addlabel("_negsign");
	addcode3("mov", "byte[esi]", "'-'");
	addcode2("inc", "ecx");
	addlabel("_wrtint");
	addcode3("mov", "edx", "ecx"); // string length
	addcode3("mov", "eax", "4"); // syscall number, NR
	addcode3("mov", "ebx", "1"); // fd: 1=stdout
	addcode3("mov", "ecx", "esi"); // ptr to string buffer
	addcode2("int", "0x80");
	addcode1("ret");
}

void x86_init()
{
	addcode2("global", "_start");

	x86_iolib_wrtchar();
	x86_iolib_wrtint();
	x86_iolib_exit();
}

void x86_enter(syment_t *e)
{
	if (!strcmp(e->name, "@main")) {
		addlabel("_start");
		addcode2("push", EBPREG);
		addcode3("mov", EBPREG, ESPREG);
	} else {
		addlabel(e->name);
	}
}

void x86_mov(reg_t *reg, syment_t *var)
{
	addcode4("mov", reg->name, addr(var), var->label);
}

void x86_mov2(syment_t *var, reg_t *reg)
{
	addcode4("mov", addr(var), reg->name, var->label);
}

void x86_mov3(reg_t *reg, syment_t *arr, reg_t *off)
{
	addcode4("lea", IDXREG, addr(arr), arr->label);
	addcode3("imul", off->name, tostr(ALIGN));
	addcode3("sub", IDXREG, off->name);
	addcode3("mov", reg->name, sround(IDXREG));
}

void x86_mov4(syment_t *arr, reg_t *off, reg_t *reg)
{
	addcode4("lea", IDXREG, addr(arr), arr->label);
	addcode3("imul", off->name, tostr(ALIGN));
	addcode3("sub", IDXREG, off->name);
	addcode3("mov", sround(IDXREG), reg->name);
}

void x86_mov5(reg_t *r1, reg_t *r2)
{
	addcode3("mov", r1->name, r2->name);
}

void x86_mov6(reg_t *reg, int num)
{
	addcode3("mov", reg->name, tostr(num));
}

void x86_lea(reg_t *reg, syment_t *var)
{
	addcode3("lea", reg->name, addr(var));
}

void x86_lea2(reg_t *reg, syment_t *arr, reg_t *off)
{
	addcode3("lea", reg->name, addr(arr));
	addcode3("imul", off->name, tostr(ALIGN));
	addcode3("sub", reg->name, off->name);
}

void x86_add(reg_t *r1, reg_t *r2)
{
	addcode3("add", r1->name, r2->name);
}

void x86_sub(reg_t *r1, reg_t *r2)
{
	addcode3("sub", r1->name, r2->name);
}

void x86_mul(reg_t *r1, reg_t *r2)
{
	addcode3("imul", r1->name, r2->name);
}

// idiv (r/imm32)
//    edx:eax / (r/imm32)
// result:
//    eax <- quotient
//    edx <- remainder
reg_t *x86_div(reg_t *r1, reg_t *eax, reg_t *edx)
{
	addcode3("xor", edx->name, edx->name);
	addcode2("div", r1->name);
	return eax;
}

void x86_neg(reg_t *r1)
{
	addcode2("neg", r1->name);
}

void x86_inc(reg_t *r1)
{
	addcode2("inc", r1->name);
}

void x86_dec(reg_t *r1)
{
	addcode2("dec", r1->name);
}

void x86_pop(reg_t *reg)
{
	addcode2("pop", reg->name);
}

void x86_push(reg_t *reg)
{
	addcode2("push", reg->name);
}

void x86_push2(syment_t *var)
{
	addcode2("push", var->label);
}

void x86_call(syment_t *func)
{
	addcode2("call", func->label);
	int off = ALIGN * (func->stab->varoff + func->stab->tmpoff);
	addcode3("add", ESPREG, tostr(off));
}

void x86_ret()
{
	addcode1("ret");
}

reg_t *x86_syscall(char *func, reg_t *eax)
{
	addcode2("call", func);
	return eax;
}

void x86_label(syment_t *lab)
{
	addlabel(lab->label);
}

void x86_jmp(syment_t *lab)
{
	addcode2("jmp", lab->label);
}

void x86_cmp(reg_t *r1, reg_t *r2)
{
	addcode3("cmp", r1->name, r2->name);
}

void x86_jz(syment_t *lab)
{
	addcode2("jz", lab->label);
}

void x86_jnz(syment_t *lab)
{
	addcode2("jnz", lab->label);
}

void x86_jg(syment_t *lab)
{
	addcode2("jg", lab->label);
}

void x86_jng(syment_t *lab)
{
	addcode2("jng", lab->label);
}

void x86_jl(syment_t *lab)
{
	addcode2("jl", lab->label);
}

void x86_jnl(syment_t *lab)
{
	addcode2("jnl", lab->label);
}

void x86_sret(syment_t *reg)
{
	char retref[16];
	sprintf(retref, "[%s-%d]", EBPREG, ALIGN);
	addcode3("mov", retref, reg->name);
}
