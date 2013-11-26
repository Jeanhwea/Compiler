r = DEBUG
CC = gcc
AS = nasm
ASFLAG = -g -f elf
LK = gcc
LFLAG = -g
ifeq ($r, )
CFLAGS =
else
CFLAGS = -g -Wall
endif

OBJS = main.o util.o scan.o error.o parse.o analyse.o \
       nspace.o symtab.o quad.o code.o asm.o elf.o

compiler: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o compiler

main.o: main.c global.h util.h parse.h analyse.h code.h elf.h
	$(CC) $(CFLAGS) -c main.c

elf.o: elf.c global.h parse.h symtab.h quad.h elf.h
	$(CC) $(CFLAGS) -c elf.c

asm.o: asm.c global.h parse.h symtab.h quad.h asm.h
	$(CC) $(CFLAGS) -c asm.c

code.o: code.c global.h util.h parse.h analyse.h \
	   symtab.h quad.h error.h nspace.h
	$(CC) $(CFLAGS) -c code.c

quad.o: quad.c global.h parse.h symtab.h quad.h
	$(CC) $(CFLAGS) -c quad.c

symtab.o: symtab.c global.h parse.h symtab.h nspace.h
	$(CC) $(CFLAGS) -c symtab.c

analyse.o: analyse.c global.h util.h parse.h analyse.h \
	   symtab.h quad.h error.h nspace.h
	$(CC) $(CFLAGS) -c analyse.c

parse.o: parse.c parse.h scan.h util.h global.h error.h
	$(CC) $(CFLAGS) -c parse.c

scan.o: scan.c scan.h util.h global.h error.h
	$(CC) $(CFLAGS) -c scan.c

error.o: error.c error.h global.h
	$(CC) $(CFLAGS) -c error.c

nspace.o: nspace.c nspace.h global.h parse.h
	$(CC) $(CFLAGS) -c nspace.c

util.o: util.c util.h global.h scan.h
	$(CC) $(CFLAGS) -c util.c

all: nice compiler

nice: nice.o
	$(LK) $(LFLAG) -o nice nice.o

nice.o: nice.asm asm/io.asm
	$(AS) $(ASFLAG) nice.asm

nice.asm: compiler example/untitled.pas
	./compiler example/untitled.pas > nice.asm 2> ./example/untitled.q

.PHONY: clean
clean:
	-rm $(OBJS) nice.o
