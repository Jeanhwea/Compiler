/**
 * File: bblock.c
 * Date: Dec 10, 2013
 * Author: Jeanhwea
 */
 
#include "global.h"
#include "parse.h"
#include "symtab.h"
#include "quad.h"
#include "elf.h"
#include "dag.h"
#include "util.h"
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
			if (p->prev !=NULL && BRANCE(p->prev)) {
				leader = p;
				return p;
			} else {
				leader = p->next;
				return p->next;
			}
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
	p->pres = NULL;
	p->posts = NULL;
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
	BBListSP pre, post;
	if (bbtail == NULL) {
		// deal normal precursors and postcursors
		NEWBBLIST(pre);
		NEWBBLIST(post);
		pre->bbp = NULL;
		pre->next = NULL;
		post->bbp = NULL;
		post->next = NULL;
		b->pres = pre;
		b->posts = post;

		NEWBBLIST(bl);
		bl->bbp = b;
		bl->next = NULL;
		bblst = bbtail = bl;
	} else {
		// deal normal precursors and postcursors
		NEWBBLIST(pre);
		NEWBBLIST(post);
		if (bbtail->bbp->scope == b->scope) 
			pre->bbp = bbtail->bbp;
		pre->next = NULL;
		post->bbp = NULL;
		post->next = NULL;
		if (bbtail->bbp->scope == b->scope) 
			bbtail->bbp->posts->bbp = b;
		b->pres = pre;
		b->posts = post;

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
	BBListSP q;
	fprintf(code, "\nBBLOCK_ID = %d; SCOPE = %s\n", 
		b->id, b->scope->d->name);
	fprintf(code, "PRE BBLOCK = ");
	for (q = b->pres; q != NULL; q = q->next) {
		if (q->bbp)
			fprintf(code, "%d ", q->bbp->id);
	}
	fprintf(code, "\n");
	fprintf(code, "POST BBLOCK = ");
	for (q = b->posts; q != NULL; q = q->next) {
		if (q->bbp)
			fprintf(code, "%d ", q->bbp->id);
	}
	fprintf(code, "\n");
	
	fprintf(code, "use -> ");
	printBitsmap(b->use);
	fprintf(code, "def -> ");
	printBitsmap(b->def);
	fprintf(code, "in  -> ");
	printBitsmap(b->in);
	fprintf(code, "out -> ");
	printBitsmap(b->out);
	// fprintf(code, "---------------------------------------");
	fprintf(code, "-------------------------------------\n");
	for (p = b->first; p != NULL; p = p->next) {
		printQuad(p);
		if (p == b->last) break;
	}
	// fprintf(code, "---------------------------------------");
	fprintf(code, "-------------------------------------\n");
}

void _printBblock(BBSP b)
{
	QuadSP p;
	BBListSP q;
	fprintf(code, "\nBBLOCK_ID = %d; SCOPE = %s\n", 
		b->id, b->scope->d->name);
	fprintf(code, "PRE BBLOCK = ");
	for (q = b->pres; q != NULL; q = q->next) {
		if (q->bbp)
			fprintf(code, "%d ", q->bbp->id);
	}
	fprintf(code, "\n");
	fprintf(code, "POST BBLOCK = ");
	for (q = b->posts; q != NULL; q = q->next) {
		if (q->bbp)
			fprintf(code, "%d ", q->bbp->id);
	}
	fprintf(code, "\n");
	
	fprintf(code, "use -> ");
	printBitsmap(b->use);
	fprintf(code, "def -> ");
	printBitsmap(b->def);
	fprintf(code, "in  -> ");
	printBitsmap(b->in);
	fprintf(code, "out -> ");
	printBitsmap(b->out);
	// fprintf(code, "---------------------------------------");
	fprintf(code, "-------------------------------------\n");
	for (p = b->qhead; p != NULL; p = p->next) {
		printQuad(p);
	}
	// fprintf(code, "---------------------------------------");
	fprintf(code, "-------------------------------------\n");
}

void printAllBblock()
{
	BBListSP p;
	for (p = bblst; p != NULL; p = p->next) {
		printBblock(p->bbp);
	}
}

void _printAllBblock()
{
	BBListSP p;
	for (p = bblst; p != NULL; p = p->next) {
		_printBblock(p->bbp);
	}
}

void get_quad(BBSP b)
{
	QuadSP h, t;
	// printAllDN();
	// printAllNT();
	make_iter();
	dag2quad();
	// printf("((((((000after dag2quad000))))))\n");
	// printAllDN();
	// printAllNT();
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

void elf_for_block(BBSP b)
{
	QuadSP q;
	for (q = b->qhead; q != NULL; q = q->next) {
		cgen(q);
		if (q == b->qtail)
			break;
	}
}

void make_dag_for_bblock(BBSP b)
{
	QuadSP q, tmp_q;
	initDag();
	for (q = b->first; q != NULL; q = q->next) {
		switch (q->op) {
		case ADD_op: case SUB_op:
		case MUL_op: case DIV_op:
		case NEG_op:
		case LOAD_op:
			addQuad(q);
			break;
		case ASS_op:
			if (q->r->obj == Tmp_Obj_t) {
				addQuad(q);
			} else {
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
			}
			break;
		case EQU_op: case NEQ_op: case GTT_op:
		case GEQ_op: case LST_op: case LEQ_op:
		case INC_op: case DEC_op:
		case JMP_op:
		case READ_op:
		case READC_op:
		case WRS_op: case WRI_op: case WRC_op:
		case LABEL_op:
		case CALL_op: case PUSHA_op: 
		case PUSH_op:
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


// link fgraph here to ........
BBListSP search_block_for_brance(SymTabESP label_search)
{
	BBListSP r;
	QuadSP q;
	for (r = bblst; r != NULL; r = r->next) {
		for (q = r->bbp->qhead; q != NULL; q = q->next) {
			if (LABEL(q) && q->d == label_search) 
				return r;
		}
	}
	return NULL;
}

void add_bblist(BBListSP des, BBListSP src)
{
	BBListSP b;
	for (b = des; b != NULL && b->next != NULL; b = b->next)
		;
	if (b == NULL) {
		src->next = NULL;
		b = src;
	} else {
		src->next = NULL;
		b->next = src;
	}

}

void link_bblock(void)
{
	BBListSP bl, brance_des, pre, post;
	QuadSP q;
	for (bl = bblst; bl != NULL; bl = bl->next) {
		for (q = bl->bbp->qhead; q != NULL && q->next != NULL; q = q->next) 
			;
		if (q != NULL && BRANCE(q)) {
		// find some postcursor for brance in this bblock
			brance_des = search_block_for_brance(q->d);
			assert(brance_des != NULL);

			NEWBBLIST(pre);
			NEWBBLIST(post);
			pre->next = NULL;
			pre->bbp = bl->bbp;
			post->next = NULL;
			post->bbp = brance_des->bbp;
			add_bblist(brance_des->bbp->pres, pre);
			add_bblist(bl->bbp->posts, post);
		}
	}
}
