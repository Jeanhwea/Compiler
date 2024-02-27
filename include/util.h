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
#define ELEMENTBITS 32
#define MAXSETNUM (MAXSETBITS / ELEMENTBITS)

// unsigned 64 bit int
typedef unsigned int bits_t;
typedef char bin_t[ELEMENTBITS + 1];

//
//   HIGH                   LOW
//  index xxxxxxxxxxxxxxxxx
//        |---------||----|
//             |       |
//             |        `- offset in the bit (LSB 6 bits in index)
//             `---------- position in array (HSB (ELEMENTBITS-6) bits in index)
//
#define BITSHIFT 6
#define OFF(i) (((bits_t)i) & (~((~0) << BITSHIFT)))
#define POS(i) ((((bits_t)i) & ((~0) << BITSHIFT)) >> BITSHIFT)

#define MASK(i) (1 << OFF(i))

void convbin(bin_t bits, bits_t b);
#endif /* End of _UTIL_H_ */
