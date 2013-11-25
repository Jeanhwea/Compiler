/**
 * File: elf.c
 * Date: Nov 23, 2013
 * Author: Jeanhwea
 */

#include "global.h"
#include "parse.h"
#include "symtab.h"
#include "quad.h"
#include "elf.h"
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
static void BRZA(SymTabESP r, SymTabESP s, SymTabESP d);
static void BNZA(SymTabESP r, SymTabESP s, SymTabESP d);
static void BGTA(SymTabESP r, SymTabESP s, SymTabESP d);
static void BLTA(SymTabESP r, SymTabESP s, SymTabESP d);
static void JMPA(SymTabESP r, SymTabESP s, SymTabESP d);
static void PUSHA(SymTabESP r, SymTabESP s, SymTabESP d);
static void POPA(SymTabESP r, SymTabESP s, SymTabESP d);
static void CALLA(SymTabESP r, SymTabESP s, SymTabESP d);
static void SRETA(SymTabESP r, SymTabESP s, SymTabESP d);
static void ENTERA(SymTabESP r, SymTabESP s, SymTabESP d);
static void FINA(SymTabESP r, SymTabESP s, SymTabESP d);
static void READA(SymTabESP r, SymTabESP s, SymTabESP d);
static void WRSA(SymTabESP r, SymTabESP s, SymTabESP d);
static void WRIA(SymTabESP r, SymTabESP s, SymTabESP d);
static void WRCA(SymTabESP r, SymTabESP s, SymTabESP d);
static void LABELA(SymTabESP r, SymTabESP s, SymTabESP d);

void ADDA(SymTabESP r, SymTabESP s, SymTabESP d)
{
	switch (r->obj) {
	case Var_Obj_t:
	case Tmp_Obj_t:
	case Para_Val_Obj_t:
	case Num_Obj_t:
		movRM_asm("ecx", r);
		break;
	default:
		fprintf(asmlist, "ELF BUG:57\n");
	}
	switch (s->obj) {
	case Var_Obj_t:
	case Tmp_Obj_t:
	case Para_Val_Obj_t:
	case Num_Obj_t:
		movRM_asm("edx", s);
		break;
	default:
		fprintf(asmlist, "ELF BUG:67\n");
	}
	switch (d->obj) {
	case Var_Obj_t:
	case Tmp_Obj_t:
		addRR_asm("ecx", "edx");
		movMR_asm(d, "ecx");
		break;
	default:
		fprintf(asmlist, "ELF BUG:75\n");
	}
}

void SUBA(SymTabESP r, SymTabESP s, SymTabESP d)
{
}

void MULA(SymTabESP r, SymTabESP s, SymTabESP d)
{
}

void DIVA(SymTabESP r, SymTabESP s, SymTabESP d)
{
}

void INCA(SymTabESP r, SymTabESP s, SymTabESP d)
{
}

void DECA(SymTabESP r, SymTabESP s, SymTabESP d)
{
}

void NEGA(SymTabESP r, SymTabESP s, SymTabESP d)
{
}

void LOADA(SymTabESP r, SymTabESP s, SymTabESP d)
{
	switch (s->obj) {
	case Var_Obj_t:
	case Tmp_Obj_t:
	case Num_Obj_t:
	case Para_Val_Obj_t:
		movRM_asm("eax", s);
		break;
	default:
		fprintf(errlist, "ELF BUG:199\n");
	}
	movRA_asm(r, "eax", "ecx");
	switch (d->obj) {
	case Var_Obj_t:
	case Tmp_Obj_t:
		movMR_asm(d, "ecx");
		break;
	default:
		fprintf(errlist, "ELF BUG:139\n");
	}
}

void ASSA(SymTabESP r, SymTabESP s, SymTabESP d)
{
	switch (r->obj) {
	case Var_Obj_t:
	case Tmp_Obj_t:
	case Num_Obj_t:
	case Para_Val_Obj_t:
		movRM_asm("ecx", r);
		break;
	default:
		fprintf(errlist, "ELF BUG:87\n");
	}
	switch (d->obj) {
	case Var_Obj_t:
		movMR_asm(d, "ecx");
		break;
	default:
		fprintf(errlist, "ELF BUG:92\n");
	}
}

