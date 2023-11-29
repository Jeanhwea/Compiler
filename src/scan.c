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
