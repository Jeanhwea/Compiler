/**
 * File: util.c
 * Date: Nov 4, 2013
 * Author: Jeanhwea
 */

#include "global.h"
#include "util.h"

/* tokenCount is the number of current token */
int tokenCount = 0;

void printToken(TokenType token, const char *tokenString)
{
	switch (token) {
		case ID:
			fprintf(listing, "ID %s\n", tokenString);
			break;
		case UNS:
			fprintf(listing, "UNS %s\n",tokenString);
			break;
		case CH:
			fprintf(listing, "CH %s\n",tokenString);
			break;
		case STRING:
			fprintf(listing, "STRING %s\n",tokenString);
			break;
		case CONST:
			fprintf(listing, "CONST %s\n",tokenString);
			break;
		case INTEGER:
			fprintf(listing, "INTEGER %s\n",tokenString);
			break;
		case CHAR:
			fprintf(listing, "CHAR %s\n",tokenString);
			break;
		case VAR:
			fprintf(listing, "VAR %s\n",tokenString);
			break;
		case ARRAY:
			fprintf(listing, "ARRAY %s\n",tokenString);
			break;
		case OF:
			fprintf(listing, "OF %s\n",tokenString);
			break;
		case REPEAT:
			fprintf(listing, "REPEAT %s\n",tokenString);
			break;
		case UNTIL:
			fprintf(listing, "UNTIL %s\n",tokenString);
			break;
		case IF:
			fprintf(listing, "IF %s\n",tokenString);
			break;
		case THEN:
			fprintf(listing, "THEN %s\n",tokenString);
			break;
		case ELSE:
			fprintf(listing, "ELSE %s\n",tokenString);
			break;
		case DO:
			fprintf(listing, "DO %s\n",tokenString);
			break;
		case FOR:
			fprintf(listing, "FOR %s\n",tokenString);
			break;
		case TO:
			fprintf(listing, "TO %s\n",tokenString);
			break;
		case DOWNTO:
			fprintf(listing, "DOWNTO %s\n",tokenString);
			break;
		case PROCEDURE:
			fprintf(listing, "PROCEDURE %s\n",tokenString);
			break;
		case FUNCTION:
			fprintf(listing, "FUNCTION %s\n",tokenString);
			break;
		case READ:
			fprintf(listing, "READ %s\n",tokenString);
			break;
		case WRITE:
			fprintf(listing, "WRITE %s\n",tokenString);
			break;
		case BEGIN:
			fprintf(listing, "BEGIN %s\n",tokenString);
			break;
		case END:
			fprintf(listing, "END %s\n",tokenString);
			break;
		case PLUS:
			fprintf(listing, "PLUS %s\n",tokenString);
			break;
		case MINUS:
			fprintf(listing, "MINUS %s\n",tokenString);
			break;
		case STAR:
			fprintf(listing, "STAR %s\n",tokenString);
			break;
		case OVER:
			fprintf(listing, "OVER %s\n",tokenString);
			break;
		case LST:
			fprintf(listing, "LST %s\n",tokenString);
			break;
		case LEQ:
			fprintf(listing, "LEQ %s\n",tokenString);
			break;
		case GTT:
			fprintf(listing, "GTT %s\n",tokenString);
			break;
		case GEQ:
			fprintf(listing, "GEQ %s\n",tokenString);
			break;
		case EQU:
			fprintf(listing, "EQU %s\n",tokenString);
			break;
		case NEQ:
			fprintf(listing, "NEQ %s\n",tokenString);
			break;
		case ASSIGN:
			fprintf(listing, "ASSIGN %s\n",tokenString);
			break;
		case SEMI:
			fprintf(listing, "SEMI %s\n",tokenString);
			break;
		case COMMA:
			fprintf(listing, "COMMA %s\n",tokenString);
			break;
		case DOT:
			fprintf(listing, "DOT %s\n",tokenString);
			break;
		case COLON:
			fprintf(listing, "COLON %s\n",tokenString);
			break;
		case SQUO:
			fprintf(listing, "SQUO %s\n",tokenString);
			break;
		case DQUO:
			fprintf(listing, "DQUO %s\n",tokenString);
			break;
		case LPAR:
			fprintf(listing, "LPAR %s\n",tokenString);
			break;
		case RPAR:
			fprintf(listing, "RPAR %s\n",tokenString);
			break;
		case LBRA:
			fprintf(listing, "LBRA %s\n",tokenString);
			break;
		case RBRA:
			fprintf(listing, "RBRA %s\n",tokenString);
			break;
		case LBBR:
			fprintf(listing, "LBBR %s\n",tokenString);
			break;
		case RBBR:
			fprintf(listing, "RBBR %s\n",tokenString);
			break;
		case ERROR:
			fprintf(listing, "ERROR %s\n", tokenString);
			break;
		case ENDFILE:
			fprintf(listing, "ENDFILE %s\n", tokenString);
			break;
		default:
			fprintf(errlist, "unknown token: %s\n",tokenString);
			++tokenCount;
	}
}

char *copyString(char *s)
{
	int n;
	char *t;
	if (s == NULL) {
		return NULL;
	}
	n = strlen(s) + 1;
	t = (char *) malloc(n * sizeof(char));
	if (t == NULL) {
		fprintf(errlist, "Out of memory error at line %d\n", lineno);
	} else {
		strcpy(t, s);
		if (ShowTip)
			fprintf(tiplist, "%s\n", s);
	}
	return t;
}

static int indentno = 0;
static void Indent(void)
{
	int i;
	for (i = 0; i < indentno; i++) {
		if (ShowAST)
			fprintf(listing, "\t");
	}
}

void headPr(char *cont)
{
	Indent();
	indentno += 1;
	if (ShowAST)
		fprintf(listing, "<%s>\n", cont);
}

void innerPr(int n, ...)
{
	int i;
	char *chp;
	va_list vl;
	va_start(vl, n);
	for (i = 0; i < n; i++) {
		chp = va_arg(vl, char *);
		if (ShowAST)
			fprintf(listing, "%s", chp);
	}
	va_end(vl);
}

void innerIdnPr(int n, ...)
{
	int i;
	char *chp;
	va_list vl;
	Indent();
	va_start(vl, n);
	for (i = 0; i < n; i++) {
		chp = va_arg(vl, char *);
		if (ShowAST)
			fprintf(listing, "%s", chp);
	}
	va_end(vl);
}

void innerlnPr(int n, ...)
{
	int i;
	char *chp;
	va_list vl;
	va_start(vl, n);
	for (i = 0; i < n; i++) {
		chp = va_arg(vl, char *);
		if (ShowAST)
			fprintf(listing, "%s", chp);
	}
	va_end(vl);
	if (ShowAST) {
		fprintf(listing, "\n");
	}
}

void innerIdnlnPr(int n, ...)
{
	int i;
	char *chp;
	va_list vl;
	Indent();
	va_start(vl, n);
	for (i = 0; i < n; i++) {
		chp = va_arg(vl, char *);
		if (ShowAST)
			fprintf(listing, "%s", chp);
	}
	va_end(vl);
	if (ShowAST) {
		fprintf(listing, "\n");
	}
}

void innerIntPr(int val)
{
	if (ShowAST)
		fprintf(listing, "%d\n", val);
}

void innerCharPr(char val)
{
	if (ShowAST)
		fprintf(listing, "%c\n", val);
}

void tailPr(char *cont)
{
	indentno -= 1;
	Indent();
	if (ShowAST)
		fprintf(listing, "</%s>\n", cont);
}