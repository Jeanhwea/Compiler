#ifndef _SYMTAB_H_
#define _SYMTAB_H_
#include "global.h"
#include "parse.h"

#define MAXBUCKETS 16
#define MAXLABEL 16

typedef struct _sym_param_struct param_t;
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
	/*  6 */ BYVAL_OBJ,
	/*  7 */ BYREF_OBJ,
	// Additional
	/*  8 */ TMP_OBJ,
	/*  9 */ LABEL_OBJ,
	/* 10 */ NUM_OBJ,
	/* 11 */ STR_OBJ
} cate_t;

// symbol type
typedef enum _sym_type_enum {
	/* 0 */ VOID_TYPE,
	/* 1 */ INT_TYPE,
	/* 2 */ CHAR_TYPE,
	/* 3 */ STR_TYPE
} type_t;

// signature for procedure and function
typedef struct _sym_param_struct {
	syment_t *symbol;
	param_t *next;
} param_t;

typedef struct _sym_entry_struct {
	// identifier name
	int sid;
	char *name;
	cate_t cate;
	type_t type;
	// const value, initval value
	int initval;
	int arrlen;
	char *str;
	param_t *phead;
	param_t *ptail;
	// label for assemble codes
	char label[MAXLABEL];
	int off; // offset, for assembly stack mapping
	// referenced line number
	int lineno;
	// which symbol table
	symtab_t *stab;
	syment_t *next;
} syment_t;

typedef struct _sym_table_struct {
	int id; // symbol table ID
	int depth; // symbol table nested depth
	char *nspace; // namespace
	// for assembly stack mapping
	int varoff; // variable offset
	int tmpoff; // temporary variable offset
	symtab_t *inner;
	symtab_t *outer;
	syment_t buckets[MAXBUCKETS];
} symtab_t;

// Constructor
#define NEWPARAM(v) INITMEM(param_t, v)
#define NEWENTRY(v) INITMEM(syment_t, v)
#define NEWSTAB(v) INITMEM(symtab_t, v)

// scope management
symtab_t *scope_entry(char *nspace);
symtab_t *scope_exit(void);
symtab_t *scope_top();
// symbol operator
void symadd(syment_t *entry);
// symget only search current scope, while symfind search all.
syment_t *symget(char *name);
syment_t *symfind(char *name);
void symdump();
syment_t *syminit(ident_node_t *idp);
syment_t *symalloc(symtab_t *stab, char *name, cate_t cate, type_t type);
#endif /* End of _SYMTAB_H_ */
