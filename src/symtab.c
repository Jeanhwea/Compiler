/**
 * File: symtab.c
 * Date: Nov 12, 2013
 * Author: Jeanhwea
 */

#include "global.h"
#include "util.h"
#include "parse.h"
#include "symtab.h"
#include "nspace.h"
/* hash size */
int HASHSIZE = 211;
/* hash shift */
int SHIFT = 4;

SymTabSP top = NULL;

SymTabSP pop()
{
	SymTabSP t;
	if (top != NULL) {
		t = top;
		top = t->prev;
		if (top != NULL)
			top->next = NULL;
	} else t = NULL;
	return t;
}

void push(SymTabSP t)
{
	t->next = NULL;
	t->prev = top;
	if (top != NULL)
		top->next = t;
	top = t;
}

static inline int hash(char *key)
{
	int h = 0;
	int i;
	for (i = 0; key[i] != '\0'; i++) {
		h = ((h << SHIFT) + key[i]) % HASHSIZE;
	}
	return h;
}

void sym_insert(SymBucketSP bp, SymTabSP st)
{
	int h;
	SymBucketSP p;
	SymBucketSP *head;
	if (bp == NULL || st == NULL) {
		fprintf(errlist, "SYMTAB BUG:50\n");
		return ;
	}
	h = hash(bp->ep->name);
	head = st->sbp + h;
	for (p = *head; p != NULL; p = p->next) {
		if (!strcmp(bp->ep->name, p->ep->name))
			break;
	}
	if (p == NULL) {
		bp->next = *head;
		*head = bp;
	} else {
	}
}

void sym_insert_const(IdentSP idp)
{
	SymBucketSP p;
	SymTabESP e;
	SymLineSP l;
	int h = hash(idp->name);
	if (top == NULL) 
		fprintf(errlist, "SYMTAB BUG:57\n");
	for (p = *(top->sbp + h); p != NULL; p = p->next) {
		if ((p->ep != NULL) && (!strcmp(idp->name, p->ep->name)) ) 
				break;
	}
	if (p == NULL) {
		ENTRY(SymLineS, l);
		l->lineno = idp->line;
		l->next = NULL;
		ENTRY(SymTabES, e);
		e->name = copyString(idp->name);
		e->label = Nappend(idp->name);
		e->lines = l;
		e->len = 0;
		e->obj = Const_Obj_t;
		switch (idp->type) {
		case Int_Const_Ident_t:
			e->type = Int_Type_t;
			break;
		case Char_Const_Ident_t:
			e->type = Char_Type_t;
			break;
		default:
			fprintf(errlist, "SYMTAB BUG: 73\n");
		}
		e->stp = top;
		ENTRY(SymBucketS, p);
		p->ep = e;
		p->next = NULL;
		sym_insert(p, top);
	} else {
		fprintf(errlist, "\nduplicated const define: %s\n: %d",
				idp->name, idp->line);
	}
}

void sym_insert_var(IdentSP idp)
{
	SymBucketSP p;
	SymTabESP e;
	SymLineSP l;
	int h = hash(idp->name);
	if (top == NULL) 
		fprintf(errlist, "SYMTAB BUG:121\n");
	for (p = *(top->sbp + h); p != NULL; p = p->next) {
		if ((p->ep != NULL) && (!strcmp(idp->name, p->ep->name)) ) 
				break;
	}
	if (p == NULL) {
		ENTRY(SymLineS, l);
		l->lineno = idp->line;
		l->next = NULL;
		ENTRY(SymTabES, e);
		e->name = copyString(idp->name);
		e->label = Nappend(idp->name);
		e->lines = l;
		e->obj = Var_Obj_t;
		switch (idp->type) {
		case Int_Var_Ident_t:
			e->type = Int_Type_t;
			e->len = 0;
			break;
		case Char_Var_Ident_t:
			e->type = Char_Type_t;
			e->len = 0;
			break;
		case IntArr_Var_Ident_t:
			e->type = Array_Type_t;
			e->len = idp->length;
			break;
		case CharArr_Var_Ident_t:
			e->type = Array_Type_t;
			e->len = idp->length;
			break;
		default:
			fprintf(errlist, "SYMTAB BUG: 143\n");
		}
		e->stp = top;
		ENTRY(SymBucketS, p);
		p->ep = e;
		p->next = NULL;
		sym_insert(p, top);
	} else {
		fprintf(errlist, "\nduplicated var define: %s\n: %d",
				idp->name, idp->line);
	}
}

