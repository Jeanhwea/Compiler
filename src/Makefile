CC = gcc

CFLAGS = -g

OBJS = main.o util.o scan.o error.o parse.o analyse.o

compiler: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o compiler

main.o: main.c global.h util.h scan.h parse.h
	$(CC) $(CFLAGS) -c main.c

analyse.o: analyse.c global.h util.h scan.h parse.h analyse.h
	$(CC) $(CFLAGS) -c analyse.c

parse.o: parse.c parse.h scan.h util.h global.h error.h
	$(CC) $(CFLAGS) -c parse.c

scan.o: scan.c scan.h util.h global.h error.h
	$(CC) $(CFLAGS) -c scan.c

error.o: error.c error.h
	$(CC) $(CFLAGS) -c error.c

util.o: util.c util.h global.h
	$(CC) $(CFLAGS) -c util.c

.PHONY: clean
clean:
	-rm compiler
	-rm $(OBJS)
