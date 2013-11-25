/**
 * File: asm.c
 * Date: Nov 20, 2013
 * Author: Jeanhwea
 */

#include "global.h"
#include "parse.h"
#include "symtab.h"
#include "quad.h"
#include "asm.h"

/* current level */
int lvl;
/* current length of var region */
int varc;
/* current length of tmp region */
int tmpc;
/* current length of parameter region */
int parac;

void enter(SymTabESP e)
{
	SymTabSP st;
	int offset;
	if (e == NULL) {
		fprintf(errlist, "ASM BUG:25\n");
		exit(1);
	}
	if (e->obj == Fun_Obj_t || e->obj == Proc_Obj_t) {
		st = e->stp;
		if (st == NULL) {
			fprintf(asmlist, "ASM BUG:32\n");
			abort();
		}
		lvl = st->level;
		varc = st->posi_var;
		tmpc = st->posi_tmp;
		parac = st->posi_para;
		offset = 4 * (1 + varc + tmpc);
		fprintf(asmlist, "\tsub\tesp, %d\n", offset);
	} else {
		fprintf(asmlist, "ASM BUG:34\n");
	}
}

void movRM_asm(char *reg, SymTabESP e)
{
	switch (e->obj) {
	case Var_Obj_t:
		if (e->level == lvl) {
			fprintf(asmlist, "\tmov\t%s, [ebp - %d]\t; %s\n", 
				reg, VAROFFSET, e->label);
		} else if (e->level < lvl) {
			fprintf(asmlist, "\tmov\tesi, [ebp + %d]\t; %s\n",
				DISPLAY, e->label);
			fprintf(asmlist, "\tmov\t%s, [esi - %d]\n",
				reg, VAROFFSET);
		} else {
			fprintf(errlist, "ASM BUG:68\n");
		}
		break;
	case Tmp_Obj_t:
		if (e->level == lvl) {
			fprintf(asmlist, "\tmov\t%s, [ebp - %d]\t; %s\n",
				reg, TMPOFFSET, e->label);
		} else {
			fprintf(errlist, "ASM BUG:76");
		}
		break;
	case Para_Val_Obj_t:
		if (e->level == lvl) {
			fprintf(asmlist, "\tmov\t%s, [ebp + %d]\t; %s\n",
				reg, PARAOFFSET, e->label);
		} else {
			fprintf(errlist, "ASM BUG:107\n");
		}
		break;
	case Num_Obj_t:
		fprintf(asmlist, "\tmov\t%s, %s\n", reg, e->label);
		break;
	default:
		fprintf(errlist, "ASM BUG:88\n");
	}
}

void movMR_asm(SymTabESP e, char *reg)
{
	switch (e->obj) {
	case Var_Obj_t:
		if (e->level == lvl) {
			fprintf(asmlist, "\tmov\t[ebp - %d], %s\t; %s\n",
				VAROFFSET, reg, e->label);
		} else if (e->level < lvl) {
			fprintf(asmlist, "\tmov\tesi, [ebp + %d]\n",
				DISPLAY);
			fprintf(asmlist, "\tmov\t[esi - %d], %s\t; %s\n",
				VAROFFSET, reg, e->label);
		} else {
			fprintf(errlist, "ASM BUG:106\n");
		}
		break;
	case Tmp_Obj_t:
		if (e->level == lvl) {
			fprintf(asmlist, "\tmov\t[ebp - %d], %s\t; %s\n",
				TMPOFFSET, reg, e->label);
		} else {
			fprintf(errlist, "ASM BUG:113");
		}
		break;
	case Para_Val_Obj_t:
		if (e->level == lvl) {
			fprintf(asmlist, "\tmov\t[ebp + %d], %s\t; %s\n",
				PARAOFFSET, reg, e->label);
		} else {
			fprintf(errlist, "ASM BUG:117\n");
		}
		break;
	default:
		fprintf(errlist, "ASM BUG:126\n");
	}
}

