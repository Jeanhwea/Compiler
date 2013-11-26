/**
 * File: quad.c
 * Date: Nov 18, 2013
 * Author: Jeanhwea
 */
#include "global.h"
#include "parse.h"
#include "symtab.h"
#include "quad.h"

QuadSP qlst = NULL;
QuadSP qtail = NULL;

static void printQuad(QuadSP);

void emit(QuadSP q)
{
	if (qtail == NULL) {
		q->prev = qtail;
		q->next = NULL;
		qlst = qtail = q;
	} else {
		q->prev = qtail;
		q->next = NULL;
		qtail->next = q;
		qtail = q;
	}
	if (ShowQuad) {
		printQuad(q);
	}
}

void printAllQuad()
{
	QuadSP q = qlst;
	for (; q != NULL; q = q->next) {
		printQuad(q);
	}
}

void printQuad(QuadSP q)
{
	switch (q->op) {
	case ADD_op:
		NEED3(r,s,d);
		fprintf(code, "\tADD\t%s, %s, %s\n",
			q->r->label, q->s->label, q->d->label);
		break;
	case SUB_op:
		NEED3(r,s,d);
		fprintf(code, "\tSUB\t%s, %s, %s\n",
			q->r->label, q->s->label, q->d->label);
		break;
	case MUL_op:
		NEED3(r,s,d);
		fprintf(code, "\tMUL\t%s, %s, %s\n",
			q->r->label, q->s->label, q->d->label);
		break;
	case DIV_op:
		NEED3(r,s,d);
		fprintf(code, "\tDIV\t%s, %s, %s\n",
			q->r->label, q->s->label, q->d->label);
		break;
	case INC_op:
		NEED(d);
		fprintf(code, "\tINC\t-, -, %s\n", q->d->label);
		break;
	case DEC_op:
		NEED(d);
		fprintf(code, "\tDEC\t-, -, %s\n", q->d->label);
		break;
	case NEG_op:
		NEED(d);
		fprintf(code, "\tNEG\t-, -, %s\n", q->d->label);
		break;
	case LOAD_op:
		NEED3(r,s,d);
		fprintf(code, "\tLOAD\t%s, %s, %s\n",
			q->r->label, q->s->label, q->d->label);
		break;
	case ASS_op:
		NEED2(r,d);
		fprintf(code, "\tASS\t%s, -, %s\n",
			q->r->label, q->d->label);
		break;
	case AARR_op:
		NEED3(r,s,d);
		fprintf(code, "\tAARR\t%s, %s, %s\n",
			q->r->label, q->s->label, q->d->label);
		break;
	case EQU_op:
		NEED3(r,s,d);
		fprintf(code, "\tEQU\t%s, %s, %s\n",
			q->r->label, q->s->label, q->d->label);
		break;
	case NEQ_op:
		NEED3(r,s,d);
		fprintf(code, "\tNEQ\t%s, %s, %s\n",
			q->r->label, q->s->label, q->d->label);
		break;
	case GTT_op:
		NEED3(r,s,d);
		fprintf(code, "\tGTT\t%s, %s, %s\n",
			q->r->label, q->s->label, q->d->label);
		break;
	case GEQ_op:
		NEED3(r,s,d);
		fprintf(code, "\tGEQ\t%s, %s, %s\n",
			q->r->label, q->s->label, q->d->label);
		break;
	case LST_op:
		NEED3(r,s,d);
		fprintf(code, "\tLST\t%s, %s, %s\n",
			q->r->label, q->s->label, q->d->label);
		break;
	case LEQ_op:
		NEED3(r,s,d);
		fprintf(code, "\tLEQ\t%s, %s, %s\n",
			q->r->label, q->s->label, q->d->label);
		break;
	case JMP_op:
		NEED(d);
		fprintf(code, "\tJMP\t-, -, %s\n", q->d->label);
		break;
	case PUSH_op:
		NEED(d);
		fprintf(code, "\tPUSH\t-, -, %s\n", q->d->label);
		break;
	case PUSHA_op:
		NEED(d);
		fprintf(code, "\tPUSHA\t-, -, *%s\n", q->d->label);
		break;
	case POP_op:
		NEED(d);
		fprintf(code, "\tPOP\t-, -, %s\n", q->d->label);
		break;
	case CALL_op:
		NEED(r);
		if (q->d != NULL) {
			fprintf(code, "\tCALL\t%s, -, %s\n",
				q->r->label, q->d->label);
		} else {
			fprintf(code, "\tCALL\t%s, -, -\n", q->r->label);
		}
		break;
	case SRET_op:
		NEED2(r,d);
		fprintf(code, "\tSRET\t%s, -, %s\n",
			q->r->label, q->d->label);
		break;
	case ENTER_op:
		NEED(d);
		fprintf(code, "%s:\n", q->d->label);
		break;
	case FIN_op:
		fprintf(code, "\tFIN\t-, -, -\n");
		break;
	case READ_op:
		NEED(d);
		fprintf(code, "\tREAD\t-, -, %s\n", q->d->label);
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

