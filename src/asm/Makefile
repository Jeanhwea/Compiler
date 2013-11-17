AS = nasm
ASFLAG = -g -f elf
LK = gcc
LFLAG = -g

all: nice ch

ch: ch.o
	$(LK) $(LFLAG) -o ch ch.o

ch.o: ch.asm
	$(AS) $(ASFLAG) ch.asm

nice: nice.o
	$(LK) $(LFLAG) -o nice nice.o

nice.o: nice.asm
	$(AS) $(ASFLAG) nice.asm

clean:
	rm *.o
