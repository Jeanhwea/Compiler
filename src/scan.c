#include "global.h"
#include "lexical.h"
#include <stdio.h>
#include "scan.h"

// see scan.h
char token_data[MAXTOKENSIZE + 1];
extern int token_line;

////////////////////////////////////////////////////////////////////////////////
// Source Code Line Buffer
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

token_t get_token(void)
{
	token_t curr;
	int ch;
	while ((ch = readchar(FALSE)) != EOF) {
		putchar(ch);
	}
	return curr;
}
