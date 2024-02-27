#ifndef _UTIL_H_
#define _UTIL_H_
#include "limits.h"
#include "common.h"
#include <stdio.h>
#include <string.h>

// common string buffer
extern char prtbuf[MAXSTRBUF];

// strcat + sprintf
#define appendf(s, fmt, args...)                                               \
	do {                                                                   \
		sprintf(prtbuf, fmt, ##args);                                  \
		strcat(s, prtbuf);                                             \
	} while (0)

void strcopy(char *d, char *s);
void chgsuf(char *str, char *to, char *from);
char *itoa(int num);
bool chkcmd(char *cmd);

// bitset constants
// bit shift
#define BITSHIFT 5
// elements of bit shift, which is 2^BITSHIFT
#define ELEMENTS (1 << BITSHIFT)
// array number counter
#define NBITARR (MAXSETBITS / ELEMENTS)

// unsigned 64 bit int
typedef unsigned int bits_t;
typedef char bin_t[ELEMENTS + 1];

//
//   HIGH                   LOW
//  index xxxxxxxxxxxxxxxxx
//        |---------||----|
//             |       |
//             |        `- offset in the bit (LSB BITSHIFT bits in index)
//             `---------- position in array (HSB (ELEMENTS-BITSHIFT) bits in index)
//
// offset of index(i)
#define OFF(i) (((bits_t)i) & (~((~0) << BITSHIFT)))
// position of index(i)
#define POS(i) ((((bits_t)i) & ((~0) << BITSHIFT)) >> BITSHIFT)

#define MASK(i) (1L << OFF(i))

void bconv(bin_t str, bits_t b);
void bset(bits_t bits[], int i);
void bclr(bits_t bits[], int i);
bool bget(bits_t bits[], int i);
void bclrall(bits_t bits[], int n);
void bsetall(bits_t bits[], int n);
bool bsame(bits_t a[], bits_t b[], int n);
void bdup(bits_t des[], bits_t src[], int n);
void bunion(bits_t r[], bits_t a[], bits_t b[], int n);
void bsub(bits_t r[], bits_t a[], bits_t b[], int n);

#endif /* End of _UTIL_H_ */
