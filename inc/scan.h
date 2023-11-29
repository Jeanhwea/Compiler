#ifndef _SCAN_H_
#define _SCAN_H_
#include "lexical.h"

#define MAXTOKENSIZE 256
// token data, store current token string
extern char token_data[MAXTOKENSIZE + 1];
// token location, line number
extern int token_line;

// return next token in source file
token_t get_token(void);

// get_token states
typedef enum _state_enum {
	/* 0 */ START,
	/* 1 */ INSTR,
	/* 2 */ INUNS,
	/* 3 */ INIDE,
	/* 4 */ INLES,
	/* 5 */ INCOM,
	/* 6 */ INGRE,
	/* 7 */ INCHA,
	/* 8 */ COMMENT,
	/* 9 */ DONE
} state_t;

// helper
static int readchar(bool peek);
static void unreadchar(void);
static token_t kwget(char *s);

#endif /* End of _SCAN_H_ */
