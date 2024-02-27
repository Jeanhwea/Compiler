#include "common.h"
#include "global.h"
#include "limits.h"
#include "util.h"
#include <error.h>
#include <stdio.h>
#include <string.h>

// for appendf(...)
char prtbuf[MAXSTRBUF];

void strcopy(char *d, char *s)
{
	strncpy(d, s, MAXSTRLEN);
}

// change suffix: from => to, str
void chgsuf(char *str, char *to, char *from)
{
	char buf[MAXSTRBUF];
	char *pos;
	while ((pos = strstr(str, from)) != NULL) {
		// prepare prefix
		strncpy(buf, str, pos - str);
		buf[pos - str] = '\0';

		// append new suffix
		strcat(buf, to);

		// copy to dest str
		strcpy(str, buf);
	}
}

char numbuf[MAXSTRBUF];
char *itoa(int num)
{
	sprintf(numbuf, "%d", num);
	return numbuf;
}

bool chkcmd(char *cmd)
{
	char cmdbuf[MAXSTRBUF];
	sprintf(cmdbuf, "which %s", cmd);

	FILE *fp;
	fp = popen(cmdbuf, "r");
	if (fp == NULL) {
		giveup(ENOCMD, "command not found: %s", cmd);
	}

	char path[MAXSTRBUF];
	while (fgets(path, sizeof(path) - 1, fp) != NULL) {
		pclose(fp);
		return TRUE;
	}

	if (feof(fp)) {
		return FALSE;
	} else {
		return TRUE;
	}

	pclose(fp);

	return TRUE;
}

void convbin(bin_t bits, bits_t b)
{
	int i = ELEMENTBITS;
	bits[i--] = '\0';
	while (b > 0) {
		bits[i--] = (b & 0x1) ? '1' : '0';
		b >>= 1;
	}
	while (i >= 0) {
		bits[i--] = '0';
	}
}
