/**
 * File: symtab.h
 * Date: Nov 12, 2013
 * Author: Jeanhwea
 */
#ifndef SYMTAB_H

#define SYMTAB_H
/* hash size */
extern int HASHSIZE;
/* hash shift */
extern int SHIFT;

typedef struct _SymTabS *SymTabSP;
typedef struct _SymLineS *SymLineSP;
typedef struct _SymBucketS *SymBucketSP;
typedef struct _SymTabES *SymTabESP;

typedef enum {
	Const_Obj_t, Var_Obj_t, Nop_Obj_t,
	Proc_Obj_t, Fun_Obj_t
} Obj_t;

typedef enum {
	Int_Type_t, Char_Type_t, Array_Type_t,
	Nop_Type_t
} Type_t;

/**
 * symbol table stack 
 * is a stack that
 * manage symbol table in
 * each function
 */
typedef struct _SymTabS {
	SymBucketSP *sbp;
	char *ns; 		// namespace for a block
	SymTabSP prev;
	SymTabSP next;
} SymTabS;

/**
 * store which line a varible
 * be referenced
 */
typedef struct _SymLineS {
	int lineno;
	SymLineSP next;
} SymLineS;

/**
 * symbol table entry 
 * bucket list
 */
typedef struct _SymBucketS {
	SymTabESP ep;		// element infomation
	SymBucketSP next;
} SymBucketS;

typedef struct _SymTabES {
	char *name;		// identifier name
	char *label;		// namespace label
	int len;		// array length
	SymLineSP lines;	// referenced lines
	Obj_t obj;		// object type
	Type_t type;		// type 
	SymTabSP stp; 		// point to symbol table
} SymTabES;

/* some helpful macros */
/** 
 * v = variable, symtab struct pointer 
 */
#define NEWSYMTAB(v) \
do { \
	v = (SymTabSP) malloc(sizeof(SymTabS));					\
	if (v == NULL) {							\
		fprintf(errlist, "OUTOFMEM: on building symbol table\n");	\
		exit(1);							\
	} else {								\
		v->prev = NULL;							\
		v->next = NULL;							\
		v->sbp = (SymBucketSP *) malloc( HASHSIZE * sizeof(SymBucketS));\
		if (v->sbp == NULL) {						\
			fprintf(errlist, "OUTOFMEM: on allocte bucket\n");	\
			exit(1);						\
		}								\
	}									\
} while(0)

/**
 * s = struct name for a entry name,
 * v = variable, a struct pointer
 */
#define ENTRY(s,v) \
do { \
	v = (s##P) malloc(sizeof(s));						\
	if (v == NULL) {							\
		fprintf(errlist, "OUTOFMEM: on allocating entry\n");		\
		exit(1);							\
	}									\
} while(0)

SymTabSP pop(void);
void push(SymTabSP);
void sym_insert_const(IdentSP);
void sym_insert_var(IdentSP);
void sym_insert_fun(IdentSP, ParaListSP);
void sym_insert_proc(IdentSP, ParaListSP);
void printTab(SymTabSP);
#endif /* end of include guard: SYMTAB_H */
