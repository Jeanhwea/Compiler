#ifndef _GLOBAL_H_
#define _GLOBAL_H_

enum phase_t { INIT, LEXICAL, SYNTAX, SEMANTIC, IR, CODE_GEN };

extern enum phase_t phase;

#endif /* End of _GLOBAL_H_ */
