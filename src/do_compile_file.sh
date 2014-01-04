#!/bin/bash
echo "./compiler $1.txt && \\"
echo "nasm -g -f elf $1.asm -o $1.o && \\"
echo "gcc -g $1.o -o $1"
echo 
./compiler $1.txt && \
nasm -g -f elf $1.asm -o $1.o && \
gcc -g $1.o -o $1
