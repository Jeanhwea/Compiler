/**
 * File: symtab.h
 * Date: Nov 12, 2013
 * Author: Jeanhwea
 */
#ifndef SYMTAB_H

#define SYMTAB_H
/* hash size */
int HASHSIZE = 211;
/* hash shift */
int SHIFT = 4;

typedef enum {
	Const_Obj_t, Var_Obj_t, Nop_Obj_t,
	Proc_Obj_t, Fun_Obj_t
} Obj_t;

typedef enum {
	Int_Type_t, Char_Type_t, Array_Type_t,
	Nop_Type_t
} Type_t;

typedef struct _SymTabS *SymTabSP;
typedef struct _SymLineS *SymLineSP;
typedef struct _SymBucketS *SymBucketSP;
typedef struct _SymTabES *SymTabESP;
typedef struct _ASymTabS *ASymTabSP;
typedef struct _BSymTabS *BSymTabSP;

/**
 * symbol table stack 
 * is a stack that
 * manage symbol table in
 * each function
 */
typedef struct _SymTabS {
	SymBucketSP *sbp;
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
	int lev;		// level
	SymLineSP lines;	// referenced lines
	Obj_t obj;		// object type
	Type_t type;		// type 
	ASymTabSP ap; 		// array vector pointer
	BSymTabSP bp;		// block vector pointer
	SymTabSP stp; 		// point to symbol table
} SymTabES;

typedef struct _ASymTabS {	// array vector struct
	Type_t type;
	int length;
} ASymTabS;

typedef struct _BSymTabS {	// block vector struct
	SymBucketSP last;
	SymBucketSP lastpar;
	int psize;
	int vsize;
} BSymTabS;

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
		v->ep = (SymBucketSP *) malloc( HASHSIZE * sizeof(SymListSP));	\
		if (v->ep == NULL) {						\
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

#endif /* end of include guard: SYMTAB_H */
