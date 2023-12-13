#include <assert.h>
#include "symtab.h"

int main(int argc, char *argv[])
{
	syment_t *e;
	scope_entry("root");
	NEWENTRY(e);
	e->name = "aaa";
	addsym(e);

	NEWENTRY(e);
	e->name = "bbb";
	addsym(e);

	e = findsym("aaa");
	assert(!strcmp(e->name, "aaa"));
	assert(!strcmp(e->stab->nspace, "root"));

	e = findsym("ccc");
	assert(e == NULL);

	scope_entry("test01");

	NEWENTRY(e);
	e->name = "aaa";
	addsym(e);

	NEWENTRY(e);
	e->name = "ccc";
	addsym(e);

	e = findsym("aaa");
	assert(!strcmp(e->name, "aaa"));
	assert(!strcmp(e->stab->nspace, "test01"));
	e = findsym("bbb");
	assert(!strcmp(e->name, "bbb"));
	assert(!strcmp(e->stab->nspace, "root"));
	e = findsym("ccc");
	assert(!strcmp(e->name, "ccc"));
	assert(!strcmp(e->stab->nspace, "test01"));

	scope_exit();

	e = findsym("ccc");
	assert(e == NULL);

	scope_exit();
	return 0;
}
