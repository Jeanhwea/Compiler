#ifndef _SCAN_H_
#define _SCAN_H_
#include "lexical.h"
#include "limits.h"

// token data, store current token string
extern char tokbuf[MAXTOKSIZE + 1];
// token location, line number
extern int toklineno;

// gettok states
typedef enum _state_enum {
	/* 0 */ START,
	/* 1 */ INSTR,
	/* 2 */ INUNS,
	/* 3 */ INIDE,
	/* 4 */ INLES,
	/* 5 */ INCOM,
	/* 6 */ INGRE,
	/* 7 */ INCHA,
	/* 8 */ INCMT,
	/* 9 */ DONE
} state_t;

// helper
static int readc(bool peek);
static void unreadc(void);
static token_t getkw(char *s);

// get next token
token_t gettok(void);
#endif /* End of _SCAN_H_ */
