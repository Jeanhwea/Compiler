#include "optim.h"
#include "symtab.h"
#include "util.h"

void bmset(bits_t bits[], syment_t *e)
{
	bset(bits, e->sid);
}

bool bmget(bits_t bits[], syment_t *e)
{
	return bget(bits, e->sid);
}
