/**
 * File: error.c
 * Date: Nov 10, 2013
 * Author: Jeanhwea
 */
#include "global.h"
#include "error.h" 

char *ERRVEC[MAXERROR] = 
{
	"Fatal, Unexpect symbol token -> ",
	"Char defination is too long",
	"Char can only be defined as digit or letter",
	"Wrong defination of a string type",
	"Missing a '.' at the end of a program",

	"Missing a ';' after -> ",
	"Missing a '=' after -> ",
	"Missing a unsign number after -> ",
	"Missing a ':' after -> ",
	"Missing a '[' after -> ",

	"Missing a ']' after -> ",
	"Missing a '(' after -> ",
	"Missing a ')' after -> ",
	"Missing a keyword 'of' after -> ",
	"Missing a ':=' after -> ",

	"Missing a keyword 'then' after -> ",
	"Missing a keyword 'until' after -> ",
	"Missing a keyword 'to' or 'downto' after -> ",
	"Missing a keyword 'do' after -> ",
	"Missing a function or procedure body",
	
	"Missing a identifier after -> ",
	"Missing a keyword 'end' after -> ",
	"Duplicate defined symbol -> ",
	"First used an undefined symbol -> ",
	"Should be a array type symbol -> ",

	"Should be var/fun/para symbol -> ",
	"Should be a procedure type symbol -> ",
	"Should be a function type symbol -> ",
	"Different size of parameters and arguments while using -> ",
	"Error use pass value by reference -> "
};

void lexError(ERRNO errno)
{
	fprintf(errlist, "lex error:%d: ", lineno);
	fprintf(errlist, "%s\n", ERRVEC[errno]);
	exit(1);
}

void syntaxError(ERRNO errno, int lineno, BOOL fatal, char *msg)
{
	fprintf(errlist, "syntax error:%d: ", lineno);
	if (msg != NULL) {
		fprintf(errlist, "%s%s\n", ERRVEC[errno], msg);
	} else {
		fprintf(errlist, "%s\n", ERRVEC[errno]);
	}
	if (fatal) {
		exit(1);
	}
}

void semanticError(ERRNO errno, int lineno, BOOL fatal, char *msg)
{
	fprintf(errlist, "semantic error:%d: ", lineno);
	if (msg != NULL) {
		fprintf(errlist, "%s%s\n", ERRVEC[errno], msg);
	} else {
		fprintf(errlist, "%s\n", ERRVEC[errno]);
	}
	if (fatal) {
		exit(1);
	}
}
