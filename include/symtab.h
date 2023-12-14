#ifndef _SYMTAB_H_
#define _SYMTAB_H_
#include "global.h"

#define MAXBUCKETS 16
#define MAXLABEL 16

typedef struct _sym_entry_struct syment_t;
typedef struct _sym_table_struct symtab_t;

// symbol category
typedef enum _sym_cate_enum {
	// Primary Object
	/*  0 */ NOP_OBJ,
	/*  1 */ CONST_OBJ,
	/*  2 */ VAR_OBJ,
	/*  3 */ PROC_OBJ,
	/*  4 */ FUN_OBJ,
	/*  5 */ ARRAY_OBJ,
	/*  6 */ PARA_VAL_OBJ,
	/*  7 */ PARA_REF_OBJ,
	// Additional
	/*  9 */ TMP_OBJ,
	/* 10 */ LABEL_OBJ,
	/* 11 */ NUM_OBJ,
	/* 12 */ STRING_OBJ
} cate_t;

// symbol type
typedef enum _sym_type_enum {
	/* 0 */ NOP_TYPE,
	/* 1 */ INT_TYPE,
	/* 2 */ CHAR_TYPE,
	/* 3 */ STR_TYPE
} type_t;

typedef struct _sym_entry_struct {
	// identifier name
	char *name;
	// assembly label
	char label[MAXLABEL];
	// const value, initval value
	int initval;
	int arrlen;
	// referenced line number
	int lineno;
	// on which level
	int level;
	//on which positon
	int pos;
	// object type
	cate_t cate;
	// type
	type_t type;
	// which symbol table
	symtab_t *stab;
	syment_t *next;
} syment_t;

typedef struct _sym_table_struct {
	int id;
	int depth;
	char *nspace; // namespace
	symtab_t *inner;
	symtab_t *outer;
	syment_t buckets[MAXBUCKETS];
} symtab_t;

// Constructor
#define NEWENTRY(v) INITMEM(syment_t, v)
#define NEWSTAB(v) INITMEM(symtab_t, v)

// scope management
symtab_t *scope_entry(char *nspace);
symtab_t *scope_exit(void);
// symbol operator
void symadd(syment_t *entry);
syment_t *symfind(char *name);
void symdump();
#endif /* End of _SYMTAB_H_ */
