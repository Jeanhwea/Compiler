/**
 * File: scan.c
 * Date: Nov 4, 2013
 * Author: Jeanhwea
 */

#include "global.h"
#include "util.h"
#include "scan.h"
#include "error.h"

/* state define for DFA */
typedef enum {
	START, INSTR, INUNS, INIDE,
	INLES, INCOM, INGRE, INCHA,
	COMMENT, DONE
} StateType;

/* lexeme or identifier or reserved word */
char tokenString[MAXTOKENSIZE + 1];
/* hold current token location, which line */
int tokenLocation;

/* BUFLEN = the length of source line buffer */
#define BUFLEN 1024

static char lineBuf[BUFLEN]; // hold the current line
static int linepos = 0;      // current position in lineBuf
static int bufsize = 0;      // current size of buffered string
static BOOL EOF_flag = FALSE; // for ungetchar behavior

BOOL char_to_long = FALSE;
static int getNextChar(BOOL flag)
{
	/**
	 * the flag means whether get next character seriously
	 * if flag is TRUE
	 *    we will get next character
	 * else if flag is FALSE
	 *    we just have a peek at next character
	 */
	if (linepos < bufsize) {
		return (flag)? lineBuf[linepos++]: lineBuf[linepos];
	}
	lineno++;
	if (fgets(lineBuf,BUFLEN-1,source)) {
		if(PrintSource)
			fprintf(listing, "%4d: %s",lineno, lineBuf);
		bufsize = strlen(lineBuf);
		linepos = 0;
		return (flag)? lineBuf[linepos++]: lineBuf[linepos];
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
	int save; /* whether the current character be saved */
	while (state != DONE) {
		int c = getNextChar(TRUE);
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
					currentToken = ENDFILE;
					break;
				case '.':
					currentToken = DOT;
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
				case '/':
					currentToken = OVER;
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
				case '{':
					currentToken = LBBR;
					break;
				case '}':
					currentToken = RBBR;
					break;
				default:
					currentToken = ERROR;
					break;
				}
			}
			break;
		case COMMENT:
			save = FALSE;
			if (c == EOF) {
				state = DONE;
				currentToken = ENDFILE;
			} else if (c == '}') {
				state = START;
			}
			break;
		case INSTR: /* in string */
			if (c == '"') {
				state = DONE;
				save = FALSE;
				currentToken = STRING;
			} else if (c >= 32 && c <= 126) {
			// check if the string character is printable
			} else {
				state = DONE;
				if (c == EOF) {
					save = FALSE;
					tokenStringIndex = 0;
					currentToken = ENDFILE;
				}
				--runlevel;
				lexError(ERRSTRINGTYPE);
			}
			break;
		case INCHA: /* in character */
			if (c == '\'' && char_to_long) {
				state = DONE;
				save = FALSE;
				currentToken = CH;
			} else if (isdigit(c) || isalpha(c)) {
			// TODO: check if the string character is
			//       digit or character
				if (char_to_long) {
					--runlevel;
					lexError(ERRCHARLEN);
				}
				char_to_long = TRUE;
			} else {
				if (c == EOF) {
					save = FALSE;
					tokenStringIndex = 0;
					currentToken = ENDFILE;
					state = DONE;
				}
				--runlevel;
				lexError(ERRCHARTYPE);
			}
			break;
		case INUNS: /* in unsign number */
			if (!isdigit(c)) {
				ungetNextChar();
				save = FALSE;
				state = DONE;
				currentToken = UNS;
			}
			break;
		case INIDE: /* in identifier */
			if (!(isdigit(c) || isalpha(c))) {
				ungetNextChar();
				save = FALSE;
				state = DONE;
				currentToken = ID;
			}
			break;
		case INLES: /* in less than */
			state = DONE;
			if (c == '=') {
				currentToken = LEQ;
			} else if (c == '>') {
				currentToken = NEQ;
			} else {
				ungetNextChar();
				save = FALSE;
				currentToken = LST;
			}
			break;
		case INCOM: /* in comma */
			state = DONE;
			if (c == '=') {
				currentToken = ASSIGN;
			} else {
				ungetNextChar();
				save = FALSE;
				currentToken = COLON;
			}
			break;
		case INGRE: /* in great than */
			state = DONE;
			if (c == '=') {
				currentToken = GEQ;
			} else {
				ungetNextChar();
				save = FALSE;
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
			tokenString[tokenStringIndex] = '\0';	
		} else if (tokenStringIndex > MAXTOKENSIZE) {
			fprintf(errlist, "\nlineno:%d: token size is too long\n",
					lineno);
		}
		if (state == DONE) {
			tokenString[tokenStringIndex] = '\0';
			tokenLocation = lineno;
			if (currentToken == ID) {
				currentToken = reservedLookup(tokenString);	
			}
			char_to_long = FALSE;
		}
	}
	if (TraceScan) {
		fprintf(listing, "lineno:%d: ", lineno);
		printToken(currentToken, tokenString);
	}
	return currentToken;
}

