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

// convert bit to char array
void bconv(bin_t str, bits_t b)
{
	int i = BITSIZE;
	str[i--] = '\0';
	while (b > 0) {
		str[i--] = (b & 0x1) ? '1' : '0';
		b >>= 1;
	}
	while (i >= 0) {
		str[i--] = '0';
	}
}

// set bit
void bset(bits_t bits[], int i)
{
	bits[POS(i)] |= MASK(i);
}

// clear bit
void bclr(bits_t bits[], int i)
{
	bits[POS(i)] &= ~(MASK(i));
}

// get bit
bool bget(bits_t bits[], int i)
{
	return bits[POS(i)] & MASK(i) ? TRUE : FALSE;
}

// clear all bits
void bclrall(bits_t bits[], int n)
{
	int i;
	for (i = 0; i < n; ++i) {
		bits[i] &= 0;
	}
}

// set all bits
void bsetall(bits_t bits[], int n)
{
	int i;
	for (i = 0; i < n; ++i) {
		bits[i] |= ~0;
	}
}

// check if a[] and b[] is same
bool bsame(bits_t a[], bits_t b[], int n)
{
	int i;
	for (i = 0; i < n; ++i) {
		if (a[i] ^ b[i]) {
			return FALSE;
		}
	}
	return TRUE;
}

// duplicate set
void bdup(bits_t des[], bits_t src[], int n)
{
	int i;
	for (i = 0; i < n; ++i) {
		des[i] = src[i];
	}
}

// bits union
void bunion(bits_t r[], bits_t a[], bits_t b[], int n)
{
	int i;
	for (i = 0; i < n; ++i) {
		r[i] = a[i] | b[i];
	}
}

// bits substract
void bsub(bits_t r[], bits_t a[], bits_t b[], int n)
{
	int i;
	for (i = 0; i < n; ++i) {
		r[i] = a[i] & (~b[i]);
	}
}
