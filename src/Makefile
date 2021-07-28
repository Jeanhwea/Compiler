CC = gcc
AS = nasm
ASFLAG = -g -f elf
CFLAGS = -g

SRCS := $(wildcard *.c)
OBJS := $(SRCS:%.c=%.o)

compiler: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o compiler

%.o: %.c %.h
	$(CC) $(CFLAGS) $< -o $@

.SUFFIXES:
.SUFFIXES: .o .c

.PHONY: clean
clean:
	-rm $(OBJS)