void printToken(TokenType token, const char *tokenString)
{
	switch (token) {
		case ID:
			fprintf(listing, "ID %s\n", tokenString);
			break;
		case UNS:
			fprintf(listing, "UNS %s\n", tokenString);
			break;
		case CH:
			fprintf(listing, "CH %s\n", tokenString);
			break;
		case STRING:
			fprintf(listing, "STRING %s\n", tokenString);
			break;
		case CONST:
			fprintf(listing, "CONST %s\n", tokenString);
			break;
		case INTEGER:
			fprintf(listing, "INTEGER %s\n", tokenString);
			break;
		case CHAR:
			fprintf(listing, "CHAR %s\n", tokenString);
			break;
		case VAR:
			fprintf(listing, "VAR %s\n", tokenString);
			break;
		case ARRAY:
			fprintf(listing, "ARRAY %s\n", tokenString);
			break;
		case OF:
			fprintf(listing, "OF %s\n", tokenString);
			break;
		case REPEAT:
			fprintf(listing, "REPEAT %s\n", tokenString);
			break;
		case UNTIL:
			fprintf(listing, "UNTIL %s\n", tokenString);
			break;
		case IF:
			fprintf(listing, "IF %s\n", tokenString);
			break;
		case THEN:
			fprintf(listing, "THEN %s\n", tokenString);
			break;
		case ELSE:
			fprintf(listing, "ELSE %s\n", tokenString);
			break;
		case DO:
			fprintf(listing, "DO %s\n", tokenString);
			break;
		case FOR:
			fprintf(listing, "FOR %s\n", tokenString);
			break;
		case TO:
			fprintf(listing, "TO %s\n", tokenString);
			break;
		case DOWNTO:
			fprintf(listing, "DOWNTO %s\n", tokenString);
			break;
		case PROCEDURE:
			fprintf(listing, "PROCEDURE %s\n", tokenString);
			break;
		case FUNCTION:
			fprintf(listing, "FUNCTION %s\n", tokenString);
			break;
		case READ:
			fprintf(listing, "READ %s\n", tokenString);
			break;
		case WRITE:
			fprintf(listing, "WRITE %s\n", tokenString);
			break;
		case BEGIN:
			fprintf(listing, "BEGIN %s\n", tokenString);
			break;
		case END:
			fprintf(listing, "END %s\n", tokenString);
			break;
		case PLUS:
			fprintf(listing, "PLUS %s\n", tokenString);
			break;
		case MINUS:
			fprintf(listing, "MINUS %s\n", tokenString);
			break;
		case STAR:
			fprintf(listing, "STAR %s\n", tokenString);
			break;
		case OVER:
			fprintf(listing, "OVER %s\n", tokenString);
			break;
		case LST:
			fprintf(listing, "LST %s\n", tokenString);
			break;
		case LEQ:
			fprintf(listing, "LEQ %s\n", tokenString);
			break;
		case GTT:
			fprintf(listing, "GTT %s\n", tokenString);
			break;
		case GEQ:
			fprintf(listing, "GEQ %s\n", tokenString);
			break;
		case EQU:
			fprintf(listing, "EQU %s\n", tokenString);
			break;
		case NEQ:
			fprintf(listing, "NEQ %s\n", tokenString);
			break;
		case ASSIGN:
			fprintf(listing, "ASSIGN %s\n", tokenString);
			break;
		case SEMI:
			fprintf(listing, "SEMI %s\n", tokenString);
			break;
		case COMMA:
			fprintf(listing, "COMMA %s\n", tokenString);
			break;
		case DOT:
			fprintf(listing, "DOT %s\n", tokenString);
			break;
		case COLON:
			fprintf(listing, "COLON %s\n", tokenString);
			break;
		case SQUO:
			fprintf(listing, "SQUO %s\n", tokenString);
			break;
		case DQUO:
			fprintf(listing, "DQUO %s\n", tokenString);
			break;
		case LPAR:
			fprintf(listing, "LPAR %s\n", tokenString);
			break;
		case RPAR:
			fprintf(listing, "RPAR %s\n", tokenString);
			break;
		case LBRA:
			fprintf(listing, "LBRA %s\n", tokenString);
			break;
		case RBRA:
			fprintf(listing, "RBRA %s\n", tokenString);
			break;
		case LBBR:
			fprintf(listing, "LBBR %s\n", tokenString);
			break;
		case RBBR:
			fprintf(listing, "RBBR %s\n", tokenString);
			break;
		case ERROR:
			fprintf(listing, "ERROR %s\n", tokenString);
			break;
		case ENDFILE:
			fprintf(listing, "ENDFILE %s\n", tokenString);
			break;
		default:
			fprintf(errlist, "unknown token: %s\n", tokenString);
	}
}
