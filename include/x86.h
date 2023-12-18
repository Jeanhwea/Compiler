#ifndef _X86_H_
#define _X86_H_

// register
typedef struct _reg_struct {
	char name[4];
	int refcnt;
} reg_t;

reg_t *getreg();
void *putreg(reg_t *r);

// asm instructions
#define ALIGN 4
#define OFFSET(e) (ALIGN * e->off)
#endif /* End of _X86_H_ */
