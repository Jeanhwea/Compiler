#include "x86.h"
#include "asm.h"
#include "common.h"
#include "debug.h"
#include "global.h"
#include "ir.h"
#include "symtab.h"
#include "util.h"
#include <stdio.h>
#include <string.h>

////////////////////////////////////////////////////////////////////////////////
// register table
reg_t regs[4] = {
	[0] = { REG_RA, 0 },
	[1] = { REG_RB, 0 },
	[2] = { REG_RC, 0 },
	[3] = { REG_RD, 0 },
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
	sprintf(addrbuf, "[%s-%d]", REG_BP, ALIGN * e->off);
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
void adddata2(char *name, char *initval)
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
	fprintf(target, "section .text\n");
	for (int k = 0; k < prog.itext; ++k) {
		x86i_t *i = &prog.text[k];
		if (i->islab) {
			fprintf(target, "%s:\n", i->op);
			continue;
		}
		if (strlen(i->et)) {
			fprintf(target, "\t%s\t%s, %s\t; %s\n", i->op, i->fa,
				i->fb, i->et);
		} else if (strlen(i->fb)) {
			fprintf(target, "\t%s\t%s, %s\n", i->op, i->fa, i->fb);
		} else if (strlen(i->fa)) {
			fprintf(target, "\t%s\t%s\n", i->op, i->fa);
		} else if (strlen(i->op)) {
			fprintf(target, "\t%s\n", i->op);
		} else {
			unlikely();
		}
	}

	if (!prog.idata)
		return;

	fprintf(target, "section .data\n");
	for (int k = 0; k < prog.idata; ++k) {
		x86i_t *d = &prog.data[k];
		fprintf(target, "\t%s db '%s', 0\n", d->op, d->fa);
	}

	fclose(target);
}

void x86_iolib_exit()
{
	addlabel(LIBEXIT);
	addcode3("mov", REG_RA, "1"); // syscall number
	addcode3("xor", REG_RB, REG_RB); // return value
	addcode2("int", SYSCAL);
}

void x86_iolib_wrtchr()
{
	adddata2("_chrbuf", "?");

	addlabel(LIBWCHR);
	addcode3("mov", "[_chrbuf]", REG_RA);
	addcode3("mov", REG_RA, "4");
	addcode3("mov", REG_RB, "1");
	addcode3("mov", REG_RC, "_chrbuf");
	addcode3("mov", REG_RD, "1");
	addcode2("int", SYSCAL);
	addcode1("ret");
}

void x86_iolib_wrtstr()
{
	addlabel(LIBWSTR);
	addcode3("mov", REG_SI, REG_RA);
	addcode3("xor", REG_RC, REG_RC);
	addlabel("_loopnext");
	addcode3("mov", "cl", PTR_SI);
	addcode3("test", REG_RC, REG_RC);
	addcode2("jz", "_writestr");
	addcode2("inc", REG_SI);
	addcode2("jmp", "_loopnext");
	addlabel("_writestr");
	addcode3("sub", REG_SI, REG_RA);
	addcode3("mov", REG_RC, REG_RA);
	addcode3("mov", REG_RA, "4");
	addcode3("mov", REG_RB, "1");
	addcode3("mov", REG_RD, REG_SI);
	addcode2("int", SYSCAL);
	addcode1("ret");
}

