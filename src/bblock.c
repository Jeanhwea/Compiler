/**
 * File: bblock.c
 * Date: Dec 10, 2013
 * Author: Jeanhwea
 */
 
#include "global.h"
#include "parse.h"
#include "symtab.h"
#include "quad.h"
#include "dag.h"
#include "bblock.h"

// qhead => quadruples list after semantic analysis
// see qaud.c
static QuadSP leader = NULL ;

// header pointer to the function 
// the current block blogs to
static QuadSP header = NULL; 

static int bblock_id = 0;

// point to basic block head
BBListSP bblst = NULL;
// point to basic block list after 
// basic block partition
BBListSP bbtail = NULL;
BOOL quad_end_flag = FALSE;

void initLeader(void)
{
	leader = qhead;
	header = qhead;
}

static QuadSP nextleader(void)
{
	QuadSP p;
	// jump continues labels
	// the leader is a label, or we will make mistakes
	for (   p = leader->next; 
		p != NULL && LABEL(leader) && LABEL(p); 
		p = p->next ) 
		;
	for (; p != NULL; p = p->next) {
		if (PFHEAD(p)) {
			header = p;
			leader = p;
			return p;
		} else if (PFHEAD(leader)) {
			leader = p;
			return p;
		} else if (FINISH(p)) {
			leader = p;
			return p;
		} else if (LABEL(p)) {
			leader = p;
			return p;
		} else if (BRANCE(p)) {
			leader = p->next;
			return p->next;
		}
	}
	leader = NULL;
	quad_end_flag = TRUE;
	return NULL;
}

BBSP newBblock(void)
{
	BBSP p;
	NEWBB(p);
	p->id = ++bblock_id;
	p->qhead = NULL;
	p->qtail = NULL;
	p->scope = header;
	p->first = leader;
	nextleader();
	if (leader != NULL) {
		p->last = leader->prev;
	} else {
		p->last = NULL;
	}
	return p;
}

void addBblock(BBSP b)
{
	BBListSP bl;
	// BBListSP in, out;
	if (bbtail == NULL) {
		NEWBBLIST(bl);
		bl->bbp = b;
		bl->next = NULL;
		bblst = bbtail = bl;
	} else {
		NEWBBLIST(bl);
		bl->bbp = b;
		bl->next = NULL;
		bbtail->next = bl;
		bbtail = bl;
	}
}

BOOL quad_end(void)
{
	return quad_end_flag;
}

void printBblock(BBSP b)
{
	QuadSP p;
	// BBListSP q;
	fprintf(code, "\nBBLOCK_ID = %d; SCOPE = %s\n", 
		b->id, b->scope->d->name);
	// fprintf(code, "INS = ");
	// for (q = b->ins; q != NULL; q = q->next) {
	// 	fprintf(code, "%d ", q->bbp->id);
	// }
	// fprintf(code, "\n");
	// fprintf(code, "OUTS = ");
	// for (q = b->outs; q != NULL; q = q->next) {
	// 	fprintf(code, "%d ", q->bbp->id);
	// }
	// fprintf(code, "\n");
	fprintf(code, "---------------------------------------");
	fprintf(code, "-------------------------------------\n");
	for (p = b->first; p != NULL; p = p->next) {
		printQuad(p);
		if (p == b->last) break;
	}
	fprintf(code, "---------------------------------------");
	fprintf(code, "-------------------------------------\n");
}

void printAllBblock()
{
	BBListSP p;
	for (p = bblst; p != NULL; p = p->next) {
		printBblock(p->bbp);
	}
}

void get_quad(BBSP b)
{
	QuadSP h, t;
	printAllDN();
	printAllNT();
	make_iter();
	dag2quad();
	h = get_qdhead();
	t = get_qdtail();
	if (h != NULL) {
		if (b->qhead == NULL) {
			h->prev = b->qhead;
			t->next = NULL;
			b->qhead = h;
			b->qtail = t;
		} else {
			h->prev = b->qtail;
			t->next = NULL;
			b->qtail->next = h;
			b->qtail = t;
		}
	}
	destory_DNL();
	destory_NTL();
	initDag();
}

void make_dag_for_bblock(BBSP b)
{
	QuadSP q, tmp_q;
	initDag();
	for (q = b->first; q != NULL; q = q->next) {
		switch (q->op) {
		case ADD_op: case SUB_op:
		case MUL_op: case DIV_op:
		case NEG_op: case ASS_op:
			addQuad(q);
			break;
		case EQU_op: case NEQ_op: case GTT_op:
		case GEQ_op: case LST_op: case LEQ_op:
		case JMP_op:
		case READ_op:
		case READC_op:
		case WRS_op: case WRI_op: case WRC_op:
		case LABEL_op:
			get_quad(b);
			tmp_q = dupQuad(q);
			assert(tmp_q);
			if (b->qhead == NULL) {
				tmp_q->next = NULL;
				tmp_q->prev = b->qtail;
				b->qhead = b->qtail = tmp_q;
			} else {
				tmp_q->next = NULL;
				tmp_q->prev = b->qtail;
				b->qtail->next = tmp_q;
				b->qtail = tmp_q;
			}
			break;
		default:
			fprintf(errlist, "BBLOCK BUG:179\n");
			assert(0);
		}
		if (q == b->last) break;
	// printAllQuads(b->qhead);
	}
	get_quad(b);
}

void copy_quad_for_bblock(BBSP b)
{
	QuadSP q, tmp_q;
	for (q = b->first; q != NULL; q = q->next) {
		tmp_q = dupQuad(q);
		assert(tmp_q);
		if (b->qhead == NULL) {
			tmp_q->next = NULL;
			tmp_q->prev = b->qtail;
			b->qhead = b->qtail = tmp_q;
		} else {
			tmp_q->next = NULL;
			tmp_q->prev = b->qtail;
			b->qtail->next = tmp_q;
			b->qtail = tmp_q;
		}
		if (q == b->last) break;
	}
}