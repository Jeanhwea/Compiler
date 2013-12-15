/**
 * File: dag.c
 * Date: Dec 10, 2013
 * Author: Jeanhwea
 */

#include "global.h"
#include "parse.h"
#include "symtab.h"
#include "quad.h"
#include "dag.h"
#include "bblock.h"
#include "fgraph.h"

NTListSP nthead = NULL;
NTListSP nttail = NULL;
DNListSP dnhead = NULL;
DNListSP dntail = NULL;

QuadSP qdhead = NULL;
QuadSP qdtail = NULL;

int dag_node_id = 0;

QuadSP get_qdhead()
{
	return qdhead;
}

QuadSP get_qdtail()
{
	return qdtail;
}

static inline DNodeESP newDNodeE(void)
{
	DNodeESP dne;
	NEWENTRY(DNodeES, dne);
	dne->id = ++dag_node_id;
	// dne->attr.op or dne->attr.ste
	// are left for other function todo
	// when construct the dag node
	dne->left = NULL;
	dne->right = NULL;
	dne->visit = FALSE;
	dne->iter = NULL;
	return dne;
}

static inline DNListSP newDNList(void)
{
	DNListSP dnl;
	NEWENTRY(DNListS, dnl);
	dnl->dne = NULL;
	dnl->next = NULL;
	return dnl;
}

static inline NTabESP newNTabE(void)
{
	NTabESP nte;
	NEWENTRY(NTabES, nte);
	nte->ste = NULL;
	nte->dne = NULL;
	return nte;
}

static inline NTListSP newNTList(void)
{
	NTListSP ntl;
	NEWENTRY(NTListS, ntl);
	ntl->nte = NULL;
	ntl->next = NULL;
	return ntl;
}

void initDag()
{
	nthead = NULL;
	nttail = NULL;
	dnhead = NULL;
	dntail = NULL;
	qdhead = NULL;
	qdtail = NULL;
	dag_node_id = 0;
}

DNListSP pushDNL(DNodeESP dne)
{
	DNListSP dnl;
	if (dntail == NULL) {
		dnl = newDNList();
		dnl->dne = dne;
		dnl->next = NULL;
		dntail = dnhead = dnl;
	} else {
		dnl = newDNList();
		dnl->dne = dne;
		dnl->next = NULL;
		dntail->next = dnl;
		dntail = dnl;
	}
	return dnl;
}

NTListSP pushNTL(NTabESP nte)
{
	NTListSP ntl;
	if (nttail == NULL) {
		ntl = newNTList();
		ntl->nte = nte;
		ntl->next = NULL;
		nttail = nthead = ntl;
	} else {
		ntl = newNTList();
		ntl->nte = nte;
		ntl->next = NULL;
		nttail->next = ntl;
		nttail = ntl;
	}
	return ntl;
}

QuadSP pushQuad(QuadSP q)
{
	if (qdtail == NULL) {
		q->prev = qdtail;
		q->next = NULL;
		qdhead = qdtail = q;
	} else {
		q->prev = qdtail;
		q->next = NULL;
		qdtail->next = q;
		qdtail = q;
	}
	printQuad(q);
	return q;
}

void push_back_iter(NTabESP nte, DNodeESP dne)
{
	NTListSP p, ntl;
	if (dne->iter == NULL) {
		ntl = newNTList();
		ntl->nte = nte;
		ntl->next = NULL;
		dne->iter = ntl;
		return ;
	}
	for (p = dne->iter; p->next != NULL; p = p->next) 
		;
	ntl = newNTList();
	ntl->nte = nte;
	ntl->next = NULL;
	p->next = ntl;
	return ;
}

void push_front_iter(NTabESP nte, DNodeESP dne)
{
	NTListSP ntl;
	if (dne->iter == NULL) {
		ntl = newNTList();
		ntl->nte = nte;
		ntl->next = NULL;
		dne->iter = ntl;
		return ;
	}
	ntl = newNTList();
	ntl->nte = nte;
	ntl->next = dne->iter;
	dne->iter = ntl;
	return ;
}

