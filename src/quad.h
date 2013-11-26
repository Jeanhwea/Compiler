/**
 * File: quad.h
 * Date: Nov 18, 2013
 * Author: Jeanhwea
 */
#ifndef QUAD_H

#define QUAD_H

typedef struct _QuadS *QuadSP;

typedef enum {
	/* Arith */
	ADD_op, SUB_op, MUL_op, DIV_op,
	/* unary */
	INC_op, DEC_op, NEG_op,
	/* save and store */
	LOAD_op, ASS_op, AARR_op,
	/* conditional branch */
	EQU_op, NEQ_op, GTT_op, GEQ_op,
	LST_op, LEQ_op,
	/* unconditional branch */
	JMP_op,
	/* stack management */
	PUSH_op, PUSHA_op, POP_op,
	/* function management */
	CALL_op, SRET_op, ENTER_op, FIN_op,
	/* I/O management */
	READ_op, WRS_op, WRI_op, WRC_op,
	/* label marker */
	LABEL_op
} Quad_t;

typedef struct _QuadS {
	Quad_t op;
	SymTabESP r;
	SymTabESP s;
	SymTabESP d;
	QuadSP prev;
	QuadSP next;
} QuadS;

#define NEED(a) \
do { \
	if (q->a == NULL) {					\
		fprintf(errlist, "1)NULL POINT IN QUAD\n");	\
		abort();					\
	}							\
} while(0)
#define NEED2(a,b) \
do { \
	if (q->a == NULL || q->b == NULL) {			\
		fprintf(errlist, "2)NULL POINT IN QUAD\n");	\
		abort();					\
	}							\
} while(0)
#define NEED3(a,b,c) \
do { \
	if (q->a == NULL || q->b == NULL || q->c == NULL) {	\
		fprintf(errlist, "3)NULL POINT IN QUAD\n");	\
		abort();					\
	}							\
} while(0)

#define NEWQUAD(v) \
do { \
	v = (QuadSP) malloc(sizeof(QuadS));			\
	if (v == NULL) {					\
		fprintf(errlist, "OUTOFMEM: on build quad\n");	\
		exit(1);					\
	}							\
	v->prev = NULL;						\
	v->next = NULL;						\
} while(0)

extern QuadSP qlst;
void emit(QuadSP);
void printAllQuad();

#endif /* end of include guard: QUAD_H */
