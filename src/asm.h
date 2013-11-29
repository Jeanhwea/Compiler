/**
 * File: asm.h
 * Date: Nov 20, 2013
 * Author: Jeanhwea
 */

#ifndef ASM_H

#define ASM_H

typedef struct _String *StringSP;
typedef struct _String {
	char *loc;
	char *content;
	StringSP next;
} StringS;

void enter(SymTabESP e);
void movRM_asm(char *reg, SymTabESP e);
void leaRM_asm(char *reg, SymTabESP e);
void leaRA_asm(char *reg, char *offsetreg, SymTabESP e);
void movMR_asm(SymTabESP e, char *reg);
void movRA_asm(SymTabESP e, char *offsetreg, char *reg);
void movAR_asm(SymTabESP e, char *offsetreg, char *reg);
void movRR_asm(char *reg, char *reg2);
void movRI_asm(char *reg, int imm);
void addRI_asm(char *reg, int imm);
void addRR_asm(char *reg, char *reg2);
void subRR_asm(char *reg, char *reg2);
void mulRR_asm(char *reg, char *reg2);
void divR_asm(char *reg);
void neg_asm(char *reg);
void inc_asm(char *reg);
void dec_asm(char *reg);
void pusha_asm(SymTabESP e);
void pushR_asm(char *reg);
void popR_asm(char *reg);
void call_asm(SymTabESP e);
void ret_asm(void);
void label_asm(SymTabESP e);
void jmp_asm(SymTabESP e);
void cmpRR_asm(char *reg, char *reg2);
void jz_asm(SymTabESP e);
void jnz_asm(SymTabESP e);
void jg_asm(SymTabESP e);
void jng_asm(SymTabESP e);
void jl_asm(SymTabESP e);
void jnl_asm(SymTabESP e);
void retval_asm(char *reg);
void clsR_asm(char *reg);
char *allocs_asm(SymTabESP str);
void setString_asm();

/**
 *             RUNTIME STACK OVERVIEW
 *
 *                   high addr
 *               |    ... ...   |
 *               |    ... ...   |
 *               | parameter(1) |
 *               | parameter(2) |       ||
 *               | parameter(3) |       ||
 *               | saved ebp(3) |       ||
 *               | saved ebp(2) |       ||
 *      ebp+8 -> | saved ebp(1) |       ||
 *      ebp+4 -> | return addr  |       || stack
 *        ebp -> | prev ebp     |       || pointer
 *               | return value |       || increase
 *               | variables(1) |       ||
 *               | variables(2) |      \||/
 *               | variables(3) |       \/
 *               | temporary(1) |
 *               | temporary(2) |
 *               | temporary(3) |
 *               | saved ebx    |
 *               | saved esi    |
 *               | saved edi    |
 *               |    ... ...   |
 *        esp -> |    ... ...   |
 *
 **                   low addr
 */



#define RESERVED (4 * (1 + varc + tmpc))
#define DISPLAY (4 * (2 + e->level-1))
#define VAROFFSET (4 * (1 + e->posi+1))
#define TMPOFFSET (4 * (1 + varc + e->posi+1))
#define PARAOFFSET (4 * (2 + e->level-1 + parac - e->posi-1))

#endif /* end of include guard: ASM_H */
