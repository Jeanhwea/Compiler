#include "global.h"
#include "debug.h"
#include "limits.h"
#include "parse.h"
#include "util.h"
#include "syntax.h"
#include "symtab.h"

// symbol table management
symtab_t *top = NULL;
int depth = 0;
int tidcnt = 0;

syment_t *syments[MAXSYMENT];
int sidcnt = 0;

symtab_t *scope_entry(char *nspace)
{
	symtab_t *t;
	NEWSTAB(t);
	t->tid = ++tidcnt;
	t->depth = ++depth;
	strcopy(t->nspace, nspace);
	t->varoff = 1; // reserve function return value

	// Push
	t->outer = top;
	if (top) {
		top->inner = t;
	}
	top = t;

	// trace log
	dbg("push depth=%d tid=%d nspace=%s\n", t->depth, t->tid, t->nspace);
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

	// trace log
	//   1. dump table info
	//   2. dump all table entry
	dbg("pop depth=%d tid=%d nspace=%s\n", t->depth, t->tid, t->nspace);
	int i;
	for (i = 0; i < MAXBUCKETS; ++i) {
		syment_t *hair, *e;
		hair = &t->buckets[i];
		for (e = hair->next; e; e = e->next) {
			dbg("sid=%d, name=%s\n", e->sid, e->name);
		}
	}
	return t;
}

symtab_t *scope_top(void)
{
	nevernil(top);
	return top;
}

// entry management
const int HASHSIZE = 211;
const int HASHSHIFT = 4;

static inline int hash(char *key)
{
	if (!key) {
		panic("BAD_HASH_KEY");
	}

	int h, i;
	for (i = h = 0; key[i] != '\0'; i++) {
		h = ((h << HASHSHIFT) + key[i]) % HASHSIZE;
	}

	return h;
}

static syment_t *getsym(symtab_t *stab, char *name)
{
	syment_t *hair, *e;
	hair = &stab->buckets[hash(name) % MAXBUCKETS];
	for (e = hair->next; e; e = e->next) {
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

	// for debugging
	if (e->sid + 1 >= MAXSYMENT) {
		panic("TOO_MANY_SYMBOL_ENTRY");
	}
	syments[e->sid] = e;

	dbg("tid=%d nspace=%s sym=%s\n", stab->tid, stab->nspace, e->name);
}

static void dumptab(symtab_t *stab)
{
	char indent[MAXSTRBUF] = "\0";
	int i;
	for (i = 0; i < stab->depth; ++i) {
		strcat(indent, "  ");
	}

	symtab_t *t = stab;
	msg("%sstab(tid=%d): depth=%d, nspace=%s\n", indent, t->tid, t->depth,
	    t->nspace);

	strcat(indent, "  ");
	for (i = 0; i < MAXBUCKETS; ++i) {
		syment_t *hair, *e;
		hair = &t->buckets[i];
		for (e = hair->next; e; e = e->next) {
			msg("%ssid=%d, name=%s, cate=%d, type=%d, value=%d, label=%s\n",
			    indent, e->sid, e->name, e->cate, e->type,
			    e->initval, e->label);
		}
	}
}

syment_t *symget(char *name)
{
	nevernil(top);
	return getsym(top, name);
}

syment_t *symget2(symtab_t *stab, char *name)
{
	return getsym(stab, name);
}

syment_t *symfind(char *name)
{
	nevernil(top);
	syment_t *e;
	symtab_t *t;
	e = NULL;
	for (t = top; t; t = t->outer) {
		if ((e = getsym(t, name)) != NULL) {
			return e;
		}
	}
	return e;
}

void symadd(syment_t *entry)
{
	symadd2(top, entry);
}

void symadd2(symtab_t *stab, syment_t *entry)
{
	nevernil(stab);
	putsym(stab, entry);
	entry->stab = stab;
}

void stabdump()
{
	msg("DUMP SYMBOL TABLE:\n");
	symtab_t *t;
	for (t = top; t; t = t->outer) {
		dumptab(t);
	}
	msg("\n");
}

syment_t *syminit(ident_node_t *idp)
{
	return syminit2(top, idp, idp->name);
}

syment_t *syminit2(symtab_t *stab, ident_node_t *idp, char *key)
{
	syment_t *e;
	NEWENTRY(e);
	e->sid = ++sidcnt;

	strcopy(e->name, key);
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
	switch (e->cate) {
	case NOP_OBJ:
	case CONST_OBJ:
		// no need allocation
		break;
	case VAR_OBJ:
	case PROC_OBJ:
	case FUN_OBJ:
		e->off = stab->varoff;
		stab->varoff++;
		break;
	case BYVAL_OBJ:
	case BYREF_OBJ:
		e->off = stab->argoff;
		stab->argoff++;
		break;
	case ARRAY_OBJ:
		e->off = stab->varoff;
		stab->varoff += e->arrlen;
		break;
	default:
		unlikely();
	}

	symadd2(stab, e);
	return e;
}

syment_t *symalloc(symtab_t *stab, char *name, cate_t cate, type_t type)
{
	syment_t *e;
	NEWENTRY(e);
	strcopy(e->name, name);
	e->sid = ++sidcnt;

	e->cate = cate;
	e->type = type;

	sprintf(e->label, "T%03d", e->sid);
	switch (e->cate) {
	case TMP_OBJ:
		// from now on, we will NEVER alloc local variables so just
		// alloc temporary variables
		e->off = stab->varoff + stab->tmpoff;
		stab->tmpoff++;
		break;
	case LABEL_OBJ:
	case NUM_OBJ:
	case STR_OBJ:
		// label/number/string never use bytes
		break;
	default:
		unlikely();
	}

	e->stab = stab;
	putsym(stab, e);
	return e;
}
