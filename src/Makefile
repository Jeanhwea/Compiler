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
       nspace.o symtab.o quad.o code.o asm.o elf.o \
       dag.o fgraph.o bblock.o

compiler: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o compiler

main.o: main.c global.h util.h parse.h analyse.h code.h elf.h \
	symtab.h quad.h dag.h bblock.h fgraph.h
	$(CC) $(CFLAGS) -c main.c

fgraph.o: fgraph.c global.h parse.h symtab.h quad.h dag.h bblock.h \
	fgraph.h
	$(CC) $(CFLAGS) -c fgraph.c

dag.o: dag.c global.h parse.h symtab.h quad.h dag.h bblock.h
	$(CC) $(CFLAGS) -c dag.c

bblock.o: bblock.c global.h parse.h symtab.h quad.h dag.h bblock.h
	$(CC) $(CFLAGS) -c bblock.c

asm.o: asm.c global.h parse.h symtab.h quad.h asm.h
	$(CC) $(CFLAGS) -c asm.c

elf.o: elf.c global.h parse.h symtab.h quad.h elf.h
	$(CC) $(CFLAGS) -c elf.c

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

.PHONY: clean
clean:
	-rm $(OBJS)
