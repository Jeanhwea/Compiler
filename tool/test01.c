#include "util.h"
#include "optim.h"

int main(int argc, char *argv[])
{
	// printf("char   = %ld\n", sizeof(char));
	// printf("int    = %ld\n", sizeof(int));
	// printf("long   = %ld\n", sizeof(long));
	// printf("bits_t = %ld\n", sizeof(bits_t));
	for (int i = 0; i < 500; i++) {
		bin_t buf;
		convbin(buf, MASK(i));
		printf("0x%x\tposition=%d\toffset=%d\tmask=0b%s\n", i, POS(i),
		       OFF(i), buf);
	}

	return 0;
}
