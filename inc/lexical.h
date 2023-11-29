#ifndef _LEXICAL_H_
#define _LEXICAL_H_

// Define all token
typedef enum _token_enum {
	// Book-keeping Token
	ENDFILE,
	ERROR,
	// Reserved Key Word
	KW_ARRAY,
	KW_BEGIN,
	KW_CHAR,
	KW_CONST,
	KW_DO,
	KW_DOWNTO,
	KW_ELSE,
	KW_END,
	KW_FOR,
	KW_FUNCTION,
	KW_IF,
	KW_INTEGER,
	KW_OF,
	KW_PROCEDURE,
	KW_READ,
	KW_REPEAT,
	KW_THEN,
	KW_TO,
	KW_UNTIL,
	KW_VAR,
	KW_WRITE,
	// Multi-Character Token
	MC_ID,
	MC_CH,
	MC_UNS,
	MC_STR,
	// Special Symbol as Token
	SS_PLUS,
	SS_MINUS,
	SS_STAR,
	SS_OVER,
	SS_EQU,
	SS_LST,
	SS_LEQ,
	SS_GTT,
	SS_GEQ,
	SS_NEQ,
	SS_COMMA,
	SS_SEMI,
	SS_ASSIGN,
	SS_LPAR,
	SS_RPAR,
	SS_LBRA,
	SS_RBRA,
	SS_LBBR,
	SS_RBBR,
	SS_SQUO,
	SS_DQUO,
	SS_COLON,
	SS_DOT
} token_t;

#define MAXRESERVED 21

#endif /* End of _LEXICAL_H_ */
