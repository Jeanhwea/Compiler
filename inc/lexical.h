#ifndef _LEXICAL_H_
#define _LEXICAL_H_

// Define all token
typedef enum _token_enum {
	// Book-keeping Token
	/*  0 */ ENDFILE = 0,
	/*  1 */ ERROR = 1,
	// Reserved Key Word
	/*  2 */ KW_ARRAY = 2,
	/*  3 */ KW_BEGIN = 3,
	/*  4 */ KW_CHAR = 4,
	/*  5 */ KW_CONST = 5,
	/*  6 */ KW_DO = 6,
	/*  7 */ KW_DOWNTO = 7,
	/*  8 */ KW_ELSE = 8,
	/*  9 */ KW_END = 9,
	/* 10 */ KW_FOR = 10,
	/* 11 */ KW_FUNCTION = 11,
	/* 12 */ KW_IF = 12,
	/* 13 */ KW_INTEGER = 13,
	/* 14 */ KW_OF = 14,
	/* 15 */ KW_PROCEDURE = 15,
	/* 16 */ KW_READ = 16,
	/* 17 */ KW_REPEAT = 17,
	/* 18 */ KW_THEN = 18,
	/* 19 */ KW_TO = 19,
	/* 20 */ KW_UNTIL = 20,
	/* 21 */ KW_VAR = 21,
	/* 22 */ KW_WRITE = 22,
	// Multi-Character Token
	/* 23 */ MC_ID = 23,
	/* 24 */ MC_CH = 24,
	/* 25 */ MC_UNS = 25,
	/* 26 */ MC_STR = 26,
	// Special Symbol as Token
	/* 27 */ SS_PLUS = 27,
	/* 28 */ SS_MINUS = 28,
	/* 29 */ SS_STAR = 29,
	/* 30 */ SS_OVER = 30,
	/* 31 */ SS_EQU = 31,
	/* 32 */ SS_LST = 32,
	/* 33 */ SS_LEQ = 33,
	/* 34 */ SS_GTT = 34,
	/* 35 */ SS_GEQ = 35,
	/* 36 */ SS_NEQ = 36,
	/* 37 */ SS_COMMA = 37,
	/* 38 */ SS_SEMI = 38,
	/* 39 */ SS_ASGN = 39,
	/* 40 */ SS_LPAR = 40,
	/* 41 */ SS_RPAR = 41,
	/* 42 */ SS_LBRA = 42,
	/* 43 */ SS_RBRA = 43,
	/* 44 */ SS_LBBR = 44,
	/* 45 */ SS_RBBR = 45,
	/* 46 */ SS_SQUO = 46,
	/* 47 */ SS_DQUO = 47,
	/* 48 */ SS_COLON = 48,
	/* 49 */ SS_DOT = 49
} token_t;

#endif /* End of _LEXICAL_H_ */
