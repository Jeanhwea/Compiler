#ifndef ERROR_H

#define ERROR_H

#define MAXERROR 50

/* define a list of error number */
typedef int ERRNO;

#define ERRCHARLEN 0
#define ERRCHARTYPE 1
#define ERRSTRINGTYPE 2
#define MISSDOT 3

extern char *ERRVEC[MAXERROR];

void lexError(ERRNO errno);
void syntaxError(ERRNO errno);

#endif /* end of include guard: ERROR_H */
