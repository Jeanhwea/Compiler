#include <ctype.h>
#include "global.h"
#include "lexical.h"
#include "scan.h"

char token_data[MAXTOKENSIZE + 1];
int token_line;

token_t get_token(void)
{
	int i = 0; // token index
	token_t curr; // current token
	state_t state = START;
	/* whether the current character be saved */
	int save;
	while (state != DONE) {
		int c = readchar(TRUE);
		save = TRUE;
		switch (state) {
		case START:
			if (isspace(c)) {
				// white space
				save = FALSE;
			} else if (isdigit(c)) {
				state = INUNS;
			} else if (c == '"') {
				save = FALSE;
				state = INSTR;
			} else if (c == '\'') {
				save = FALSE;
				state = INCHA;
			} else if (c == '{') {
				save = FALSE;
				state = COMMENT;
			} else if (isalpha(c)) {
				state = INIDE;
			} else if (c == ':') {
				state = INCOM;
			} else if (c == '>') {
				state = INGRE;
			} else if (c == '<') {
				state = INLES;
			} else {
				state = DONE;
				switch (c) {
				case EOF:
					save = FALSE;
					curr = ENDFILE;
					break;
				case '.':
					curr = SS_DOT;
					break;
				case '+':
					curr = SS_PLUS;
					break;
				case '-':
					curr = SS_MINUS;
					break;
				case '*':
					curr = SS_STAR;
					break;
				case '/':
					curr = SS_OVER;
					break;
				case '=':
					curr = SS_EQU;
					break;
				case ',':
					curr = SS_COMMA;
					break;
				case ';':
					curr = SS_SEMI;
					break;
				case '(':
					curr = SS_LPAR;
					break;
				case ')':
					curr = SS_RPAR;
					break;
				case '[':
					curr = SS_LBRA;
					break;
				case ']':
					curr = SS_RBRA;
					break;
				case '{':
					curr = SS_LBBR;
					break;
				case '}':
					curr = SS_RBBR;
					break;
				default:
					curr = ERROR;
					break;
				}
			}
			break;
		case COMMENT:
			save = FALSE;
			if (c == EOF) {
				state = DONE;
				curr = ENDFILE;
			} else if (c == '}') {
				state = START;
			}
			break;
		case INSTR: /* in string */
			if (c == '"') {
				state = DONE;
				save = FALSE;
				curr = MC_STR;
			} else if (c >= 32 && c <= 126) {
				// check if the string character is printable
			} else {
				state = DONE;
				if (c == EOF) {
					save = FALSE;
					i = 0;
					curr = ENDFILE;
				}
			}
			break;
		case INCHA: /* in character */
			if (c == '\'') {
				state = DONE;
				save = FALSE;
				curr = MC_CH;
			} else if (isdigit(c) || isalpha(c)) {
			} else {
				if (c == EOF) {
					save = FALSE;
					i = 0;
					curr = ENDFILE;
					state = DONE;
				}
			}
			break;
		case INUNS: /* in unsign number */
			if (!isdigit(c)) {
				unreadchar();
				save = FALSE;
				state = DONE;
				curr = MC_UNS;
			}
			break;
		case INIDE: /* in identifier */
			if (!(isdigit(c) || isalpha(c))) {
				unreadchar();
				save = FALSE;
				state = DONE;
				curr = MC_ID;
			}
			break;
		case INLES: /* in less than */
			state = DONE;
			if (c == '=') {
				curr = SS_LEQ;
			} else if (c == '>') {
				curr = SS_NEQ;
			} else {
				unreadchar();
				save = FALSE;
				curr = SS_LST;
			}
			break;
		case INCOM: /* in comma */
			state = DONE;
			if (c == '=') {
				curr = SS_ASSIGN;
			} else {
				unreadchar();
				save = FALSE;
				curr = SS_COLON;
			}
			break;
		case INGRE: /* in great than */
			state = DONE;
			if (c == '=') {
				curr = SS_GEQ;
			} else {
				unreadchar();
				save = FALSE;
				curr = SS_GTT;
			}
			break;
		case DONE:
		default:
			dbg("error state = %d", state);
			state = DONE;
			curr = ERROR;
			break;
		}
		if ((save) && (i <= MAXTOKENSIZE)) {
			token_data[i++] = (char)c;
			token_data[i] = '\0';
		} else if (i > MAXTOKENSIZE) {
			dbg("lineno:%d: token size is too long\n", lineno);
		}
		if (state == DONE) {
			token_data[i] = '\0';
			token_line = lineno;
			if (curr == MC_ID) {
				curr = kwget(token_data);
			}
		}
	}
	return curr;
}

////////////////////////////////////////////////////////////////////////////////
// Source Code Buffer
////////////////////////////////////////////////////////////////////////////////
#define BUFLEN 4096
// hold current line buffer
static char linebuf[BUFLEN];
static int bufsize = 0;
// when meet EOF, then set done to TRUE
static bool fileend = FALSE;
// hold current read postion in line_buf
static int linepos = 0;

static int readchar(bool peek)
{
	if (linepos < bufsize) {
		goto ready;
	}

	lineno++;
	if (fgets(linebuf, BUFLEN - 1, source) == NULL) {
		fileend = TRUE;
		return EOF;
	}
	dbg("source %4d: %s", lineno, linebuf);

	bufsize = strlen(linebuf);
	linepos = 0;
	goto ready;

ready:
	return (peek) ? linebuf[linepos] : linebuf[linepos++];
}

static void unreadchar(void)
{
	if (linepos <= 0) {
		panic("unread at line postion zero!");
	}
	if (!fileend) {
		linepos--;
	}
}

////////////////////////////////////////////////////////////////////////////////
// Reserved Keyword Table
////////////////////////////////////////////////////////////////////////////////
static struct {
	// keyword string
	char *str;
	// represented token
	token_t tok;
} PL0_KEYWORDS[MAXRESERVED] = {
	/*  0 */ { "array", KW_ARRAY },
	/*  1 */ { "begin", KW_BEGIN },
	/*  2 */ { "char", KW_CHAR },
	/*  3 */ { "const", KW_CONST },
	/*  4 */ { "do", KW_DO },
	/*  5 */ { "downto", KW_DOWNTO },
	/*  6 */ { "else", KW_ELSE },
	/*  7 */ { "end", KW_END },
	/*  8 */ { "for", KW_FOR },
	/*  9 */ { "function", KW_FUNCTION },
	/* 10 */ { "if", KW_IF },
	/* 11 */ { "integer", KW_INTEGER },
	/* 12 */ { "of", KW_OF },
	/* 13 */ { "procedure", KW_PROCEDURE },
	/* 14 */ { "read", KW_READ },
	/* 15 */ { "repeat", KW_REPEAT },
	/* 16 */ { "then", KW_THEN },
	/* 17 */ { "to", KW_TO },
	/* 18 */ { "until", KW_UNTIL },
	/* 19 */ { "var", KW_VAR },
	/* 20 */ { "write", KW_WRITE }
};

// if s is keyword return token, otherwise return MC_ID
static token_t kwget(char *s)
{
	int i;
	for (i = 0; i < MAXRESERVED; i++) {
		if (!strcmp(s, PL0_KEYWORDS[i].str)) {
			return PL0_KEYWORDS[i].tok;
		}
	}
	return MC_ID;
}
