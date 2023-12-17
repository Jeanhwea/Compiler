#ifndef _IR_H_
#define _IR_H_
#include "symtab.h"

typedef struct _inst_struct inst_t;

// Instruction Operator Type
typedef enum _inst_op_enum {
	// Arithmetic
	/*  0 */ ADD_OP,
	/*  1 */ SUB_OP,
	/*  2 */ MUL_OP,
	/*  3 */ DIV_OP,
	/*  4 */ INC_OP,
	/*  5 */ DEC_OP,
	/*  6 */ NEG_OP,
	// Save and Store
	/*  7 */ LOAD_OP,
	/*  8 */ ASS_OP,
	/*  9 */ ASA_OP,
	// Conditional Branch
	/* 10 */ EQU_OP,
	/* 11 */ NEQ_OP,
	/* 12 */ GTT_OP,
	/* 13 */ GEQ_OP,
	/* 14 */ LST_OP,
	/* 15 */ LEQ_OP,
	// Unconditional Branch
	/* 16 */ JMP_OP,
	// Stack Management
	/* 17 */ PUSH_OP,
	/* 18 */ PUSHA_OP,
	/* 19 */ POP_OP,
	// Function Management
	/* 20 */ CALL_OP,
	/* 21 */ SRET_OP,
	/* 22 */ ENTER_OP,
	/* 23 */ FIN_OP,
	// I/O Management
	/* 24 */ RDI_OP,
	/* 25 */ RDC_OP,
	/* 26 */ WRS_OP,
	/* 27 */ WRI_OP,
	/* 28 */ WRC_OP,
	// Label Marker
	/* 29 */ LABEL_OP
} op_t;

// Instruction struct
typedef struct _inst_struct {
	int xid;
	op_t op;
	syment_t *r;
	syment_t *s;
	syment_t *d;
	inst_t *prev;
	inst_t *next;
} inst_t;

// Constructor
#define NEWINST(v) INITMEM(inst_t, v)

// hold instructions
extern inst_t *ihead;
extern inst_t *itail;

// emit an instruction
inst_t *emit0();
inst_t *emit1(op_t op, syment_t *d);
inst_t *emit2(op_t op, syment_t *r, syment_t *d);
inst_t *emit3(op_t op, syment_t *r, syment_t *s, syment_t *d);
#endif /* End of _IR_H_ */
