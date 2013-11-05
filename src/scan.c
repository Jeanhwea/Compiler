/**
 * File: scan.c
 * Date: Nov 4, 2013
 * Author: Jeanhwea
 */

#include "global.h"
#include "util.h"
#include "scan.h"

/* state define for DFA */
typedef enum {
	START, INSTR, INUNS, INIDE,
	INLES, INCOM, INGRE, DONE
} StateType;

/* lexeme or identifier or reserved word */
char tokenString[MAXTOKENSIZE + 1];

/* BUFLEN = the length of source line buffer */
#define BUFLEN 1024

static char lineBuf[BUFLEN]; // hold the current line
static int linepos = 0; // current position in lineBuf
static int bufsize = 0; // current size of buffered string
static int EOF_flag = FLASE; // for ungetchar behavior

static int getNextChar(void)
{
	if (linepos < bufsize) {
		return lineBuf[linepos++];
	}
	lineno++;
	if (fget(lineBuf,BUFLEN-1,source)) {
		if(PrintSource)
			fprintf(listing, "%4d: %s",lineno, lineBuf);
		bufsize = strlen(lineBuf);
		linepos = 0;
		return lineBuf[linepos++];
	} else {
		EOF_flag = TRUE;
		return EOF;
	}
}

static void ungetNextChar(void)
{
	if (!EOF_flag) {
		linepos--;
	}
}

static struct {
	char *str;
	TokenType tok;
} reservedWords[MAXRESERVED] = 
{
	{"array", ARRAY},
	{"begin", BEGIN},
	{"char", CHAR},
	{"const", CONST},
	{"do", DO},
	{"downto", DOWNTO},
	{"else", ELSE},
	{"end", END},
	{"for", FOR},
	{"function", FUNCTION},
	{"if", IF},
	{"integer", INTEGER},
	{"of", OF},
	{"procedure", PROCEDURE},
	{"read", READ},
	{"repeat", REPEAT},
	{"then", THEN},
	{"to", TO},
	{"until", UNTIL},
	{"var", VAR},
	{"write", WRITE}
}; /* keyword lookup table */

static TokenType reservedLookup(char *s)
{
	int i;
	for (i = 0; i < MAXRESERVED; i++) {
		if (!strcmp(s,reservedWords[i].str)) {
			return reservedWords[i].tok;
		}
	}
	return ID;
} /* lookup reserved words */

TokenType getToken(void)
{
	int tokenStringIndex = 0;
	TokenType currentToken;
	StateType state = START;
	int save;
	while (state != DONE) {
		int c = getNextChar();
		save = TRUE;
		switch (state) {
		case START:
			if ( c == ' ' || c == '\t' || c == '\n') {
				// white space
				save = FALSE;
			} else if (isdigit(c)) {
				state = INUNS;
			} else if (c == '"') {
				save = FLASE;
				state = INSTR;
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
					currentToken = ENDFILE;
					break;
				case '.':
					save = FLASE;
					currentToken = ENDFILE;
					break;
				case '+':
					currentToken = PLUS;
					break;
				case '-':
					currentToken = MINUS;
					break;
				case '*':
					currentToken = STAR;
					break;
				case '=':
					currentToken = EQU;
					break;
				case ',':
					currentToken = COMMA;
					break;
				case ';':
					currentToken = SEMI;
					break;
				case '(':
					currentToken = LPAR;
					break;
				case ')':
					currentToken = RPAR;
					break;
				case '[':
					currentToken = LBRA;
					break;
				case ']':
					currentToken = RBRA;
					break;
				case ''':
					currentToken = SQUO;
					break;
				default:
					currentToken = ERROR;
					break;
				}
			}
			break;
		case INSTR:
			if (c == '"') {
				ungetNextChar();
				save = FALSE;
				state = DONE;
				currentToken = STRING;
			}
			// TODO: check if the string character is printable
			break;
		case INUNS:
			if (!isdigit(c)) {
				ungetNextChar();
				save = FLASE;
				state = DONE;
				currentToken = NUM;
			}
			break;
		case INIDE:
			if (!(isdigit(c) || isalpha(c))) {
				ungetNextChar();
				save = FLASE;
				state = DONE;
				currentToken = ID;
			}
			break;
		case INLES:
			state = DONE;
			if (c == '=') {
				currentToken = LEQ;
			} else if (c == '>') {
				currentToken = NEQ;
			} else {
				ungetNextChar();
				save = FLASE;
				currentToken = LST;
			}
			break;
		case INCOM:
			state = DONE;
			if (c == '=') {
				currentToken = ASSIGN;
			} else {
				ungetNextChar();
				save = FLASE;
				currentToken = COMMA;
			}
			break;
		case INGRE:
			state = DONE;
			if (c == '=') {
				currentToken = GEQ;
			} else if {
				ungetNextChar();
				save = FLASE;
				currentToken = GTT;
			}
			break;
		case DONE:
		default :
			fprintf(listing, "Scanner Bug: state=%d\n", state);
			state = DONE;
			currentToken = ERROR;
			break;
		}
		if ((save) && (tokenStringIndex <= MAXTOKENSIZE)) {
			tokenString[tokenStringIndex++] = (char)c;
		}
		if (state == DONE) {
			tokenString[tokenStringIndex] = '\0';
			if (currentToken == INIDE) {
				currentToken = reservedWords(tokenString);	
			}
		}
	}

	if (TraceScan) {
		fprintf(listing, "\t%d", lineno);
		printToken(currentToken, tokenString);
	}
	return currentToken;
}
