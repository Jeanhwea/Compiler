#include "global.h"
#include "debug.h"
#include "symtab.h"

////////////////////////////////////////////////////////////////////////////////
// symbol table management
symtab_t *curr = NULL;
int depth = 0;
int counter = 0;

symtab_t *scope_entry(char *namespace)
{
	symtab_t *t;
	NEWSTAB(t);
	t->id = ++counter;
	t->depth = ++depth;
	t->namespace = namespace;

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

// hash size
int HASHSIZE = 211;
// hash shift
int HASHSHIFT = 4;

static inline int hash(char *key)
{
	int h = 0;
	int i;
	if (!key) {
		panic("BAD_HASH_KEY");
	}
	for (i = 0; key[i] != '\0'; i++) {
		h = ((h << HASHSHIFT) + key[i]) % HASHSIZE;
	}
	return h;
}

syment_t *getsym(symtab_t *stab, char *name)
{
	if (!stab) {
		panic("NULL_SYMBOL_TABLE");
	}

	int h = hash(name);
	syment_t *hair = stab->buckets[h % MAXBUCKETS];

	for (e = hair.next; e != NULL; e = e->next) {
		if (strcmp(e->name, name)) {
			return e;
		}
	}
	return NULL;
}

syment_t *putsym(symtab_t *stab, syment_t *entry)
{
	if (!stab) {
		panic("NULL_SYMBOL_TABLE");
	}

	int h = hash(entry->name);
	syment_t *hair = stab->buckets[h % MAXBUCKETS];

	entry->next = hair.next;
	hair.next = entry;
	return NULL;
}