void sym_insert_proc(IdentSP idp, ParaListSP plp)
{
	char *proclabel;
	char *procsign;
	SymBucketSP p;
	SymTabESP e;
	SymLineSP l;
	int h = hash(idp->name);
	procsign = signature(idp, plp);
	proclabel = Nappend(procsign);
	if (top == NULL) 
		fprintf(errlist, "SYMTAB BUG:121\n");
	for (p = *(top->sbp + h); p != NULL; p = p->next) {
		if ((p->ep != NULL) && (!strcmp(idp->name, p->ep->name)) 
			&& (!strcmp(proclabel, p->ep->label)) ) 
				break;
	}
	if (p == NULL) {
		ENTRY(SymLineS, l);
		l->lineno = idp->line;
		l->next = NULL;
		ENTRY(SymTabES, e);
		e->name = copyString(idp->name);
		e->label = proclabel; 
		Npush(procsign);
		e->lines = l;
		e->obj = Proc_Obj_t;
		e->type = Nop_Type_t;
		e->stp = top;
		ENTRY(SymBucketS, p);
		p->ep = e;
		p->next = NULL;
		sym_insert(p, top);
	} else {
		fprintf(errlist, "\nduplicated procedure define: %s\n: %d",
				idp->name, idp->line);
	}
}

void sym_insert_fun(IdentSP idp, ParaListSP plp)
{
	char *funlabel;
	char *funsign;
	SymBucketSP p;
	SymTabESP e;
	SymLineSP l;
	int h = hash(idp->name);
	funsign = signature(idp, plp);
	funlabel = Nappend(funsign);
	if (top == NULL) 
		fprintf(errlist, "SYMTAB BUG:121\n");
	for (p = *(top->sbp + h); p != NULL; p = p->next) {
		if ((p->ep != NULL) && (!strcmp(idp->name, p->ep->name)) 
			&& (!strcmp(funlabel, p->ep->label)) ) 
				break;
	}
	if (p == NULL) {
		ENTRY(SymLineS, l);
		l->lineno = idp->line;
		l->next = NULL;
		ENTRY(SymTabES, e);
		e->name = copyString(idp->name);
		e->label = funlabel; 
		Npush(funsign);
		e->lines = l;
		e->obj = Fun_Obj_t;
		switch (idp->type) {
		case Int_Fun_Ident_t:
			e->type = Int_Type_t;
			e->len = 0;
			break;
		case Char_Fun_Ident_t:
			e->type = Char_Type_t;
			e->len = 0;
			break;
		default:
			fprintf(errlist, "SYMTAB BUG: 201\n");
		}
		e->stp = top;
		ENTRY(SymBucketS, p);
		p->ep = e;
		p->next = NULL;
		sym_insert(p, top);
	} else {
		fprintf(errlist, "\nduplicated funtion define: %s\n: %d",
				idp->name, idp->line);
	}
}

SymBucketSP sym_lookup(char *name)
{
	SymTabSP t;
	SymBucketSP p;
	int h = hash(name);
	if (top == NULL) 
		fprintf(errlist, "SYMTAB BUG:108\n");
	for (t = top; t != NULL; t = t->prev) {
		for (p = *(t->sbp + h); p != NULL; p = p->next) {
			if ((p->ep != NULL) 
				&& (!strcmp(name, p->ep->name)) ) 
				return p;
		}
	}
	return NULL;
}

void printTab(SymTabSP t)
{
	SymBucketSP p;
	int i;
	if (t != NULL) {
		fprintf(tiplist, "\nname\t\tlabel\t\tline\tobject\ttype\n");
		for (i = 0; i < HASHSIZE; i++) {
			for (p = *(t->sbp + i); p != NULL; p = p->next) {
				fprintf(tiplist, "%s\t%s\t%d\t",
					p->ep->name, p->ep->label, 
					p->ep->lines->lineno);
				switch (p->ep->obj) {
				case Const_Obj_t:
					fprintf(tiplist, "Const_Obj_t");
					break;
				case Var_Obj_t:
					fprintf(tiplist, "Var_Obj_t");
					break;
				case Proc_Obj_t:
					fprintf(tiplist, "Proc_Obj_t");
					break;
				case Fun_Obj_t:
					fprintf(tiplist, "Fun_Obj_t");
					break;
				default:
					fprintf(errlist, "SYMTAB BUG:210\n");
				}
				fprintf(tiplist, "\t");
				switch (p->ep->type) {
				case Int_Type_t:
					fprintf(tiplist, "Int_Type_t");
					break;
				case Char_Type_t:
					fprintf(tiplist, "Char_Type_t");
					break;
				case Array_Type_t:
					fprintf(tiplist, "Array_Type_t");
					break;
				case Nop_Type_t:
					fprintf(tiplist, "Nop_Type_t");
					break;
				default:
					fprintf(errlist, "SYMTAB BUG:226\n");
				}
				fprintf(tiplist, "\n");
			}
		}
	}
}
