#include "global.h"
#include "ast.h"
#include "util.h"
#include "syntax.h"
#include <stdio.h>
#include <string.h>

#define MAXNODES 1024
#define MAXEDGES 1024
int nedges = 0;
char *nodes[MAXNODES];
int beg[MAXEDGES];
int end[MAXEDGES];

int level = 0;

void dispnode(node_t *node)
{
	level++;
	for (int i = 1; i < level; ++i) {
		msg(" ");
	}

	if (!node) {
		msg("(nil)");
		goto postwork;
	}

	char buf[1024];
	sprintf(buf, "%s %d", node->name, node->type);

	if (node->idp) {
		ident_node_t *idp = node->idp;
		char append[512];
		sprintf(append, " [name=%s]", idp->name);
		strcat(buf, append);
	}
	msg("%s\n", buf);

	nodes[node->id] = dupstr(buf);
	for (int i = 0; i < node->total; ++i) {
		node_t *child = node->childs[i];
		if (!child) {
			continue;
		}
		beg[nedges] = node->id;
		end[nedges] = child->id;
		++nedges;
		dispnode(child);
	}

postwork:
	level--;
}

void makedot()
{
	for (int i = 0; i < MAXNODES; ++i) {
		if (nodes[i]) {
			printf("n%03d %s\n", i, nodes[i]);
		}
	}
	for (int i = 0; i < nedges; ++i) {
		printf("%d -> %d\n", beg[i], end[i]);
	}
}

int main(int argc, char *argv[])
{
	init(argc, argv);
	parse();
	node_t *tree = conv_ast();
	msg("tree = %p\n", tree);

	dispnode(tree);
	makedot(tree);
	return 0;
}
