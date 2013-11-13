/**
 * File: global.h
 * Date: Nov 3, 2013
 * Author: Jeanhwea 
 */

#ifndef GLOBAL_H

#define GLOBAL_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdarg.h>

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

typedef int BOOL;


/* MAXRESERVED = the number of reserved words */
#define MAXRESERVED 21

extern FILE *source; /* source code text file */
extern FILE *listing; /* listing output text file */
extern FILE *code; /* code text file */
extern FILE *errlist; /* errors text file */

extern int lineno; /* source line number for listing */


/* begin for scan */
/* end for scan */


/* some global flags */
extern BOOL PrintSource;
extern BOOL TraceScan;
extern BOOL ShowAST;
#endif /* end of include guard: GLOBAL_H */
