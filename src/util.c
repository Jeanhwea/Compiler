/**
 * File: util.c
 * Date: Nov 4, 2013
 * Author: Jeanhwea
 */

#include "global.h"
#include "scan.h"
#include "parse.h"
#include "util.h"

char *copyString(char *s)
{
	int n;
	char *t;
	if (s == NULL) {
		return NULL;
	}
	n = strlen(s) + 1;
	t = (char *) malloc(n * sizeof(char));
	if (t == NULL) {
		fprintf(errlist, "Out of memory error at line %d\n", lineno);
	} else {
		strcpy(t, s);
	}
	return t;
}

static int indentno = 0;
static void Indent(void)
{
	int i;
	for (i = 0; i < indentno; i++) {
		if (ShowAST)
			fprintf(astlist, "\t");
	}
}

void headPr(char *cont)
{
	Indent();
	indentno += 1;
	if (ShowAST)
		fprintf(astlist, "<%s>\n", cont);
}

void innerPr(int n, ...)
{
	int i;
	char *chp;
	va_list vl;
	va_start(vl, n);
	for (i = 0; i < n; i++) {
		chp = va_arg(vl, char *);
		if (ShowAST)
			fprintf(astlist, "%s", chp);
	}
	va_end(vl);
}

void innerIdnPr(int n, ...)
{
	int i;
	char *chp;
	va_list vl;
	Indent();
	va_start(vl, n);
	for (i = 0; i < n; i++) {
		chp = va_arg(vl, char *);
		if (ShowAST)
			fprintf(astlist, "%s", chp);
	}
	va_end(vl);
}

void innerlnPr(int n, ...)
{
	int i;
	char *chp;
	va_list vl;
	va_start(vl, n);
	for (i = 0; i < n; i++) {
		chp = va_arg(vl, char *);
		if (ShowAST)
			fprintf(astlist, "%s", chp);
	}
	va_end(vl);
	if (ShowAST) {
		fprintf(astlist, "\n");
	}
}

void innerIdnlnPr(int n, ...)
{
	int i;
	char *chp;
	va_list vl;
	Indent();
	va_start(vl, n);
	for (i = 0; i < n; i++) {
		chp = va_arg(vl, char *);
		if (ShowAST)
			fprintf(astlist, "%s", chp);
	}
	va_end(vl);
	if (ShowAST) {
		fprintf(astlist, "\n");
	}
}

void innerIntPr(int val)
{
	if (ShowAST)
		fprintf(astlist, "%d\n", val);
}

void innerCharPr(char val)
{
	if (ShowAST)
		fprintf(astlist, "%c\n", val);
}

void tailPr(char *cont)
{
	indentno -= 1;
	Indent();
	if (ShowAST)
		fprintf(astlist, "</%s>\n", cont);
}

void ioasm(void)
{
	fprintf(asmlist, "SECTION .DATA\n");
	fprintf(asmlist, "\tfmt_int_r:  DB \"%%d\", 0\n");
	fprintf(asmlist, "\tfmt_int_w:  DB \"%%d\", 10, 0\n");
	fprintf(asmlist, "\tfmt_char_r: DB 10, \"%%c\", 0\n");
	fprintf(asmlist, "\tfmt_char_w: DB \"%%c\", 10, 0\n");
	fprintf(asmlist, "\tfmt_string: DB \"%%s\", 0\n\n");

	fprintf(asmlist, "SECTION .TEXT\n");
	fprintf(asmlist, "\tEXTERN\tscanf, printf\n");
	fprintf(asmlist, "\tGLOBAL\tscan_int, scan_char\n");
	fprintf(asmlist, "\tGLOBAL\tprint_int, print_char, print_string\n\n");

	fprintf(asmlist, "scan_int:\n");
	fprintf(asmlist, "\tpush\tebp\n");
	fprintf(asmlist, "\tmov\tebp, esp\n");
	fprintf(asmlist, "\tsub\tesp, 0x4\n");
	fprintf(asmlist, "\tlea\teax, [ebp - 4]\n");
	fprintf(asmlist, "\tpush\teax\n");
	fprintf(asmlist, "\tpush\tfmt_int_r\n");
	fprintf(asmlist, "\tcall\tscanf\n");
	fprintf(asmlist, "\tpop\tecx\n");
	fprintf(asmlist, "\tpop\tecx\n");
	fprintf(asmlist, "\tmov\teax, [ebp - 4]\n");
	fprintf(asmlist, "\tmov\tesp, ebp\n");
	fprintf(asmlist, "\tpop\tebp\n");
	fprintf(asmlist, "\tret\n\n");

	fprintf(asmlist, "scan_char:\n");
	fprintf(asmlist, "\tpush\tebp\n");
	fprintf(asmlist, "\tmov\tebp, esp\n");
	fprintf(asmlist, "\tsub\tesp, 0x4\n");
	fprintf(asmlist, "\tlea\teax, [ebp - 4]\n");
	fprintf(asmlist, "\tpush\teax\n");
	fprintf(asmlist, "\tpush\tfmt_char_r\n");
	fprintf(asmlist, "\tcall\tscanf\n");
	fprintf(asmlist, "\tpop\tecx\n");
	fprintf(asmlist, "\tpop\tecx\n");
	fprintf(asmlist, "\tmov\teax, [ebp - 4]\n");
	fprintf(asmlist, "\tleave\n");
	fprintf(asmlist, "\tret\n\n");

	fprintf(asmlist, "print_int:\n");
	fprintf(asmlist, "\tpush\tebp\n");
	fprintf(asmlist, "\tmov\tebp, esp\n");
	fprintf(asmlist, "\tpush\teax\n");
	fprintf(asmlist, "\tpush\tfmt_int_w\n");
	fprintf(asmlist, "\tcall\tprintf\n");
	fprintf(asmlist, "\tpop\tecx\n");
	fprintf(asmlist, "\tpop\tecx\n");
	fprintf(asmlist, "\txor\teax, eax\n");
	fprintf(asmlist, "\tleave\n");
	fprintf(asmlist, "\tret\n\n");

	fprintf(asmlist, "print_char:\n");
	fprintf(asmlist, "\tpush\tebp\n");
	fprintf(asmlist, "\tmov\tebp, esp\n");
	fprintf(asmlist, "\tpush\teax\n");
	fprintf(asmlist, "\tpush\tfmt_char_w\n");
	fprintf(asmlist, "\tcall\tprintf\n");
	fprintf(asmlist, "\tpop\tecx\n");
	fprintf(asmlist, "\tpop\tecx\n");
	fprintf(asmlist, "\txor\teax, eax\n");
	fprintf(asmlist, "\tleave\n");
	fprintf(asmlist, "\tret\n\n");

	fprintf(asmlist, "print_string:\n");
	fprintf(asmlist, "\tpush\tebp\n");
	fprintf(asmlist, "\tmov\tebp, esp\n");
	fprintf(asmlist, "\tpush\teax\n");
	fprintf(asmlist, "\tpush\tfmt_string\n");
	fprintf(asmlist, "\tcall\tprintf\n");
	fprintf(asmlist, "\tpop\tecx\n");
	fprintf(asmlist, "\tpop\tecx\n");
	fprintf(asmlist, "\txor\teax, eax\n");
	fprintf(asmlist, "\tleave\n");
	fprintf(asmlist, "\tret\n\n");
}
