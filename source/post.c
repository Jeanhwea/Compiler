#include "post.h"
#include "common.h"
#include "global.h"
#include <stdio.h>

void post_nasm()
{
	char cmd[1024];
	sprintf(cmd, "nasm -f elf -o %s %s", PL0E_OBJECT, PL0E_ASSEM);
	errnum = system(cmd);
	chkerr("post_nasm fail and exit.");
	phase = LINK;
	msg("assemble object file %s\n", PL0E_OBJECT);
}

void post_link()
{
	char cmd[1024];
	sprintf(cmd, "ld -m elf_i386 -o %s %s", PL0E_TARGET, PL0E_OBJECT);
	errnum = system(cmd);
	chkerr("post_link fail and exit.");
	phase = SUCCESS;
	msg("link target file %s\n", PL0E_TARGET);
}
