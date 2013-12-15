/**
 * File: util.h
 * Date: Nov 4, 2013
 * Author: Jeanhwea
 */

#ifndef UTIL_H

#define UTIL_H

/* allocate and copy a string */
char *copyString(char *);

/* a bundle print function */
void headPr(char *);
void innerPr(int , ...);
void innerIdnPr(int , ...);
void innerlnPr(int , ...);
void innerIdnlnPr(int , ...);
void innerIntPr(int );
void innerCharPr(char );
void tailPr(char *);

void ioasm(void);
#endif /* end of include guard: UTIL_H */
