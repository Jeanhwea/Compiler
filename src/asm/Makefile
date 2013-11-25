AS = nasm
ASFLAG = -g -f elf
LK = gcc
LFLAG = -g

all: nice sum

nice: nice.o
	$(LK) $(LFLAG) -o nice nice.o

nice.o: nice.asm io.asm
	$(AS) $(ASFLAG) nice.asm

sum: sum.o
	$(LK) $(LFLAG) -o sum sum.o

sum.o: sum.asm io.asm
	$(AS) $(ASFLAG) sum.asm

clean:
	rm nice.o nice sum.o sum
