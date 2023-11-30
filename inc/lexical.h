#ifndef _LEXICAL_H_
#define _LEXICAL_H_

// Define all token
typedef enum _token_enum {
	// Book-keeping Token
	/*  0 */ ENDFILE,
	/*  1 */ ERROR,
	// Reserved Key Word
	/*  2 */ KW_ARRAY,
	/*  3 */ KW_BEGIN,
	/*  4 */ KW_CHAR,
	/*  5 */ KW_CONST,
	/*  6 */ KW_DO,
	/*  7 */ KW_DOWNTO,
	/*  8 */ KW_ELSE,
	/*  9 */ KW_END,
	/* 10 */ KW_FOR,
	/* 11 */ KW_FUNCTION,
	/* 12 */ KW_IF,
	/* 13 */ KW_INTEGER,
	/* 14 */ KW_OF,
	/* 15 */ KW_PROCEDURE,
	/* 16 */ KW_READ,
	/* 17 */ KW_REPEAT,
	/* 18 */ KW_THEN,
	/* 19 */ KW_TO,
	/* 20 */ KW_UNTIL,
	/* 21 */ KW_VAR,
	/* 22 */ KW_WRITE,
	// Multi-Character Token
	/* 23 */ MC_ID,
	/* 24 */ MC_CH,
	/* 25 */ MC_UNS,
	/* 26 */ MC_STR,
	// Special Symbol as Token
	/* 27 */ SS_PLUS,
	/* 28 */ SS_MINUS,
	/* 29 */ SS_STAR,
	/* 30 */ SS_OVER,
	/* 31 */ SS_EQU,
	/* 32 */ SS_LST,
	/* 33 */ SS_LEQ,
	/* 34 */ SS_GTT,
	/* 35 */ SS_GEQ,
	/* 36 */ SS_NEQ,
	/* 37 */ SS_COMMA,
	/* 38 */ SS_SEMI,
	/* 39 */ SS_ASSIGN,
	/* 40 */ SS_LPAR,
	/* 41 */ SS_RPAR,
	/* 42 */ SS_LBRA,
	/* 43 */ SS_RBRA,
	/* 44 */ SS_LBBR,
	/* 45 */ SS_RBBR,
	/* 46 */ SS_SQUO,
	/* 47 */ SS_DQUO,
	/* 48 */ SS_COLON,
	/* 49 */ SS_DOT
} token_t;

#endif /* End of _LEXICAL_H_ */
