#include "optim.h"

int main(int argc, char *argv[])
{
	printf("char = %ld\n", sizeof(char));
	printf("int  = %ld\n", sizeof(int));
	printf("long = %ld\n", sizeof(long));
	printf("u64  = %ld\n", sizeof(u64));
	for (int i = 0; i < 500; i++) {
		printf("0x%x\tNTH=%d\tOFF=%d\n", i, NTH(i), OFF(i));
	}
	return 0;
}
