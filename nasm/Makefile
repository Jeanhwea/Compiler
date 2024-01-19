AS   := nasm
LD   := ld

SRCS := $(wildcard *.s)
RUNS := $(SRCS:%.s=%.run)

all: $(RUNS)

%.o: %.s
	$(AS) -f elf -o $@ $<

%.run: %.o
	$(LD) -m elf_i386 -o $@ $<

clean:
	-rm -f *.o *.run
