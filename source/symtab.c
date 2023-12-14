#include "global.h"
#include "debug.h"
#include "symtab.h"

////////////////////////////////////////////////////////////////////////////////
// symbol table management
symtab_t *curr = NULL;
int depth = 0;
int counter = 0;

symtab_t *scope_entry(char *nspace)
{
	symtab_t *t;
	NEWSTAB(t);
	t->id = ++counter;
	t->depth = ++depth;
	t->nspace = nspace;

	// Push
	t->outer = curr;
	curr = t;
	return t;
}

symtab_t *scope_exit(void)
{
	if (curr == NULL) {
		panic("EXIT_WHEN_CURR_NULL");
	}

	// Pop
	symtab_t *t = curr;
	curr = t->outer;
	if (curr != NULL) {
		curr->inner = NULL;
	}
	depth--;

	return t;
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

syment_t *getsym(symtab_t *stab, char *name)
{
	syment_t *hair = &stab->buckets[hash(name) % MAXBUCKETS];
	for (syment_t *e = hair->next; e != NULL; e = e->next) {
		if (!strcmp(e->name, name)) {
			return e;
		}
	}
	return NULL;
}

void putsym(symtab_t *stab, syment_t *entry)
{
	syment_t *hair = &stab->buckets[hash(entry->name) % MAXBUCKETS];
	entry->next = hair->next;
	hair->next = entry;
}

void dumptab(symtab_t *stab)
{
	msg("dump stab#%d: nspace=%s\n", stab->id, stab->nspace);
}

syment_t *findsym(char *name)
{
	if (!curr) {
		panic("NULL_SYMBOL_TABLE");
	}

	syment_t *e = NULL;
	for (symtab_t *t = curr; t; t = t->outer) {
		if ((e = getsym(t, name)) != NULL) {
			return e;
		}
	}
	return e;
}

void addsym(syment_t *entry)
{
	if (!curr) {
		panic("NULL_SYMBOL_TABLE");
	}
	putsym(curr, entry);
	entry->stab = curr;
}
