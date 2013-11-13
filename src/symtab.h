/**
 * File: symtab.h
 * Date: Nov 12, 2013
 * Author: Jeanhwea
 */
#ifndef SYMTAB_H

#define SYMTAB_H

#define MAXREFFENCE 100

typedef enum {
	Var_Sym_t, Fun_Sym_t, Proc_Sym_t,
	Arr_Sym_t, Para_Sym_t
} SymType;

typedef struct _SymtabES {
	char *name;
	int addr;
	SymType type;
	int decline;
	int refline[MAXREFFENCE];
} SymtabES;

#endif /* end of include guard: SYMTAB_H */