void x86_iolib_wrtint()
{
	adddata2("_intbuf", "????????????????");

	addlabel(LIBWINT);
	addcode3("xor", REG_SI, REG_SI); // negtive flag
	addcode3("cmp", REG_RA, "0");
	addcode2("jnl", "_nonneg");
	addcode2("inc", REG_DI);
	addcode2("neg", REG_RA);
	addlabel("_nonneg");
	addcode3("mov", REG_RB, "10"); // number base
	addcode3("xor", REG_RC, REG_RC); // number string length
	addcode3("mov", REG_SI, "_intbuf+15"); // number string pointer
	addlabel("_loopdigit");
	addcode3("xor", REG_RD, REG_RD);
	addcode2("div", REG_RB);
	addcode3("add", REG_RD, "'0'");
	addcode3("mov", BTP_SI, "dl");
	addcode2("dec", REG_SI);
	addcode2("inc", REG_RC);
	addcode3("test", REG_RA, REG_RA);
	addcode2("jnz", "_loopdigit");
	addcode3("test", REG_DI, REG_DI);
	addcode2("jnz", "_negsign");
	addcode2("inc", REG_SI);
	addcode2("jmp", "_wrtint");
	addlabel("_negsign");
	addcode3("mov", BTP_SI, "'-'");
	addcode2("inc", REG_RC);
	addlabel("_wrtint");
	addcode3("mov", REG_RD, REG_RC); // string length
	addcode3("mov", REG_RA, "4"); // syscall number, NR
	addcode3("mov", REG_RB, "1"); // fd: 1=stdout
	addcode3("mov", REG_RC, REG_SI); // ptr to string buffer
	addcode2("int", SYSCAL);
	addcode1("ret");
}

void x86_iolib_readchr()
{
	adddata2("_scanbuf", "????????????????");

	addlabel(LIBRCHR);
	addcode3("mov", REG_RA, "3"); // syscall number, NR
	addcode3("mov", REG_RB, "0"); // fd: 0=stdin
	addcode3("mov", REG_RC, "_scanbuf"); // ptr to scan buffer
	addcode3("mov", REG_RD, "1"); // buffer size
	addcode2("int", SYSCAL);
	addcode3("xor", REG_RA, REG_RA); // save result to eax
	addcode3("mov", "al", "[_scanbuf]");
	addcode3("cmp", "al", "10"); // if ra == 'nl'(10), retry
	addcode2("jz", LIBRCHR);
	addcode1("ret");
}

void x86_iolib_readint()
{
	addlabel(LIBRINT);
	addcode1("ret");
}

void x86_init()
{
	addcode2("global", "_start");

	x86_iolib_readchr();
	x86_iolib_readint();
	x86_iolib_wrtchr();
	x86_iolib_wrtstr();
	x86_iolib_wrtint();
	x86_iolib_exit();
}

void x86_enter(syment_t *e)
{
	if (!strcmp(e->name, "@main")) {
		addlabel("_start");
		addcode2("push", REG_BP);
		addcode3("mov", REG_BP, REG_SP);
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
	addcode4("lea", REG_SI, addr(arr), arr->label);
	addcode3("imul", off->name, tostr(ALIGN));
	addcode3("sub", REG_SI, off->name);
	addcode3("mov", reg->name, sround(REG_SI));
}

void x86_mov4(syment_t *arr, reg_t *off, reg_t *reg)
{
	addcode4("lea", REG_SI, addr(arr), arr->label);
	addcode3("imul", off->name, tostr(ALIGN));
	addcode3("sub", REG_SI, off->name);
	addcode3("mov", sround(REG_SI), reg->name);
}

void x86_mov5(reg_t *r1, reg_t *r2)
{
	addcode3("mov", r1->name, r2->name);
}

void x86_mov6(reg_t *reg, int num)
{
	addcode3("mov", reg->name, tostr(num));
}

void x86_mov7(reg_t *reg, char *strconst)
{
	addcode3("mov", reg->name, strconst);
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

void x86_xor(reg_t *r1, reg_t *r2)
{
	addcode3("xor", r1->name, r2->name);
}

void x86_cls(reg_t *r1)
{
	addcode3("xor", r1->name, r1->name);
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
	addcode3("add", REG_SP, tostr(off));
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

void x86_sret(reg_t *reg)
{
	char retref[16];
	sprintf(retref, "[%s-%d]", REG_BP, ALIGN);
	addcode3("mov", retref, reg->name);
}

void x86_alloc_string(char *name, char *initval)
{
	adddata2(name, initval);
}
