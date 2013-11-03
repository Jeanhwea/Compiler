/**
 * File: util.c
 * Date: Nov 4, 2013
 * Author: Jeanhwea
 */

#include <global.h>
#include <util.h>

void printToken(TokenType token, const char *tokenString)
{
	switch (token) {
		case ARRAY:
		case BEGIN:
			fprintf(listing, "reserved word: %s\n", tokenString);
			break;
		default:
			fprintf(listing, "unknown token: %s\n", token);
	}
}
