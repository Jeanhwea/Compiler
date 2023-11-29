#ifndef _GLOBAL_H_
#define _GLOBAL_H_

// compiler phase
typedef enum _phase_enum {
	/* 0 */ INIT,
	/* 1 */ LEXICAL,
	/* 2 */ SYNTAX,
	/* 3 */ SEMANTIC,
	/* 4 */ IR,
	/* 5 */ CODE_GEN
} phase_e;

extern phase_e phase;

#endif /* End of _GLOBAL_H_ */
