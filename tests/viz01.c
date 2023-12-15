#include "debug.h"
#include "global.h"
#include "ast.h"
#include "util.h"
#include "syntax.h"
#include <stdio.h>
#include <string.h>

#define MAXNODES 1024
#define MAXEDGES 1024
static int nedges = 0;
static char *nodes[MAXNODES];
static int beg[MAXEDGES];
static int end[MAXEDGES];

static char buf[1024];

void visit(node_t *node)
{
	nevernil(node);

	sprintf(buf, "%s/%d", node->name, node->type);

	if (node->idp) {
		ident_node_t *idp = node->idp;
		char append[512];
		sprintf(append, "\\nname=%s", idp->name);
		strcat(buf, append);
	}

	nodes[node->id] = dupstr(buf);
	for (int i = 0; i < node->nchild; ++i) {
		node_t *child = node->childs[i];
		if (!child) {
			continue;
		}

		beg[nedges] = node->id;
		end[nedges] = child->id;
		++nedges;
		visit(child);
	}
}

void makedot()
{
	char *outname = "viz.dot";
	FILE *fd = fopen(outname, "w");
	fprintf(fd, "digraph %s {}", PL0C_PROGNAME);
	for (int i = 0; i < MAXNODES; ++i) {
		if (nodes[i]) {
			printf(fd, "n%03d %s\n", i, nodes[i]);
		}
	}
	for (int i = 0; i < nedges; ++i) {
		printf(fd, "%d -> %d\n", beg[i], end[i]);
	}
	fclose(fd);
}

int main(int argc, char *argv[])
{
	silent = 1;
	init(argc, argv);
	parse();
	node_t *tree = conv_ast();
	visit(tree);
	makedot(tree);
	return 0;
}
