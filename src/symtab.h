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
	Nop_Obj_t, Const_Obj_t, Var_Obj_t,
	Proc_Obj_t, Fun_Obj_t, Array_Obj_t,
	Para_Val_Obj_t, Para_Ref_Obj_t,
	/* additional type for quad */
	Tmp_Obj_t, Label_Obj_t, Num_Obj_t,
	String_Obj_t
} Obj_t;

typedef enum {
	Int_Type_t, Char_Type_t, Nop_Type_t
} Type_t;

/**
 * symbol table stack 
 * is a stack that
 * manage symbol table in
 * each function
 */
typedef struct _SymTabS {
	SymBucketSP *sbp;	// hashed symbol table contents
	int posi_var;		// last var position
	int posi_para;		// last parameter position
	int posi_tmp;		// last tmp position
	int level;		// current level
	SymBucketSP headinfo;	// head parameter info
	SymBucketSP tailinfo;	// tail parameter info
	SymTabSP prev;
	SymTabSP next;
} SymTabS;

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
	int val;		// array length
				// or const value
				// or unsign value
	int lineno;		// referenced lines
	int level;		// level
	int posi;		// on which position
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

SymTabSP newstab(void);
SymTabSP pop(void);
void push(SymTabSP);
SymTabESP sym_insert_const(IdentSP);
SymTabESP sym_insert_var(IdentSP);
SymTabESP sym_insert_para(IdentSP);
SymTabESP sym_insert_fun(IdentSP, ParaListSP);
SymTabESP sym_insert_proc(IdentSP, ParaListSP);
SymTabESP sym_insert_tmp(Type_t);
SymTabESP sym_make_usi(int);
SymTabESP sym_make_label(void);
SymTabESP sym_make_main(void);
SymTabESP sym_make_string(char *);
SymTabESP sym_lookup(char *);
void printTab(SymTabSP);

#endif /* end of include guard: SYMTAB_H */
