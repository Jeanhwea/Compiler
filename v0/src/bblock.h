/**
 * File: bblock.h
 * Date: Dec 10, 2013
 * Author: Jeanhwea
 */
#ifndef BBLOCK_H

#define BBLOCK_H

typedef struct _BBS *BBSP;
typedef struct _BBListS *BBListSP;

typedef struct _BBListS {
	BBSP bbp;
	BBListSP next;
} BBListS;

typedef struct _BBS {
	int id;
	QuadSP qhead;
	QuadSP qtail;
	QuadSP scope;
	QuadSP first; // first position of basic block
	QuadSP last;  // last position of basic block

	BBListSP pres;
	BBListSP posts;

	// 16-bits for a int type
	// 8 * 16 = 128 symbol table entrys
	int use[8];
	int def[8];

	int in_old[8];
	int out_old[8];
	int in[8];
	int out[8];
} BBS;

#define NEWBBLIST(v) \
do { \
	v = (BBListSP) malloc(sizeof(BBListS));			\
	if (v == NULL) {					\
		fprintf(errlist, "OUTOFMEM: on build bblock\n");\
		assert(0);					\
	}							\
	v->bbp = NULL;						\
	v->next = NULL;						\
} while(0)

#define NEWBB(v) \
do { \
	v = (BBSP) malloc(sizeof(BBS));				\
	if (v == NULL) {					\
		fprintf(errlist, "OUTOFMEM: on build bblock\n");\
		assert(0);					\
	}							\
} while(0)

#define PFHEAD(v) (v->op==ENTER_op)
#define FINISH(v) (v->op==FIN_op)
#define LABEL(v) (v->op==LABEL_op)
#define BRANCE(v) (\
(v->op==EQU_op)||(v->op==NEQ_op)||(v->op==GTT_op)\
||(v->op==GEQ_op)||(v->op==LST_op)||(v->op==LEQ_op)\
||(v->op==JMP_op)\
)

extern BBListSP bblst;

void initLeader(void);
BBSP newBblock(void);
void addBblock(BBSP);
BOOL quad_end(void);

void printBblock(BBSP);
void printAllBblock();
void _printAllBblock();

void elf_for_block(BBSP);

void make_dag_for_bblock(BBSP b);
void copy_quad_for_bblock(BBSP b);

void link_bblock(void);

#endif /* end of include guard: BBLOCK_H */
