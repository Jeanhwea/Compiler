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
			fprintf(listing, "%d IDEN %s\n",
					++tokenCount, tokenString);
			break;
		case NUM:
			fprintf(listing, "%d INTCON %s\n",
					++tokenCount, tokenString);
			break;
		case CH:
			fprintf(listing, "%d CHARCON %s\n",
					++tokenCount, tokenString);
			break;
		case STRING:
			fprintf(listing, "%d STRCON %s\n",
					++tokenCount, tokenString);
			break;
		case CONST:
			fprintf(listing, "%d CONSTTK %s\n",
					++tokenCount, tokenString);
			break;
		case INTEGER:
			fprintf(listing, "%d INITK %s\n",
					++tokenCount, tokenString);
			break;
		case CHAR:
			fprintf(listing, "%d CHARTK %s\n",
					++tokenCount, tokenString);
			break;
		case VAR:
			fprintf(listing, "%d VARTK %s\n",
					++tokenCount, tokenString);
			break;
		case ARRAY:
			fprintf(listing, "%d ARRAYTK %s\n",
					++tokenCount, tokenString);
			break;
		case OF:
			fprintf(listing, "%d OFTK %s\n",
					++tokenCount, tokenString);
			break;
		case REPEAT:
			fprintf(listing, "%d REPTTK %s\n",
					++tokenCount, tokenString);
			break;
		case UNTIL:
			fprintf(listing, "%d UNLTK %s\n",
					++tokenCount, tokenString);
			break;
		case IF:
			fprintf(listing, "%d IFTK %s\n",
					++tokenCount, tokenString);
			break;
		case THEN:
			fprintf(listing, "%d THENTK %s\n",
					++tokenCount, tokenString);
			break;
		case ELSE:
			fprintf(listing, "%d ELSETK %s\n",
					++tokenCount, tokenString);
			break;
		case DO:
			fprintf(listing, "%d DOTK %s\n",
					++tokenCount, tokenString);
			break;
		case FOR:
			fprintf(listing, "%d FORTK %s\n",
					++tokenCount, tokenString);
			break;
		case TO:
			fprintf(listing, "%d TOTK %s\n",
					++tokenCount, tokenString);
			break;
		case DOWNTO:
			fprintf(listing, "%d DOWNTOTK %s\n",
					++tokenCount, tokenString);
			break;
		case PROCEDURE:
			fprintf(listing, "%d PROCETK %s\n",
					++tokenCount, tokenString);
			break;
		case FUNCTION:
			fprintf(listing, "%d FUNCTK %s\n",
					++tokenCount, tokenString);
			break;
		case READ:
			fprintf(listing, "%d READTK %s\n",
					++tokenCount, tokenString);
			break;
		case WRITE:
			fprintf(listing, "%d WRITETK %s\n",
					++tokenCount, tokenString);
			break;
		case BEGIN:
			fprintf(listing, "%d BEGINTK %s\n",
					++tokenCount, tokenString);
			break;
		case END:
			fprintf(listing, "%d ENDTK %s\n",
					++tokenCount, tokenString);
			break;
		case PLUS:
			fprintf(listing, "%d PLUS %s\n",
					++tokenCount, tokenString);
			break;
		case MINUS:
			fprintf(listing, "%d MINU %s\n",
					++tokenCount, tokenString);
			break;
		case STAR:
			fprintf(listing, "%d MULT %s\n",
					++tokenCount, tokenString);
			break;
		case OVER:
			fprintf(listing, "%d DIV %s\n",
					++tokenCount, tokenString);
			break;
		case LST:
			fprintf(listing, "%d LSS %s\n",
					++tokenCount, tokenString);
			break;
		case LEQ:
			fprintf(listing, "%d LEQ %s\n",
					++tokenCount, tokenString);
			break;
		case GTT:
			fprintf(listing, "%d GRE %s\n",
					++tokenCount, tokenString);
			break;
		case GEQ:
			fprintf(listing, "%d GEQ %s\n",
					++tokenCount, tokenString);
			break;
		case EQU:
			fprintf(listing, "%d EQU %s\n",
					++tokenCount, tokenString);
			break;
		case NEQ:
			fprintf(listing, "%d NEQ %s\n",
					++tokenCount, tokenString);
			break;
		case ASSIGN:
			fprintf(listing, "%d ASSIGN %s\n",
					++tokenCount, tokenString);
			break;
		case SEMI:
			fprintf(listing, "%d SEMICN %s\n",
					++tokenCount, tokenString);
			break;
		case COMMA:
			fprintf(listing, "%d COMMA %s\n",
					++tokenCount, tokenString);
			break;
		case DOT:
			fprintf(listing, "%d PERIOD %s\n",
					++tokenCount, tokenString);
			break;
		case COLON:
			fprintf(listing, "%d COLON %s\n",
					++tokenCount, tokenString);
			break;
		case SQUO:
			fprintf(listing, "%d QMARK %s\n",
					++tokenCount, tokenString);
			break;
		case DQUO:
			fprintf(listing, "%d DQMARK %s\n",
					++tokenCount, tokenString);
			break;
		case LPAR:
			fprintf(listing, "%d LPARENT %s\n",
					++tokenCount, tokenString);
			break;
		case RPAR:
			fprintf(listing, "%d RPARENT %s\n",
					++tokenCount, tokenString);
			break;
		case LBRA:
			fprintf(listing, "%d LBRACK %s\n",
					++tokenCount, tokenString);
			break;
		case RBRA:
			fprintf(listing, "%d RBRACK %s\n",
					++tokenCount, tokenString);
			break;
		case LBBR:
			fprintf(listing, "%d LBRACE %s\n",
					++tokenCount, tokenString);
			break;
		case RBBR:
			fprintf(listing, "%d RBRACE %s\n",
					++tokenCount, tokenString);
			break;
		default:
			fprintf(listing, "unknown token: %s\n",tokenString);
			++tokenCount;
	}
}

//void printToken(TokenType token, const char *tokenString)
//{
//	switch (token) {
//		case ARRAY:
//		case BEGIN:
//			fprintf(listing, "reserved word: %s\n", tokenString);
//			break;
//		default:
//			fprintf(listing, "unknown token: %s\n", token);
//	}
//}
