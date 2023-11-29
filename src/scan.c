#include "global.h"
#include "lexical.h"
#include "scan.h"

char token_data[MAXTOKENSIZE + 1];
int token_line;

token_t get_token(void)
{
	token_t curr;
	int ch;
	while ((ch = readchar(FALSE)) != EOF) {
		putchar(ch);
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
