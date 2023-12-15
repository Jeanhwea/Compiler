#include "anlys.h"
#include "debug.h"
#include "global.h"
#include "ast.h"
#include "symtab.h"
#include "util.h"
#include "syntax.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXNODES 1024
#define MAXEDGES 1024

static int nedges = 0;
static char *label[MAXNODES];
static node_t *nodes[MAXNODES];
static int beg[MAXEDGES];
static int end[MAXEDGES];
static char *ref[MAXEDGES];

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

	label[node->id] = dupstr(buf);
	nodes[node->id] = node;
	for (int i = 0; i < node->total; ++i) {
		node_t *child = node->childs[i];
		if (!child) {
			continue;
		}

		beg[nedges] = node->id;
		end[nedges] = child->id;
		ref[nedges] = node->refs[i];
		++nedges;
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
	for (int i = 0; i < MAXNODES; ++i) {
		if (label[i]) {
			char *shape = "oval";
			if (!strncmp(nodes[i]->name, "IDENT", 5)) {
				shape = "box";
			}
			fprintf(fd,
				"%sn%03d[label=\"#%d %s\", shape=\"%s\"];\n",
				indent, i, i, label[i], shape);
		}
	}
	for (int i = 0; i < nedges; ++i) {
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
	node_t *tree = conv_ast();
	visit(tree);
	writedot();
	system("dot -Tpdf viz.dot -o viz.pdf");
	// system("rm viz.dot");
	return 0;
}