void AARRA(SymTabESP r, SymTabESP s, SymTabESP d)
{
	switch (r->obj) {
	case Var_Obj_t:
	case Tmp_Obj_t:
	case Num_Obj_t:
	case Para_Val_Obj_t:
		movRM_asm("ecx", r);
		break;
	default:
		fprintf(errlist, "ELF BUG:139\n");
	}
	switch (s->obj) {
	case Var_Obj_t:
	case Tmp_Obj_t:
	case Num_Obj_t:
	case Para_Val_Obj_t:
		movRM_asm("eax", s);
		break;
	default:
		fprintf(errlist, "ELF BUG:149\n");
	}
	movAR_asm(d, "eax", "ecx");
}

void EQUA(SymTabESP r, SymTabESP s, SymTabESP d)
{
}

void NEQA(SymTabESP r, SymTabESP s, SymTabESP d)
{
}

void GTTA(SymTabESP r, SymTabESP s, SymTabESP d)
{
}

void GEQA(SymTabESP r, SymTabESP s, SymTabESP d)
{
}

void LSTA(SymTabESP r, SymTabESP s, SymTabESP d)
{
}

void LEQA(SymTabESP r, SymTabESP s, SymTabESP d)
{
}

void BRZA(SymTabESP r, SymTabESP s, SymTabESP d)
{
}

void BNZA(SymTabESP r, SymTabESP s, SymTabESP d)
{
}

void BGTA(SymTabESP r, SymTabESP s, SymTabESP d)
{
}

void BLTA(SymTabESP r, SymTabESP s, SymTabESP d)
{
}

void JMPA(SymTabESP r, SymTabESP s, SymTabESP d)
{
}

void PUSHA(SymTabESP r, SymTabESP s, SymTabESP d)
{
	switch (d->obj) {
	case Var_Obj_t:
		movRM_asm("ecx", d);
		pushR_asm("ecx");
		break;
	case Num_Obj_t:
		push_asm(d);
		break;
	default:
		fprintf(errlist, "ELF BUG:184\n");
	}
}

void POPA(SymTabESP r, SymTabESP s, SymTabESP d)
{
}

void CALLA(SymTabESP r, SymTabESP s, SymTabESP d)
{
	if (d == NULL) {
		call_asm(r);
	} else {
		fprintf(errlist, "ELF BUG:165\n");
	}
}

void SRETA(SymTabESP r, SymTabESP s, SymTabESP d)
{
}

void ENTERA(SymTabESP r, SymTabESP s, SymTabESP d)
{
	if (d == NULL) {
		fprintf(errlist, "ELF BUG:97\n");
		abort();
	}
	if (d->stp == NULL) {
		fprintf(errlist, "ELF BUG:104\n");
		abort();
	}
	label_asm(d);
	pushR_asm("ebp");
	movRR_asm("ebp", "esp");
	enter(d);
}

void FINA(SymTabESP r, SymTabESP s, SymTabESP d)
{
	movRR_asm("eax", "[ebp - 4]");
	movRR_asm("esp", "ebp");
	pop_asm("ebp");
	ret_asm();
}

void READA(SymTabESP r, SymTabESP s, SymTabESP d)
{
}

void WRSA(SymTabESP r, SymTabESP s, SymTabESP d)
{
}

void WRIA(SymTabESP r, SymTabESP s, SymTabESP d)
{
	movRM_asm("eax", d);
	fprintf(asmlist, "\tcall\tprint_int\n");
}

void WRCA(SymTabESP r, SymTabESP s, SymTabESP d)
{
}

void LABELA(SymTabESP r, SymTabESP s, SymTabESP d)
{
}

void cgen(QuadSP t)
{
	if (t == NULL) {
		fprintf(errlist, "ELF BUG:314\n");
		return ;
	}
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
	case BRZ_op:
		BRZA(t->r, t->s, t->d);
		break;
	case BNZ_op:
		BNZA(t->r, t->s, t->d);
		break;
	case BGT_op:
		BGTA(t->r, t->s, t->d);
		break;
	case BLT_op:
		BLTA(t->r, t->s, t->d);
		break;
	case JMP_op:
		JMPA(t->r, t->s, t->d);
		break;
	case PUSH_op:
		PUSHA(t->r, t->s, t->d);
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
	fprintf(asmlist, "%%include \"asm/io.asm\"\n");
	for (q = qlst; q != NULL; q = q->next) {
		cgen(q);
	}
}
