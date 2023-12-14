#include <assert.h>
#include "symtab.h"

#define DUMP()                                                                 \
	do {                                                                   \
		msg("%s():%d ", __func__, __LINE__);                           \
		symdump();                                                     \
	} while (0)

void func01();
void func02();

void add_test_symbol(char *name)
{
	syment_t *e;
	NEWENTRY(e);
	e->name = name;
	symadd(e);
}

void func01()
{
	syment_t *e;
	scope_entry("func01");
	DUMP();

	e = symfind("aaa");
	assert(e && !strcmp(e->stab->nspace, "root"));

	add_test_symbol("aaa");

	func02();

	add_test_symbol("ccc");
	DUMP();

	e = symfind("aaa");
	assert(e && !strcmp(e->stab->nspace, "func01"));
	e = symfind("bbb");
	assert(e && !strcmp(e->stab->nspace, "root"));
	e = symfind("ccc");
	assert(e && !strcmp(e->stab->nspace, "func01"));
	e = symfind("ddd");
	assert(!e);

	scope_exit();
}

void func02()
{
	syment_t *e;
	scope_entry("func02");
	DUMP();

	add_test_symbol("aaa");
	add_test_symbol("ddd");
	DUMP();

	e = symfind("ccc");
	assert(!e);

	scope_exit();
}

int main(int argc, char *argv[])
{
	syment_t *e;
	scope_entry("root");

	add_test_symbol("aaa");
	DUMP();

	add_test_symbol("bbb");
	DUMP();

	e = symfind("aaa");
	assert(!strcmp(e->name, "aaa"));
	assert(!strcmp(e->stab->nspace, "root"));

	e = symfind("ccc");
	assert(e == NULL);

	func01();

	e = symfind("ccc");
	assert(e == NULL);

	scope_exit();
	return 0;
}
