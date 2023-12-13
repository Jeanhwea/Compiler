#ifndef _SYMTAB_H_
#define _SYMTAB_H_

#define MAXBUCKETS 16

typedef struct _sym_entry_struct syment_t;
typedef struct _sym_table_struct symtab_t;

typedef enum _sym_obj_enum {
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
} object_t;

typedef enum _sym_type_enum {
	/* 0 */ INT_TYPE,
	/* 1 */ CHAR_TYPE,
	/* 2 */ NOP_TYPE
} type_t;

typedef struct _sym_entry_struct {
	// identifier name
	char *name;
	// assembly label
	char *label;
	// array length, const value, unsigned value
	int value;
	// referenced line number
	int lineno;
	// on which level
	int level;
	//on which positon
	int pos;
	// object type
	object_t obj;
	// type
	type_t type;
	// which symbol table
	symtab_t *stab;
	syment_t *next;
} syment_t;

typedef struct _sym_table_struct {
	syment_t buckets[MAXBUCKETS];
	int id;
	int depth;
	symtab_t *inner;
	symtab_t *outer;
} symtab_t;

////////////////////////////////////////////////////////////////////////////////
// Initialize symbol table entry struct, allocate memory
//     NEWENTRY(v: variable, sturct pointer)
#define NEWENTRY(v)                                                            \
	do {                                                                   \
		v = (syment_t *)malloc(sizeof(syment_t));                      \
		if (v == NULL) {                                               \
			panic("OUT_OF_MEMORY");                                \
		};                                                             \
		memset(v, 0, sizeof(syment_t));                                \
	} while (0)

////////////////////////////////////////////////////////////////////////////////
// Initialize symbol table struct, allocate memory
//     NEWSTAB(v: variable, sturct pointer)
#define NEWSTAB(v)                                                             \
	do {                                                                   \
		v = (symtab_t *)malloc(sizeof(symtab_t));                      \
		if (v == NULL) {                                               \
			panic("OUT_OF_MEMORY");                                \
		};                                                             \
		memset(v, 0, sizeof(symtab_t));                                \
	} while (0)

// scope
symtab_t *scope_entry(void);
symtab_t *scope_exit(void);
#endif /* End of _SYMTAB_H_ */
