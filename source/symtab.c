#include "global.h"
#include "debug.h"
#include "symtab.h"

////////////////////////////////////////////////////////////////////////////////
// symbol table management
symtab_t *curr = NULL;
int depth = 0;
int counter = 0;

symtab_t *scope_entry(void)
{
	symtab_t *t;
	NEWSTAB(t);
	t->id = ++counter;
	t->depth = ++depth;

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
