#include "symtab.h"

int main(int argc, char *argv[])
{
	scope_entry("root");
	scope_entry("test01");
	scope_exit();
	scope_exit();
	return 0;
}
