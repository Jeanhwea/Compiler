#include <assert.h>
#include "symtab.h"

void add_test_symbol(char *name)
{
	syment_t *e;
	NEWENTRY(e);
	e->name = name;
	symadd(e);
}

int main(int argc, char *argv[])
{
	syment_t *e;

	scope_entry("root");

	add_test_symbol("aaa");

	symdump();

	add_test_symbol("bbb");

	symdump();

	e = symfind("aaa");
	assert(!strcmp(e->name, "aaa"));
	assert(!strcmp(e->stab->nspace, "root"));

	e = symfind("ccc");
	assert(e == NULL);

	scope_entry("test01");

	add_test_symbol("aaa");
	add_test_symbol("ccc");

	symdump();

	e = symfind("aaa");
	assert(!strcmp(e->name, "aaa"));
	assert(!strcmp(e->stab->nspace, "test01"));
	e = symfind("bbb");
	assert(!strcmp(e->name, "bbb"));
	assert(!strcmp(e->stab->nspace, "root"));
	e = symfind("ccc");
	assert(!strcmp(e->name, "ccc"));
	assert(!strcmp(e->stab->nspace, "test01"));

	scope_exit();

	e = symfind("ccc");
	assert(e == NULL);

	scope_exit();
	return 0;
}