void make_iter(void)
{
	NTListSP p;
	for (p = nthead; p != NULL; p = p->next) {
		if (p->nte->ste->obj == Tmp_Obj_t) 
			push_back_iter(p->nte, p->nte->dne);
		else
			push_front_iter(p->nte, p->nte->dne);
	}
}

static void free_DNE_iter_container(DNodeESP d)
{
	NTListSP p, q;
	for (p = d->iter; p != NULL; p = q) {
		q = p->next;
		// free(p->nte); notice this bug
		// all we need to do free
		// the node table entry's container
		free(p);
	}
	d->iter = NULL;
}


void destory_DNL(void)
{
	DNListSP p, q;
	for (p = dnhead; p != NULL; p = q) {
		q = p->next;
		free_DNE_iter_container(p->dne);
		free(p->dne);
		free(p);
	}
	dnhead = NULL;
}

void destory_NTL(void)
{
	NTListSP p, q;
	for (p = nthead; p != NULL; p = q) {
		q = p->next;
		free(p->nte);
		free(p);
	}
	nthead = NULL;
}

DNodeESP lookup_dag(Quad_t op, DNodeESP l, DNodeESP r)
{
	DNListSP p;
	for (p = dnhead; p != NULL; p = p->next) {
		if ((l == p->dne->left) &&
		    (r == p->dne->right) &&
		    (p->dne->attr.op == op) ) {
			return p->dne;
		}
	}
	return NULL;
}

NTabESP lookup_nodetab(SymTabESP key)
{
	NTListSP p;
	for (p = nthead; p != NULL; p = p->next) {
		if (key == p->nte->ste) 
			return p->nte;
	}
	return NULL;
}

void make_dag_for_binary(QuadSP q)
{
	NTabESP  x, y, z;
	DNodeESP i, j, k;
	x = lookup_nodetab(q->r);
	if (x == NULL) {
		i = newDNodeE();
		pushDNL(i);
		i->attr.ste = q->r;
		x = newNTabE();
		pushNTL(x);
		x->ste = q->r;
		x->dne = i;
	} else {
		i = x->dne;
	}
	y = lookup_nodetab(q->s);
	if (y == NULL) {
		j = newDNodeE();
		pushDNL(j);
		j->attr.ste = q->s;
		y = newNTabE();
		pushNTL(y);
		y->ste = q->s;
		y->dne = j;
	} else {
		j = y->dne;
	}
	k = lookup_dag(q->op, i, j);
	if (k == NULL) {
		k = newDNodeE();
		pushDNL(k);
		k->attr.op = q->op;
		k->left = i;
		k->right = j;
	}
	z = lookup_nodetab(q->d);
	if (z == NULL) {
		z = newNTabE();
		pushNTL(z);
		z->ste = q->d;
		z->dne = k;
	} else {
		z->dne = k;
	}
}

void make_dag_for_unary(QuadSP q)
{
	NTabESP  x, z;
	DNodeESP i, k;
	x = lookup_nodetab(q->r);
	if (x == NULL) {
		i = newDNodeE();
		pushDNL(i);
		i->attr.ste = q->r;
		x = newNTabE();
		pushNTL(x);
		x->ste = q->r;
		x->dne = i;
	} else {
		i = x->dne;
	}
	k = lookup_dag(q->op, i, i);
	if (k == NULL) {
		k = newDNodeE();
		pushDNL(k);
		k->attr.op = q->op;
		k->left = i;
		k->right = i;
	}
	z = lookup_nodetab(q->d);
	if (z == NULL) {
		z = newNTabE();
		pushNTL(z);
		z->ste = q->d;
		z->dne = k;
	} else {
		z->dne = k;
	}
}

