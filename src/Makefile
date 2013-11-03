CC = gcc

CFLAGS = -g

OBJS = main.o util.o scan.o

compiler: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o compiler

main.o: main.c globals.h util.h scan.h
	$(CC) $(CFLAGS) -c main.c

util.o: util.c util.h globals.h
	$(CC) $(CFLAGS) -c util.c

scan.o: scan.c scan.h util.h globals.h
	$(CC) $(CFLAGS) -c scan.c

clean:
	-rm compiler
	-rm tm
	-rm $(OBJS)
