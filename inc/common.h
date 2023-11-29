#ifndef _COMMON_H_
#define _COMMON_H_

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

typedef int bool;

// Compiling Phase
typedef enum _phase_enum {
	/* 0 */ INIT,
	/* 1 */ LEXICAL,
	/* 2 */ SYNTAX,
	/* 3 */ SEMANTIC,
	/* 4 */ IR,
	/* 5 */ CODE_GEN
} phase_t;

#endif /* End of _COMMON_H_ */
