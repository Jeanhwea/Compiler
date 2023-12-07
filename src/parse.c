#include "parse.h"
#include "syntax.h"

// current token
static token_t currtok;
// hold previous token
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

static inline bool match(token_t expect)
{
}

/**
 * program ->
 *	block .
 */
static pgm_p parse_pgm(void)
{
	pgm_p t;
	INITMEM(pgm, t);
	t->bp = parse_block();
}
