#!/bin/bash
for (( i = 1; i < 13; i++ )); do
	echo "compiling t$i.pas ~>"
	./compiler t${i}.pas
	nasm -g -f elf t${i}.asm -o t${i}.o
	gcc -g t${i}.o -o run${i}
done