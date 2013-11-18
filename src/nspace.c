#include "global.h"
#include "parse.h"
#include "nspace.h"
static char nspace[MAXNAMESPACE];
int nspacelen = 0;

void Ninit(void)
{
	strcpy(nspace,"NICE");
	nspacelen = strlen(nspace);
}

void Npush(char *name)
{
	strcat(nspace,"_");
	strcat(nspace, name);
	nspacelen = strlen(nspace);
}

BOOL Npop(void)
{
	int i;
	for (i = nspacelen - 1; i >= 0; i--) {
		if (nspace[i] == '_') {
			nspace[i] = '\0';
			nspacelen = strlen(nspace);
			return TRUE;
		}
	}
	return FALSE;
}

char *Nappend(char *name)
{
	int n;
	char *t;
	if (name == NULL) {
		return NULL;
	}
	n = strlen(name);
	t = (char *) malloc((n+nspacelen+2)*sizeof(char));
	if (t == NULL) {
		fprintf(errlist, "OUTOFMEM: in Nappend\n");
		return NULL;
	}
	strcpy(t, nspace);
	strcat(t, "_");
	strcat(t, name);
	return t;
}

char *signature(IdentSP idp, ParaListSP plp)
{
	int n;
	char *t;
	ParaListSP p;
	ParaDefSP q;
	if (idp == NULL) {
		return NULL;
	}
	n = strlen(idp->name);
	for (p = plp; p != NULL; p = p->next) {
		for (q = p->pdp; q != NULL; q = q->next) {
			n += 2;
		}
	}
	t = (char *) malloc((n+1)*sizeof(char));
	if (t == NULL) {
		fprintf(errlist, "OUTOFMEM: in funLabel\n");
		return NULL;
	}
	strcpy(t,idp->name);
	for (p = plp; p != NULL; p = p->next) {
		for (q = p->pdp; q != NULL; q = q->next) {
			switch (q->idp->type) {
			case Int_Para_Val_Ident_t:
			case Int_Para_Ref_Ident_t:
				strcat(t,"$I");
				break;
			case Char_Para_Val_Ident_t:
			case Char_Para_Ref_Ident_t:
				strcat(t,"$C");
				break;
			default:
				fprintf(errlist, "NSPACE BUG:87\n");
			}
		}
	}
	return t;
}
