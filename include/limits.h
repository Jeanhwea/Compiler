#ifndef _LIMITS_H_
#define _LIMITS_H_

// system constants
#define MAXSTRLEN 256
#define MAXSTRBUF 4096
#define MAXLINEBUF 4096
#define MAXTOKSIZE 256
#define MAXNODECHILD 128
#define MAXSYMENT 1024
#define MAXREGNAME 8
#define MAXFIELDLEN 64
#define MAXDATASEC 128
#define MAXTEXTSEC 4096
#define MAXBBINST 4096
#define MAXBBLINK 32
#define MAXDAGNODES 1024

// set constants
#define ELEMENTBITS 64
#define MAXSETBITS 1024
#define MAXSETNUM (MAXSETBITS / ELEMENTBITS)

//
//   HIGH                   LOW
//  index xxxxxxxxxxxxxxxxx
//        |---------||----|
//             |       |
//             |        `- offset       (LSB in index)
//             `---------- nth in array (HSB in index)
//
#define SHIFT 6
#define OFF(index) (index & (~((~0) << SHIFT)))
#define NTH(index) ((index & ((~0) << SHIFT)) >> SHIFT)

#endif /* End of _LIMITS_H_ */
