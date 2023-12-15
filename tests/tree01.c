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
	if (node->idp) {
		ident_node_t *idp;
		msg("%s [%s]\n", node->name, idp->name);
	} else {
		msg("%s\n", node->name);
	}
	for (int i = 0; i < node->nchild; ++i) {
		dispnode(node->childs[i]);
	}
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
