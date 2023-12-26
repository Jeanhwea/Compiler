#include "global.h"
#include "anlys.h"
#include "conv.h"
#include "limits.h"
#include "parse.h"
#include "util.h"
#include "syntax.h"

int indent = 0;

void prtnode(node_t *node)
{
	indent++;
	int i;
	for (i = 1; i < indent; ++i) {
		msg(" ");
	}

	if (!node) {
		msg("(nil)");
		goto postwork;
	}

	char buf[MAXSTRBUF];
	sprintf(buf, "#%03d %s", node->id, node->name);

	if (strlen(node->extra)) {
		appendf(buf, " [%s]", node->extra);
	}

	if (node->idp) {
		ident_node_t *idp = node->idp;
		appendf(buf, " name=%s kind=%d", idp->name, idp->kind);
		syment_t *sym = idp->symbol;
		if (sym) {
			appendf(buf, " type=%d cate=%d label=%s", sym->type,
				sym->cate, sym->label);
		}
	}
	msg("%s\n", buf);

	for (i = 0; i < node->total; ++i) {
		prtnode(node->childs[i]);
	}

postwork:
	indent--;
}

int main(int argc, char *argv[])
{
	init(argc, argv);
	parse();
	analysis();
	node_t *tree = conv_pgm_node(pgm);
	prtnode(tree);
	return 0;
}
