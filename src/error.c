/**
 * File: error.c
 * Date: Nov 10, 2013
 * Author: Jeanhwea
 */
#include "global.h"
#include "error.h" 

char *ERRVEC[MAXERROR] = 
{
	"Char defination is too long",
	"Char can only be defined as digit or letter",
	"Wrong defination of a string type",
	"Missing a dot at the end of a program"
};

void lexError(ERRNO errno)
{
	fprintf(errlist, "\nlex error:%d: ", lineno);
	fprintf(errlist, "%s\n", ERRVEC[errno]);
}

void syntaxError(ERRNO errno)
{
	fprintf(errlist, "\nsyntax error:%d: ", lineno);
	fprintf(errlist, "%s\n", ERRVEC[errno]);
}

void sematicError(ERRNO errno)
{
	fprintf(errlist, "\nsematic error:%d: ", lineno);
	fprintf(errlist, "%s\n", ERRVEC[errno]);
}
