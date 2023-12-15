#include "global.h"
#include "ast.h"
#include "util.h"
#include "syntax.h"
#include <stdio.h>
#include <string.h>

int indent = 0;

void prtnode(node_t *node)
{
	indent++;
	for (int i = 1; i < indent; ++i) {
		msg(" ");
	}

	if (!node) {
		msg("(nil)");
		goto postwork;
	}

	char buf[1024];
	sprintf(buf, "#%03d %s cate=%d", node->id, node->name, node->cate);

	if (node->idp) {
		ident_node_t *idp = node->idp;
		appendf(buf, ": name=%s", idp->name);
	}
	msg("%s\n", buf);

	for (int i = 0; i < node->total; ++i) {
		prtnode(node->childs[i]);
	}

postwork:
	indent--;
}

int main(int argc, char *argv[])
{
	init(argc, argv);
	parse();
	node_t *tree = conv_ast();
	prtnode(tree);
	return 0;
}
