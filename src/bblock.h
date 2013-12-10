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
	BBListSP in;
	BBListSP out;
	QuadSP quads;
} BBS;

#define NEWBBLIST(v) \
do { \
	v = (BBListSP) malloc(sizeof(BBListS));			\
	if (v == NULL) {					\
		fprintf(errlist, "OUTOFMEM: on build bblock\n");\
		exit(1);					\
	}							\
	v->bbp = NULL;						\
	v->next = NULL;						\
} while(0)

#define NEWBB(v) \
do { \
	v = (BBSP) malloc(sizeof(BBS));				\
	if (v == NULL) {					\
		fprintf(errlist, "OUTOFMEM: on build bblock\n");\
		exit(1);					\
	}							\
	v->in = NULL;						\
	v->out = NULL;						\
	v->quads = NULL;					\
} while(0)

#endif /* end of include guard: BBLOCK_H */
