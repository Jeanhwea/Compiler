#include "post.h"
#include "global.h"
#include <stdio.h>

void post_nasm()
{
	char cmd[1024];
	sprintf(cmd, "nasm -f elf -o %s %s", PL0C_OBJECT, PL0C_ASSEM);
	msg("%s\n", cmd);
	system(cmd);
}

void post_link()
{
	char cmd[1024];
	sprintf(cmd, "ld -m elf_i386 -o %s %s", PL0C_TARGET, PL0C_OBJECT);
	msg("%s\n", cmd);
	system(cmd);
}
