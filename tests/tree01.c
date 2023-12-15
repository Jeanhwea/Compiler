#include "global.h"
#include "ast.h"
#include "syntax.h"

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

	if (node->idp) {
		ident_node_t *idp = node->idp;
		msg("%s #%d %d [name=%s, line=%d]\n", node->name, node->id,
		    node->type, idp->name, idp->line);
	} else {
		msg("%s #%d %d\n", node->name, node->id, node->type);
	}
	for (int i = 0; i < node->nchild; ++i) {
		dispnode(node->childs[i]);
	}

postwork:
	level--;
}

int main(int argc, char *argv[])
{
	init(argc, argv);
	parse();
	node_t *tree = conv_ast();
	msg("tree = %p\n", tree);

	dispnode(tree);
	return 0;
}
