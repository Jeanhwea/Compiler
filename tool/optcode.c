#include "global.h"
#include "anlys.h"
#include "debug.h"
#include "conv.h"
#include "ir.h"
#include "limits.h"
#include "optim.h"
#include "symtab.h"
#include "util.h"
#include "syntax.h"
#include "gen.h"
#include <stdio.h>
#include <string.h>

bool opt_dag = FALSE;
bool opt_lva = FALSE;

void initopt(int argc, char *argv[])
{
	int i;
	for (i = 1; i < argc; ++i) {
		if (!strcmp("-dag", argv[i])) {
			opt_dag = TRUE;
		}
		if (!strcmp("-lva", argv[i])) {
			opt_lva = TRUE;
		}
	}
}

char *oprepr[32] = {
	[0] = "+",     [1] = "-",    [2] = "*",	    [3] = "/",	   [4] = "++",
	[5] = "--",    [6] = "NEG",  [7] = "LOAD",  [8] = ":=",	   [9] = "[]=",
	[10] = "=",    [11] = "<>",  [12] = ">",    [13] = ">=",   [14] = "<",
	[15] = "<=",   [16] = "JMP", [17] = "PUSH", [18] = "PADR", [19] = "POP",
	[20] = "CALL", [21] = "ENT", [22] = "FIN",  [23] = "RDI",  [24] = "RDC",
	[25] = "WRS",  [26] = "WRI", [27] = "WRC",  [28] = "LAB",
};

char *symcate[12] = {
	[0] = "NOP", [1] = "CONST", [2] = "VAR",   [3] = "PROC",
	[4] = "FUN", [5] = "ARRAY", [6] = "BYVAL", [7] = "BYREF",
	[8] = "TMP", [9] = "LABEL", [10] = "NUM",  [11] = "STR",
};

void fmtinst2(inst_t *x)
{
	char buf[MAXSTRBUF];
	sprintf(buf, "  #%03d: %s", x->xid, opcode[x->op]);
	if (x->d) {
		appendf(buf, "\td=%s", x->d->label);
	}
	if (x->r) {
		appendf(buf, "\tr=%s", x->r->label);
	}
	if (x->s) {
		appendf(buf, "\ts=%s", x->s->label);
	}
	msg("%s\n", buf);
}

void dumpent(syment_t *e)
{
	msg("label=%s type=%d cate=%s name=%s off=%d stab=%d depth=%d initval=%d arrlen=%d str=%s\n",
	    e->label, e->type, symcate[e->cate], e->name, e->off, e->stab->tid,
	    e->stab->depth, e->initval, e->arrlen, e->str);
}

void dumpdag(bb_t *bb)
{
	char *ind = "  ";
	char outname[128];
	sprintf(outname, "dagB%d.dot", bb->bid);

	FILE *fd = fopen(outname, "w");
	if (fd == NULL) {
		panic("FAIL_TO_OPEN_FILE");
	}

	dgraph_t *g;
	g = bb->dag;

	fprintf(fd, "digraph dag {\n");

	int i;
	dnode_t *v = NULL;
	for (i = 0; i < g->nodecnt; ++i) {
		v = g->nodes[i];

		char vars[256] = "";
		dnvar_t *p;
		for (p = v->reflist; p; p = p->next) {
			if (strlen(vars) > 0) {
				appendf(vars, ", ");
			}
			if (p->sym->cate == TMP_OBJ) {
				appendf(vars, "T%d", p->sym->sid);
			} else {
				appendf(vars, "%s", p->sym->name);
			}
		}

		switch (v->cate) {
		case OPERNODE:
			fprintf(fd,
				"%sn%03d [shape=oval label=\"#%d [%s]\\n%s\"];\n",
				ind, v->nid, v->nid, oprepr[v->op], vars);
			if (v->lhs) {
				fprintf(fd, "%sn%03d -> n%03d;\n", ind, v->nid,
					v->lhs->nid);
			}
			if (v->rhs) {
				fprintf(fd, "%sn%03d -> n%03d;\n", ind, v->nid,
					v->rhs->nid);
			}
			break;
		case SYMBOLNODE:
			fprintf(fd,
				"%sn%03d [shape=box  label=\"#%d [%s0]\\n%s\"];\n",
				ind, v->nid, v->nid, v->syment->name, vars);
			break;
		}
	}

	fprintf(fd, "}\n");
	fclose(fd);

	char cmd[MAXSTRBUF];
	sprintf(cmd, "dot -Tpdf %s -o %s.pdf", outname, outname);
	system(cmd);
}

void dumpinst2(bb_t *bb)
{
	int i;
	if (bb->inst2cnt <= 0) {
		return;
	}

	msg("   => insts2 after DAG\n");
	for (i = 0; i < bb->inst2cnt; i++) {
		fmtinst2(bb->insts2[i]);
	}
}

void dumpinst3(bb_t *bb)
{
	int i;
	if (bb->inst3cnt <= 0) {
		return;
	}

	msg("   => insts3 after LVA\n");
	for (i = 0; i < bb->inst3cnt; i++) {
		fmtinst2(bb->insts3[i]);
	}
}

int main(int argc, char *argv[])
{
	echo = 0;
	init(argc, argv);
	initopt(argc, argv);
	parse();
	analysis();
	genir();
	msg("\n");

	msg("DUMP SYMBOLS:\n");
	int i;
	for (i = 1; i <= sidcnt; ++i) {
		syment_t *e = syments[i];
		dumpent(e);
	}
	msg("\n");

	msg("DUMP INTERMEDIATE REPRESENTATION:\n");

	optim();

	fun_t *fun;
	for (fun = mod.fhead; fun; fun = fun->next) {
		msg("func(nspace=%s)\n", fun->scope->nspace);
		bb_t *bb;
		for (bb = fun->bhead; bb; bb = bb->next) {
			char bbinfo[MAXSTRBUF];
			sprintf(bbinfo, "B%d", bb->bid);

			int i;
			appendf(bbinfo, " pred=");
			for (i = 0; i < MAXBBLINK; ++i) {
				if (!bb->pred[i]) {
					break;
				}
				if (i > 0) {
					appendf(bbinfo, ",");
				}
				appendf(bbinfo, "B%d", bb->pred[i]->bid);
			}

			appendf(bbinfo, " succ=");
			for (i = 0; i < MAXBBLINK; ++i) {
				if (!bb->succ[i]) {
					break;
				}
				if (i > 0) {
					appendf(bbinfo, ",");
				}
				appendf(bbinfo, "B%d", bb->succ[i]->bid);
			}

			msg(" block(%s)\n", bbinfo);
			for (i = 0; i < bb->total; i++) {
				fmtinst2(bb->insts[i]);
			}

			if (opt_dag) {
				dumpinst2(bb);
			}

			if (opt_lva) {
				dumpinst3(bb);
			}
		}
	}
	msg("\n");

	for (fun = mod.fhead; fun; fun = fun->next) {
		bb_t *bb;
		for (bb = fun->bhead; bb; bb = bb->next) {
			if (!bb->dag) {
				continue;
			}
			if (opt_dag) {
				dumpdag(bb);
			}
		}
	}
	msg("\n");

	return 0;
}
