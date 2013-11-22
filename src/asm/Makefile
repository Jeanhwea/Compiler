AS = nasm
ASFLAG = -g -f elf
LK = gcc
LFLAG = -g

nice: nice.o
	$(LK) $(LFLAG) -o nice nice.o

nice.o: nice.asm io.asm
	$(AS) $(ASFLAG) nice.asm

clean:
	rm nice.o nice
