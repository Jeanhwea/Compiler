CC = gcc
CFLAGS = -g -Wall

OBJS = main.o util.o scan.o error.o parse.o analyse.o \
       nspace.o symtab.o quad.o code.o

compiler: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o compiler

main.o: main.c global.h util.h parse.h analyse.h
	$(CC) $(CFLAGS) -c main.c

code.o: code.c global.h parse.h symtab.h quad.h code.h
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
