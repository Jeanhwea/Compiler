#include "anlys.h"
#include "common.h"
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

bool opt_show_extra = FALSE;
bool opt_show_symbol = FALSE;

#define MAXNODES 1024
#define MAXEDGES 1024

// nodes
static int nedges = 0;
static node_t *nodes[MAXNODES];
// edges: beg -> end; ptr: pointer name
static int beg[MAXEDGES];
static int end[MAXEDGES];
static char ptrs[MAXEDGES][MAXSTRLEN];

static char buf[MAXSTRBUF];
void visit(node_t *node)
{
	nodes[node->seq] = node;
	int i;
	for (i = 0; i < node->nchild; ++i) {
		node_t *child = node->childs[i];
		beg[nedges] = node->seq;
		end[nedges] = child->seq;
		strcopy(ptrs[nedges], node->chdptrs[i]);
		++nedges;
	}

	for (i = 0; i < node->nchild; ++i) {
		node_t *child = node->childs[i];
		visit(child);
	}
}

char *outname = "viz.dot";
FILE *fd = NULL;
char *indent = "  ";

void drawnode(node_t *node)
{
	char *shape = "oval";
	if (!strcmp(node->name, "IDENT")) {
		shape = "box";
	}

	char label[MAXSTRBUF];
	sprintf(label, "%s", node->name);

	if (!opt_show_extra) {
		goto makenode;
	}
	sprintf(label, "%s\\nnid=%d", node->nid);

	if (strlen(node->extra) > 0) {
		appendf(label, " [%s]", node->extra);
	}

	if (!node->idp) {
		goto makenode;
	}
	ident_node_t *idp = node->idp;
	appendf(label, "\\nname=%s\\nkind=%d", idp->name, idp->kind);

	if (opt_show_symbol && !idp->symbol) {
		goto makenode;
	}
	syment_t *symbol = idp->symbol;
	appendf(label, "\\nlabel=%s", symbol->label);
	appendf(label, "\\ntype=%d", symbol->type);
	appendf(label, "\\ncate=%d", symbol->cate);

makenode:
	fprintf(fd, "%sn%03d[label=\"#%d %s\", shape=\"%s\"];\n", indent,
		node->seq, node->seq, label, shape);
}

void drawedge(int i)
{
	fprintf(fd, "%sn%03d -> n%03d[label=\"%s\"];\n", indent, beg[i], end[i],
		ptrs[i]);
}

void draw()
{
	fd = fopen(outname, "w");
	if (fd == NULL) {
		panic("FAIL_TO_OPEN_FILE");
	}

	fprintf(fd, "digraph viz {\n");
	// fprintf(fd, "%srankdir=LR;\n", indent);

	int i;
	for (i = 0; i < MAXNODES; ++i) {
		if (!nodes[i]) {
			continue;
		}
		drawnode(nodes[i]);
	}

	for (i = 0; i < nedges; ++i) {
		drawedge(i);
	}

	fprintf(fd, "}\n");
	fclose(fd);

	printf("%s", outname);
}

void initopt(int argc, char *argv[])
{
	int i;
	for (i = 0; i < argc; ++i) {
		if (!strcmp("-x", argv[i])) {
			opt_show_extra = TRUE;
		}
		if (!strcmp("-xx", argv[i])) {
			opt_show_extra = TRUE;
			opt_show_symbol = TRUE;
		}
	}
}

int main(int argc, char *argv[])
{
	echo = 0;
	silent = 1;
	init(argc, argv);
	initopt(argc, argv);
	parse();
	analysis();
	node_t *tree = conv_pgm_node(pgm);

	visit(tree);

	draw();
	system("dot -Tpdf viz.dot -o viz.pdf");
	// system("rm viz.dot");
	return 0;
}
