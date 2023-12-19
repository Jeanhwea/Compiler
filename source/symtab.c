#include "global.h"
#include "debug.h"
#include "util.h"
#include "syntax.h"
#include "symtab.h"

////////////////////////////////////////////////////////////////////////////////
// symbol table management
symtab_t *top = NULL;
int depth = 0;
int ntab = 0;
int symcnt = 0;

symtab_t *scope_entry(char *nspace)
{
	symtab_t *t;
	NEWSTAB(t);
	t->id = ++ntab;
	t->depth = ++depth;
	t->nspace = dupstr(nspace);

	// Push
	t->outer = top;
	top = t;
	return t;
}

symtab_t *scope_exit(void)
{
	nevernil(top);

	// Pop
	symtab_t *t = top;
	top = t->outer;
	if (top) {
		top->inner = NULL;
	}
	depth--;

	return t;
}

symtab_t *scope_top(void)
{
	nevernil(top);
	return top;
}

////////////////////////////////////////////////////////////////////////////////
// entry management

const int HASHSIZE = 211;
const int HASHSHIFT = 4;

static inline int hash(char *key)
{
	if (!key) {
		panic("BAD_HASH_KEY");
	}

	int h = 0;
	for (int i = 0; key[i] != '\0'; i++) {
		h = ((h << HASHSHIFT) + key[i]) % HASHSIZE;
	}

	return h;
}

static syment_t *getsym(symtab_t *stab, char *name)
{
	syment_t *hair = &stab->buckets[hash(name) % MAXBUCKETS];
	for (syment_t *e = hair->next; e; e = e->next) {
		if (!strcmp(e->name, name)) {
			return e;
		}
	}
	return NULL;
}

static void putsym(symtab_t *stab, syment_t *e)
{
	syment_t *hair = &stab->buckets[hash(e->name) % MAXBUCKETS];
	e->next = hair->next;
	hair->next = e;
}

static void dumptab(symtab_t *stab)
{
	char indent[128] = "\0";
	for (int i = 0; i < stab->depth; ++i) {
		strcat(indent, "  ");
	}

	symtab_t *t = stab;
	msg("%sstab(#%d): depth=%d, nspace=%s\n", indent, t->id, t->depth,
	    t->nspace);

	strcat(indent, "  ");
	for (int i = 0; i < MAXBUCKETS; ++i) {
		syment_t *hair = &stab->buckets[i];
		for (syment_t *e = hair->next; e; e = e->next) {
			msg("%sname=%s, value=%d, label=%s, obj=%d, type=%d\n",
			    indent, e->name, e->initval, e->label, e->cate,
			    e->type);
		}
	}
}

syment_t *symget(char *name)
{
	nevernil(top);
	return getsym(top, name);
}

syment_t *symfind(char *name)
{
	nevernil(top);
	syment_t *e = NULL;
	for (symtab_t *t = top; t; t = t->outer) {
		if ((e = getsym(t, name)) != NULL) {
			return e;
		}
	}
	return e;
}

void symadd(syment_t *entry)
{
	nevernil(top);
	putsym(top, entry);
	entry->stab = top;
}

void symdump()
{
	msg("DUMP SYMBOL TABLE:\n");
	for (symtab_t *t = top; t; t = t->outer) {
		dumptab(t);
	}
	msg("\n");
}

syment_t *syminit(ident_node_t *idp)
{
	syment_t *e;
	NEWENTRY(e);
	e->sid = ++symcnt;

	e->name = dupstr(idp->name);
	e->initval = idp->value;
	e->arrlen = idp->length;
	e->lineno = idp->line;

	switch (idp->kind) {
	case PROC_IDENT:
		e->cate = PROC_OBJ;
		break;
	case INT_FUN_IDENT:
	case CHAR_FUN_IDENT:
		e->cate = FUN_OBJ;
		break;
	case INT_CONST_IDENT:
	case CHAR_CONST_IDENT:
		e->cate = CONST_OBJ;
		break;
	case INT_VAR_IDENT:
	case CHAR_VAR_IDENT:
		e->cate = VAR_OBJ;
		break;
	case INT_ARRVAR_IDENT:
	case CHAR_ARRVAR_IDENT:
		e->cate = ARRAY_OBJ;
		break;
	case INT_BYVAL_IDENT:
	case CHAR_BYVAL_IDENT:
		e->cate = BYVAL_OBJ;
		break;
	case INT_BYADR_IDENT:
	case CHAR_BYADR_IDENT:
		e->cate = BYREF_OBJ;
		break;
	default:
		e->cate = NOP_OBJ;
	}

	switch (idp->kind) {
	case INT_FUN_IDENT:
	case INT_CONST_IDENT:
	case INT_VAR_IDENT:
	case INT_ARRVAR_IDENT:
	case INT_BYVAL_IDENT:
	case INT_BYADR_IDENT:
		e->type = INT_TYPE;
		break;
	case CHAR_FUN_IDENT:
	case CHAR_CONST_IDENT:
	case CHAR_VAR_IDENT:
	case CHAR_ARRVAR_IDENT:
	case CHAR_BYVAL_IDENT:
	case CHAR_BYADR_IDENT:
		e->type = CHAR_TYPE;
		break;
	default:
		e->type = VOID_TYPE;
	}

	sprintf(e->label, "L%03d", e->sid);
	e->off = top->varoff;
	if (e->cate == ARRAY_OBJ) {
		top->varoff += e->arrlen;
	} else {
		top->varoff += 1;
	}

	symadd(e);
	return e;
}

syment_t *symalloc(symtab_t *stab, char *name, cate_t cate, type_t type)
{
	syment_t *e;
	NEWENTRY(e);
	e->name = dupstr(name);
	e->sid = ++symcnt;

	e->cate = cate;
	e->type = type;

	sprintf(e->label, "T%03d", e->sid);
	e->off = stab->varoff;
	if (e->cate == ARRAY_OBJ) {
		stab->varoff += e->arrlen;
	} else {
		stab->varoff += 1;
	}

	e->stab = stab;
	putsym(stab, e);
	return e;
}
