#ifndef _BITSET_H_
#define _BITSET_H_
#include "limits.h"

// set constants
#define ELEMENTBITS 64
#define MAXSETNUM (MAXSETBITS / ELEMENTBITS)

// unsigned 64 bit int
typedef unsigned long long bits_t;

//
//   HIGH                   LOW
//  index xxxxxxxxxxxxxxxxx
//        |---------||----|
//             |       |
//             |        `- offset       (LSB in index)
//             `---------- nth in array (HSB in index)
//
#define BITSHIFT 6
#define OFF(index) (index & (~((~0) << BITSHIFT)))
#define NTH(index) ((index & ((~0) << BITSHIFT)) >> BITSHIFT)

#endif /* End of _BITSET_H_ */