void movRA_asm(SymTabESP e, char *offsetreg, char *reg)
{
	switch (e->obj) {
	case Array_Obj_t:
		if (e->level == lvl) {
			fprintf(asmlist, "\tlea\tedi, [ebp - %d]\t; %s\n",
				VAROFFSET, e->label);
			fprintf(asmlist, "\timul\t%s, %s, 4\n",
				offsetreg, offsetreg);
			fprintf(asmlist, "\tsub\tedi, %s\n", offsetreg);
			fprintf(asmlist, "\tmov\t%s, [edi]\n", reg);
		} else if (e->level < lvl) {
			fprintf(asmlist, "\tmov\tesi, [ebp + %d]\n",
				DISPLAY);
			fprintf(asmlist, "\tlea\tedi, [esi - %d]\t; %s\n",
				VAROFFSET, e->label);
			fprintf(asmlist, "\timul\t%s, %s, 4\n",
				offsetreg, offsetreg);
			fprintf(asmlist, "\tsub\tedi, %s\n", offsetreg);
			fprintf(asmlist, "\tmov\t%s, [edi]\n", reg);
		}
		break;
	default:
		fprintf(asmlist, "ASM BUG:143\n");
	}
}

void movAR_asm(SymTabESP e, char *offsetreg, char *reg)
{
	switch (e->obj) {
	case Array_Obj_t:
		if (e->level == lvl) {
			fprintf(asmlist, "\tlea\tedi, [ebp - %d]\t; %s\n",
				VAROFFSET, e->label);
			fprintf(asmlist, "\timul\t%s, %s, 4\n",
				offsetreg, offsetreg);
			fprintf(asmlist, "\tsub\tedi, %s\n", offsetreg);
			fprintf(asmlist, "\tmov\t[edi], %s\n", reg);
		} else if (e->level < lvl) {
			fprintf(asmlist, "\tmov\tesi, [ebp + %d]\n",
				DISPLAY);
			fprintf(asmlist, "\tlea\tedi, [esi - %d]\t; %s\n",
				VAROFFSET, e->label);
			fprintf(asmlist, "\timul\t%s, %s, 4\n",
				offsetreg, offsetreg);
			fprintf(asmlist, "\tsub\tedi, %s\n", offsetreg);
			fprintf(asmlist, "\tmov\t[edi], %s\n", reg);
		}
		break;
	default:
		fprintf(asmlist, "ASM BUG:143\n");
	}
}

void movRR_asm(char *reg, char *reg2)
{
	fprintf(asmlist, "\tmov\t%s, %s\n", reg, reg2);
}

void addRI_asm(char *reg, int imm)
{
	fprintf(asmlist, "\tadd\t%s, %d\n", reg, imm);
}

void addRR_asm(char *reg, char *reg2)
{
	fprintf(asmlist, "\tadd\t%s, %s\n", reg, reg2);
}

void push_asm(SymTabESP e)
{
	fprintf(asmlist, "\tpush\t%s\n", e->label);
}

void pushR_asm(char *reg)
{
	fprintf(asmlist, "\tpush\t%s\n", reg);
}

void pop_asm(char *reg)
{
	fprintf(asmlist, "\tpop\t%s\n", reg);
}

void call_asm(SymTabESP e)
{
	int i, offset;
	if (e->level == lvl) {
		fprintf(asmlist, "\tpush\tebp\t\t; display new\n");
		for (i = 1; i < e->level; i++) {
			offset = 4 * (e->level-1 + 2 - i);
			fprintf(asmlist, "\tmov\tedi, [ebp + %d]\n",
				offset);
			fprintf(asmlist, "\tpush\tedi\t\t; display new\n");
		}
		fprintf(asmlist, "\tcall\t%s\n", e->label);
		offset = 4 * (e->stp->posi_para + e->level);
		fprintf(asmlist, "\tadd\tesp, %d\n", offset);
	} else if (e->level < lvl) {
		for (i = 1; i < e->level; i++) {
			offset = 4 * (e->level-1 + 2 - i);
			fprintf(asmlist, "\tmov\tedi, [ebp + %d]\n",
				offset);
			fprintf(asmlist, "\tpush\tedi\t\t; display\n");
		}
		fprintf(asmlist, "\tcall\t%s\n", e->label);
		offset = 4 * (e->stp->posi_para + e->level);
		fprintf(asmlist, "\tadd\tesp, %d\n", offset);
	} else {
		fprintf(errlist, "ASM BUG:186\n");
	}
}

void ret_asm(void)
{
	fprintf(asmlist, "\tret\n");
}

void label_asm(SymTabESP e)
{
	if (e->obj == Fun_Obj_t || e->obj == Proc_Obj_t) {
		fprintf(asmlist, "\nSECTION .TEXT\n");
		// fprintf(asmlist, "\tALIGN 16\n");
		fprintf(asmlist, "\tGLOBAL %s\n", e->label);
		fprintf(asmlist, "%s:\n", e->label);
	} else if (e->obj == Label_Obj_t) {
		fprintf(asmlist, "%s:\n", e->label);
	}
}
