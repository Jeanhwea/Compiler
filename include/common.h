#ifndef _COMMON_H_
#define _COMMON_H_

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

// global defines
typedef int bool;
typedef enum _token_enum token_t;
typedef struct _pgm_node pgm_node_t;

////////////////////////////////////////////////////////////////////////////////
// Initialize struct, allocate memory
//     INITMEM(s: struct, v: variable, sturct pointer)
#define INITMEM(s, v)                                                          \
	do {                                                                   \
		v = (s *)malloc(sizeof(s));                                    \
		if (v == NULL) {                                               \
			panic("OUT_OF_MEMORY");                                \
		};                                                             \
		memset(v, 0, sizeof(s));                                       \
	} while (0)

// Compiling Phase
typedef enum _phase_enum {
	/* 0 */ INIT,
	/* 1 */ LEXICAL,
	/* 2 */ SYNTAX,
	/* 3 */ SEMANTIC,
	/* 4 */ IR,
	/* 5 */ CODE_GEN,
	/* 6 */ SUCCESS
} phase_t;

#endif /* End of _COMMON_H_ */
