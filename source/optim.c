#include "optim.h"

// define the global module
mod_t mod;

// re-generated instruction counter
int xidcnt2 = 500;

void optim(void)
{
	// make flow graph
	partition_basic_blocks();
	construct_flow_graph();

	// DAG optimization
	dag_optim();

	// Live Variables Analysis
	lva_optim();
}

void sset(bits_t bits[], syment_t *e)
{
	bset(bits, e->sid);
}

bool sget(bits_t bits[], syment_t *e)
{
	return bget(bits, e->sid);
}

void sdup(bits_t des[], bits_t src[])
{
	bdup(des, src, NBITARR);
}

void sclr(bits_t *bits)
{
	bclrall(bits, NBITARR);
}

bool ssame(bits_t a[], bits_t b[])
{
	return bsame(a, b, NBITARR);
}

void sunion(bits_t *r, bits_t *a, bits_t *b)
{
	bunion(r, a, b, NBITARR);
}

void ssub(bits_t *r, bits_t *a, bits_t *b)
{
	bsub(r, a, b, NBITARR);
}

inst_t *dupinst(op_t op, syment_t *d, syment_t *r, syment_t *s)
{
	inst_t *x;
	NEWINST(x);
	x->op = op;
	x->xid = ++xidcnt2;
	x->r = r;
	x->s = s;
	x->d = d;
	return x;
}