void make_dag_for_copy(QuadSP q)
{
	NTabESP  x, z;
	DNodeESP i;
	x = lookup_nodetab(q->r);
	if (x == NULL) {
		i = newDNodeE();
		pushDNL(i);
		i->attr.ste = q->r;
		x = newNTabE();
		pushNTL(x);
		x->ste = q->r;
		x->dne = i;
	} else {
		i = x->dne;
	}
	z = lookup_nodetab(q->d);
	if (z == NULL) {
		z = newNTabE();
		pushNTL(z);
		z->ste = q->d;
		z->dne = i;
	} else {
		z->dne = i;
	}
}

void addQuad(QuadSP q)
{
	switch (q->op) {
	case ADD_op: case SUB_op:
	case MUL_op: case DIV_op:
		NEED3(r,s,d);
		make_dag_for_binary(q);
		break;
	case NEG_op:
		NEED2(r,d);
		make_dag_for_unary(q);
		break;
	case ASS_op:
		NEED2(r,d);
		// make_dag_for_unary(q);
		make_dag_for_copy(q);
		break;
	default:
		fprintf(errlist, "DAG BUG:179\n");
		assert(0);
	}
}

static DNodeESP find(void)
{
	DNListSP p;
	for (p = dnhead; p != NULL; p = p->next) {
		if (!p->dne->visit && p->dne->iter &&
			(p->dne->left||p->dne->right))
			return p->dne;
	}
	return NULL;
}

static void _dag2quad(DNodeESP d)
{
	QuadSP q;
	NTListSP it;
	if (d == NULL) return ;
	if (d->visit) return ;
	if (!(d->left||d->right)) return;
	_dag2quad(d->left);
	_dag2quad(d->right);
	d->visit = TRUE;
	assert(d->left->iter);
	assert(d->right->iter);
	switch (d->attr.op) {
	case ADD_op: case SUB_op:
	case MUL_op: case DIV_op:
		NEWQUAD(q);
		q->op = d->attr.op;
		q->r = d->left->iter->nte->ste;
		q->s = d->right->iter->nte->ste;
		q->d = d->iter->nte->ste;
		pushQuad(q);
		break;
	case NEG_op:
		NEWQUAD(q);
		q->op = d->attr.op;
		q->r = d->left->iter->nte->ste;
		q->s = NULL;
		q->d = d->iter->nte->ste;
		pushQuad(q);
		break;
	case ASS_op:
		NEWQUAD(q);
		q->op = d->attr.op;
		q->r = (d->left->iter == NULL) ? 
			d->left->attr.ste:
			d->left->iter->nte->ste;
		q->s = NULL;
		q->d = d->iter->nte->ste;
		pushQuad(q);
		break;
	default:
		assert(0);
	}
	// generate a list assign quadruples
	assert(d->iter);
	for (it = d->iter->next; 
		it != NULL; it = it->next) {
		NEWQUAD(q);
		q->op = ASS_op;
		q->r = d->iter->nte->ste;
		q->s = NULL;
		q->d = it->nte->ste;
		pushQuad(q);
	}
	return ;
}

void dag2quad()
{
	DNodeESP dne;
	for (; (dne = find()) != NULL; ) 
		_dag2quad(dne);
}

void printNTE(NTabESP nte)
{
	fprintf(daglist, "%5s -> Node(%2d)\n", 
		nte->ste->name, nte->dne->id);
}

void printAllNT()
{
	NTListSP p;
	for (p = nthead; p != NULL; p = p->next) {
		printNTE(p->nte);
	}
}

void printDNE(DNodeESP dne)
{
	fprintf(daglist, "Node(%2d), Left(%2d), Right(%2d), Attr(%5s)\n", 
		dne->id, (dne->left)?dne->left->id:0,
		(dne->right)?dne->right->id:0,
		(dne->left||dne->right)?
			quadMap[dne->attr.op]:
			dne->attr.ste->name
		);
}

void printAllDN()
{
	DNListSP p;
	for (p = dnhead; p != NULL; p = p->next) {
		printDNE(p->dne);
	}
}
