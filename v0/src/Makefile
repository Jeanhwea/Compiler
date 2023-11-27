CC = gcc
CFLAGS = -g
AS = nasm
ASFLAG = -g -f elf

SRCS := $(wildcard *.c)
OBJS := $(SRCS:%.c=%.o)

compiler: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o compiler

%.o: %.c %.h global.h
	$(CC) $(CFLAGS) $< -o $@

.SUFFIXES:
.SUFFIXES: .o .c

.PHONY: clean
clean:
	-rm $(OBJS)
