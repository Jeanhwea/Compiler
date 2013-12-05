/**
 * File: error.h
 * Date: Nov 10, 2013
 * Author: Jeanhwea
 */
#ifndef ERROR_H

#define ERROR_H

#define MAXERROR 50

/* define a list of error number */
typedef int ERRNO;

#define UNEXPECT 0
#define ERRCHARLEN 1
#define ERRCHARTYPE 2
#define ERRSTRINGTYPE 3
#define MISSDOT 4

#define MISSSEMI 5
#define	MISSEQU 6
#define MISSUNS 7
#define MISSCOLON 8
#define MISSLBRA 9

#define MISSRBRA 10
#define MISSLPAR 11
#define MISSRPAR 12
#define MISSOF 13
#define MISSASS 14

#define MISSTHEN 15
#define MISSUNTIL 16
#define MISSTODOWN 17
#define MISSDO 18
#define MISSBODY 19

#define MISSID 20
#define MISSEND 21
#define DUPSYM 22
#define NULLSYM 23
#define NOPARRAY 24

#define NOPVAR 25
#define NOPPROC 26
#define NOPFUN 27
#define ARGERROR 28
#define ERRREF 29

extern char *ERRVEC[MAXERROR];

void lexError(ERRNO errno);
void syntaxError(ERRNO errno, int lineno, BOOL fatal, char *msg);
void semanticError(ERRNO errno, int lineno, BOOL fatal, char *msg);

#endif /* end of include guard: ERROR_H */
