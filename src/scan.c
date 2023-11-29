#include <ctype.h>
#include "global.h"
#include "lexical.h"
#include "scan.h"

char tokbuf[MAXTOKENSIZE + 1];
int toklineno;

token_t get_token(void)
{
	// token buffer index
	int i = 0;
	// current token
	token_t curr;
	// whether save current character to tokbuf[...]
	bool save;

	// the state of our state machine
	state_t state = START;
	while (state != DONE) {
		int ch = readchar(FALSE);
		save = TRUE;
		switch (state) {
		case START:
			if (isspace(ch)) {
				save = FALSE;
			} else if (isdigit(ch)) {
				state = INUNS;
			} else if (ch == '"') {
				save = FALSE;
				state = INSTR;
			} else if (ch == '\'') {
				save = FALSE;
				state = INCHA;
			} else if (ch == '{') {
				save = FALSE;
				state = COMMENT;
			} else if (isalpha(ch)) {
				state = INIDE;
			} else if (ch == ':') {
				state = INCOM;
			} else if (ch == '>') {
				state = INGRE;
			} else if (ch == '<') {
				state = INLES;
			} else {
				state = DONE;
				switch (ch) {
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
		case COMMENT: /* comment */
			save = FALSE;
			if (ch == EOF) {
				state = DONE;
				curr = ENDFILE;
			} else if (ch == '}') {
				state = START;
			}
			break;
		case INSTR: /* in string */
			if (ch == '"') {
				state = DONE;
				save = FALSE;
				curr = MC_STR;
			} else if (isprint(ch)) { // only allow printable character
				dbg("printable character. ch = %c", ch);
			} else {
				state = DONE;
				if (ch == EOF) {
					save = FALSE;
					i = 0;
					curr = ENDFILE;
				}
			}
			break;
		case INCHA: /* in character */
			if (ch == '\'') {
				state = DONE;
				save = FALSE;
				curr = MC_CH;
			} else if (isdigit(ch) || isalpha(ch)) {
			} else {
				if (ch == EOF) {
					save = FALSE;
					i = 0;
					curr = ENDFILE;
					state = DONE;
				}
			}
			break;
		case INUNS: /* in unsign number */
			if (!isdigit(ch)) {
				unreadchar();
				save = FALSE;
				state = DONE;
				curr = MC_UNS;
			}
			break;
		case INIDE: /* in identifier */
			if (!(isdigit(ch) || isalpha(ch))) {
				unreadchar();
				save = FALSE;
				state = DONE;
				curr = MC_ID;
			}
			break;
		case INLES: /* in less than */
			state = DONE;
			if (ch == '=') {
				curr = SS_LEQ;
			} else if (ch == '>') {
				curr = SS_NEQ;
			} else {
				unreadchar();
				save = FALSE;
				curr = SS_LST;
			}
			break;
		case INCOM: /* in comma */
			state = DONE;
			if (ch == '=') {
				curr = SS_ASSIGN;
			} else {
				unreadchar();
				save = FALSE;
				curr = SS_COLON;
			}
			break;
		case INGRE: /* in great than */
			state = DONE;
			if (ch == '=') {
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

		// post check state works
		if ((save) && (i <= MAXTOKENSIZE)) {
			tokbuf[i++] = (char)ch;
			tokbuf[i] = '\0';
		} else if (i > MAXTOKENSIZE) {
			dbg("token size is too long, lineno = %d\n", lineno);
		}

		// finish get token
		if (state == DONE) {
			tokbuf[i] = '\0';
			toklineno = lineno;
			if (curr == MC_ID) {
				curr = kwget(tokbuf);
			}
		}
	}

	dbg("token = %2d, tokbuf = %s\n", curr, tokbuf);
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
	dbg("source L%03d: %s", lineno, linebuf);

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

// if s is keyword return token,
//       otherwise return MC_ID
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
