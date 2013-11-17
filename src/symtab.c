/**
 * File: symtab.c
 * Date: Nov 12, 2013
 * Author: Jeanhwea
 */

#include "global.h"
#include "scan.h"
#include "parse.h"
#include "error.h"
#include "symtab.h"


SymTabSP top = NULL;

static inline SymTabSP pop()
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

static inline void push(SymTabSP t)
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

void sym_insert(Identp idp)
{
	SymTabSP t;
	SymBucketSP p;
	SymLineSP l;
	int h = hash(idp->name);
	if (top == NULL) 
		fprintf(errlist, "SYMTAB BUG:57\n");
	for (t = top; t != NULL; t = t->prev) {
		for (p = *(t->sbp + h); p != NULL; p = p->next) {
			if ((p->ep != NULL) 
				&& (!strcmp(name, p->ep->name)) ) 
				goto OUT;
		}
	}
OUT:
	if (p == NULL) { /* symbol not yet in table */
		/* line and reference line */
		ENTRY(SymLineS, l);
		l->lineno = idp->line;
		l->next = NULL;
		ENTRY(SymBucketS, p);
		p->ep->name = idp->name;
		p->ep->lev = level;
		p->ep->lines = l;
		p->ep->ap = NULL;
		p->ep->bp = NULL;
		p->ep->stp = t;
		switch (idp->type) {
		case Proc_Ident_t:
			p->ep->obj = Proc_Obj_t;
			break;
		case Int_Fun_Ident_t:
		case Char_Fun_Ident_t:
			p->ep->obj = Fun_Obj_t;
			break;
		case Int_Const_Ident_t:
		case Char_Const_Ident_t:
			p->ep->obj = Const_Obj_t;
			break;
		case Int_Var_Ident_t:
		case Char_Var_Ident_t:
		case IntArr_Var_Ident_t:
		case CharArr_Var_Ident_t:
			p->ep->obj = Var_Obj_t;
			break;
		case Init_Ident_t:
		case Int_Para_Val_Ident_t:
		case Char_Para_Val_Ident_t:
		case Int_Para_Ref_Ident_t:
		case Char_Para_Ref_Ident_t:
			p->ep->obj = Nop_Obj_t;
			break;
		default:
			fprintf(errlist, "SYMTAB BUG:95\n");
		}
		switch (idp->type) {
		case Init_Ident_t:
		case Proc_Ident_t:
			p->ep->type = Nop_Type_t;
			break;
		case Int_Fun_Ident_t:
		case Int_Const_Ident_t:
		case Int_Var_Ident_t:
		case IntArr_Var_Ident_t:
		case Int_Para_Val_Ident_t:
		case Int_Para_Ref_Ident_t:
			p->ep->type = Int_type_t;
			break;
		case Char_Fun_Ident_t:
		case Char_Const_Ident_t:
		case Char_Var_Ident_t:
		case CharArr_Var_Ident_t:
		case Char_Para_Val_Ident_t:
		case Char_Para_Ref_Ident_t:
			p->ep->type = Char_Type_t;
			break;
		default:
			fprintf(errlist, "SYMTAB BUG:124\n");
		}
	}
}
