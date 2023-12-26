#include "anlys.h"
#include "debug.h"
#include "global.h"
#include "conv.h"
#include "limits.h"
#include "symtab.h"
#include "util.h"
#include "syntax.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXNODES 1024
#define MAXEDGES 1024

static int nedges = 0;
static node_t *nodes[MAXNODES];
static char label[MAXNODES][MAXSTRLEN];
static int beg[MAXEDGES];
static int end[MAXEDGES];
static char ref[MAXEDGES][MAXSTRLEN];

static char buf[1024];

void visit(node_t *node)
{
	nevernil(node);

	sprintf(buf, "%s", node->name);
	if (node->extra) {
		appendf(buf, " [%s]", node->extra);
	}

	if (node->idp) {
		ident_node_t *idp = node->idp;
		appendf(buf, "\\nname=%s\\nkind=%d", idp->name, idp->kind);
		syment_t *sym = idp->symbol;
		if (sym) {
			appendf(buf, "\\ntype=%d\\ncate=%d\\nlabel=%s",
				sym->type, sym->cate, sym->label);
		}
	}

	nodes[node->id] = node;
	strcopy(label[node->id], buf);
	int i;
	for (i = 0; i < node->total; ++i) {
		node_t *child = node->childs[i];
		beg[nedges] = node->id;
		end[nedges] = child->id;
		strcopy(ref[nedges], node->refs[i]);
		++nedges;
	}

	for (i = 0; i < node->total; ++i) {
		node_t *child = node->childs[i];
		visit(child);
	}
}

void writedot()
{
	char *outname = "viz.dot";
	FILE *fd = fopen(outname, "w");
	fprintf(fd, "digraph viz {\n");
	char *indent = "  ";
	// fprintf(fd, "%srankdir=LR;\n", indent);
	int i;
	for (i = 0; i < MAXNODES; ++i) {
		if (!nodes[i]) {
			continue;
		}
		node_t *n = nodes[i];

		char *shape = "oval";
		if (!strncmp(n->name, "IDENT", 5)) {
			shape = "box";
		}

		fprintf(fd, "%sn%03d[label=\"%d #%d %s\", shape=\"%s\"];\n",
			indent, n->id, n->id, n->nid, label[i], shape);
	}
	for (i = 0; i < nedges; ++i) {
		fprintf(fd, "%sn%03d -> n%03d[label=\"%s\"];\n", indent, beg[i],
			end[i], ref[i]);
	}
	fprintf(fd, "}\n");
	fclose(fd);
	printf("%s", outname);
}

int main(int argc, char *argv[])
{
	echo = 0;
	silent = 1;
	init(argc, argv);
	parse();
	analysis();
	node_t *tree = conv_pgm_node(ast);
	visit(tree);
	writedot();
	system("dot -Tpdf viz.dot -o viz.pdf");
	// system("rm viz.dot");
	return 0;
}
