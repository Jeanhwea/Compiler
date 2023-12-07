#include "parse.h"
#include "syntax.h"

static token_t currtok;
static token_t prevtok;
static char prevtokbuf[MAXTOKENSIZE + 1];
static int prevlineno;

static inline void getsym(void)
{
	strncpy(prevtokbuf, tokbuf, MAXTOKENSIZE);
	prevtok = currtok;
	prevlineno = toklineno;
	currtok = gettok();
}

static pgm_p parse_pgm(void)
{
	pgm_p t;
	ALLOCMEM(pgm, t);
}
