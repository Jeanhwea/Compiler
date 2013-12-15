/**
 * File: dag.h
 * Date: Dec 10, 2013
 * Author: Jeanhwea
 */
#ifndef DAG_H

#define DAG_H

// dag node entry pointer
typedef struct _DNodeES *DNodeESP;
// dag node list pointer
typedef struct _DNListS *DNListSP;
// node table entry pointer
typedef struct _NTabES *NTabESP;
// node table list pointer
typedef struct _NTListS *NTListSP;

typedef struct _DNodeES {
	int id;
	union {
		Quad_t op;
		SymTabESP ste;
	} attr;
	DNodeESP left;
	DNodeESP right;
	BOOL visit;
	NTListSP iter;
} DNodeES;

typedef struct _DNListS {
	DNodeESP dne;
	DNListSP next;
} DNListS;

typedef struct _NTabES {
	SymTabESP ste;
	DNodeESP dne;
} NTabES;

typedef struct _NTListS {
	NTabESP nte;
	NTListSP next;
} NTListS;

void addQuad(QuadSP q);
void printAllNT();
void printAllDN();
void initDag();
QuadSP get_qdhead();
QuadSP get_qdtail();
void make_iter(void);
void destory_DNL(void);
void destory_NTL(void);
void dag2quad();

#define NEWENTRY(s, v) \
do { \
	v = (s##P) malloc(sizeof(s));				\
	if (v == NULL) {					\
		fprintf(errlist, "OUTOFMEM: dag node table\n");	\
		assert(0);					\
	}							\
} while(0)

#define DAGABLE(v) (\
(v->op==ADD_op)||(v->op==SUB_op)||(v->op==MUL_op)||(v->op==DIV_op)\
||(v->op==NEG_op)||(v->op==ASS_op)\
||(v->op==EQU_op)||(v->op==NEQ_op)||(v->op==GTT_op)\
||(v->op==GEQ_op)||(v->op==LST_op)||(v->op==LEQ_op)\
||(v->op==WRI_op)||(v->op==WRC_op)||(v->op==WRS_op)\
||(v->op==JMP_op)\
||(v->op==LABEL_op)\
)

#endif /* end of include guard: DAG_H */
