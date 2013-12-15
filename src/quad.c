/**
 * File: quad.c
 * Date: Nov 18, 2013
 * Author: Jeanhwea
 */
#include "global.h"
#include "parse.h"
#include "symtab.h"
#include "quad.h"

char *quadMap[30] = 
{
	"ADD",
	"SUB",
	"MUL",
	"DIV",
	"INC",
	"DEC",
	"NEG",
	"LOAD",
	"ASS",
	"AARR",
	"EQU",
	"NEQ",
	"GTT",
	"GEQ",
	"LST",
	"LEQ",
	"JMP",
	"PUSH",
	"PUSHA",
	"POP",
	"CALL",
	"SRET",
	"ENTER",
	"FIN",
	"READ",
	"READC",
	"WRS",
	"WRI",
	"WRC",
	"LABEL"
};

QuadSP qhead = NULL;
QuadSP qtail = NULL;

void emit(QuadSP q)
{
	if (qtail == NULL) {
		q->prev = qtail;
		q->next = NULL;
		qhead = qtail = q;
	} else {
		q->prev = qtail;
		q->next = NULL;
		qtail->next = q;
		qtail = q;
	}
	if (ShowQuad) {
		if (runlevel > 0) {
			/*printQuad(q);*/
		}
	}
}

QuadSP dupQuad(QuadSP q)
{
	QuadSP r;
	NEWQUAD(r);
	r->op = q->op;
	r->r = q->r;
	r->s = q->s;
	r->d = q->d;
	r->prev = NULL;
	r->next = NULL;
	return r;
}

void printAllQuads(QuadSP q)
{
	for (; q != NULL; q = q->next) {
		printQuad(q);
	}
}

void printAllQuad()
{
	printAllQuads(qhead);
}

void printQuad(QuadSP q)
{
	switch (q->op) {
	case ADD_op:
		NEED3(r,s,d);
		fprintf(code, "\tADD\t%s, %s, %s\n",
			q->r->name, q->s->name, q->d->name);
		break;
	case SUB_op:
		NEED3(r,s,d);
		fprintf(code, "\tSUB\t%s, %s, %s\n",
			q->r->name, q->s->name, q->d->name);
		break;
	case MUL_op:
		NEED3(r,s,d);
		fprintf(code, "\tMUL\t%s, %s, %s\n",
			q->r->name, q->s->name, q->d->name);
		break;
	case DIV_op:
		NEED3(r,s,d);
		fprintf(code, "\tDIV\t%s, %s, %s\n",
			q->r->name, q->s->name, q->d->name);
		break;
	case INC_op:
		NEED(d);
		fprintf(code, "\tINC\t-, -, %s\n", q->d->name);
		break;
	case DEC_op:
		NEED(d);
		fprintf(code, "\tDEC\t-, -, %s\n", q->d->name);
		break;
	case NEG_op:
		NEED2(r, d);
		fprintf(code, "\tNEG\t%s, -, %s\n", 
			q->r->name, q->d->name);
		break;
	case LOAD_op:
		NEED3(r,s,d);
		fprintf(code, "\tLOAD\t%s, %s, %s\n",
			q->r->name, q->s->name, q->d->name);
		break;
	case ASS_op:
		NEED2(r,d);
		fprintf(code, "\tASS\t%s, -, %s\n",
			q->r->name, q->d->name);
		break;
	case AARR_op:
		NEED3(r,s,d);
		fprintf(code, "\tAARR\t%s, %s, %s\n",
			q->r->name, q->s->name, q->d->name);
		break;
	case EQU_op:
		NEED3(r,s,d);
		fprintf(code, "\tEQU\t%s, %s, %s\n",
			q->r->name, q->s->name, q->d->label);
		break;
	case NEQ_op:
		NEED3(r,s,d);
		fprintf(code, "\tNEQ\t%s, %s, %s\n",
			q->r->name, q->s->name, q->d->label);
		break;
	case GTT_op:
		NEED3(r,s,d);
		fprintf(code, "\tGTT\t%s, %s, %s\n",
			q->r->name, q->s->name, q->d->label);
		break;
	case GEQ_op:
		NEED3(r,s,d);
		fprintf(code, "\tGEQ\t%s, %s, %s\n",
			q->r->name, q->s->name, q->d->label);
		break;
	case LST_op:
		NEED3(r,s,d);
		fprintf(code, "\tLST\t%s, %s, %s\n",
			q->r->name, q->s->name, q->d->label);
		break;
	case LEQ_op:
		NEED3(r,s,d);
		fprintf(code, "\tLEQ\t%s, %s, %s\n",
			q->r->name, q->s->name, q->d->label);
		break;
	case JMP_op:
		NEED(d);
		fprintf(code, "\tJMP\t-, -, %s\n", q->d->label);
		break;
	case PUSH_op:
		NEED(d);
		fprintf(code, "\tPUSH\t-, -, %s\n", q->d->name);
		break;
	case PUSHA_op:
		NEED(d);
		if (q->s == NULL) {
			fprintf(code, "\tPUSHA\t-, -, *%s\n", q->d->name);
		} else {
			fprintf(code, "\tPUSHA\t-, %s, *%s\n",
				q->s->name, q->d->name);			
		}
		break;
	case POP_op:
		NEED(d);
		fprintf(code, "\tPOP\t-, -, %s\n", q->d->name);
		break;
	case CALL_op:
		NEED(r);
		if (q->d != NULL) {
			fprintf(code, "\tCALL\t%s, -, %s\n",
				q->r->name, q->d->name);
		} else {
			fprintf(code, "\tCALL\t%s, -, -\n", q->r->name);
		}
		break;
	case SRET_op:
		NEED2(r,d);
		fprintf(code, "\tSRET\t%s, -, %s\n",
			q->r->name, q->d->name);
		break;
	case ENTER_op:
		NEED(d);
		fprintf(code, "%s:\n", q->d->name);
		break;
	case FIN_op:
		fprintf(code, "\tFIN\t-, -, -\n");
		break;
	case READ_op:
		NEED(d);
		fprintf(code, "\tREAD\t-, -, %s\n", q->d->name);
		break;
	case READC_op:
		NEED(d);
		fprintf(code, "\tREADC\t-, -, %s\n", q->d->name);
		break;
	case WRS_op:
		NEED(d);
		fprintf(code, "\tWRS\t-, -, %s\n", q->d->label);
		break;
	case WRI_op:
		NEED(d);
		fprintf(code, "\tWRI\t-, -, %s\n", q->d->label);
		break;
	case WRC_op:
		NEED(d);
		fprintf(code, "\tWRC\t-, -, %s\n", q->d->label);
		break;
	case LABEL_op:
		NEED(d);
		fprintf(code, "%s:\n", q->d->label);
		break;
	default:
		fprintf(errlist, "QUAD BUG:179\n");
	}
}
