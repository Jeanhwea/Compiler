#!/bin/bash
./compiler test.pas && \
nasm -g -f elf test.asm -o test.o && \
gcc -g test.o -o test
