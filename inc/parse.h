#ifndef _PARSE_H_
#define _PARSE_H_

#include "global.h"
#include "syntax.h"
#include "scan.h"

// parse source file
pgm_p parse(void);

// ID read mode
typedef int idreadmode_t;
#define READCURR 0
#define READPREV 1

// Initialize struct, allocate memory, s:struct, v: variable, sturct pointer
#define INITMEM(s, v)                                                          \
	do {                                                                   \
		v = (s##_p)malloc(sizeof(s));                                  \
		if (v == NULL) {                                               \
			panic("OUT_OF_MEMORY");                                \
		};                                                             \
		memset(v, 0, sizeof(s));                                       \
	} while (0)

// hold current token
static token_t currtok;

// if (CURRTOK_ANY(a, b, c, ...))
#define CURRTOK_ANY(a) (currtok == (a))
#define CURRTOK_ANY2(a, b) (currtok == (a) || currtok == (b))
#define CURRTOK_ANY3(a, b, c)                                                  \
	(currtok == (a) || currtok == (b) || currtok == (c))
#define CURRTOK_ANY4(a, b, c, d)                                               \
	(currtok == (a) || currtok == (b) || currtok == (c) || currtok == (d))
#define CURRTOK_ANY5(a, b, c, d, e)                                            \
	(currtok == (a) || currtok == (b) || currtok == (c) ||                 \
	 currtok == (d) || currtok == (e))
#define CURRTOK_ANY6(a, b, c, d, e, f)                                         \
	(currtok == (a) || currtok == (b) || currtok == (c) ||                 \
	 currtok == (d) || currtok == (e) || currtok == (f))

#endif /* End of _PARSE_H_ */
