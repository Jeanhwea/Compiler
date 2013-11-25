/**
 * File: asm.h
 * Date: Nov 20, 2013
 * Author: Jeanhwea
 */

#ifndef ASM_H

#define ASM_H

void enter(SymTabESP e);
void movRM_asm(char *reg, SymTabESP e);
void movMR_asm(SymTabESP e, char *reg);
void movRR_asm(char *reg, char *reg2);
void movRA_asm(SymTabESP e, char *offsetreg, char *reg);
void movAR_asm(SymTabESP e, char *offsetreg, char *reg);
void addRI_asm(char *reg, int imm);
void addRR_asm(char *reg, char *reg2);
void push_asm(SymTabESP e);
void pushR_asm(char *reg);
void pop_asm(char *reg);
void call_asm(SymTabESP e);
void ret_asm(void);
void label_asm(SymTabESP e);

#define DISPLAY (4 * (2 + e->level-1))
#define VAROFFSET (4 * (1 + e->posi+1))
#define TMPOFFSET (4 * (1 + varc + e->posi+1))
#define PARAOFFSET (4 * (2 + lvl-1 + parac - e->posi-1))

#endif /* end of include guard: ASM_H */
