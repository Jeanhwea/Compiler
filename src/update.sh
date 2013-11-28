#!/bin/bash
for (( i = 1; i < 13; i++ )); do
	./compiler test/t${i}.pas > test/${i}.asm 2> test/${i}.q
	nasm -g -f elf test/${i}.asm -o test/${i}.o
	gcc -g test/${i}.o -o test/run${i}
done
