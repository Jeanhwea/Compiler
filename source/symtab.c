#include "debug.h"

// symbol table
// struct sym_table stable;

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
