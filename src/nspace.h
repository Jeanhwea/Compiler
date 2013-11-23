/**
 * File: nspace.h
 * Date: Nov 19, 2013
 * Author: Jeanhwea
 */

#ifndef NSPACE_H

#define NSPACE_H

#define MAXNAMESPACE 1024

void Ninit(void);
void Npush(char *);
BOOL Npop(void);
char *Nappend(char *);
char *signature(IdentSP, ParaListSP);

#endif /* end of include guard: NSPACE_H */
